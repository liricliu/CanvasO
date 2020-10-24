#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#define LABEL_TITLE_SET "绘制","稿件","关于"  //修改此宏时须检查与LABEL_TITLE_AMOUNT是否对应
#define LABEL_TITLE_AMOUNT 3                //此宏应当随着LABEL_TITLE_SET的改变而改变
#define PEN_TYPE_TITLE_SET "编辑","线段","折线","多边形","正方形","长方形","圆形","椭圆"
#define PEN_TYPE_TITLE_AMOUNT 8
//#define BUTTON_TITLE_P2_SET "打开文件","保存文件","统计","应用更改"
//#define BUTTON_TITLE_P2_AMOUNT 4
#define BUTTON_TITLE_P2_SET "统计","应用更改"
#define BUTTON_TITLE_P2_AMOUNT 2

enum penType{
    edit,line,multiLine,poly,square,rectangle,circle,ellipse
};

class menuBar : public QWidget
{
    Q_OBJECT
private:
    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    //以下为MenuBar上的标签页列表链表节点，我都觉得自己很搞笑，干嘛非要搞个类出来
    class labelOfMenuBar{
    private:
        const char* title;
        const int turn;
        labelOfMenuBar* const head;
        labelOfMenuBar* next;
        int focus;//第一个标签的focus是1
        void add(labelOfMenuBar* n){next=n;}//将新建的节点添加到尾部
    public:
        labelOfMenuBar():title("CanvasO"),turn(0),head(this),next(nullptr),focus(1){}//新建头部节点
        labelOfMenuBar(labelOfMenuBar* last,const char* b):title(b),turn(last->getTurn()+1),head(last->at(0)),next(nullptr){last->add(this);}//新建普通节点
        int getTurn(){return turn;}//获取节点顺位
        labelOfMenuBar* at(int num){//依据顺位查找节点
            labelOfMenuBar* p=head;
            for (int i=0;i<num;i++) {
                p=p->next;
            }
            return p;
        }
        labelOfMenuBar* toNext(){return (next==nullptr)?head:next;}
        const char* getTitle(){return title;}//获取标签名称
        char isEnd(){return (next==nullptr)?1:0;}//判断是否是尾部节点
        int focusOn(){return head->focus;}//获取焦点位置
        void setFocus(int a){(this==this->head)?((void)(focus=a)):(head->setFocus(a));}//设置焦点
    };
    // ///////////////////////////////////
    labelOfMenuBar* menuLabel;
    constexpr static const char* labelTitle[]={LABEL_TITLE_SET};
    constexpr static const char* penTypeTitle[]={PEN_TYPE_TITLE_SET};
    penType mouseStat;
    QLineEdit* lineEditPageX;
    QLineEdit* lineEditPageY;
    QLabel* labelPageXInfo;
    QLabel* labelPageYInfo;
    int buttonPressed;
    int buttonPressedOrder;//-1为未点击任何按钮
    constexpr static const char* buttonTitleP2[]={BUTTON_TITLE_P2_SET};
    void labelp2show(int);
public:
    explicit menuBar(QWidget *parent = nullptr,int w=0,int h=0);
    penType getPenType(){return mouseStat;}
    void toEdit(){mouseStat=edit;repaint();}
signals:

public slots:
};


#endif // MENUBAR_H
