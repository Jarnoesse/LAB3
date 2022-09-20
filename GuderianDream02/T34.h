#ifndef T34_H
#define T34_H

#include "Tank.h"

class T34 : public Tank
{
public:
    T34(int);
    virtual void move(int);
    virtual void changeHealth(double);
    virtual int getTerritoryID();
    virtual int getDivisionType();
    virtual double getAttack();
    virtual double getDefence();
    virtual string getName();
private:
    int TerritoryID;
    double health;
    string name;
    double attack;
    double defence;
    double type;
};


#endif // T34_H
