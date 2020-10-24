#ifndef SHAPE_H
#define SHAPE_H

#define SHAPE_CANVAS 0
#define SHAPE_LINE 1
#define SHAPE_LINES 2
#define SHAPE_MULTANGLE 3
#define SHAPE_RECTANGLE 5
#define SHAPE_SQUARE 4
#define SHAPE_CIRCLE 6
#define SHAPE_ELLIPSE 7

class Shape
{
public:
    Shape();
    virtual ~Shape();
private:
    int id;
    Shape* next;
    Shape* last;
    unsigned char colorR;
    unsigned char colorG;
    unsigned char colorB;
    unsigned char edgecolorR;
    unsigned char edgecolorG;
    unsigned char edgecolorB;
    int edgeWidth;
    int rotateDeg;
    static int totalAmount;
    static Shape* selectedShape;
    static Shape* headShape;
    static int idPond;
public:
    virtual int x(){return 0;}
    virtual int y(){return 0;}
    virtual int width(){return 0;}
    virtual int height(){return 0;}
    virtual int type(){return SHAPE_CANVAS;}
    virtual void move(int moX,int moY){}
    virtual void transShape(int trX,int trY,unsigned char mode){}
    //mode第一位选左右，第二位选上下,0左1右，0上1下
    virtual int area(){return 0;}
    virtual int count(){return totalAmount;}
    // ///////////////////以下为基类公共函数
    void setColor(int seR,int seG,int seB);
    void setEdgeColor(int seR,int seG,int seB);
    inline int color(){return colorR*65536+colorG*256+colorB;}
    inline int edgeColor(){return edgecolorR*65536+edgecolorG*256+edgecolorB;}
    inline void rotate(int roDeg){rotateDeg=roDeg;}
    inline int getRotateDeg(){return rotateDeg;}
    inline int getEdgeWidth(){return edgeWidth;}
    inline void setEdgeWidth(int seEW){edgeWidth=seEW;}
    void moveTo(int toX,int toY){move(toX-x(),toY-y());}
    inline int getID(){return id;}
    // /////////////////////以下为链表用函数
    inline Shape* head(){return headShape;}
    inline Shape* selected(){return selectedShape;}
    inline void selectNext(){if(selectedShape->next) selectedShape=selectedShape->next;}
    inline void selectLast(){if(selectedShape->last) selectedShape=selectedShape->last;}
    inline void selectHead(){selectedShape=headShape;}
    inline Shape* getNext(){return next;}
    inline Shape* getLast(){return last;}
    void layerUp();
    void layerDown();
    void insert(Shape* d);//
    void del();
    int layerOrder();
};

class lineShape:public Shape{
public:
    lineShape(int p1x,int p1y,int p2x,int p2y);
    ~lineShape();//构造函数和析构函数参照shapes.h里的具体实现
    //坐标轴系统：左上角为原点，右和下为正方向
    virtual int x();//返回能把图形包裹起来的最小矩形的左上角x坐标
    virtual int y();//返回能把图形包裹起来的最小矩形的左上角y坐标
    virtual int width();//返回能把图形包裹起来的最小矩形的宽度
    virtual int height();//返回能把图形包裹起来的最小矩形的宽度
    virtual int type(){return SHAPE_LINE;}//返回图形的类型，宏定义在本文件最上面
    virtual void move(int moX,int moY);//分别沿x和y正方向移动移动moX和moY
    virtual void transShape(int trX,int trY,unsigned char mode=3);
    //编辑图形，将“能把图形包裹起来的最小矩形”拖拽某个角产生形变，
    //trX和trY指定了在x轴和y轴正方向上拖拽的距离
    //mode指定了拖拽的是哪个角，可取0到3，对应关系如下：
    //0 2
    //1 3
    //好处是mode%2的值指示了这个角在上面还是在下面（0上1下），
    //而mode/2的值指示了这个角在左边还是右边（0左1右）
    virtual int area(){return 0;}//返回面积
    virtual int count(){return totalAmount;}
    //注意所有的新类都在里面把这行复制一下就行了
    inline int p1x(){return point1X;}
    inline int p2x(){return point2X;}
    inline int p1y(){return point1Y;}
    inline int p2y(){return point2Y;}
private:
    static int totalAmount;//所有新类必须有一个这个成员
    //下面的成员是自己定义的用于描述这种图形的信息的变量
    int point1X;
    int point1Y;
    int point2X;
    int point2Y;
};

class linesShape : public Shape {
public:
    linesShape(int pnum, const int *px, const int *py);
    ~linesShape(); //构造函数和析构函数参照shapes.h里的具体实现
    //坐标轴系统：左上角为原点，右和下为正方向
    virtual int x(); //返回能把图形包裹起来的最小矩形的左上角x坐标
    virtual int y(); //返回能把图形包裹起来的最小矩形的左上角y坐标
    virtual int width();  //返回能把图形包裹起来的最小矩形的宽度
    virtual int height(); //返回能把图形包裹起来的最小矩形的宽度
    virtual int type() {
        return SHAPE_LINES;
    } //返回图形的类型，宏定义在本文件最上面
    virtual void move(int moX, int moY); //分别沿x和y正方向移动移动moX和moY
    virtual void transShape(int trX, int trY, unsigned char mode = 3);
    //编辑图形，将“能把图形包裹起来的最小矩形”拖拽某个角产生形变，
    // trX和trY指定了在x轴和y轴正方向上拖拽的距离
    // mode指定了拖拽的是哪个角，可取0到3，对应关系如下：
    // 0 2
    // 1 3
    //好处是mode%2的值指示了这个角在上面还是在下面（0上1下），
    //而mode/2的值指示了这个角在左边还是右边（0左1右）
  virtual int area() { return 0; } //返回面积
  virtual int count() { return totalAmount; }
  //注意所有的新类都在里面把这行复制一下就行了
    inline int getPointNum(){return pointNum;}
    inline int* pX(){return pointX;}
    inline int* pY(){return pointY;}
private:
  static int totalAmount; //所有新类必须有一个这个成员
  //下面的成员是自己定义的用于描述这种图形的信息的变量
  int pointNum;
  int *pointX;
  int *pointY;
};

class multangleShape : public Shape {
public:
  multangleShape(int pnum, const int *px, const int *py);
  ~multangleShape(); //构造函数和析构函数参照shapes.h里的具体实现
  //坐标轴系统：左上角为原点，右和下为正方向
  virtual int x(); //返回能把图形包裹起来的最小矩形的左上角x坐标
  virtual int y(); //返回能把图形包裹起来的最小矩形的左上角y坐标
  virtual int width();  //返回能把图形包裹起来的最小矩形的宽度
  virtual int height(); //返回能把图形包裹起来的最小矩形的宽度
  virtual int type() {
    return SHAPE_MULTANGLE;
  } //返回图形的类型，宏定义在本文件最上面
  virtual void move(int moX, int moY); //分别沿x和y正方向移动移动moX和moY
  virtual void transShape(int trX, int trY, unsigned char mode = 3);
  //编辑图形，将“能把图形包裹起来的最小矩形”拖拽某个角产生形变，
  // trX和trY指定了在x轴和y轴正方向上拖拽的距离
  // mode指定了拖拽的是哪个角，可取0到3，对应关系如下：
  // 0 2
  // 1 3
  //好处是mode%2的值指示了这个角在上面还是在下面（0上1下），
  //而mode/2的值指示了这个角在左边还是右边（0左1右）
  virtual int area(); //返回面积
  virtual int count() { return totalAmount; }
  //注意所有的新类都在里面把这行复制一下就行了
  inline int getPointNum(){return pointNum;}
  inline int* pX(){return pointX;}
  inline int* pY(){return pointY;}
private:
  static int totalAmount; //所有新类必须有一个这个成员
  //下面的成员是自己定义的用于描述这种图形的信息的变量
  int pointNum;
  int *pointX;
  int *pointY;
  //三顶点三角形面积
  double trangle_area(int x1, int x2, int x3, int y1, int y2, int y3);
  // 1->2->3 用1、-1判断顺时针、逆时针
  int trangle_order(int x1, int x2, int x3, int y1, int y2, int y3);
};

class rectangleShape : public Shape {
public:
  rectangleShape(int p1x, int p1y, int p2x, int p2y);
  ~rectangleShape(); //构造函数和析构函数参照shapes.h里的具体实现
  //坐标轴系统：左上角为原点，右和下为正方向
  virtual int x(); //返回能把图形包裹起来的最小矩形的左上角x坐标
  virtual int y(); //返回能把图形包裹起来的最小矩形的左上角y坐标
  virtual int width();  //返回能把图形包裹起来的最小矩形的宽度
  virtual int height(); //返回能把图形包裹起来的最小矩形的宽度
  virtual int type() {
    return SHAPE_RECTANGLE;
  } //返回图形的类型，宏定义在本文件最上面
  virtual void move(int moX, int moY); //分别沿x和y正方向移动移动moX和moY
  virtual void transShape(int trX, int trY, unsigned char mode = 3);
  //编辑图形，将“能把图形包裹起来的最小矩形”拖拽某个角产生形变，
  // trX和trY指定了在x轴和y轴正方向上拖拽的距离
  // mode指定了拖拽的是哪个角，可取0到3，对应关系如下：
  // 0 2
  // 1 3
  //好处是mode%2的值指示了这个角在上面还是在下面（0上1下），
  //而mode/2的值指示了这个角在左边还是右边（0左1右）
  virtual int area(); //返回面积
  virtual int count() { return totalAmount; }
  //注意所有的新类都在里面把这行复制一下就行了
private:
  static int totalAmount; //所有新类必须有一个这个成员
  //下面的成员是自己定义的用于描述这种图形的信息的变量
  int pointX; //左上角x
  int pointY; //左上角y
  int W;      //宽
  int H;      //高
};

class squareShape : public Shape {
public:
  //画布上扒拉一个长方形，在里面以短边为边长，第一个点为顶点构筑正方形
  squareShape(int p1x, int p1y, int p2x, int p2y);
  ~squareShape(); //构造函数和析构函数参照shapes.h里的具体实现
  //坐标轴系统：左上角为原点，右和下为正方向
  virtual int x(); //返回能把图形包裹起来的最小矩形的左上角x坐标
  virtual int y(); //返回能把图形包裹起来的最小矩形的左上角y坐标
  virtual int width();  //返回能把图形包裹起来的最小矩形的宽度
  virtual int height(); //返回能把图形包裹起来的最小矩形的宽度
  virtual int type() {
    return SHAPE_SQUARE;
  } //返回图形的类型，宏定义在本文件最上面
  virtual void move(int moX, int moY); //分别沿x和y正方向移动移动moX和moY
  virtual void transShape(int trX, int trY, unsigned char mode = 3);
  //编辑图形，将“能把图形包裹起来的最小矩形”拖拽某个角产生形变，
  // trX和trY指定了在x轴和y轴正方向上拖拽的距离
  // mode指定了拖拽的是哪个角，可取0到3，对应关系如下：
  // 0 2
  // 1 3
  //好处是mode%2的值指示了这个角在上面还是在下面（0上1下），
  //而mode/2的值指示了这个角在左边还是右边（0左1右）
  virtual int area(); //返回面积
  virtual int count() { return totalAmount; }
  //注意所有的新类都在里面把这行复制一下就行了
private:
  static int totalAmount; //所有新类必须有一个这个成员
  //下面的成员是自己定义的用于描述这种图形的信息的变量
  int pointX; //左上角x
  int pointY; //左上角y
  int A;      //边长
};

// SHAPE_CIRCLE
class circleShape : public Shape {
public:
  //画布上扒拉一个长方形，在里面以短边为边长，第一个点为顶点构筑正方形的内接圆
  circleShape(int p1x, int p1y, int p2x, int p2y);
  ~circleShape(); //构造函数和析构函数参照shapes.h里的具体实现
  //坐标轴系统：左上角为原点，右和下为正方向
  virtual int x(); //返回能把图形包裹起来的最小矩形的左上角x坐标
  virtual int y(); //返回能把图形包裹起来的最小矩形的左上角y坐标
  virtual int width();  //返回能把图形包裹起来的最小矩形的宽度
  virtual int height(); //返回能把图形包裹起来的最小矩形的宽度
  virtual int type() {
    return SHAPE_CIRCLE;
  } //返回图形的类型，宏定义在本文件最上面
  virtual void move(int moX, int moY); //分别沿x和y正方向移动移动moX和moY
  virtual void transShape(int trX, int trY, unsigned char mode = 3);
  //编辑图形，将“能把图形包裹起来的最小矩形”拖拽某个角产生形变，
  // trX和trY指定了在x轴和y轴正方向上拖拽的距离
  // mode指定了拖拽的是哪个角，可取0到3，对应关系如下：
  // 0 2
  // 1 3
  //好处是mode%2的值指示了这个角在上面还是在下面（0上1下），
  //而mode/2的值指示了这个角在左边还是右边（0左1右）
  virtual int area(); //返回面积
  virtual int count() { return totalAmount; }
  //注意所有的新类都在里面把这行复制一下就行了
private:
  static int totalAmount; //所有新类必须有一个这个成员
  //下面的成员是自己定义的用于描述这种图形的信息的变量
  int pointX; //圆心x
  int pointY; //圆心y
  int R;      //半径
};
// SHAPE_ELLIPSE
class ellipseShape : public Shape {
public:
  //画布上扒拉一个长方形，在里面以短边为边长，第一个点为顶点构筑正方形的内接圆
  ellipseShape(int p1x, int p1y, int p2x, int p2y);
  ~ellipseShape(); //构造函数和析构函数参照shapes.h里的具体实现
  //坐标轴系统：左上角为原点，右和下为正方向
  virtual int x(); //返回能把图形包裹起来的最小矩形的左上角x坐标
  virtual int y(); //返回能把图形包裹起来的最小矩形的左上角y坐标
  virtual int width();  //返回能把图形包裹起来的最小矩形的宽度
  virtual int height(); //返回能把图形包裹起来的最小矩形的宽度
  virtual int type() {
    return SHAPE_ELLIPSE;
  } //返回图形的类型，宏定义在本文件最上面
  virtual void move(int moX, int moY); //分别沿x和y正方向移动移动moX和moY
  virtual void transShape(int trX, int trY, unsigned char mode = 3);
  //编辑图形，将“能把图形包裹起来的最小矩形”拖拽某个角产生形变，
  // trX和trY指定了在x轴和y轴正方向上拖拽的距离
  // mode指定了拖拽的是哪个角，可取0到3，对应关系如下：
  // 0 2
  // 1 3
  //好处是mode%2的值指示了这个角在上面还是在下面（0上1下），
  //而mode/2的值指示了这个角在左边还是右边（0左1右）
  virtual int area(); //返回面积
  virtual int count() { return totalAmount; }
  //注意所有的新类都在里面把这行复制一下就行了
private:
  static int totalAmount; //所有新类必须有一个这个成员
  //下面的成员是自己定义的用于描述这种图形的信息的变量
  int pointX; //圆心x
  int pointY; //圆心y
  int xR;     //横轴半径
  int yR;     //纵轴半径
};

#endif // SHAPE_H
