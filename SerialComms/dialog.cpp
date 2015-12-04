#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <QRegExp>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    mapper_serial_number = "A702ZK6O";
    ui->setupUi(this);
    ui->temp_lcdNumber->display("-------");
    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";
    temperature_value = 0.0;

    /*
     *  Testing code, prints the description, vendor id, and product id of all ports.
     *  Used it to determine the values for the arduino uno.
     *
     *
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }
    */


    /*
     *   Identify the port the arduino uno is on.
     */
    bool arduino_is_available = false;
    QString arduino_uno_port_name;
    //
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
            //  check if the product ID and the vendor ID match those of the arduino uno
            if(serialPortInfo.serialNumber() == mapper_serial_number)
            {
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }

    }

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available)
    {
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud57600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
//        while(true)
//        {
//            qDebug() << "send data";
//            sendData();
//        }
    }
    else
    {
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close(); //    Close the serial port if it's open.
        qDebug() << "serial port closed";
    }
    delete ui;
}

void Dialog::readSerial()
{
    qDebug() << "in read serial";
    /*
     * readyRead() doesn't guarantee that the entire message will be received all at once.
     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
     *
     */
//    QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

    //  Check to see if there less than 3 tokens in buffer_split.
    //  If there are at least 3 then this means there were 2 commas,
    //  means there is a parsed temperature value as the second token (between 2 commas)
//    if(buffer_split.length() < 3)
//    {
        // no parsed value yet so continue accumulating bytes from serial in the buffer.
        serialData.clear();
        serialData = arduino->readAll();
        QString tempstr = QString::fromStdString(serialData.toStdString());
        qDebug() << tempstr;
        //QString tempstr = serialData.at(serialData.length());
        //QRegExp re("[^a-zA-Z\\d\\s]");
        QRegExp re("[A-Za-z0-9]");
        if(tempstr.contains(re))                    //re.exactMatch(tempstr)
        {
            qDebug() << "passed regexp";
            int length = tempstr.length();
            const char* dat = tempstr.toStdString().c_str();
            arduino->write(dat, length);
            serialBuffer = serialBuffer + tempstr;
            serialData.clear();
        }


//    }
//    else
//    {
//        // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
//        serialBuffer = "";
//        qDebug() << buffer_split << "\n";
//        parsed_data = buffer_split[1];
//        temperature_value = (9/5.0) * (parsed_data.toDouble()) + 32; // convert to fahrenheit
//        qDebug() << "Temperature: " << temperature_value << "\n";
//        parsed_data = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
//        Dialog::updateTemperature(parsed_data);
//    }

}

void Dialog::sendData()
{
    char temp;
    cout << "Input Character: ";
    cin >> temp;
    serialData.append(temp);
    qDebug() << serialData;
    const char* dat = serialData.constData();
    qDebug() << dat;
    arduino->write(dat, 1);
    serialData.clear();

}

void Dialog::updateTemperature(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    ui->temp_lcdNumber->display(sensor_reading);
}
