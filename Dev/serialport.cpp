#include "serialport.h"
#include <string>

SerialPort::SerialPort()
{
    count = 0;

    mapperFinished = false;
//    mapper_serial_number = "A702ZK6O";    //proper
//    user_serial_number = "AD02FKX4";
    mapper_serial_number = "AD02FKX4";  //wrong serial numbers for wiflys, used to test user comms with mapper wiflys
    user_serial_number = "A702ZK6O";
    mapper = new QSerialPort(this);
    user = new QSerialPort(this);
    bool mapper_is_available = false;
    bool user_is_available = false;
    QString mapper_port_name;
    QString user_port_name;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
            if(serialPortInfo.serialNumber() == mapper_serial_number)
            {
                mapper_is_available = true; //    mapper is available on this port
                qDebug() << "mapper is available";
                mapper_port_name = serialPortInfo.portName();
                qDebug() << "port name has been set to: " << mapper_port_name;
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
        mapper->setPortName(mapper_port_name);
        if(!mapper->open(QSerialPort::ReadWrite))
            qDebug() << mapper->errorString();
        else
        {
            mapper->setBaudRate(QSerialPort::Baud57600);
            mapper->setDataBits(QSerialPort::Data8);
            mapper->setFlowControl(QSerialPort::NoFlowControl);
            mapper->setParity(QSerialPort::NoParity);
            mapper->setStopBits(QSerialPort::OneStop);
            mapper->write("ok*");
            connect(mapper, SIGNAL(readyRead()), this, SLOT(readMapperSerial()));
        }
    }
    if(user_is_available)
    {
        qDebug() << "Found the user port...";
        user->setPortName(user_port_name);
        if(!user->open(QSerialPort::ReadWrite))
            qDebug() << user->errorString();
        else
        {
            user->setBaudRate(QSerialPort::Baud57600);
            user->setDataBits(QSerialPort::Data8);
            user->setFlowControl(QSerialPort::NoFlowControl);
            user->setParity(QSerialPort::NoParity);
            user->setStopBits(QSerialPort::OneStop);
            connect(user, SIGNAL(readyRead()), this, SLOT(readUserSerial()));
        }
    }

    qDebug() << "connecting start mapper and user signals";
    connect(this, SIGNAL(startMapper()), this, SLOT(sendMapperStart()));
    connect(this, SIGNAL(startUser()), this, SLOT(sendUserStart()));
    connect(this, SIGNAL(sendUserPath()), this, SLOT(sendUserSerial()));

    if(mapper->isOpen())
    {
        qDebug() << "mapper is open";
    }
}

SerialPort::~SerialPort()
{
    qDebug() << "serialport destructor called";
    if(mapper->isOpen())
    {
        mapper->close(); //    Close the serial port if it's open.
        qDebug() << "mapper serial port closed";
    }
    if(user->isOpen())
    {
        user->close(); //    Close the serial port if it's open.
        qDebug() << "user serial port closed";
    }
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

void SerialPort::sendPath(QStringList path)
{
    pathDat = path;
    qDebug() << pathDat;
    emit sendUserPath();
}

QStringList SerialPort::returnList()
{
    return list;
}

void SerialPort::readMapperSerial()
{
    qDebug() << "in mapper read serial";

/*                 Serial Communiction In                           */

    mapper_serialData.clear();
    mapper_serialData = mapper->readAll();
    qDebug() << "mapper data read in from serial port";
    QString tempstr = QString::fromStdString(mapper_serialData.toStdString());
    qDebug() << "tempstr created";
    QRegExp re("[A-Za-z0-9]");
    tempstr.remove(QChar(QChar::Null));
    qDebug() << tempstr;
    if(tempstr.contains(re) || tempstr.contains("#") || tempstr.contains("!") || tempstr.contains("."))                    //re.exactMatch(tempstr)
    {
        qDebug() << "passed mapper regexp";
        int length = tempstr.length();
        const char* dat = tempstr.toStdString().c_str();
        mapper->write(dat, length); //used to echo characters back, will not be in release
        mapperBuffer.append(dat);
        mapper_serialData.clear();
    }
/*                             END                                   */

    qDebug() << mapperBuffer;
    if(mapperBuffer.at(0) == 'E') //end
    {
        list.append(mapperBuffer);
        emit recieveMapperInstr();
        return;
    }
    else if(mapperBuffer.contains("#")) //error or warning somewhere
    {
        if(mapperBuffer.contains(".")) //complete error has been recieved
        {
            bool error = false;
            int start;
            int end;
            QString tempdat;
            for(int j = 0; j < mapperBuffer.length(); j++)
            {
                if(mapperBuffer.at(j) == '#') // beggingin of error message
                {
                    error = true;
                    start = j;
                }
                if(mapperBuffer.at(j) == '!') // beggingin of warning message
                {
                    start = j;
                }
                if(mapperBuffer.at(j) == '.') // beggingin of error/warning message
                {
                    end = j;
                }
            }
            mapperBuffer.remove(start,1);
            start++;
            int index = start;

            if(error)
                tempdat.append("Error: ");
            else
                tempdat.append("Warning: ");

            for(start; start <= end; start++)
            {
                tempdat.append(mapperBuffer.at(index));
                mapperBuffer.remove(index,1);
            }
            list.append(tempdat);
            emit recieveMapperInstr();
            return;
        }
        return;
    }
    else if(mapperBuffer.length() >= 5) //a packet of data has been sent and is ready to be
    {
        QString dat;
        for(int i = 0; i < 5; i++)
        {
            dat.append(mapperBuffer.at(0));
            mapperBuffer.remove(0,1);
        }
        list.append(dat);
        emit recieveMapperInstr(); //sends signal that an instruction has been recieved and added to list
        return;
    }
}

void SerialPort::sendMapperStart() //send start signal to mapper
{
        const char* dat = "S";
        mapper->write(dat, 1);
}

void SerialPort::sendUserStart() //final
{
        const char* dat = "S";
        user->write(dat, 1);
}

void SerialPort::sendUserSerial() //final
{

    qDebug() << "in send user serial";
    QString tempstr;
    int j = 0;
    while(j < pathDat.length())
    {
        tempstr = pathDat.at(j);
        const char* dat = tempstr.toStdString().c_str();
        int length = tempstr.length();
        user->write(dat, length);
        j++;

    }
}

void SerialPort::readUserSerial() //final
{
/*                 Serial Communiction In                           */

    user_serialData.clear();
    user_serialData = user->readAll();
    QString tempstr = QString::fromStdString(user_serialData.toStdString());
    QRegExp re("[A-Za-z0-9]");
    tempstr.remove(QChar(QChar::Null));
    if(tempstr.contains(re) || tempstr.contains(" ") || tempstr.contains("!") || tempstr.contains("."))
    {
        userBuffer.append(tempstr);
        user_serialData.clear();
    }
/*                             END                                   */


    if(userBuffer.contains(".")) //this is the end of an error message
    {
        //signal to widget.cpp to update with user_error
        int endpos = userBuffer.indexOf(".");
        for(int i = 0; i < endpos+1; i++)
        {
            user_error.append(userBuffer.at(0));
            userBuffer.remove(0,1);
        }
        emit user_error_recieved();

    }

}




