#include "mainwin.h"

#define IS_EDIT_MODE (((x>p1x-5)&&(x<p1x+5))&&((y>p1y-5)&&(y<p1y+5)))||(((x>p2x-5)&&(x<p2x+5))&&((y>p2y-5)&&(y<p2y+5)))||(((x>p3x-5)&&(x<p3x+5))&&((y>p3y-5)&&(y<p3y+5)))||(((x>p4x-5)&&(x<p4x+5))&&((y>p4y-5)&&(y<p4y+5)))

#define GET_SHAPE_COLOR QColor(shape->color()/65536,(shape->color()/256)%256,shape->color()%256,255)
#define GET_EDGE_COLOR QColor(shape->edgeColor()/65536,(shape->edgeColor()/256)%256,shape->edgeColor()%256,255)

canvas::canvas(QWidget *parent,int w,int h) : QWidget(parent)
{
    int TempX;
    heightOfFrame=h*31/32-w/12-5;
    widthOfFrame=w*5/6-5;
    widthOfDocument=999;
    heightOfDocument=999;
    TempX=(widthOfDocument*heightOfFrame)/heightOfDocument;
    if(TempX>widthOfFrame){
        heightOfCanvas=(heightOfDocument*widthOfFrame)/widthOfDocument;
        widthOfCanvas=widthOfFrame;
    }else {
        widthOfCanvas=TempX;
        heightOfCanvas=heightOfFrame;
    }
    lastMouseX=0;
    lastMouseY=0;
    mouseMoving=0;
    status=STAT_READY;
    doubleClicked=0;
}
void canvas::paintEvent(QPaintEvent *e){
    Shape* shape=((mainWin*)parent())->getShape()->head();
    int amount=shape->count();
    QPainter p(this);
    p.setRenderHint(QPainter:: Antialiasing, true);
    p.setBrush(QColor(255,255,255,255));
    p.setPen(QPen(QColor(0,0,0,255),2));
    p.drawRect(QRect(0,0,widthOfCanvas,heightOfCanvas));
    for(int i=0;i<amount-1;i++){//amount-1为除了head之外的数量
        shape=shape->getNext();
        p.setPen(QPen(GET_EDGE_COLOR,shape->getEdgeWidth()));
        p.setBrush(GET_SHAPE_COLOR);
        p.translate(toCanvasSize(shape->x()+shape->width()/2),toCanvasSize(shape->y()+shape->height()/2));
        p.rotate(shape->getRotateDeg());
        p.translate(-toCanvasSize(shape->x()+shape->width()/2),-toCanvasSize(shape->y()+shape->height()/2));
        switch (shape->type()) {
        case SHAPE_LINE:
            p.drawLine(QLine(toCanvasSize(((lineShape*)shape)->p1x()),
                             toCanvasSize(((lineShape*)shape)->p1y()),
                             toCanvasSize(((lineShape*)shape)->p2x()),
                             toCanvasSize(((lineShape*)shape)->p2y())));
            break;
        case SHAPE_LINES:
            for(int j=0;j<((linesShape*)shape)->getPointNum()-1;j++)
                p.drawLine(QLine(toCanvasSize((((linesShape*)shape)->pX())[j]),
                                 toCanvasSize((((linesShape*)shape)->pY())[j]),
                                 toCanvasSize((((linesShape*)shape)->pX())[j+1]),
                                 toCanvasSize((((linesShape*)shape)->pY())[j+1])));
            break;
        case SHAPE_MULTANGLE:
            QPoint* pointToDraw;
            pointToDraw=new QPoint[((multangleShape*)shape)->getPointNum()];

            for(int j=0;j<((multangleShape*)shape)->getPointNum();j++){
                (pointToDraw[j]).setX(toCanvasSize((((multangleShape*)shape)->pX())[j]));
                (pointToDraw[j]).setY(toCanvasSize((((multangleShape*)shape)->pY())[j]));
            }
            p.drawPolygon(pointToDraw,((multangleShape*)shape)->getPointNum());
            delete [] pointToDraw;
            break;
        case SHAPE_RECTANGLE:
        case SHAPE_SQUARE:
            p.drawRect(QRect(toCanvasSize(shape->x()),
                             toCanvasSize(shape->y()),
                             toCanvasSize(shape->width()),
                             toCanvasSize(shape->height())));
            break;
        case SHAPE_CIRCLE:
        case SHAPE_ELLIPSE:
            p.drawEllipse(QRect(toCanvasSize(shape->x()),
                                toCanvasSize(shape->y()),
                                toCanvasSize(shape->width()),
                                toCanvasSize(shape->height())));
            break;
        default:
            break;
        }
        p.resetTransform();
        //p.rotate(-shape->getRotateDeg());
        //p.translate(-toCanvasSize(shape->x()),-toCanvasSize(shape->y()));
    }
    p.setBrush(QColor(0,0,0,0));
    QPen minRectPen;
    minRectPen.setColor(QColor(100,100,100));
    minRectPen.setStyle(Qt::DashDotLine);
    p.setPen(minRectPen);
    p.drawRect(QRect(toCanvasSize(shape->selected()->x()),
                     toCanvasSize(shape->selected()->y()),
                     toCanvasSize(shape->selected()->width()),
                     toCanvasSize(shape->selected()->height())));
    if(mouseMoving==1){
        switch (status) {
        case STAT_EDITING:
            p.drawRect(QRect(toCanvasSize(shape->selected()->x()),
                             toCanvasSize(shape->selected()->y()),
                             movingMouseX-toCanvasSize(shape->selected()->x()),
                             movingMouseY-toCanvasSize(shape->selected()->y())));
            break;
        case STAT_DRAGING:
            p.drawRect(QRect(toCanvasSize(shape->selected()->x())+movingMouseX-lastMouseX,
                             toCanvasSize(shape->selected()->y())+movingMouseY-lastMouseY,
                             toCanvasSize(shape->selected()->width()),
                             toCanvasSize(shape->selected()->height())));
            break;
        case STAT_DRAWING:
            p.drawRect(QRect(lastMouseX,lastMouseY,movingMouseX-lastMouseX,movingMouseY-lastMouseY));
            break;
        default:
            break;
        }
    }
}
void canvas::mouseReleaseEvent(QMouseEvent *e){
    menuBar* menu=((mainWin*)parent())->getMenu();
    Shape* shape=((mainWin*)parent())->getShape();
    sideBar* sidebar=((mainWin*)parent())->getSideBar();
    penType mouseStat=menu->getPenType();
    int x=e->x();
    int y=e->y();
    int toDocMouseX=toDocumentSize(x);
    int toDocMouseY=toDocumentSize(y);
    int toDocLastMouseX=toDocumentSize(lastMouseX);
    int toDocLastMouseY=toDocumentSize(lastMouseY);
    mouseMoving=0;
    switch (status) {
    case STAT_READY:
        break;
    case STAT_DRAGING://处理拖拽
        shape->move(toDocMouseX-toDocLastMouseX,toDocMouseY-toDocLastMouseY);
        status=STAT_READY;
        break;
    case STAT_EDITING://处理变形
            status=STAT_READY;
        shape->transShape(toDocMouseX-toDocLastMouseX,toDocMouseY-toDocLastMouseY,
                          ((shape->y()+shape->height()-toDocLastMouseY)<(toDocLastMouseY-shape->y()))
                          +2*((shape->x()+shape->width()-toDocLastMouseX)<(toDocLastMouseX-shape->x())));
        status=STAT_READY;
        break;
    case STAT_DRAWING://处理绘制的第一段
        switch (mouseStat) {
        case line:
            new lineShape(toDocLastMouseX,toDocLastMouseY,toDocMouseX,toDocMouseY);
            status=STAT_READY;
            break;
        case multiLine:
        case poly:
            headPointToDraw=new pointList;
            currentPoint=new pointList;
            headPointToDraw->next=currentPoint;
            currentPoint->next=nullptr;
            pointAmount=2;
            headPointToDraw->x=toDocLastMouseX;
            headPointToDraw->y=toDocLastMouseY;
            currentPoint->x=toDocMouseX;
            currentPoint->y=toDocMouseY;
            status=STAT_DRAWING_MULI;
            break;
        case square:
            new squareShape(toDocLastMouseX,toDocLastMouseY,toDocMouseX,toDocMouseY);
            status=STAT_READY;
            break;
        case rectangle:
            new rectangleShape(toDocLastMouseX,toDocLastMouseY,toDocMouseX,toDocMouseY);
            status=STAT_READY;
            break;
        case circle:
            new circleShape(toDocLastMouseX,toDocLastMouseY,toDocMouseX,toDocMouseY);
            status=STAT_READY;
            break;
        case ellipse:
            new ellipseShape(toDocLastMouseX,toDocLastMouseY,toDocMouseX,toDocMouseY);
            status=STAT_READY;
            break;
        default:
            status=STAT_READY;
        }
        break;
    case STAT_DRAWING_MULI:
        //两个分支，一个处理继续绘制，一个处理结束绘制
        if(doubleClicked==1){
            int *xx,*yy;
            xx=new int[pointAmount];
            yy=new int[pointAmount];
            currentPoint=headPointToDraw;
            for(int i=0;i<pointAmount;i++){
                xx[i]=currentPoint->x;
                yy[i]=currentPoint->y;
                currentPoint=currentPoint->next;
            }
            if(mouseStat==multiLine){
                new linesShape(pointAmount,xx,yy);
                sidebar->updateDataInLineEdit();
            }else {
                if(mouseStat==poly){
                    new multangleShape(pointAmount,xx,yy);
                    sidebar->updateDataInLineEdit();
                }
            }
            delete [] xx;
            delete [] yy;
            currentPoint=headPointToDraw;
            pointList* p;
            for(int i=0;i<pointAmount;i++){
                p=currentPoint->next;
                delete currentPoint;
                currentPoint=p;
            }
            status=STAT_READY;
        }else {
            currentPoint->next=new pointList;
            currentPoint=currentPoint->next;
            currentPoint->x=toDocMouseX;
            currentPoint->y=toDocMouseY;
            currentPoint->next=nullptr;
            pointAmount++;
        }
        break;
    default:
        status=STAT_READY;
    }
    repaint();
    if((mouseStat!=multiLine)&&(mouseStat!=poly)){
        sidebar->updateDataInLineEdit();
        menu->toEdit();
    }else {
        if(doubleClicked==1)
            menu->toEdit();
    }
    doubleClicked=0;
}
void canvas::mousePressEvent(QMouseEvent *e){
    menuBar* menu=((mainWin*)parent())->getMenu();
    Shape* shape=((mainWin*)parent())->getShape();
    penType mouseStat=menu->getPenType();
    int x=e->x();
    int y=e->y();
    int p1x=toCanvasSize(shape->x());
    int p1y=toCanvasSize(shape->y());
    int p2x=p1x;
    int p2y=p1y+toCanvasSize(shape->height());
    int p3x=p1x+toCanvasSize(shape->width());
    int p3y=p1y;
    int p4x=p3x;
    int p4y=p2y;
    //p1    p3
    //p2    p4
    lastMouseX=x;
    lastMouseY=y;
    switch (status) {
    case STAT_READY:
        if(mouseStat==edit){//该分支处理编辑模式
            //先判断是拖拽还是变形
            if(IS_EDIT_MODE){
                printf("%d %d %d %d\n",p4x,p4y,x,y);
                status=STAT_EDITING;
            }else {
                printf("%d %d %d %d\n",p4x,p4y,x,y);
                status=STAT_DRAGING;
            }
        }else {//该分支处理绘制新图形模式
            status=STAT_DRAWING;
        }
        break;
    case STAT_DRAWING_MULI://什么都不用做
        break;
    case STAT_DRAWING:
    case STAT_EDITING:
    case STAT_DRAGING:
    default:
        status=STAT_READY;
        break;
    }
}
void canvas::mouseDoubleClickEvent(QMouseEvent *event){
    int x=event->x();
    int y=event->y();
    lastMouseX=x;
    lastMouseY=y;
    doubleClicked=1;
}
void canvas::mouseMoveEvent(QMouseEvent *e){
    mouseMoving=1;
    movingMouseX=e->x();
    movingMouseY=e->y();
    update();
}
