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

    QStringList readline(QString filename);

//signals:
//public slots:
};

#endif // SERIALPORT_H
