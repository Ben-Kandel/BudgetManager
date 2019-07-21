#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <newentrywindow.h>
#include <vector>
using std::vector;
#include <entry.h>
#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string; using std::stod;
#include <QMessageBox>
#include <QSettings>

#include <fieldchecker.h>
#include <filereader.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddItem(Entry* e);

public slots:
    void DoSomething(QObject*);
    void PotentialEntry(bool);

private:
    Ui::MainWindow *ui;
    void SetupTable();
    NewEntryWindow* x = nullptr;
    vector<Entry*> items;
    QSettings* settings;
    void PrintItems();
    int currentRow;
    void AddToTable();
    double totalBudget;
    double remainingBudget;
    void UpdateLabel(double r);
    void CalculateRemaining();
    FileReader fr;
    virtual void closeEvent(QCloseEvent *event);
    void WriteSettings();
    void ReadSettings();
};

#endif // MAINWINDOW_H
