/*
    Tyler Olson
    Virginia Tech ECE 4534 Embedded System Design
    serialport.h & serialport.cpp

    DESCRIPTION:
        These files are used to open and communicate with the rovers through
        WiFi using the provided WiFlys.
*/

#include "serialport.h"
#include <string>

SerialPort::SerialPort()
{

    mapperFinished = false;
    mapper_serial_number = "A702ZK6O";    //proper
    user_serial_number = "A702ZKQU";
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
                mapper_port_name = serialPortInfo.portName();
                if(DEBUG)
                    qDebug() << "mapper is available, port name has been set to: " << mapper_port_name;
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
            connect(mapper, SIGNAL(readyRead()), this, SLOT(readMapperSerial()));
        }
    }
    if(user_is_available)
    {
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
    if(DEBUG)
        qDebug() << "connecting start mapper and user signals";
    connect(this, SIGNAL(startMapper()), this, SLOT(sendMapperStart()));
    connect(this, SIGNAL(startUser()), this, SLOT(sendUserStart()));
    connect(this, SIGNAL(sendUserPath()), this, SLOT(sendUserSerial()));
}

SerialPort::~SerialPort()
{
    if(mapper->isOpen())
    {
        mapper->close(); //    Close the serial port if it's open.
    }
    if(user->isOpen())
    {
        user->close(); //    Close the serial port if it's open.
    }
}


//used strictly for testing
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
    emit sendUserPath();
}

QStringList SerialPort::returnList()
{
    return list;
}

void SerialPort::readMapperSerial()
{

/*                 Serial Communiction In                           */

    mapper_serialData.clear();
    mapper_serialData = mapper->readAll();
    QString tempstr = QString::fromStdString(mapper_serialData.toStdString());
    QRegExp re("[A-Za-z0-9]");
    tempstr.remove(QChar(QChar::Null));
    tempstr.remove("$");
    tempstr.remove("*");
    if(tempstr.contains(re) || tempstr.contains(" ") || tempstr.contains(".") || tempstr.contains("!"))                    //re.exactMatch(tempstr)
    {
        int length = tempstr.length();
        const char* dat = tempstr.toStdString().c_str();
        mapper->write(dat, length); //used to echo characters back, will not be in release
        mapperBuffer.append(tempstr);
        mapper_serialData.clear();
    }
/*                             END                                   */

    if(mapperBuffer.at(4) == 'E') //end
    {
        list.append(mapperBuffer);
        emit recieveMapperEnd();
        return;
    }
    if(mapperBuffer.contains(".")) //this is the end of an error message
    {
        //signal to widget.cpp to update with mapper_error
        int startpos = mapperBuffer.indexOf("!");
        int endpos = mapperBuffer.indexOf(".");
        for(int i = 0; i < endpos+1; i++)
        {
            mapper_error.append(mapperBuffer.at(startpos));
            mapperBuffer.remove(startpos,1);
        }
        emit mapper_error_recieved();

    }
    else if(mapperBuffer.length() >= 5 && !mapperBuffer.contains("!")) //a packet of data has been sent and is ready to be interpretted
    {
        QString dat;
        for(int i = 0; i < 5; i++)
        {
            dat.append(mapperBuffer.at(0));
            mapperBuffer.remove(0,1);
        }
        list.append(dat);
        emit recieveMapperInstr(); //sends signal that an instruction has been recieved and added to list
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
