#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include <QImage>
#include <QVector>
#include <QLCDNumber>
#include <QMessageBox>
#include "suobutton.h"
#include "function.h"
#include "map.h"
#include "levelbutton.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

public slots:
    void Checkyouranswer(bool);
    void ResetMap(int);
    void SolveTheMap(bool);
    void Design(bool);
    void InputNumber(Map &map,SuoButton button[],int player,int pos,int N);
    void SetPlayer2(int);
    void Battle(int,int,int);
    void ShowNormalLevel(bool);
    void ShowBattleLevel(bool);
    void DesignFinish(bool);
    void CloseVictory(bool);
    void ShowOrHideP2(bool);


signals:
    void Player1ChangePoint(int);
    void Player2ChangePoint(int);




private:
    Ui::MainWindow *ui;
    int press_pos,press_pos_2, player_point[1],player_combol_1,player_combol_2,control_N[1],*level;
    bool player2work,firsttime;
    SuoButton Suo_btn[81],player2[81];
    Map Suo_map,Map2;
    QPushButton *normal_Game,*Check_ans,*player_design,*auto_solve,*battle,*messager,*player_1,*player_2,
    *instruction1_1,*instruction1_2,*instruction2_1,*instruction2_2,*DesignBtn,*Victory;
    levelbutton NormalLevel[3],BattleLevel[3];
    QLCDNumber *player1_lcd,*player2_lcd;


};

#endif // MAINWINDOW_H
