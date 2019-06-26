#ifndef ENTRY_H
#define ENTRY_H

#include <string>
using std::string;
#include <iostream>
using std::ostream;

class Entry
{
public:
    Entry() = default;
    Entry(string p, string n, string d);
    string GetPrice() const;
    string GetName() const;
    string GetDate() const;
    friend ostream& operator<<(ostream& os, const Entry& e);
    void SetPrice(string p);
    void SetName(string n);
    void SetDate(string d);
private:
    string price_;
    string name_;
    string date_;
};

#endif // ENTRY_H
