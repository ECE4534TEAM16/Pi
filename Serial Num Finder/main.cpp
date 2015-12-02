#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

char buffer[50];


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSerialPort Mapper_TEST;
    qDebug() << "Begin";

    // Example use QSerialPortInfo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();

        // Example use QSerialPort
        if(info.serialNumber() == "A702ZKQU")
        {
            Mapper_TEST.setPortName(info.portName());
            //Mapper_TEST.setPort(info);




//            Mapper_TEST.setBaudRate(QSerialPort::Baud57600);
//            Mapper_TEST.setDataBits(QSerialPort::Data8);
//            Mapper_TEST.setParity(QSerialPort::NoParity);
//            Mapper_TEST.setFlowControl(QSerialPort::NoFlowControl);
//            Mapper_TEST.setStopBits(QSerialPort::OneStop);
            qDebug() << "Serial Port Set as: " << info.serialNumber();
        }
//        if (serial.open(QIODevice::ReadWrite))
//            serial.close();
    }

    qDebug() << "End";
    if(!Mapper_TEST.open(QIODevice::ReadWrite))
    {
        qDebug() << Mapper_TEST.errorString();


    }
    if(Mapper_TEST.isOpen())
    {
        qDebug() << "opened, start reading";
        while(Mapper_TEST.isOpen())
        {
                Mapper_TEST.readyRead();
                qDebug() << "bytes Aval";
                Mapper_TEST.readLine(buffer, Mapper_TEST.bytesAvailable());
                qDebug() << buffer;



        }




    }

    exit(EXIT_SUCCESS);
    return a.exec();
}

