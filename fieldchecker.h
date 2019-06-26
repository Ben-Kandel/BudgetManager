#ifndef FIELDCHECKER_H
#define FIELDCHECKER_H

#include <QString>
#include <string>
using std::string;

class FieldChecker
{
public:
    FieldChecker() = default;
    bool IsValidNumber(QString);
};

#endif // FIELDCHECKER_H
