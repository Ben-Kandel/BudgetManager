#ifndef NEWENTRYWINDOW_H
#define NEWENTRYWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QDebug>
#include <QString>
#include <string>
using std::string;

#include <entry.h>
#include <fieldchecker.h>

namespace Ui {
class NewEntryWindow;
}

class NewEntryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewEntryWindow(QWidget *parent = nullptr);
    ~NewEntryWindow();
    Entry* GetItem();
public slots:
    void DoSomething(QObject*);
signals:
    void iChanged(QObject*);
    void FinishOrCancel(bool);

private:
    Ui::NewEntryWindow *ui;
    virtual void closeEvent(QCloseEvent *event);
    void CompleteItem();
    Entry* currentitem;
    bool IsValidPrice(QString);
    bool IsValidName(QString);
};

#endif // NEWENTRYWINDOW_H
