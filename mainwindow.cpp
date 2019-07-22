#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings("BenK", "BudgetManager");

    SetupTable();
    totalBudget = 0;
    ReadSettings();

    connect(ui->entryButton, SIGNAL(clicked()), ui->entryButton, SLOT(ButtonClicked()));
    connect(ui->entryButton, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->loadButton, SIGNAL(clicked()), ui->loadButton, SLOT(ButtonClicked()));
    connect(ui->loadButton, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->loadHelp, SIGNAL(clicked()), ui->loadHelp, SLOT(ButtonClicked()));
    connect(ui->loadHelp, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->saveButton, SIGNAL(clicked()), ui->saveButton, SLOT(ButtonClicked()));
    connect(ui->saveButton, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->saveHelp, SIGNAL(clicked()), ui->saveHelp, SLOT(ButtonClicked()));
    connect(ui->saveHelp, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->budgetEdit, SIGNAL(returnPressed()), ui->budgetEdit, SLOT(EditingFinished()));
    connect(ui->budgetEdit, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));

    connect(ui->filePathEdit, SIGNAL(returnPressed()), ui->filePathEdit, SLOT(EditingFinished()));
    connect(ui->filePathEdit, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));
}

MainWindow::~MainWindow()
{
    for(Entry* e : items){
        free(e);
    }
    WriteSettings();
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
    ui->entryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::DoSomething(QObject* sender){
    if(sender == ui->entryButton){
        //we want to open up a new window.
        if(x == nullptr){
            x = new NewEntryWindow();
            x->show();
            connect(x, SIGNAL(iChanged(QObject*)), this, SLOT(DoSomething(QObject*)));
            connect(x, SIGNAL(FinishOrCancel(bool)), this, SLOT(PotentialEntry(bool)));
        }else{
            //we already have a window open. just bring it to the front.
            x->show(); //not sure if all of these are necessary, but im doing it anyway
            x->raise();
            x->activateWindow();
        }
    }
    if(sender == x){
        x = nullptr;
    }
    if(sender == ui->loadButton){
        fr.ReadFile();
        vector<Entry*> stuff = fr.GetLines();
        for(Entry* x : stuff){
            AddItem(x);
        }
        ui->loadButton->setEnabled(false);
    }
    if(sender == ui->loadHelp){
        QMessageBox mb;
        mb.setText("BudgetManager is able to load from an excel file you "
                   "provide in the directory. Please include a header line, "
                   "with 'Name', 'Price', and 'Date' (do not include any extra punctuation) over the columns "
                   "containing this information. BudgetManager will ignore any data in a column that does not "
                   "have a correct header. You can update the file path in the text box in the bottom left. "
                   "Simply go to the folder containing the file 'budgetmanager.csv', and paste the path into the box. "
                   "Do not add anything to the end.");
        mb.exec();
    }
    if(sender == ui->saveButton){
        //when we click this button, we want to write all NEW entries to the .csv file.
        //so we need to be keeping track of all of the new entries. should we store them in a vector? why not.
        //and then when we click this button, we can write it all, and then clear the vector so that if we click the button again,
        //we don't write the stuff twice.
        if(saveItems.size() == 0){
            //dont do anything. idk
        }else{
            fw.WriteNewItems(saveItems, fr.GetFilePath(), fr.GetPriceC(), fr.GetNameC(), fr.GetDateC());
            saveItems.clear();
        }
    }
    if(sender == ui->saveHelp){
        QMessageBox mb;
        mb.setText("Saving will write all NEW entries to the budgetmanager.csv file. The next time you open "
                   "the program and press 'load data', the data will be loaded, along with your previous"
                   "new entries.");
        mb.exec();
    }
    if(sender == ui->budgetEdit){
        //qDebug() << "editing finished";
        FieldChecker fc;
        if(fc.IsValidNumber(ui->budgetEdit->text())){
            totalBudget = ui->budgetEdit->text().toDouble();
            CalculateRemaining();
        }else{
            QMessageBox mb;
            mb.critical(0, "Error", "Please enter a valid number in the 'Budget' field.");
            mb.setFixedSize(500, 200);
        }
    }
    if(sender == ui->filePathEdit){
        //in the future, we could have this save the file path so we can remember it, but...
        //let's get it to work for now.
        fr.UpdateFilePath(ui->filePathEdit->text());
    }
}

void MainWindow::PotentialEntry(bool add){
    if(add){
        qDebug() << "adding item.";
        AddItem(x->GetItem());
        saveItems.push_back(x->GetItem());
    }else{
        qDebug() << "not adding item.";
    }
    x->close();
    x = nullptr;
}

void MainWindow::AddItem(Entry *e){
    items.push_back(e);
    AddToTable();
}

void MainWindow::PrintItems(){
    for(Entry* e : items){
        cout << *e << endl;
    }
}

void MainWindow::AddToTable(){
    //so we just added an item to the table. do the indices in the vector correspond to the indices in the table. they should.
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

void MainWindow::closeEvent(QCloseEvent *event){
    qDebug() << "closing the main window. writing settings.";
    WriteSettings();
    event->accept(); //close the window
}

void MainWindow::WriteSettings(){
    settings->setValue("path", fr.GetFilePath());
    settings->setValue("totalbudget", totalBudget);
}

void MainWindow::ReadSettings(){
    //updating the file path:
    fr.UpdateFilePath(settings->value("path").toString());
    ui->filePathEdit->setText(settings->value("path").toString());
    //updating the total budget:
    totalBudget = settings->value("totalbudget").toDouble();
    ui->budgetEdit->setText(QString::number(totalBudget));
}
