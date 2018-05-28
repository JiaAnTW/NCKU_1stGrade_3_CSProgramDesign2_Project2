#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <QVector>
#include <QTime>



class Map
{
    public:
        Map();
        QVector<int> map_sol,map_ex;
        void SetMap(int);
        void RandomMap_LR(int);
        void RandomMap_UD(int);
        void RandomMap_LineLR(int);
        void RandomMap_LineUD(int);
        void setMapNumber(int, int);
        int GetMap_Ques(int,int);
        int Map_Number(int,int);
        void SetQ(int);
        void SetRandomMap(int,int);
        bool CheckUnity(QVector<int> arr);
        bool isCorrect();
        int getNextBlank();
        bool isRepeat();
        QVector<int> CheckPossible(int Number);
        bool Solution(Map question,Map &answer);


    private:
        QVector<int> map_ans;
        QString data_open,data_final;


};

#endif // MAP_H
