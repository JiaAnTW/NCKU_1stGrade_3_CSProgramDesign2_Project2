#include "suobutton.h"


SuoButton::SuoButton()
{
}

void SuoButton::SetPos(int player,int y,int x){
    xpos=x;
    ypos=y;
    if(player==1)
        Sudoku->setGeometry(50*(ypos+1)+(ypos/3*5),105+50*(xpos+1)+(xpos/3*5),50,50);
    else
        Sudoku->setGeometry(650+50*(ypos+1)+(ypos/3*5),105+50*(xpos+1)+(xpos/3*5),50,50);
}

void SuoButton::SetImage(int click, int Number,int player,int N_ques){
    N=Number;
    who=player;
    QNumber=N_ques;
    QString address_btn = "QPushButton{border-image: url(:/Image/";
    if(who==1){
         if(click==0)
            address_btn.append("R");
         }
    else{
         if(click==0)
            address_btn.append("V");
        }
    if(N_ques==0 && N!=0 && click==0)
        address_btn.append("_ANS");
    address_btn.append(QString::number(N));
    address_btn.append(".png);}");
    const QString address = address_btn;
    Sudoku->setStyleSheet(address);
}

void SuoButton::SetPress(){
    if(QNumber==0)
        SetImage(1,N,who,QNumber);
}

void SuoButton::SetRelease(){
    if(QNumber==0)
        SetImage(0,N,who,QNumber);
}

void SuoButton::SetSlot(){
    QObject::connect(Sudoku,SIGNAL(pressed()),this,SLOT(SetPress()));
    QObject::connect(Sudoku,SIGNAL(released()),this,SLOT(SetRelease()));
}
