#include "newentrywindow.h"
#include "ui_newentrywindow.h"
#include <QMessageBox>

NewEntryWindow::NewEntryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEntryWindow)
{
    ui->setupUi(this);


    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->cancelButton, SIGNAL(clicked()), ui->cancelButton, SLOT(ButtonClicked()));
    connect(ui->cancelButton, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->finishButton, SIGNAL(clicked()), ui->finishButton, SLOT(ButtonClicked()));
    connect(ui->finishButton, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

}

NewEntryWindow::~NewEntryWindow()
{
    delete ui;
}

void NewEntryWindow::closeEvent(QCloseEvent *event){
    emit iChanged(this); //emit the signal so mainwindow knows
    qDebug() << "new entry window closed.";
    event->accept(); //still close the window.
}

void NewEntryWindow::DoSomething(QObject* sender){
    if(sender == ui->cancelButton){
        qDebug() << "cancel button.";
        //we just need to close the window. don't care about the information.
        emit(FinishOrCancel(false));
    }
    if(sender == ui->finishButton){
        qDebug() << "finish button";
        //now we need to gather up the information, create the object, and give it to main window.
        //well, first we should check if there is a valid number in the price box.
        FieldChecker fc;
        if(fc.IsValidNumber(ui->priceEdit->text())){
            CompleteItem();
            emit(FinishOrCancel(true));
        }else{
            QMessageBox mb;
            mb.critical(0, "Error", "Please enter a valid number in the 'Price' field.");
            mb.setFixedSize(500, 200);
        }
        /*
        if(IsValidPrice(ui->priceEdit->text())){
            CompleteItem();
            emit(FinishOrCancel(true));
        }else{
            QMessageBox mb;
            mb.critical(0, "Error", "Please enter a valid number in the 'Price' field.");
            mb.setFixedSize(500, 200);
        }
        */
    }
}

void NewEntryWindow::CompleteItem(){
    //we make an entry like = Entry* e = new Entry(double price, string name, string date)
    string p = ui->priceEdit->text().toStdString();
    string name = ui->nameEdit->text().toStdString();
    string date = ui->dateEdit->text().toStdString();
    /*
    qDebug() << "Price: " << p;
    qDebug() << "Name: " << ui->nameEdit->text();
    qDebug() << "Date Purchased: " << ui->dateEdit->text();
    */
    Entry* item = new Entry(p, name, date);
    currentitem = item;
}


Entry* NewEntryWindow::GetItem(){
    return currentitem;
}

bool NewEntryWindow::IsValidPrice(QString s){
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

bool NewEntryWindow::IsValidName(QString){

}

