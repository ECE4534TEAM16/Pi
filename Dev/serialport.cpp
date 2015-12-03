#include "serialport.h"

SerialPort::SerialPort()
{
    mapperFinished = false;
    mapper_serial_number = "A702ZKQU";
    bool mapper_is_available = false;
    bool user_is_available = false;
    QString mapper_port_name;
    QString user_port_name;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
            if(serialPortInfo.serialNumber() == mapper_serial_number)
            {
                mapper_is_available = true; //    mapper is available on this port
                mapper_port_name = serialPortInfo.portName();
            }
            if(serialPortInfo.serialNumber() == user_serial_number)
            {
                user_is_available = true; //    user is available on this port
                user_port_name = serialPortInfo.portName();
            }

    }

    /*
     *  Open and configure the ports if available
     */
    if(mapper_is_available)
    {
        qDebug() << "Found the mapper port...";
        mapper->setPortName(mapper_uno_port_name);
        mapper->open(QSerialPort::ReadWrite);
        mapper->setBaudRate(QSerialPort::Baud57600);
        mapper->setDataBits(QSerialPort::Data8);
        mapper->setFlowControl(QSerialPort::NoFlowControl);
        mapper->setParity(QSerialPort::NoParity);
        mapper->setStopBits(QSerialPort::OneStop);
        QObject::connect(mapper, SIGNAL(readyRead()), this, SLOT(readMapperSerial()));
    }
    if(user_is_available)
    {
        qDebug() << "Found the mapper port...";
        user->setPortName(user_uno_port_name);
        user->open(QSerialPort::ReadWrite);
        user->setBaudRate(QSerialPort::Baud57600);
        user->setDataBits(QSerialPort::Data8);
        user->setFlowControl(QSerialPort::NoFlowControl);
        user->setParity(QSerialPort::NoParity);
        user->setStopBits(QSerialPort::OneStop);
        QObject::connect(user, SIGNAL(readyRead()), this, SLOT(readUserSerial()));
    }

    QObject::connect(this, startMapper(), this, sendMapperStart());
    QObject::connect(this, startUser(), this, sendUserStart());


}



QStringList SerialPort::readline(QString filename)
{
    QFile file;
    file.setFileName(filename);
    if(!file.exists())
    {
        std::string str = filename.toStdString();
        fprintf(stderr, "The file %s does not exist\n", str.c_str());
        exit(EXIT_FAILURE);
    }
    int size;
    QString line;
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    int linenum = 0;
    while(!in.atEnd())
    {
        if(line.isEmpty())
        {
            line = in.readLine();
            linenum++;
        }
        else
        {
            line.append(in.readLine());
            linenum++;
        }
        size = line.size();
        if(size == 0)
        {}
        else
        {
            size = size-1;
            if(size == 0 && line.data()[size] == '\\') //backslash character as last line
            {
                std::string str = filename.toStdString();
                fprintf(stderr, "In file %s, line #%i consists of only a \\ character.  Ignoring this line \n", str.c_str(), linenum);
                line.clear();
            }
            else
            {
                list.append(line);
                line.clear();
            }
        }

    }
    file.close();
    return list;
}

void SerialPort::sendMapperStartSignal()
{
    emit startMapper();
}

void SerialPort::sendUserStartSignal()
{
    emit startUser();
}

QString SerialPort::readMapperSerial()
{
    qDebug() << "in read serial";
    QByteArray temp;
    temp = mapper->readAll();
    mapper_serialData.append(temp);
    qDebug() << mapper_serialData;

    if(mapper_serialData.at(0) == 'E') //end
    {
        list.append(mapper_serialData);


    }
    else if(mapper_serialData.contains("!")) //error or warning somewhere
    {
        if(mapper_serialData.contains(".")) //complete error has been recieved
        {
            int start;
            int end;
            QString tempdat;
            for(int j = 0; j < mapper_serialData.length(); j++)
            {
                if(mapper_serialData.at(j) == '!') // beggingin of error message
                {
                    start = j;
                }
                if(mapper_serialData.at(j) == '.') // beggingin of error message
                {
                    end = j;
                }
            }
            int index = start;
            for(start; start < end; start++)
            {
                tempdat.append(mapper_serialData.at(index));
                mapper_serialData.remove(index,1);
            }
            list.append(tempdat);
        }
    }
    else if(mapper_serialData.length() >= 5) //a packet of data has been sent and is ready to be
    {
        QString dat;
        for(int i = 0; i < 5; i++)
        {
            dat.append(mapper_serialData.at(0));
            mapper_serialData.remove(0,1);
        }
        list.append(dat);
    }
}

void SerialPort::sendMapperStart() //send start signal to mapper
{
        const char* dat = "S";
        mapper->write(dat, 1);
}

void SerialPort::sendUserStart()
{
        const char* dat = "S";
        user->write(dat, 1);
}

void SerialPort::sendUserSerial()
{

}

void SerialPort::readUserSerial()
{

}




