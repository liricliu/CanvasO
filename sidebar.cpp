#include "mainwin.h"

sideBar::sideBar(QWidget *parent,int w,int h) : QWidget(parent)
{
    w=w/6;//获取sideBar宽度
    //新建控件
    lineEditWidth=new QLineEdit(this);
    lineEditHeight=new QLineEdit(this);
    lineEditColorR=new QLineEdit(this);
    lineEditColorG=new QLineEdit(this);
    lineEditColorB=new QLineEdit(this);
    lineEditEdgeColorR=new QLineEdit(this);
    lineEditEdgeColorG=new QLineEdit(this);
    lineEditEdgeColorB=new QLineEdit(this);
    lineEditEdgeWidth=new QLineEdit(this);
    lineEditRotateDeg=new QLineEdit(this);
    buttonLayerUp=new QPushButton(this);
    buttonLayerDown=new QPushButton(this);
    buttonSelectUpstair=new QPushButton(this);
    buttonSelectDownstair=new QPushButton(this);
    buttonDelete=new QPushButton(this);
    //设置编辑栏位置
    lineEditWidth->setGeometry(w/2,(w+20)*2/10+8,w*5/12,w/12);
    lineEditHeight->setGeometry(w/2,(w+20)*3/10+8,w*5/12,w/12);
    lineEditColorR->setGeometry(w/2,(w+20)*4/10+8,w/8,w/12);
    lineEditColorG->setGeometry(w/2+35,(w+20)*4/10+8,w/8,w/12);
    lineEditColorB->setGeometry(w/2+70,(w+20)*4/10+8,w/8,w/12);
    lineEditEdgeColorR->setGeometry(w/2,(w+20)*5/10+8,w/8,w/12);
    lineEditEdgeColorG->setGeometry(w/2+35,(w+20)*5/10+8,w/8,w/12);
    lineEditEdgeColorB->setGeometry(w/2+70,(w+20)*5/10+8,w/8,w/12);
    lineEditEdgeWidth->setGeometry(w/2,(w+20)*6/10+8,w*5/12,w/12);
    lineEditRotateDeg->setGeometry(w/2,(w+20)*7/10+8,w*5/12,w/12);
    //设置编辑栏内容过滤
    lineEditWidth->setValidator(new QIntValidator(0, 9999, this));
    lineEditHeight->setValidator(new QIntValidator(0, 9999, this));
    lineEditColorR->setValidator(new QIntValidator(0, 999, this));
    lineEditColorG->setValidator(new QIntValidator(0, 999, this));
    lineEditColorB->setValidator(new QIntValidator(0, 999, this));
    lineEditEdgeColorR->setValidator(new QIntValidator(0, 999, this));
    lineEditEdgeColorG->setValidator(new QIntValidator(0, 999, this));
    lineEditEdgeColorB->setValidator(new QIntValidator(0, 999, this));
    lineEditEdgeWidth->setValidator(new QIntValidator(0, 99, this));
    lineEditRotateDeg->setValidator(new QIntValidator(0, 999, this));
    //设置按钮
    buttonLayerUp->move(w/10,(w+20)*9/10+8);
    buttonLayerDown->move(w/2,(w+20)*9/10+8);
    buttonSelectUpstair->move(w/10,(w+20)+8);
    buttonSelectDownstair->move(w/2,(w+20)+8);
    buttonDelete->move(w/10,(w+20)*11/10+8);
    buttonLayerUp->setText("上移图层");
    buttonLayerDown->setText("下移图层");
    buttonSelectUpstair->setText("选择上层");
    buttonSelectDownstair->setText("选择下层");
    buttonDelete->setText("删除图形");
    //连接lineEdit的回车信号
    connect(lineEditWidth,&QLineEdit::returnPressed,this,&sideBar::editWidth);
    connect(lineEditHeight,&QLineEdit::returnPressed,this,&sideBar::editHeight);
    connect(lineEditColorR,&QLineEdit::returnPressed,this,&sideBar::editColorR);
    connect(lineEditColorG,&QLineEdit::returnPressed,this,&sideBar::editColorG);
    connect(lineEditColorB,&QLineEdit::returnPressed,this,&sideBar::editColorB);
    connect(lineEditEdgeColorR,&QLineEdit::returnPressed,this,&sideBar::editEdgeColorR);
    connect(lineEditEdgeColorG,&QLineEdit::returnPressed,this,&sideBar::editEdgeColorG);
    connect(lineEditEdgeColorB,&QLineEdit::returnPressed,this,&sideBar::editEdgeColorB);
    connect(lineEditEdgeWidth,&QLineEdit::returnPressed,this,&sideBar::editEdgeWidth);
    connect(lineEditRotateDeg,&QLineEdit::returnPressed,this,&sideBar::editRotateDeg);
    //连接按钮的被点击信号
    connect(buttonLayerUp,&QPushButton::clicked,this,&sideBar::moveLayerUp);
    connect(buttonLayerDown,&QPushButton::clicked,this,&sideBar::moveLayerDown);
    connect(buttonSelectUpstair,&QPushButton::clicked,this,&sideBar::selectUpLayer);
    connect(buttonSelectDownstair,&QPushButton::clicked,this,&sideBar::selectDownLayer);
    connect(buttonDelete,&QPushButton::clicked,this,&sideBar::deleteShape);
    updateDataInLineEdit();
}
void sideBar::paintEvent(QPaintEvent *e){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    QPainter p(this);
    QRect sideBarNameRect(5,0,width()-10,width()/10);
    //绘制边栏底色
    p.setBrush(UI_COLOR_MENUBAR_BKGND);
    p.setPen(QPen(Qt::black,-1));
    p.drawRect(QRect(5,0,width()-10,height()));
    p.setBrush(UI_COLOR_MENUBAR_LABEL_BKGND);
    p.drawRect(sideBarNameRect);
    p.drawText(sideBarNameRect,Qt::AlignCenter,"属性编辑");
    //绘制label
    p.drawText(QRect(20,(width()+20)/10+10,width()-10,width()/10),Qt::AlignLeft,QString("图形ID: ").append(QString::number(selectedShape->getID())));
    p.drawText(QRect(20,(width()+20)*2/10+10,width()-10,width()/10),Qt::AlignLeft,"横向最大宽度");
    p.drawText(QRect(20,(width()+20)*3/10+10,width()-10,width()/10),Qt::AlignLeft,"纵向最大宽度");
    p.drawText(QRect(20,(width()+20)*4/10+10,width()-10,width()/10),Qt::AlignLeft,"填充色(R:G:B)");
    p.drawText(QRect(20,(width()+20)*5/10+10,width()-10,width()/10),Qt::AlignLeft,"边框颜色(R:G:B)");
    p.drawText(QRect(20,(width()+20)*6/10+10,width()-10,width()/10),Qt::AlignLeft,"边框宽度");
    p.drawText(QRect(20,(width()+20)*7/10+10,width()-10,width()/10),Qt::AlignLeft,"顺时针旋转角");
    p.drawText(QRect(20,(width()+20)*8/10+10,width()-10,width()/10),Qt::AlignLeft,QString("所在图层: ").append(QString::number(selectedShape->layerOrder())));
}

void sideBar::editWidth(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int widthNow=selectedShape->width();
    selectedShape->transShape(lineEditWidth->text().toInt()-widthNow,0,3);
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editHeight(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int heightNow=selectedShape->height();
    selectedShape->transShape(0,lineEditHeight->text().toInt()-heightNow,3);
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editColorR(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int now=selectedShape->color()/65536;
    if(lineEditColorR->text().toInt()>255){
        lineEditColorR->setText(QString::number(now));
    }
    else {
        selectedShape->setColor(lineEditColorR->text().toInt(),-1,-1);
    }
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editColorG(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int now=(selectedShape->color()/256)%256;
    if(lineEditColorG->text().toInt()>255){
        lineEditColorG->setText(QString::number(now));
    }
    else {
        selectedShape->setColor(-1,lineEditColorG->text().toInt(),-1);
    }
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editColorB(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int now=selectedShape->color()%256;
    if(lineEditColorB->text().toInt()>255){
        lineEditColorB->setText(QString::number(now));
    }
    else {
        selectedShape->setColor(-1,-1,lineEditColorB->text().toInt());
    }
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editEdgeColorR(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int now=selectedShape->edgeColor()/65536;
    if(lineEditEdgeColorR->text().toInt()>255){
        lineEditEdgeColorR->setText(QString::number(now));
    }
    else {
        selectedShape->setEdgeColor(lineEditEdgeColorR->text().toInt(),-1,-1);
    }
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editEdgeColorG(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int now=(selectedShape->edgeColor()/256)%256;
    if(lineEditEdgeColorG->text().toInt()>255){
        lineEditEdgeColorG->setText(QString::number(now));
    }
    else {
        selectedShape->setEdgeColor(-1,lineEditEdgeColorG->text().toInt(),-1);
    }
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editEdgeColorB(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int now=selectedShape->edgeColor()%256;
    if(lineEditEdgeColorB->text().toInt()>255){
        lineEditEdgeColorB->setText(QString::number(now));
    }
    else {
        selectedShape->setEdgeColor(-1,-1,lineEditEdgeColorB->text().toInt());
    }
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editEdgeWidth(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    selectedShape->setEdgeWidth(lineEditEdgeWidth->text().toInt());
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::editRotateDeg(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    int degNow=selectedShape->getRotateDeg();
    if(lineEditRotateDeg->text().toInt()>359){
        lineEditRotateDeg->setText(QString::number(degNow));
    }else {
        selectedShape->rotate(lineEditRotateDeg->text().toInt());
    }
    ((mainWin*)parent())->getCanvas()->update();
}
void sideBar::moveLayerUp(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    selectedShape->layerUp();
    ((mainWin*)parent())->getCanvas()->repaint();
    repaint();
}
void sideBar::moveLayerDown(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    selectedShape->layerDown();
    ((mainWin*)parent())->getCanvas()->repaint();
    repaint();
}
void sideBar::selectUpLayer(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    selectedShape->selectNext();
    ((mainWin*)parent())->getCanvas()->repaint();
    updateDataInLineEdit();
    repaint();
}
void sideBar::selectDownLayer(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    selectedShape->selectLast();
    ((mainWin*)parent())->getCanvas()->repaint();
    updateDataInLineEdit();
    repaint();
}
void sideBar::deleteShape(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    if(selectedShape==selectedShape->head())
        return;
    selectedShape->del();
    delete selectedShape;
    ((mainWin*)parent())->getCanvas()->repaint();
    repaint();
}
void sideBar::updateDataInLineEdit(){
    Shape* selectedShape=((mainWin*)parent())->getShape();
    lineEditWidth->setText(QString::number(selectedShape->width()));
    lineEditHeight->setText(QString::number(selectedShape->height()));
    lineEditColorR->setText(QString::number(selectedShape->color()/65536));
    lineEditColorG->setText(QString::number((selectedShape->color()/256)%256));
    lineEditColorB->setText(QString::number(selectedShape->color()%256));
    lineEditEdgeColorR->setText(QString::number(selectedShape->edgeColor()/65536));
    lineEditEdgeColorG->setText(QString::number((selectedShape->edgeColor()/256)%256));
    lineEditEdgeColorB->setText(QString::number(selectedShape->edgeColor()%256));
    lineEditEdgeWidth->setText(QString::number(selectedShape->getEdgeWidth()));
    lineEditRotateDeg->setText(QString::number(selectedShape->getRotateDeg()));
    update();
}
