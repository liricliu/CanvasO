#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include "uicolorpanel.h"

class sideBar : public QWidget
{
    Q_OBJECT
    void paintEvent(QPaintEvent* e);
    QPushButton* buttonLayerUp;
    QPushButton* buttonLayerDown;
    QPushButton* buttonSelectUpstair;
    QPushButton* buttonSelectDownstair;
    QPushButton* buttonDelete;
    QLineEdit* lineEditWidth;
    QLineEdit* lineEditHeight;
    QLineEdit* lineEditColorR;
    QLineEdit* lineEditColorG;
    QLineEdit* lineEditColorB;
    QLineEdit* lineEditEdgeColorR;
    QLineEdit* lineEditEdgeColorG;
    QLineEdit* lineEditEdgeColorB;
    QLineEdit* lineEditEdgeWidth;
    QLineEdit* lineEditRotateDeg;
private slots:
    void editWidth();
    void editHeight();
    void editColorR();
    void editColorG();
    void editColorB();
    void editEdgeColorR();
    void editEdgeColorG();
    void editEdgeColorB();
    void editEdgeWidth();
    void editRotateDeg();
    void moveLayerUp();
    void moveLayerDown();
    void selectUpLayer();
    void selectDownLayer();
    void deleteShape();
public:
    explicit sideBar(QWidget *parent = nullptr,int w=0,int h=0);
    void updateDataInLineEdit();//该函数在Canvas被点击后有可能被调用
signals:

public slots:
};

#endif // SIDEBAR_H
