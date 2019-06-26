#include "fieldchecker.h"

bool FieldChecker::IsValidNumber(QString s){
    if(s.length() == 0){
        return false;
    }
    string x = s.toStdString();
    int dotcount = 0;
    for(char c : x){
        //we run this check before, because the isdigit() would fail on the decimal point
        if(c == '.'){
            dotcount++;
            continue; //if we found one, skip the isdigit() check
        }
        if(!std::isdigit(c)){ //we're on some character, and we know it isn't a decimal point. if it's not a number, return false.
            return false;
        }
    }
    if(dotcount > 1){ //if there is more than one decimal point then that is definitely not a real number
        return false;
    }
    return true;
}
