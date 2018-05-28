#include "mainwindow.h"
#include "ui_mainwindow.h"
//constructor of MainWindow
//Start
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    player_1=new QPushButton(this);
    player_1->setGeometry(42,147,476,476);
    player_1->setStyleSheet("QPushButton{border-image: url(:/Image/player1_back.png)};");
    firsttime=true;
    player_2=new QPushButton(this);
    player_2->setGeometry(692,147,476,476);
    player_2->setStyleSheet("QPushButton{border-image: url(:/Image/player2_back.png)};");
    player_2->hide();


    //set player1
    for(int j=0;j<9;++j){
        for(int i=0;i<9;++i){
            Suo_btn[9*j+i].Sudoku = new QPushButton(this);
            Suo_btn[9*j+i].SetSlot();
        }
    }
    ResetMap(0);
    press_pos=Suo_map.getNextBlank();
    Suo_btn[press_pos].Sudoku->pressed();
    player_point[0]=100;
    player_combol_1=0;
    control_N[0]=0;

    //set player2, and also hide it    
    Map2.SetRandomMap(2,level);
    for(int j=0;j<9;++j){
        for(int i=0;i<9;++i){
            player2[9*j+i].Sudoku = new QPushButton(this);
            player2[9*j+i].SetSlot();
            player2[9*j+i].SetPos(2,i,j);
            player2[9*j+i].SetImage(0,Map2.Map_Number(j,i),2,Map2.GetMap_Ques(j,i));
            player2[9*j+i].Sudoku->hide();
        }
    }
    press_pos_2=Map2.getNextBlank();
    player2[press_pos_2].Sudoku->pressed();
    player2work=false;
    player_point[1]=100;
    player_combol_2=0;
    control_N[1]=0;


    normal_Game=new QPushButton(this);
    normal_Game->setGeometry(1300,120,150,70);
    normal_Game->setStyleSheet("QPushButton{border-image: url(:/Image/btn_new)};");
    level=1;



    Check_ans=new QPushButton(this);
    Check_ans->setGeometry(1300,200,150,70);
    Check_ans->setStyleSheet("QPushButton{border-image: url(:/Image/btn_ans)};");


    player_design=new QPushButton(this);
    player_design->setGeometry(1300,280,150,70);
    player_design->setStyleSheet("QPushButton{border-image: url(:/Image/btn_design)};");


    auto_solve=new QPushButton(this);
    auto_solve->setGeometry(1300,360,150,70);
    auto_solve->setStyleSheet("QPushButton{border-image: url(:/Image/btn_AI)};");


    battle=new QPushButton(this);
    battle->setGeometry(1300,440,150,70);
    battle->setStyleSheet("QPushButton{border-image: url(:/Image/btn_battle)};");


    messager=new QPushButton(this);
    messager->setGeometry(400,40,564,80);
    messager->setStyleSheet("QPushButton{border-image: url(:/Image/Message)};");

    player1_lcd=new QLCDNumber(this);
    player1_lcd->setGeometry(500,650,100,50);
    player1_lcd->display(player_point[0]);
    player1_lcd->hide();
    player2_lcd=new QLCDNumber(this);
    player2_lcd->setGeometry(1150,650,100,50);
    player2_lcd->display(player_point[1]);
    player2_lcd->hide();

    instruction1_1=new QPushButton(this);
    instruction1_1->setGeometry(35,670,245,109);
    instruction1_1->setStyleSheet("QPushButton{border-image: url(:/Image/instruction_1-1)};");

    instruction1_2=new QPushButton(this);
    instruction1_2->setGeometry(300,650,210,145);
    instruction1_2->setStyleSheet("QPushButton{border-image: url(:/Image/instruction_1-2)};");

    instruction2_1=new QPushButton(this);
    instruction2_1->setGeometry(685,670,245,109);
    instruction2_1->setStyleSheet("QPushButton{border-image: url(:/Image/instruction_2-1)};");
    instruction2_1->hide();

    instruction2_2=new QPushButton(this);
    instruction2_2->setGeometry(950,650,210,145);
    instruction2_2->setStyleSheet("QPushButton{border-image: url(:/Image/instruction_2-2)};");
    instruction2_2->hide();

    DesignBtn=new QPushButton(this);
    DesignBtn->setGeometry(1325,630,100,70);
    DesignBtn->setStyleSheet("QPushButton{border-image: url(:/Image/design_btn)};");
    DesignBtn->hide();
    QObject::connect(DesignBtn,SIGNAL(clicked(bool)),this,SLOT(DesignFinish(bool)));

    Victory=new QPushButton(this);
    Victory->setGeometry(225,200,750,400);
    Victory->hide();
    QObject::connect(Victory,SIGNAL(clicked(bool)),this,SLOT(CloseVictory(bool)));

    for(int i=0;i<3;++i){
        NormalLevel[i].Chooselevel=new QPushButton(this);
        NormalLevel[i].SetLevel(i+1);
        NormalLevel[i].Chooselevel->hide();
        QObject::connect(NormalLevel[i].Chooselevel,SIGNAL(clicked(bool)),&NormalLevel[i],SLOT(ReciveLevel(bool)));
        QObject::connect(&NormalLevel[i],SIGNAL(ReturnLevelMode(int)),this,SLOT(ResetMap(int)));
    }

    for(int i=0;i<3;++i){
        BattleLevel[i].Chooselevel=new QPushButton(this);
        BattleLevel[i].SetLevel(i+1);
        BattleLevel[i].Chooselevel->hide();
        QObject::connect(BattleLevel[i].Chooselevel,SIGNAL(clicked(bool)),&BattleLevel[i],SLOT(ReciveLevel(bool)));
        QObject::connect(&BattleLevel[i],SIGNAL(ReturnLevelMode(int)),this,SLOT(SetPlayer2(int)));
    }

    QObject::connect(normal_Game,SIGNAL(clicked(bool)),this,SLOT(ShowNormalLevel(bool)));
    QObject::connect(Check_ans,SIGNAL(clicked(bool)),this,SLOT(Checkyouranswer(bool)));
    QObject::connect(auto_solve,SIGNAL(clicked(bool)),this,SLOT(SolveTheMap(bool)));
    QObject::connect(player_design,SIGNAL(clicked(bool)),this,SLOT(Design(bool)));
    QObject::connect(battle,SIGNAL(clicked(bool)),this,SLOT(ShowBattleLevel(bool)));
    QObject::connect(this,SIGNAL(Player1ChangePoint(int)),player1_lcd,SLOT(display(int)));
    QObject::connect(this,SIGNAL(Player2ChangePoint(int)),player2_lcd,SLOT(display(int)));

}





//END
//Functions that helps conducting the game
//Start





void MainWindow::Checkyouranswer(bool check){ //Use Images to tell players if their ans are right
    if(check==false){
        if(Suo_map.isCorrect())
            messager->setStyleSheet("QPushButton{border-image: url(:/Image/SuccessMessage.png)};");
        else
            messager->setStyleSheet("QPushButton{border-image: url(:/Image/FailedMessage.png)};");
    }
}

void MainWindow::ResetMap(int level){ //Initizalize the map and the images on the button
        if(firsttime==false){
            for(int i=0;i<3;++i)
                NormalLevel[i].Chooselevel->hide();
        }
        Suo_map.SetRandomMap(1,level);
        for(int j=0;j<9;++j){
            for(int i=0;i<9;++i){
                Suo_btn[9*j+i].SetPos(1,i,j);
                Suo_btn[9*j+i].SetImage(0,Suo_map.Map_Number(j,i),1,Suo_map.GetMap_Ques(j,i));
            }
        }
        firsttime=false;

}

void MainWindow::SolveTheMap(bool check){ //AI will check and solve the question after this
    if (check==false){
            Map ques,ans;
            ques=Suo_map;
            if(Suo_map.Solution(ques,ans)){
                Suo_map.map_sol=ans.map_sol;
                for(int j=0;j<9;++j){
                    for(int i=0;i<9;++i){
                        Suo_btn[9*j+i].SetImage(0,Suo_map.Map_Number(j,i),1,Suo_map.GetMap_Ques(j,i));
                    }
                }
                messager->setStyleSheet("QPushButton{border-image: url(:/Image/SolveMessage.png)};");
            }
            else
                messager->setStyleSheet("QPushButton{border-image: url(:/Image/ErrorMessage.png)};");
    }
}

void MainWindow::Design(bool check){ //Let players design their own ques
    if(check==false){
        DesignBtn->show();
        for(int j=0;j<9;++j){
            for(int i=0;i<9;++i){
                Suo_map.setMapNumber(9*j+i,0);
            }
        }
        Suo_map.map_ex=Suo_map.map_sol;
        for(int j=0;j<9;++j){
            for(int i=0;i<9;++i){
                Suo_btn[9*j+i].SetImage(0,Suo_map.Map_Number(j,i),1,Suo_map.GetMap_Ques(j,i));
            }
        }
    }
}

void MainWindow::SetPlayer2(int level){ //Show the player2 which has been construct but hide in constructor
        for(int i=0;i<3;++i)
            BattleLevel[i].Chooselevel->hide();
        ResetMap(level);
        control_N[0]=0;
        control_N[1]=0;
        player_point[0]=100;
        player1_lcd->display(player_point[0]);
        if(player2work==false){
            ShowOrHideP2(true);
        }
        else{
            player_point[1]=100;
            player2_lcd->display(player_point[1]);
            Map2.SetRandomMap(2,level);
            for(int j=0;j<9;++j){
                for(int i=0;i<9;++i)
                    player2[9*j+i].SetImage(0,Map2.Map_Number(j,i),2,Map2.GetMap_Ques(j,i));
            }
        }

}

void MainWindow::Battle(int player,int pos,int Number){
    if(Number!=0){
        QVector<int> notPossibleChecker,Checker;
        if(player==1)
            Checker=Suo_map.CheckPossible(pos);
        else if(player==2)
            Checker=Map2.CheckPossible(pos);
        for(int i=1;i<10;++i){
            int j=0;
            bool repeat=false;
            while(repeat==false && j<Checker.size()){
                if(i==Checker[j])
                    repeat=true;
                ++j;
            }
            if(repeat==false)
                notPossibleChecker.append(i);
        }
        bool right=true;
        int i=0;
        while(i<notPossibleChecker.size()&&right==true){
            if(Number==notPossibleChecker[i]){
                player_point[player-1]-=10;
                if(player==0)
                        player_combol_1=0;
                else if(player==1)
                        player_combol_2=0;
                right=false;
            }
            ++i;
        }
        if(right==true){
            int combol;
            if(player==0){
                ++player_combol_1;
                combol=player_combol_1;
            }
            else if(player==1){
                ++player_combol_2;
                combol=player_combol_2;
            }
            switch (combol){
                case 3:
                    player_point[player-1]+=20;
                    break;
                case 5:
                    player_point[player-1]+=40;
                    break;
                case 10:
                    player_point[player-1]+=60;
                    break;
                default:
                    player_point[player-1]+=10;
                    break;
            }
        }
        if(player_point[0]>=(400)){
            Victory->setStyleSheet("QPushButton{border-image: url(:/Image/victory_r)};");
            Victory->show();
        }
        if(player_point[1]>=(400)){
            Victory->setStyleSheet("QPushButton{border-image: url(:/Image/victory_b)};");
            Victory->show();
        }
    if(player==1)
        emit Player1ChangePoint(player_point[0]);
    if(player==2)
        emit Player2ChangePoint(player_point[1]);
    }
}

void MainWindow::ShowNormalLevel(bool check){
    if(check==false){
        for(int i=0;i<3;++i){
            NormalLevel[i].Chooselevel->show();
        }
    }
}

void MainWindow::ShowBattleLevel(bool check){
    if(check==false){
        for(int i=0;i<3;++i){
            BattleLevel[i].Chooselevel->show();
        }
    }
}

void MainWindow::DesignFinish(bool check){
    if(check==false){
        DesignBtn->hide();
        if(Suo_map.isRepeat()==false)//check if the question can be solve
            messager->setStyleSheet("QPushButton{border-image: url(:/Image/ErrorMessage.png)};");
        else{
            Suo_map.map_ex=Suo_map.map_sol;
            for(int j=0;j<9;++j){
                for(int i=0;i<9;++i)
                    Suo_btn[9*j+i].SetImage(0,Suo_map.Map_Number(j,i),1,Suo_map.GetMap_Ques(j,i));
            }
        }
    }
}

void MainWindow::CloseVictory(bool check){
    if(check==false){
        Victory->hide();
        ShowOrHideP2(false);
    }
}

void MainWindow::ShowOrHideP2(bool show){
    if(show==true){
        player_point[1]=100;
        player2_lcd->display(player_point[1]);
        player_2->show();
        player1_lcd->show();
        player2_lcd->show();
        instruction2_1->show();
        instruction2_2->show();
        for(int j=0;j<9;++j){
            for(int i=0;i<9;++i)
                player2[9*j+i].Sudoku ->show();
        }
        player2work=true;
    }
    else{
        player_2->hide();
        player1_lcd->hide();
        player2_lcd->hide();
        instruction2_1->hide();
        instruction2_2->hide();
        for(int j=0;j<9;++j){
            for(int i=0;i<9;++i)
                player2[9*j+i].Sudoku ->hide();
        }
        player2work=true;
    }
}

// END
// Functions that help players to control and Input
// Start





void MainWindow::InputNumber(Map &map,SuoButton button[],int player,int pos,int N){
        if(map.GetMap_Ques(pos/9,pos%9)==0){
            //map.setMapNumber(pos,N);
            button[pos].SetImage(1,N,player,0);
            button[pos].Sudoku->released();
            button[pos].Sudoku->pressed();
            control_N[player-1]=N;
        }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //player1's controler
    if(event->key()==Qt::Key_A){
            Suo_map.setMapNumber(press_pos,0);
            Battle(1,press_pos,control_N[0]);
            Suo_map.setMapNumber(press_pos,control_N[0]);
            control_N[0]=0;
            Suo_btn[press_pos].Sudoku->released();
            do{
                if(press_pos%9!=0)
                    press_pos--;
                else
                    press_pos+=8;
            }while(Suo_map.GetMap_Ques(press_pos/9,press_pos%9)!=0);
            Suo_btn[press_pos].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_D){
            Suo_map.setMapNumber(press_pos,0);
            Battle(1,press_pos,control_N[0]);
            Suo_map.setMapNumber(press_pos,control_N[0]);
            control_N[0]=0;
            Suo_btn[press_pos].Sudoku->released();
            do{
                if(press_pos%9!=8)
                    press_pos++;
                else
                    press_pos-=8;
            }while(Suo_map.GetMap_Ques(press_pos/9,press_pos%9)!=0);
            Suo_btn[press_pos].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_W){
            Suo_map.setMapNumber(press_pos,0);
            Battle(1,press_pos,control_N[0]);
            Suo_map.setMapNumber(press_pos,control_N[0]);
            control_N[0]=0;
            Suo_btn[press_pos].Sudoku->released();
            do{
                if(press_pos/9!=0)
                    press_pos-=9;
                else
                    press_pos+=72;
            }while(Suo_map.GetMap_Ques(press_pos/9,press_pos%9)!=0);
            Suo_btn[press_pos].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_S){
            Suo_map.setMapNumber(press_pos,0);
            Battle(1,press_pos,control_N[0]);
            Suo_map.setMapNumber(press_pos,control_N[0]);
            control_N[0]=0;
            Suo_btn[press_pos].Sudoku->released();
              do{
                if(press_pos/9!=8)
                    press_pos+=9;
                else
                    press_pos-=72;
            }while(Suo_map.GetMap_Ques(press_pos/9,press_pos%9)!=0);
            Suo_btn[press_pos].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_B){
        InputNumber(Suo_map,Suo_btn,1,press_pos,1);
    }
    if(event->key()==Qt::Key_N){
        InputNumber(Suo_map,Suo_btn,1,press_pos,2);
    }
    if(event->key()==Qt::Key_M){
        InputNumber(Suo_map,Suo_btn,1,press_pos,3);
    }
    if(event->key()==Qt::Key_G){
        InputNumber(Suo_map,Suo_btn,1,press_pos,4);
    }
    if(event->key()==Qt::Key_H){
        InputNumber(Suo_map,Suo_btn,1,press_pos,5);
    }
    if(event->key()==Qt::Key_J){
        InputNumber(Suo_map,Suo_btn,1,press_pos,6);
    }
    if(event->key()==Qt::Key_T){
        InputNumber(Suo_map,Suo_btn,1,press_pos,7);
    }
    if(event->key()==Qt::Key_Y){
        InputNumber(Suo_map,Suo_btn,1,press_pos,8);
    }
    if(event->key()==Qt::Key_U){
        InputNumber(Suo_map,Suo_btn,1,press_pos,9);
    }
    if(event->key()==Qt::Key_F){
        InputNumber(Suo_map,Suo_btn,1,press_pos,0);
    }

    //player2's controler

    if(event->key()==Qt::Key_L){
            Map2.setMapNumber(press_pos_2,0);
            Battle(2,press_pos_2,control_N[1]);
            Map2.setMapNumber(press_pos_2,control_N[1]);
            control_N[1]=0;
            player2[press_pos_2].Sudoku->released();
            do{
                if(press_pos_2%9!=0)
                    press_pos_2--;
                else
                    press_pos_2+=8;
            }while(Map2.GetMap_Ques(press_pos_2/9,press_pos_2%9)!=0);
            player2[press_pos_2].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_Apostrophe){
            Map2.setMapNumber(press_pos_2,0);
            Battle(2,press_pos_2,control_N[1]);
            Map2.setMapNumber(press_pos_2,control_N[1]);
            control_N[1]=0;
            player2[press_pos_2].Sudoku->released();
            do{
                if(press_pos_2%9!=8)
                    press_pos_2++;
                else
                    press_pos_2-=8;
            }while(Map2.GetMap_Ques(press_pos_2/9,press_pos_2%9)!=0);
            player2[press_pos_2].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_P){
            Map2.setMapNumber(press_pos_2,0);
            Battle(2,press_pos_2,control_N[1]);
            Map2.setMapNumber(press_pos_2,control_N[1]);
            control_N[1]=0;
            player2[press_pos_2].Sudoku->released();
            do{
                if(press_pos_2/9!=0)
                    press_pos_2-=9;
                else
                    press_pos_2+=72;
            }while(Map2.GetMap_Ques(press_pos_2/9,press_pos_2%9)!=0);
            player2[press_pos_2].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_Semicolon){
            Map2.setMapNumber(press_pos_2,0);
            Battle(2,press_pos_2,control_N[1]);
            Map2.setMapNumber(press_pos_2,control_N[1]);
            control_N[1]=0;
            player2[press_pos_2].Sudoku->released();
              do{
                if(press_pos_2/9!=8)
                    press_pos_2+=9;
                else
                    press_pos_2-=72;
            }while(Map2.GetMap_Ques(press_pos_2/9,press_pos_2%9)!=0);
            player2[press_pos_2].Sudoku->pressed();
    }

    if(event->key()==Qt::Key_1){
        InputNumber(Map2,player2,2,press_pos_2,1);
    }
    if(event->key()==Qt::Key_2){
        InputNumber(Map2,player2,2,press_pos_2,2);
    }
    if(event->key()==Qt::Key_3){
        InputNumber(Map2,player2,2,press_pos_2,3);
    }
    if(event->key()==Qt::Key_4){
        InputNumber(Map2,player2,2,press_pos_2,4);
    }
    if(event->key()==Qt::Key_5){
        InputNumber(Map2,player2,2,press_pos_2,5);
    }
    if(event->key()==Qt::Key_6){
        InputNumber(Map2,player2,2,press_pos_2,6);
    }
    if(event->key()==Qt::Key_7){
        InputNumber(Map2,player2,2,press_pos_2,7);
    }
    if(event->key()==Qt::Key_8){
        InputNumber(Map2,player2,2,press_pos_2,8);
    }
    if(event->key()==Qt::Key_9){
        InputNumber(Map2,player2,2,press_pos_2,9);
    }
    if(event->key()==Qt::Key_0){
        InputNumber(Map2,player2,2,press_pos_2,0);
    }

}
//END

MainWindow::~MainWindow()
{
    delete ui;
}
