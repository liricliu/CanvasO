#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QResizeEvent>
#include "menubar.h"
#include "sidebar.h"
#include "canvas.h"
#include "shape.h"
class mainWin : public QWidget
{
    Q_OBJECT
private:
    void init();
    void initUI();
    void resizeEvent(QResizeEvent* e);
    void paintEvent(QPaintEvent* e);
    int fullSizeWidth;
    int fullSizeHeight;
    int minSizeWidth;
    int minSizeHeight;
    menuBar* mainMenu;
    sideBar* mainSideBar;
    canvas* mainCanvas;
    Shape* shapeList;
public:
    mainWin(QWidget *parent = 0);
    inline canvas* getCanvas(){return mainCanvas;}
    inline sideBar* getSideBar(){return  mainSideBar;}
    inline menuBar* getMenu(){return mainMenu;}
    inline Shape* getShape(){return shapeList->selected();}
    ~mainWin();
};

#endif // MAINWIN_H
