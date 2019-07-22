#include "entry.h"

Entry::Entry(string p, string n, string d){
    price_ = p;
    name_ = n;
    date_ = d;
}

string Entry::GetDate(){
    return date_;
}

string Entry::GetName(){
    return name_;
}

string Entry::GetPrice(){
    return price_;
}

ostream& operator<<(ostream& os, const Entry& e){
    os << "Price: " << e.price_ << ", Date Purchased: " << e.date_ << ", Name: " << e.name_;
    return os;
}

void Entry::SetDate(string d){
    date_ = d;
}

void Entry::SetName(string n){
    name_ = n;
}

void Entry::SetPrice(string p){
    price_ = p;
}
