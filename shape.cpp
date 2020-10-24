#include "mainwin.h"

Shape* Shape::selectedShape=nullptr;
int Shape::totalAmount=0;
Shape* Shape::headShape=nullptr;
int Shape::idPond=0;
Shape::Shape()
{
    id=idPond;
    idPond++;
    if(selectedShape==nullptr){
        last=nullptr;
        next=nullptr;
        headShape=this;
        selectedShape=this;
    }
    else {
        selectedShape->insert(this);
        selectedShape=this;
    }
    totalAmount++;
    setColor(0,0,0);
    setEdgeColor(0,0,0);
    setEdgeWidth(1);
    rotate(0);
}

Shape::~Shape(){
    if(last!=nullptr){
        del();
        totalAmount--;
    }
}

void Shape::setColor(int seR, int seG, int seB){
    if(seR>=0)
        colorR=static_cast<unsigned char>(seR);
    if(seG>=0)
        colorG=static_cast<unsigned char>(seG);
    if(seB>=0)
        colorB=static_cast<unsigned char>(seB);
}
void Shape::setEdgeColor(int seR,int seG,int seB){
    if(seR>=0)
        edgecolorR=static_cast<unsigned char>(seR);
    if(seG>=0)
        edgecolorG=static_cast<unsigned char>(seG);
    if(seB>=0)
        edgecolorB=static_cast<unsigned char>(seB);
}
void Shape::insert(Shape* d){
    Shape* n=this->next;
    if(n!=nullptr){
        n->last=d;
    }
    d->next=n;
    d->last=this;
    next=d;
}
void Shape::del(){
    if(next!=nullptr)
        next->last=last;
    if(last!=nullptr)
        last->next=next;
    if(this==selectedShape)
        selectedShape=last;
}
void Shape::layerUp(){//将结点后移一个
    if(next!=nullptr){
        del();
        selectedShape->next->insert(this);
        selectedShape=this;
    }
}
void Shape::layerDown(){//将结点前移一个
    if(last!=headShape){
        del();
        selectedShape->last->insert(this);
        selectedShape=this;
    }
}
int Shape::layerOrder(){
    int toRet=0;
    Shape* p=headShape;
    while(this!=p){
        p=p->next;
        toRet++;
    }
    return toRet;
}
