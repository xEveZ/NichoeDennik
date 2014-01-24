
class _man
{
public:
     _man(apreImageAnimation**,double,double,double,double);    ///oggetto texture, posizione, dimensione w,dimensione h
     ~_man();
     void draw();
     void walk();
     void jump();
     void fire();
protected:
    double x;
    double y;
    double w;
    double h;
    apreImageAnimation* an[2];
};
