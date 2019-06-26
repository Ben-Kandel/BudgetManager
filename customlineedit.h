#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>

class customlineedit : public QLineEdit
{
Q_OBJECT
public:
    customlineedit(const QString& qstring):QLineEdit(qstring){}
    customlineedit(QWidget* qw):QLineEdit(qw){}
signals:
    void iChanged(QObject*);
public slots:
    void EditingFinished();
};

#endif // CUSTOMLINEEDIT_H
