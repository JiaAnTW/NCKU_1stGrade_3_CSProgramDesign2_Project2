#include "mainwindow.h"
#include "map.h"
#include <QImage>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Project2_Sudoku");
    w.setGeometry(0,0,1500,800);
    w.setStyleSheet("QWidget{border-image: url(:/Image/BackGround.png)};");
    w.show();


    return a.exec();
}
