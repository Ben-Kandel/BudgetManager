#include "filewriter.h"

FileWriter::FileWriter()
{

}

bool FileWriter::WriteNewItems(vector<Entry *> items, QString path, size_t pricec, size_t namec, size_t datec){
    qDebug() << "WriteNewItems called.";
    QFile f(path + "budgetmanager.csv");
    if(!(f.open(QIODevice::WriteOnly | QIODevice::Append))){
        qDebug() << "couldn't write to file.";
        return false;
    }else{
        //do stuff.
        QTextStream stream(&f);
        for(Entry* x : items){
            //we write in the order name, price, date?? thats dumb.
            QString n = QString::fromStdString(x->GetName());
            QString p = QString::fromStdString(x->GetPrice());
            QString d = QString::fromStdString(x->GetDate());
            for(size_t i = 0; i<namec; i++){
                stream << ",";
            }
            stream << n;
            for(size_t i = namec; i<pricec; i++){
                stream << ",";
            }
            stream << p;
            for(size_t i = pricec; i<datec; i++){
                stream << ",";
            }
            stream << d;
            stream << "\n";
        }
        f.close();
        return true;
    }
}
