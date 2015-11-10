#include "serialport.h"

SerialPort::SerialPort()
{

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
    QStringList list;
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
