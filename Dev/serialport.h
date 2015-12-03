#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <string>


#define Test            true




class SerialPort
{
public:
    SerialPort();

    QStringList readline(QString filename); //only used during testing
    void sendMapperStartSignal();
    void sendUserStartSignal();

signals:
    void startMapper();
    void startUser();

private slots:
    QString readMapperSerial();
    void sendMapperStart();
    void sendUserStart();
    void sendUserSerial();
    void readUserSerial();

private:

    QStringList list;
    QSerialPort *mapper;
    QSerialPort *user;
    QString user_serial_number; //
    QString mapper_serial_number; //A702ZKQU
    QByteArray mapper_serialData;
    QString mapperBuffer;
    QString parsed_mapData;
    bool mapperFinished;
};

#endif // SERIALPORT_H
