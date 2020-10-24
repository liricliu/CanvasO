#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#define STAT_READY 0
#define STAT_DRAWING 1
#define STAT_DRAGING 2
#define STAT_DRAWING_MULI 3
#define STAT_EDITING 4
struct pointList{
    int x;
    int y;
    pointList* next;
};
class canvas : public QWidget
{
    Q_OBJECT
    void paintEvent(QPaintEvent* e);
    int widthOfFrame;
    int heightOfFrame;
    int widthOfCanvas;
    int heightOfCanvas;
    int widthOfDocument;
    int heightOfDocument;
    int scalingK;
    int status;
    int mouseMoving;
    int lastMouseX;
    int lastMouseY;
    int movingMouseX;
    int movingMouseY;
    pointList* headPointToDraw;
    pointList* currentPoint;
    int pointAmount;
    int doubleClicked;
    void mouseReleaseEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* e);
    int toCanvasSize(int a){return a*widthOfCanvas/widthOfDocument;}
    int toDocumentSize(int a){return a*widthOfDocument/widthOfCanvas;}
    public:
    explicit canvas(QWidget *parent = nullptr,int w=0,int h=0);
    inline void setDocSize(int a,int b){
        widthOfDocument=a;
        heightOfDocument=b;
        int TempX=(widthOfDocument*heightOfFrame)/heightOfDocument;
        if(TempX>widthOfFrame){
            heightOfCanvas=(heightOfDocument*widthOfFrame)/widthOfDocument;
            widthOfCanvas=widthOfFrame;
        }else {
            widthOfCanvas=TempX;
            heightOfCanvas=heightOfFrame;
        }
    }
    inline int getDocWidth(){return widthOfDocument;}
    inline int getDocHeight(){return heightOfDocument;}
signals:

public slots:
};

#endif // CANVAS_H
