#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextStream>

#include <vector>
using std::vector;
#include "entry.h"

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout; using std::endl;

class FileWriter
{
public:
    FileWriter();
    bool WriteNewItems(vector<Entry*> items, QString path, size_t pricec, size_t namec, size_t datec);
private:
};

#endif // FILEWRITER_H
