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

    qDebug() << "End";
    }

    exit(EXIT_SUCCESS);
    return a.exec();
}

