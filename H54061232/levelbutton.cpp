#include "levelbutton.h"

levelbutton::levelbutton()
{

}

void levelbutton::SetLevel(int recieve){
    level=recieve;
    switch (level) {
        case 1:
            Chooselevel->setStyleSheet("QPushButton{border-image: url(:/Image/level_easy)};");
            Chooselevel->setGeometry(1325,550,100,70);
            break;
        case 2:
            Chooselevel->setGeometry(1325,630,100,70);
            Chooselevel->setStyleSheet("QPushButton{border-image: url(:/Image/level_medium)};");
            break;
        case 3:
            Chooselevel->setGeometry(1325,710,100,70);
            Chooselevel->setStyleSheet("QPushButton{border-image: url(:/Image/level_hard)};");
            break;

        default:
            break;
    }
}

void levelbutton::ReciveLevel(bool check){
    if(check==false){
        emit ReturnLevelMode(level);
    }
}
