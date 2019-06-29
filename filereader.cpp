#include "filereader.h"

bool FileReader::ReadFile(){
    QString backPath = "";
    QFile f(backPath + "budgetmanager.csv");
    if(!f.open(QIODevice::ReadOnly)){
        qDebug() << f.errorString();
        qDebug() << QDir::currentPath();
        throw f.error();
    }else{
        qDebug() << "File read!";
        QTextStream in(&f);
        QString header = in.readLine();
        qDebug() << "Header: " << header;
        FigureOutImportantColumns(header);
        while(!in.atEnd()){
            QString line = in.readLine();
            qDebug() << line;
            lines_.push_back(ConvertToEntry(line));
        }
        f.close();
        PrintLines();
        return true;
    }
}

void FileReader::PrintLines(){
    cout << "Begin print of information from file: ";
    for(Entry* x : lines_){
        cout << *x << ", ";
    }
    cout << endl;
}

void FileReader::FigureOutImportantColumns(QString x){
    string l = x.toStdString();
    stringstream ss(l);
    string str;
    vector<string> results;
    while(getline(ss, str, ',')){
        results.push_back(str);
    }
    //now we have a vector that contains the header line. we should figure out which column numbers contain the
    //price, name, and date
    for(size_t i = 0; i<results.size(); i++){ //loop through the vector
        for(size_t j = 0; j<results[i].size(); j++){ //loop through characters in the string.
            results[i][j] = std::tolower(results[i][j]);
        }

        if(results[i] == "name"){
            name_ = i;
        }else if(results[i] == "price"){
            price_ = i;
        }else if(results[i] == "date"){
            date_ = i;
        }
    }
    /*
    cout << "Name is in column " << name_;
    cout << "Price is in column " << price_;
    cout << "Date is in column " << date_;
    cout << endl;
    */
}

Entry* FileReader::ConvertToEntry(QString info){
    string line = info.toStdString();
    stringstream ss(line);
    string str;
    vector<string> results;
    while(getline(ss, str, ',')){
        results.push_back(str);
    }
    //now we have a vector of the line split up by comma.
    //we know the columns of the important information.
    //we should probably have a builder class, but, I think we'll be fine.
    Entry* add = new Entry(results[price_], results[name_], results[date_]);
    return add;
}

vector<Entry*> FileReader::GetLines(){
    return lines_;
}
