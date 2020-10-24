#include "mainwin.h"
#include "uicolorpanel.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
menuBar::menuBar(QWidget *parent,int w,int h) : QWidget(parent)
{
    setMouseTracking(true);//设置监控鼠标滑动事件
    //建立标签表
    menuLabel=new labelOfMenuBar();
    for(int i=0;i<LABEL_TITLE_AMOUNT;i++){
        menuLabel=new labelOfMenuBar(menuLabel,labelTitle[i]);
    }
    mouseStat=edit;//初始化鼠标
    buttonPressed=0;
    buttonPressedOrder=-1;
    lineEditPageX=new QLineEdit(this);
    lineEditPageY=new QLineEdit(this);
    lineEditPageX->setValidator(new QIntValidator(1, 9999, this));//限定输入范围
    lineEditPageY->setValidator(new QIntValidator(1, 9999, this));
    labelPageXInfo=new QLabel(this);
    labelPageYInfo=new QLabel(this);
    labelPageXInfo->setText("页面宽度");
    labelPageYInfo->setText("页面高度");
    lineEditPageX->setText("999");
    lineEditPageY->setText("999");
    labelPageXInfo->move(10+(w/24+5)*BUTTON_TITLE_P2_AMOUNT+10,w/60+5+w/120);
    labelPageYInfo->move(10+(w/24+5)*BUTTON_TITLE_P2_AMOUNT+10,w/60+5+w/120+w/40);
    lineEditPageX->move(10+(w/24+5)*BUTTON_TITLE_P2_AMOUNT+10+w/24,w/60+5+w/120);
    lineEditPageY->move(10+(w/24+5)*BUTTON_TITLE_P2_AMOUNT+10+w/24,w/60+5+w/120+w/40);
    labelp2show(0);
}

void menuBar::paintEvent(QPaintEvent *e){
    int w=width();
    int h=height();
    QPainter p(this);
    p.setRenderHint(QPainter:: Antialiasing, true);//开启反锯齿
    p.setPen(QPen(QColor(0,0,0,255),-1));//设置无边框
    QBrush bkgndBrush(UI_COLOR_MENUBAR_BKGND);//存放按钮区域底色
    QBrush lbbkgndBrush(UI_COLOR_MENUBAR_LABEL_BKGND);//标签区域底色
    //开始绘制存放按钮区域的底色
    p.setBrush(bkgndBrush);
    QRect bkgndRect(5,h/5+5,w-10,h*4/5-10);
    p.drawRect(bkgndRect);
    //开始绘制标签区域的底色
    p.setBrush(lbbkgndBrush);
    QRect lbbkgndRect(5,5,w-10,h/5);
    p.drawRect(lbbkgndRect);
    //开始循环绘制所有剩下的标签
    QRect labelRect(10+h*3/5,7,h*2/5,h/5-2);
    menuLabel=menuLabel->at(1);
    int focusOn=menuLabel->focusOn();
    for(int i=1;i<=LABEL_TITLE_AMOUNT;i++){
        labelRect.moveTo(10+h*3/5+(h*2/5+5)*(i-1),7);
        if(focusOn==i){
            p.setBrush(bkgndBrush);
            p.drawRect(labelRect);
            p.setBrush(lbbkgndBrush);
            //绘制这个标签下的按钮
            switch(i){
            case 1://该分支绘制第一页按钮
                for(int j=0;j<PEN_TYPE_TITLE_AMOUNT;j++){
                    if(mouseStat==j){
                        p.drawRect(QRect(10+(h/2+5)*j,h/5+5+h/20,h/2,h*5/8));
                        p.setPen(QColor(255,255,255,255));
                        p.drawText(QRect(10+(h/2+5)*j,h*27/40+5,h/2,h/8),Qt::AlignCenter,penTypeTitle[j]);
                        p.setPen(QPen(QColor(0,0,0,255),-1));
                    }else {
                        p.drawText(QRect(10+(h/2+5)*j,h*27/40+5,h/2,h/8),Qt::AlignCenter,penTypeTitle[j]);
                    }
                }
                break;
            case 2://该分支绘制第二页按钮
                if(buttonPressed){
                    p.drawRect(QRect(10+(h/2+5)*buttonPressedOrder,h/5+5+h/20,h/2,h*5/8));
                    for(int i=0;i<BUTTON_TITLE_P2_AMOUNT;i++){
                        if(buttonPressedOrder==i){
                            p.setPen(QColor(255,255,255,255));
                            p.drawText(QRect(10+(h/2+5)*i,h*27/40+5,h/2,h/8),Qt::AlignCenter,buttonTitleP2[i]);
                            p.setPen(QPen(QColor(0,0,0,255),-1));
                        }else {
                            p.drawText(QRect(10+(h/2+5)*i,h*27/40+5,h/2,h/8),Qt::AlignCenter,buttonTitleP2[i]);
                        }
                    }
                }else {
                    for(int i=0;i<BUTTON_TITLE_P2_AMOUNT;i++)
                        p.drawText(QRect(10+(h/2+5)*i,h*27/40+5,h/2,h/8),Qt::AlignCenter,buttonTitleP2[i]);
                }
                break;
            case 3:
                if(buttonPressed){
                    p.drawRect(QRect(10,h/5+5+h/20,h/2,h*5/8));
                    p.setPen(QColor(255,255,255,255));
                    p.drawText(QRect(10,h*27/40+5,h/2,h/8),Qt::AlignCenter,"项目介绍");
                    p.setPen(QPen(QColor(0,0,0,255),-1));
                }else {
                    p.drawText(QRect(10,h*27/40+5,h/2,h/8),Qt::AlignCenter,"项目介绍");
                }
                break;
            default:
                break;
            }
            p.setBrush(lbbkgndBrush);
        }else {
            p.drawRect(labelRect);
        }
        p.drawText(labelRect,Qt::AlignCenter,menuLabel->getTitle());
        menuLabel=menuLabel->toNext();
    }
    //开始绘制CanvasO标签
    QRect cvsoRect(5,5,h*3/5,h/5);
    p.setBrush(QBrush(UI_COLOR_CANVASO_BKGND));//210,200,255
    p.drawRect(cvsoRect);
    p.setPen(QPen(QColor(255,255,255,255),-1));//设置无边框
    QFont bold;
    bold.setBold(true);
    bold.setPixelSize(h/9);
    p.setFont(bold);
    p.drawText(cvsoRect,Qt::AlignCenter,"CanvasO");
}

void menuBar::mouseMoveEvent(QMouseEvent *e){

}
void menuBar::mouseReleaseEvent(QMouseEvent *e){
    buttonPressed=0;
    buttonPressedOrder=-1;
    update();
}
void menuBar::mousePressEvent(QMouseEvent *e){
    int x=e->x();
    int y=e->y();
    int h=height();
    QString fileName;
    QRect lRect(10+h*3/5,7,h*2/5,h/5-2);
    QRect bRect(10,h/5+5+h/20,h/2,h*5/8);//x轴递增+(h/2+5)*j
    if(y<=lRect.bottom()){//该分支处理标签被点击
        for(int i=1;i<=LABEL_TITLE_AMOUNT;i++){
            if((x>=lRect.left())&&(x<=lRect.right())){
                menuLabel->setFocus(i);
                if(i==2){
                    labelp2show(1);
                }else {
                    labelp2show(0);
                }
                update();
                break;
            }else{
                lRect.moveTo(10+h*3/5+(h*2/5+5)*i,7);
            }
        }
    }else {//该分支处理按钮被点击
        switch(menuLabel->focusOn()){
        case 1://该分支处理第一页的按钮被点击
            for(int i=0;i<PEN_TYPE_TITLE_AMOUNT;i++){
                if((x>=bRect.left())&&(x<=bRect.right())){
                    mouseStat=(enum penType)i;
                    update();
                    break;
                }else {
                    bRect.moveTo(10+(h/2+5)*(i+1),h/5+5+h/20);
                }
            }
            break;
        case 2://该分支处理第二页的按钮被点击
            for(int i=0;i<BUTTON_TITLE_P2_AMOUNT;i++){
                if((x>=bRect.left())&&(x<=bRect.right())){
                    buttonPressed=1;
                    buttonPressedOrder=i;
                    switch (i) {
                    case 2:
                        fileName = QFileDialog::getOpenFileName(
                                this,
                                tr("open a file."),
                                "",
                                tr("CanvasO文件(*.cvso);;All files(*.*)"));
                        if(!fileName.isEmpty()){

                        }
                        buttonPressed=0;
                        break;
                    case 3:
                        fileName = QFileDialog::getOpenFileName(
                                this,
                                tr("open a file."),
                                "",
                                tr("CanvasO文件(*.cvso);;All files(*.*)"));
                        buttonPressed=0;
                        break;
                    case 0:
                        QMessageBox::about(NULL,"统计",
                                           QString("总共有")
                                           .append(QString::number(((mainWin*)parent())->getShape()->head()->count()-1))
                                           .append("个图形，\n当前图形是")
                                           .append(penTypeTitle[((mainWin*)parent())->getShape()->selected()->type()])
                                           .append("，\n总共有")
                                           .append(QString::number(((mainWin*)parent())->getShape()->count()))
                                           .append("个，\n这个图形的面积是：")
                                           .append(QString::number(((mainWin*)parent())->getShape()->area()))
                                );
                        buttonPressed=0;
                        break;
                    case 1:
                        if((lineEditPageX->text().toInt()==0)||(lineEditPageY->text().toInt()==0)){
                            QMessageBox::critical(NULL,"警告","不允许将画布设置为0", QMessageBox::Yes, QMessageBox::Yes);
                            buttonPressed=0;
                            lineEditPageX->setText(QString::number(((mainWin*)parent())->getCanvas()->getDocWidth()));
                            lineEditPageY->setText(QString::number(((mainWin*)parent())->getCanvas()->getDocHeight()));
                            break;
                        }
                        ((mainWin*)parent())->getCanvas()->setDocSize(lineEditPageX->text().toInt(),lineEditPageY->text().toInt());
                        ((mainWin*)parent())->getCanvas()->repaint();
                        break;
                    default:
                        break;
                    }
                    update();
                    break;
                }else {
                    bRect.moveTo(10+(h/2+5)*(i+1),h/5+5+h/20);
                }
            }
            break;
        case 3://该分支处理第三页的按钮被点击
            if((x>=bRect.left())&&(x<=bRect.right())){
                QDesktopServices::openUrl(QUrl("http://projects.liric.cn/canvaso/"));
                buttonPressed=1;
            }
                update();
            break;
        default:
            break;
        }
    }
}
//用于切换标签页时显示或隐藏p2的外置控件内容
void menuBar::labelp2show(int a){
    if(a==0){
        labelPageXInfo->hide();
        labelPageYInfo->hide();
        lineEditPageX->hide();
        lineEditPageY->hide();
    }else {
        labelPageXInfo->show();
        labelPageYInfo->show();
        lineEditPageX->show();
        lineEditPageY->show();
    }
}
