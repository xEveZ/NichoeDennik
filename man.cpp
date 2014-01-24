#include "includer.h"

 _man::_man(apreImageAnimation** img,double pos_x,double pos_y,double width=0, double height=0)
{
    an[0]=img[0];
    an[1]=img[1];
    x=pos_x;
    y=pos_y;
    w=width;
    h=height;
    an[0]->setPosition(pos_x,pos_y);
    an[0]->setWidth(width);
    an[0]->setHeight(height);
    an[1]->setPosition(pos_x,pos_y);
    an[1]->setWidth(width);
    an[1]->setHeight(height);

    ///giusto per vedere se li disegna
    an[1]->setPosition(0,0);
}

_man::~_man()
{
    delete an[0];
    delete an[1];
}

void _man::draw()
{
    an[0]->draw();


    an[1]->draw();

    return;
}
