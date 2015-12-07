/*
    Tyler Olson
    Virginia Tech ECE 4534 Embedded System Design
    serialport.h & serialport.cpp

    DESCRIPTION:
        These files are used to open and communicate with the rovers through
        WiFi using the provided WiFlys.
*/

#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <string>
#include <QDebug>
#include <QRegExp>


#define DEBUG       false




class SerialPort: public QObject
{
    Q_OBJECT

public:
    SerialPort();
    ~SerialPort();
    QStringList list;
    QString user_error;
    QString mapper_error;
    QStringList readline(QString filename); //only used during testing
    void sendMapperStartSignal();
    void sendUserStartSignal();
    void sendPath(QStringList path);
    QStringList returnList();

signals:
    void startMapper();
    void startUser();
    void recieveMapperInstr();
    void sendUserPath();
    void user_error_recieved();
    void mapper_error_recieved();
    void recieveMapperEnd();

private slots:
    void readMapperSerial();
    void sendMapperStart();
    void sendUserStart();
    void sendUserSerial();
    void readUserSerial();

private:
    //Serial Ports
    QSerialPort *mapper;
    QSerialPort *user;

    //ByteArrays
    QByteArray mapper_serialData;
    QByteArray user_serialData;

    //QString and QStringLists
    QString user_serial_number; //AD02FKX4
    QString mapper_serial_number; //A702ZKQU
    QString userBuffer;
    QString mapperBuffer;
    QString parsed_mapData;
    QStringList pathDat;
    QStringList testList;

    //bools
    bool mapperFinished;

};

#endif // SERIALPORT_H
