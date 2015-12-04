#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QByteArray>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void readSerial();
    void sendData();
    void updateTemperature(QString);

private:
    Ui::Dialog *ui;

    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString mapper_serial_number;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    double temperature_value;
};

#endif // DIALOG_H
