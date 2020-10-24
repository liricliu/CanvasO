#include "mainwin.h"
#include <iostream>
#include <QGuiApplication>
#include <QScreen>
mainWin::mainWin(QWidget *parent)
    : QWidget(parent)
{
    init();
    initUI();
}

mainWin::~mainWin()
{
    delete mainMenu;
    delete mainSideBar;
}

void mainWin::init(){
    shapeList=new Shape();
    /*new lineShape(10,10,10,20);
    new lineShape(10,20,30,30);
    new lineShape(10,10,30,30);
    int pX[5]={100,150,120,115,110};
    int pY[5]={100,120,150,120,120};
    new multangleShape(5,pX,pY);
    new ellipseShape(300,300,800,600);
    shapeList->selectHead();
    for(int i=0;i<5;i++){
        printf("%d %d\n",shapeList->selected()->x(),shapeList->selected()->y());
        printf("%d %d\n",shapeList->selected()->width(),shapeList->selected()->height());
                shapeList->selectNext();
    }*/
}

void mainWin::initUI(){
    setWindowTitle("CanvasO");
    setWindowState(Qt::WindowMaximized);
    //设置窗口最大与最小缩放
    fullSizeWidth=QGuiApplication::screens().at(0)->availableGeometry().width();
    fullSizeHeight=QGuiApplication::screens().at(0)->availableGeometry().height();
    minSizeWidth=fullSizeWidth/2;
    minSizeHeight=minSizeWidth*3/4;
    setMaximumSize(fullSizeWidth,fullSizeHeight);
    setMinimumSize(minSizeWidth,minSizeHeight);
    //设置顶部菜单
    mainMenu=new menuBar(this,fullSizeWidth,fullSizeHeight);
    mainMenu->move(0,0);
    //设置边栏
    mainSideBar=new sideBar(this,fullSizeWidth,fullSizeHeight);
    mainSideBar->move(0,fullSizeWidth/12);
    //设置画布
    mainCanvas=new canvas(this,fullSizeWidth,fullSizeHeight);
    mainCanvas->move(fullSizeWidth/6,fullSizeWidth/12);
}

void mainWin::resizeEvent(QResizeEvent *event){
    int w=width();
    int h=height();
    mainMenu->resize(w,fullSizeWidth/12);
    mainSideBar->resize(fullSizeWidth/6,h-fullSizeWidth/12);
    mainCanvas->resize(fullSizeWidth*5/6,fullSizeHeight*31/32-fullSizeWidth/12);
}
void mainWin::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.setBrush(QColor(160,160,160,255));
    p.setPen(QPen(QColor(0,0,0,0),-1));
    p.drawRect(QRect(0,0,width(),height()));
}
