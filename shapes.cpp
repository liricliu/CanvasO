#include "shape.h"
#include <math.h>

//线段的定义
int lineShape::totalAmount=0;

lineShape::lineShape(int p1x,int p1y,int p2x,int p2y):Shape (){
    point1X=p1x;
    point1Y=p1y;
    point2X=p2x;
    point2Y=p2y;
    totalAmount++;//所有的构造函数里必须加一句这个
}
lineShape::~lineShape(){
    totalAmount--;//所有的析构函数里必须加一句这个
}
int lineShape::x(){
    return (point1X<point2X)?point1X:point2X;
}
int lineShape::y(){
    return (point1Y<point2Y)?point1Y:point2Y;
}
int lineShape::width(){
    return (point1X<point2X)?(point2X-point1X):(point1X-point2X);
}
int lineShape::height(){
    return (point1Y<point2Y)?(point2Y-point1Y):(point1Y-point2Y);
}
void lineShape::move(int moX,int moY){
    point1X+=moX;
    point2X+=moX;
    point1Y+=moY;
    point2Y+=moY;
}
void lineShape::transShape(int trX,int trY,unsigned char mode){
    int& controlledY=((point1Y<point2Y)^((bool)(mode%2)))?point1Y:point2Y;
    int& controlledX=((point1X<point2X)^((bool)(mode/2)))?point1X:point2X;
    controlledY+=trY;
    controlledX+=trX;
}

//折线的定义
int linesShape::totalAmount = 0;
linesShape::linesShape(int pnum, const int *px, const int *py) : Shape() {
  pointNum = pnum;
  pointX = new int[pnum];
  pointY = new int[pnum];
  for (int i = 0; i < pnum; ++i) {
    pointX[i] = px[i];
    pointY[i] = py[i];
  }
  totalAmount++; //所有的构造函数里必须加一句这个
}
linesShape::~linesShape() {
  delete[] pointX;
  delete[] pointY;
  totalAmount--; //所有的析构函数里必须加一句这个
}
int linesShape::x() {
  int x = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i)
    x = (x > pointX[i]) ? pointX[i] : x;
  return x;
}
int linesShape::y() {
  int y = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i)
    y = (y > pointY[i]) ? pointY[i] : y;
  return y;
}
int linesShape::width() {
  int x_max = -0x80000000, x_min = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i) {
    x_min = (x_min > pointX[i]) ? pointX[i] : x_min;
    x_max = (x_max < pointX[i]) ? pointX[i] : x_max;
  }
  return x_max - x_min;
}
int linesShape::height() {
  int y_max = -0x80000000, y_min = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i) {
    y_min = (y_min > pointY[i]) ? pointY[i] : y_min;
    y_max = (y_max < pointY[i]) ? pointY[i] : y_max;
  }
  return y_max - y_min;
}
void linesShape::move(int moX, int moY) {
  for (int i = 0; i < pointNum; ++i) {
    pointX[i] += moX;
    pointY[i] += moY;
  }
  return;
}
void linesShape::transShape(int trX, int trY, unsigned char mode) {
  int x_max = -0x80000000, x_min = 0x7FFFFFFF;
  int y_max = -0x80000000, y_min = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i) {
    x_min = (x_min > pointX[i]) ? pointX[i] : x_min;
    x_max = (x_max < pointX[i]) ? pointX[i] : x_max;
    y_min = (y_min > pointY[i]) ? pointY[i] : y_min;
    y_max = (y_max < pointY[i]) ? pointY[i] : y_max;
  }
  //“能把图形包裹起来的最小矩形”中不变的那个点
  int &basepointX = ((bool)(mode / 2)) ? x_min : x_max;
  int &basepointY = ((bool)(mode % 2)) ? y_min : y_max;
  //“能把图形包裹起来的最小矩形”中变的那个点
  int &controlledX = ((bool)(mode / 2)) ? x_max : x_min;
  int &controlledY = ((bool)(mode % 2)) ? y_max : y_min;
  for (int i = 0; i < pointNum; ++i) {
    pointX[i] = basepointX+(pointX[i] - basepointX) * (controlledX - basepointX + trX) /
                (controlledX - basepointX);
    pointY[i] = basepointY+(pointY[i] - basepointY) * (controlledY - basepointY + trY) /
                (controlledY - basepointY);
  }
  return;
}

//多边形的定义
int multangleShape::totalAmount = 0;
multangleShape::multangleShape(int pnum, const int *px, const int *py)
    : Shape() {
  pointNum = pnum;
  pointX = new int[pnum];
  pointY = new int[pnum];
  for (int i = 0; i < pnum; ++i) {
    pointX[i] = px[i];
    pointY[i] = py[i];
  }
  totalAmount++; //所有的构造函数里必须加一句这个
}
multangleShape::~multangleShape() {
  delete[] pointX;
  delete[] pointY;
  totalAmount--; //所有的析构函数里必须加一句这个
}
int multangleShape::x() {
  int x = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i)
    x = (x > pointX[i]) ? pointX[i] : x;
  return x;
}
int multangleShape::y() {
  int y = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i)
    y = (y > pointY[i]) ? pointY[i] : y;
  return y;
}
int multangleShape::width() {
  int x_max = -0x80000000, x_min = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i) {
    x_min = (x_min > pointX[i]) ? pointX[i] : x_min;
    x_max = (x_max < pointX[i]) ? pointX[i] : x_max;
  }
  return x_max - x_min;
}
int multangleShape::height() {
  int y_max = -0x80000000, y_min = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i) {
    y_min = (y_min > pointY[i]) ? pointY[i] : y_min;
    y_max = (y_max < pointY[i]) ? pointY[i] : y_max;
  }
  return y_max - y_min;
}
void multangleShape::move(int moX, int moY) {
  for (int i = 0; i < pointNum; ++i) {
    pointX[i] += moX;
    pointY[i] += moY;
  }
  return;
}
void multangleShape::transShape(int trX, int trY, unsigned char mode) {
  int x_max = -0x80000000, x_min = 0x7FFFFFFF;
  int y_max = -0x80000000, y_min = 0x7FFFFFFF;
  for (int i = 0; i < pointNum; ++i) {
    x_min = (x_min > pointX[i]) ? pointX[i] : x_min;
    x_max = (x_max < pointX[i]) ? pointX[i] : x_max;
    y_min = (y_min > pointY[i]) ? pointY[i] : y_min;
    y_max = (y_max < pointY[i]) ? pointY[i] : y_max;
  }
  //“能把图形包裹起来的最小矩形”中不变的那个点
  int &basepointX = ((bool)(mode / 2)) ? x_min : x_max;
  int &basepointY = ((bool)(mode % 2)) ? y_min : y_max;
  //“能把图形包裹起来的最小矩形”中变的那个点
  int &controlledX = ((bool)(mode / 2)) ? x_max : x_min;
  int &controlledY = ((bool)(mode % 2)) ? y_max : y_min;
  for (int i = 0; i < pointNum; ++i) {
    pointX[i] = basepointX+(pointX[i] - basepointX) * (controlledX - basepointX + trX) /
                (controlledX - basepointX);
    pointY[i] = basepointY+(pointY[i] - basepointY) * (controlledY - basepointY + trY) /
                (controlledY - basepointY);
  }
  return;
}
int multangleShape::trangle_order(int x1, int x2, int x3, int y1, int y2,
                                  int y3) {
  double o;
  o = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
  return o > 0 ? 1 : -1;
}
double multangleShape::trangle_area(int x1, int x2, int x3, int y1, int y2,
                                    int y3) {
  double a, b, c;
  a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  b = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
  c = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
  return sqrt((a + b + c) * (a + b - c) * (a - b + c) * (b - a + c) / 16) *
         trangle_order(x1, x2, x3, y1, y2, y3);
}
int multangleShape::area() {
  double ans = 0;
  for (int i = 1; i < pointNum - 1; i++)
    ans += trangle_area(pointX[0], pointX[i], pointX[i + 1], pointY[0],
                        pointY[i], pointY[i + 1]);
  return (int)(fabs(ans));
}

//长方形的定义
int rectangleShape::totalAmount = 0;
rectangleShape::rectangleShape(int p1x, int p1y, int p2x, int p2y) : Shape() {
  pointX = (p1x < p2x) ? p1x : p2x;
  pointY = (p1y < p2y) ? p1y : p2y;
  W = (p1x < p2x) ? (p2x - p1x) : (p1x - p2x);
  H = (p1y < p2y) ? (p2y - p1y) : (p1y - p2y);

  totalAmount++; //所有的构造函数里必须加一句这个
}
rectangleShape::~rectangleShape() {
  totalAmount--; //所有的析构函数里必须加一句这个
}
int rectangleShape::x() { return pointX; }
int rectangleShape::y() { return pointY; }
int rectangleShape::width() { return W; }
int rectangleShape::height() { return H; }
void rectangleShape::move(int moX, int moY) {
  pointX += moX;
  pointY += moY;
  return;
}
void rectangleShape::transShape(int trX, int trY, unsigned char mode) {
  int x_max = pointX + W, x_min = pointX;
  int y_max = pointY + H, y_min = pointY;
  //“能把图形包裹起来的最小矩形”中不变的那个点
  int &basepointX = ((bool)(mode / 2)) ? x_min : x_max;
  int &basepointY = ((bool)(mode % 2)) ? y_min : y_max;
  //“能把图形包裹起来的最小矩形”中变的那个点
  int &controlledX = ((bool)(mode / 2)) ? x_max : x_min;
  int &controlledY = ((bool)(mode % 2)) ? y_max : y_min;
  controlledX += trX;
  controlledY += trY;

  pointX = (basepointX < controlledX) ? basepointX : controlledX;
  pointY = (basepointY < controlledY) ? basepointY : controlledY;
  W = (basepointX < controlledX) ? (controlledX - basepointX)
                                 : (basepointX - controlledX);
  H = (basepointY < controlledY) ? (controlledY - basepointY)
                                 : (basepointY - controlledY);
  return;
}
int rectangleShape::area() { return W * H; }

//正方形的定义
int squareShape::totalAmount = 0;
//画布上扒拉一个长方形，在里面以短边为边长，第一个点为顶点构筑正方形
squareShape::squareShape(int p1x, int p1y, int p2x, int p2y) : Shape() {
  pointX = (p1x < p2x) ? p1x : p2x;
  pointY = (p1y < p2y) ? p1y : p2y;
  int w = (p1x < p2x) ? (p2x - p1x) : (p1x - p2x);
  int h = (p1y < p2y) ? (p2y - p1y) : (p1y - p2y);
  A = (w < h) ? w : h;
  totalAmount++; //所有的构造函数里必须加一句这个
}
squareShape::~squareShape() {
  totalAmount--; //所有的析构函数里必须加一句这个
}
int squareShape::x() { return pointX; }
int squareShape::y() { return pointY; }
int squareShape::width() { return A; }
int squareShape::height() { return A; }
void squareShape::move(int moX, int moY) {
  pointX += moX;
  pointY += moY;
  return;
}
void squareShape::transShape(int trX, int trY, unsigned char mode) {
  int x_max = pointX + A, x_min = pointX;
  int y_max = pointY + A, y_min = pointY;
  //“能把图形包裹起来的最小矩形”中不变的那个点
  int &basepointX = ((bool)(mode / 2)) ? x_min : x_max;
  int &basepointY = ((bool)(mode % 2)) ? y_min : y_max;
  //“能把图形包裹起来的最小矩形”中变的那个点
  int &controlledX = ((bool)(mode / 2)) ? x_max : x_min;
  int &controlledY = ((bool)(mode % 2)) ? y_max : y_min;
  controlledX += trX;
  controlledY += trY;

  pointX = (basepointX < controlledX) ? basepointX : controlledX;
  pointY = (basepointY < controlledY) ? basepointY : controlledY;
  int w = (basepointX < controlledX) ? (controlledX - basepointX)
                                     : (basepointX - controlledX);
  int h = (basepointY < controlledY) ? (controlledY - basepointY)
                                     : (basepointY - controlledY);
  A = (w < h) ? w : h;
  return;
}
int squareShape::area() { return A * A; }

//园的定义
int circleShape::totalAmount = 0;
//画布上扒拉一个长方形，在里面以短边为边长，第一个点为顶点构筑正方形
circleShape::circleShape(int p1x, int p1y, int p2x, int p2y) : Shape() {
  pointX = (p1x < p2x) ? p1x : p2x;
  pointY = (p1y < p2y) ? p1y : p2y; //左上角坐标
  int w = (p1x < p2x) ? (p2x - p1x) : (p1x - p2x);
  int h = (p1y < p2y) ? (p2y - p1y) : (p1y - p2y);
  R = (w < h) ? w : h;
  R /= 2;
  //加上半径得到圆心
  pointX += R;
  pointY += R;
  totalAmount++; //所有的构造函数里必须加一句这个
}
circleShape::~circleShape() {
  totalAmount--; //所有的析构函数里必须加一句这个
}
int circleShape::x() { return pointX - R; }
int circleShape::y() { return pointY - R; }
int circleShape::width() { return 2 * R; }
int circleShape::height() { return 2 * R; }
void circleShape::move(int moX, int moY) {
  pointX += moX;
  pointY += moY;
  return;
}
void circleShape::transShape(int trX, int trY, unsigned char mode) {
  int x_max = pointX + R, x_min = pointX - R;
  int y_max = pointY + R, y_min = pointY - R;
  //“能把图形包裹起来的最小矩形”中不变的那个点
  int &basepointX = ((bool)(mode / 2)) ? x_min : x_max;
  int &basepointY = ((bool)(mode % 2)) ? y_min : y_max;
  //“能把图形包裹起来的最小矩形”中变的那个点
  int &controlledX = ((bool)(mode / 2)) ? x_max : x_min;
  int &controlledY = ((bool)(mode % 2)) ? y_max : y_min;
  controlledX += trX;
  controlledY += trY;

  pointX = (basepointX < controlledX) ? basepointX : controlledX;
  pointY = (basepointY < controlledY) ? basepointY : controlledY; //左上角坐标
  int w = (basepointX < controlledX) ? (controlledX - basepointX)
                                     : (basepointX - controlledX);
  int h = (basepointY < controlledY) ? (controlledY - basepointY)
                                     : (basepointY - controlledY);
  R = (w < h) ? w : h;
  R /= 2;
  //加上半径得到圆心
  pointX += R;
  pointY += R;
  return;
}
int circleShape::area() {
  const double PI = 3.1415626535897932;
  return (int)(PI * R * R);
}

//椭圆的定义
int ellipseShape::totalAmount = 0;
//画布上扒拉一个长方形，得到其内接的椭圆
ellipseShape::ellipseShape(int p1x, int p1y, int p2x, int p2y) : Shape() {
  pointX = (p1x < p2x) ? p1x : p2x;
  pointY = (p1y < p2y) ? p1y : p2y; //左上角坐标
  xR = (p1x < p2x) ? (p2x - p1x) : (p1x - p2x);
  yR = (p1y < p2y) ? (p2y - p1y) : (p1y - p2y);
  xR /= 2;
  yR /= 2;
  pointX += xR;
  pointY += yR;
  totalAmount++; //所有的构造函数里必须加一句这个
}
ellipseShape::~ellipseShape() {
  totalAmount--; //所有的析构函数里必须加一句这个
}
int ellipseShape::x() { return pointX - xR; }
int ellipseShape::y() { return pointY - yR; }
int ellipseShape::width() { return 2 * xR; }
int ellipseShape::height() { return 2 * yR; }
void ellipseShape::move(int moX, int moY) {
  pointX += moX;
  pointY += moY;
  return;
}
void ellipseShape::transShape(int trX, int trY, unsigned char mode) {
  int x_max = pointX + xR, x_min = pointX - xR;
  int y_max = pointY + yR, y_min = pointY - yR;
  //“能把图形包裹起来的最小矩形”中不变的那个点
  int &basepointX = ((bool)(mode / 2)) ? x_min : x_max;
  int &basepointY = ((bool)(mode % 2)) ? y_min : y_max;
  //“能把图形包裹起来的最小矩形”中变的那个点
  int &controlledX = ((bool)(mode / 2)) ? x_max : x_min;
  int &controlledY = ((bool)(mode % 2)) ? y_max : y_min;
  controlledX += trX;
  controlledY += trY;

  pointX = (basepointX < controlledX) ? basepointX : controlledX;
  pointY = (basepointY < controlledY) ? basepointY : controlledY; //左上角坐标
  xR = (basepointX < controlledX) ? (controlledX - basepointX)
                                  : (basepointX - controlledX);
  yR = (basepointY < controlledY) ? (controlledY - basepointY)
                                  : (basepointY - controlledY);
  xR /= 2;
  yR /= 2;
  pointX += xR;
  pointY += yR;
  return;
}
int ellipseShape::area() {
  const double PI = 3.1415626535897932;
  return (int)(PI * xR * yR);
}
