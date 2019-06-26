#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupTable();
    totalBudget = 0;
    connect(ui->entryButton, SIGNAL(clicked()), ui->entryButton, SLOT(ButtonClicked()));
    connect(ui->entryButton, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->loadButton, SIGNAL(clicked()), ui->loadButton, SLOT(ButtonClicked()));
    connect(ui->loadButton, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->budgetEdit, SIGNAL(editingFinished()), ui->budgetEdit, SLOT(EditingFinished()));
    connect(ui->budgetEdit, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));
}

MainWindow::~MainWindow()
{
    for(Entry* e : items){
        free(e);
    }
    delete ui;
}

void MainWindow::SetupTable(){
    ui->entryTable->setColumnCount(3);
    ui->entryTable->setRowCount(0);
    QStringList itemtableheader;
    itemtableheader << "Price" << "Date Added" << "Name/Details";
    ui->entryTable->setHorizontalHeaderLabels(itemtableheader);
    ui->entryTable->verticalHeader()->setVisible(false);
    ui->entryTable->horizontalHeader()->setStretchLastSection(true);
    currentRow = 0;
}

void MainWindow::DoSomething(QObject* sender){
    if(sender == ui->entryButton){
        //we want to open up a new window.
        //qDebug() << "we clicked on entry button.";
        if(x == nullptr){
            //qDebug() << "making new window";
            x = new NewEntryWindow();
            x->show();
            connect(x, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));
            connect(x, SIGNAL(FinishOrCancel(bool)), this, SLOT(PotentialEntry(bool)));
        }else{
            //we already have a window open. just bring it to the front.
            x->show();
            x->raise();
            x->activateWindow();
        }
    }
    if(sender == x){
        //qDebug() << "we received a signal from the window.";
        x = nullptr;
    }
    if(sender == ui->loadButton){
        //for now, we are having this print out the list.
        qDebug() << "Printing Items: ";
        PrintItems();
    }
    if(sender == ui->budgetEdit){
        qDebug() << "editing finished";
        FieldChecker fc;
        if(fc.IsValidNumber(ui->budgetEdit->text())){
            totalBudget = ui->budgetEdit->text().toDouble();
            CalculateRemaining();
        }else{
            QMessageBox mb;
            mb.critical(0, "Error", "Please enter a valid number in the 'Budget' field.");
            mb.setFixedSize(500, 200);
        }
        //UpdateLabel(totalBudget);
        //CalculateRemaining();
    }
}

void MainWindow::PotentialEntry(bool add){
    if(add){
        qDebug() << "adding item.";
        AddItem(x->GetItem());
    }else{
        qDebug() << "not adding item.";
    }
    x->close();
    x = nullptr;
}

void MainWindow::AddItem(Entry *e){
    items.push_back(e);
    AddToTable();
    //everytime we add an item, we should also be updating the table. or just adding it to the table.
}

void MainWindow::PrintItems(){
    for(Entry* e : items){
        cout << *e << endl;
    }
}

void MainWindow::AddToTable(){
    //so we just added an item to the table. do the indices in the vector correspond to the indices in the table. they should.
    //ui->entryTable.setite
    //so we need to take our vector that contains three things, and put them in the currentRow, price in column 0, date in column 1, and name in
    //column 3
    ui->entryTable->setRowCount(currentRow+1);
    vector<string> putIn{items[currentRow]->GetPrice(), items[currentRow]->GetDate(), items[currentRow]->GetName()};
    for(int i = 0; i<3; i++){
        QString a = QString::fromStdString(putIn[i]);
        ui->entryTable->setItem(currentRow, i, new QTableWidgetItem(a));
    }
    currentRow++;
    CalculateRemaining();
}

void MainWindow::UpdateLabel(double r){
    QString a = QString::number(r);
    ui->remainingBudget->setText(a);

    int percent = (r / totalBudget) * 100;
    QString b = QString::number(percent);
    QString c = "% left!";
    b.append(c);
    ui->percentLeft->setText(b);
}

void MainWindow::CalculateRemaining(){
    double sum = 0;
    for(Entry* e : items){
        sum += stod(e->GetPrice());
    }
    remainingBudget = totalBudget - sum;
    UpdateLabel(remainingBudget);
}
