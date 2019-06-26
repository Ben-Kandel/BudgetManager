#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{
Q_OBJECT
public:
    button(QWidget* qw):QPushButton(qw){}
signals:
    void iChanged(QObject*);
public slots:
    void ButtonClicked();
};

#endif // BUTTON_H
