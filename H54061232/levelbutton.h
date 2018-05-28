#ifndef LEVELBUTTON_H
#define LEVELBUTTON_H
#include <QPushButton>

class levelbutton:public QObject
{
    Q_OBJECT

public:
    levelbutton();
    void SetLevel(int);
    QPushButton *Chooselevel;

public slots:
    void ReciveLevel(bool);

signals:
    void ReturnLevelMode(int);


private:
    int level;
};

#endif // LEVELBUTTON_H
