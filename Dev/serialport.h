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


#define Test            true




class SerialPort: public QObject
{
    Q_OBJECT

public:
    SerialPort();
    ~SerialPort();
    QStringList list;
    QStringList readline(QString filename); //only used during testing
    void sendMapperStartSignal();
    void sendUserStartSignal();
    QStringList returnList();

signals:
    void startMapper();
    void startUser();
    void recieveMapperInstr();

private slots:
    void readMapperSerial();
    void sendMapperStart();
    void sendUserStart();
    void sendUserSerial();
    void readUserSerial();

private:


    QSerialPort *mapper;
    QSerialPort *user;
    QString user_serial_number; //AD02FKX4
    QString mapper_serial_number; //A702ZKQU
    QByteArray mapper_serialData;
    QString mapperBuffer;
    QString parsed_mapData;
    bool mapperFinished;
};

#endif // SERIALPORT_H
