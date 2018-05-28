#ifndef SUOBUTTON_H
#define SUOBUTTON_H

#include <QPushButton>
#include <QVector>
#include <QString>
#include <QObject>

class SuoButton:public QObject
{
    Q_OBJECT
public:
    SuoButton();
    QPushButton *Sudoku;
    void SetPos(int,int,int);
    void SetImage(int, int,int,int);
    void SetSlot();

public slots:
    void SetPress();
    void SetRelease();




private:
    int xpos,ypos,N,who,QNumber;

};

#endif // SUOBUTTON_H
