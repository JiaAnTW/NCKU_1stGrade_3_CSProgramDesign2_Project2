#include "map.h"

Map::Map()
{
   for(int i=0;i<81;i++){
       map_ans.append(0);//initilze map_ans
   }
 }

void Map::SetMap(int Map_N){ //include the base question, use map_ex to set map_ans
        map_ex.clear();
        QString address_map = ":/Suo_Map/Map_";
        address_map.append(QString::number(Map_N));
        address_map.append(".txt");
        const QString address = address_map;
        QFile OpenMap(address);
        OpenMap.open(QIODevice::ReadOnly);
        int i=0;
        while(!OpenMap.atEnd()){
           data_open=OpenMap.readLine();
           for(int j=0;j<9;j++){
                   data_final=data_open[2*j];
                   map_ex.append(data_final.toInt());
                   map_ans[9*i+j]=map_ex.at(9*i+j);
            }
            i++;
        }
        OpenMap.close();
}

void Map::RandomMap_LR(int Do){
    if(Do==1){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;++j){
                if(j==4)
                    map_ans[9*i+j]=map_ex.at(9*i+j);
                else
                    map_ans[9*(i+1)-j-1]=map_ex.at(9*i+j);
            }
        }
    }
}

void Map::RandomMap_UD(int Do){
    if(Do==1){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;++j){
                if(i==4)
                    map_ans[9*i+j]=map_ex.at(9*i+j);
                else
                    map_ans[(9*i+j)-((i-4)*2*9)]=map_ex.at(9*i+j);

            }
        }
    }
}

void Map::RandomMap_LineLR(int Do){
    if(Do==1){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;++j){
                    map_ans[9*j+i]=map_ex.at(9*i+j);

            }
        }
    }
}

void Map::RandomMap_LineUD(int Do){
    if(Do==1){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;++j){
                    map_ans[9*(8-j)+8-i]=map_ex.at(9*i+j);
            }
        }
    }
}
void Map::setMapNumber(int pos, int Number){
    map_sol[pos]=Number;
}

int Map::GetMap_Ques(int y, int x){
    return map_ex.at(9*y+x);
}

int Map::Map_Number(int y, int x){
    return map_sol.at(9*y+x);
}

void Map::SetQ(int level){
    int blank;
    srand(time(NULL));
    map_sol=map_ans;
    switch (level) {
    case 3:
        map_sol.clear();
        for(int i=0;i<81;++i)
            map_sol.append(0);
        for(int i=0;i<9;++i){
            for(int j=0;j<3;++j){
                blank=rand()%3;
                setMapNumber(i*9+3*j+blank,map_ans[i*9+3*j+blank]);
            }
        }
        break;
    case 2:
        for(int i=0;i<79;i+=2){
                blank=rand()%2;
                setMapNumber(i+blank,0);
        }

        break;

    default:
        for(int i=0;i<9;++i){
            for(int j=0;j<3;++j){
                blank=rand()%3;
                setMapNumber(i*9+3*j+blank,0);
            }
        }
        break;
    }



    map_ex=map_sol;
}

void Map::SetRandomMap(int player,int level){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if(player==1)
        SetMap(qrand()%5+1);
    else
        SetMap(qrand()%5+6);
    RandomMap_LR(qrand()%2);
    RandomMap_UD(qrand()%2);
    RandomMap_LineUD(qrand()%2);
    RandomMap_LineLR(qrand()%2);
    SetQ(level);
}

bool Map::CheckUnity(QVector<int> arr){
    int arr_unity[9]={0,0,0,0,0,0,0,0};
    for(int i=0;i<9;++i)
        ++arr_unity[arr[i]-1];//if N has been written, arr_unity[N-1]=1
    for(int i=0;i<9;++i)
        if(arr_unity[i]!=1){
            return false;
        }

    return true;
}

bool Map::isRepeat()
{
    int check_arr[9];
    int location;
    for(int i=0; i<81; i+=9)    // check rows
    {
        int arr_unity[9]={0,0,0,0,0,0,0,0};
        for(int j=0; j<9; ++j)
           check_arr[j] = map_sol[i+j];
        for(int j=0;j<9;++j){
            if(check_arr[j]!=0)
                ++arr_unity[check_arr[j]-1];
        }
        for(int j=0;j<9;++j){
            if(arr_unity[j]>1)
                return false;
        }

    }

    for(int i=0; i<9; ++i)   // check columns
    {
        int arr_unity[9]={0,0,0,0,0,0,0,0};
        for(int j=0; j<9; ++j)
            check_arr[j] = map_sol[i+9*j];
        for(int j=0;j<9;++j){
            if(check_arr[j]!=0)
                ++arr_unity[check_arr[j]-1];
        }
        for(int j=0;j<9;++j){
            if(arr_unity[j]>1)
                return false;
        }

    }
    for(int i=0; i<9; ++i)   // check cells
    {
        int arr_unity[9]={0,0,0,0,0,0,0,0};
        for(int j=0; j<9; ++j)
        {
            location = 27*(i/3) + 3*(i%3) +9*(j/3) + (j%3);
            check_arr[j] = map_sol[location];
        }
        for(int j=0;j<9;++j){
            if(check_arr[j]!=0)
                ++arr_unity[check_arr[j]-1];
        }
        for(int j=0;j<9;++j){
            if(arr_unity[j]>1)
                return false;
        }

    }
    return true;
}

int Map::getNextBlank(){
    for(int i=0;i<81;++i){
        if(map_sol[i]==0){
            return i;
        }
    }
    return -1;
}

bool Map::isCorrect()
{
    bool check_result;
    QVector<int> check_arr(9);
    int location;
    for(int i=0; i<81; i+=9)    // check rows
    {
        for(int j=0; j<9; ++j)
           check_arr[j] = map_sol[i+j];
        check_result = CheckUnity(check_arr);
        if(check_result == false){
            return false;
        }
    }
    for(int i=0; i<9; ++i)   // check columns
    {
        for(int j=0; j<9; ++j)
            check_arr[j] = map_sol[i+9*j];
        check_result = CheckUnity(check_arr);
        if(check_result == false){
            return false;
        }
    }
    for(int i=0; i<9; ++i)   // check cells
    {
        for(int j=0; j<9; ++j)
        {
            location = 27*(i/3) + 3*(i%3) +9*(j/3) + (j%3);
            check_arr[j] = map_sol[location];
        }
        check_result = CheckUnity(check_arr);
        if(check_result == false){
            return false;
        }
    }
    return true;
}


QVector<int> Map::CheckPossible(int Number){
    QVector<int> Maybe;
    int check_arr[9];
    int arr_unity[9]={0,0,0,0,0,0,0,0};
    int location;
    for(int j=0; j<9; ++j){// check rows
           check_arr[j] = map_sol[Number/9*9+j];
           if(check_arr[j]!=0){
                ++arr_unity[check_arr[j]-1];
           }
    }


    for(int j=0; j<9; ++j){// check columns
            check_arr[j] = map_sol[Number%9+9*j];
            if(check_arr[j]!=0){
                 ++arr_unity[check_arr[j]-1];
            }
     }

    for(int j=0; j<9; ++j)
        {
            location = 27*(Number/9/3) + 3*(Number%9/3) +9*(j/3) + (j%3);

            check_arr[j] = map_sol[location];
            if(check_arr[j]!=0){
                 ++arr_unity[check_arr[j]-1];
            }
     }

    for(int i=0;i<9;i++){
        int number=i+1;
        if(arr_unity[i]==0){
            Maybe.append(number);
        }
    }
    return Maybe;
}


bool Map::Solution(Map question,Map &answer){
    int FirstBlank;
    QVector<int> Possible;
    FirstBlank=question.getNextBlank();
    if(FirstBlank==-1){
        if(question.isCorrect())
        {
            answer=question;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        Possible=question.CheckPossible(FirstBlank);
        for(int i=0;i<Possible.size();++i){
                question.setMapNumber(FirstBlank,Possible[i]);
                if(Solution(question,answer))
                    return true;
        }
        return false;
    }
}


