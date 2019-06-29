#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>

#include <vector>
using std::vector;
#include "entry.h"

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout; using std::endl;

class FileReader
{
public:
    FileReader() = default;
    bool ReadFile();
    vector<Entry*> GetLines();
private:
    size_t price_;
    size_t name_;
    size_t date_;
    void FigureOutImportantColumns(QString);
    vector<Entry*> lines_;
    Entry* ConvertToEntry(QString);
    void PrintLines();
};

#endif // FILEREADER_H
