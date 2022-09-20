#ifndef PANZERIV_H
#define PANZERIV_H

#include "Tank.h"

class PanzerIV : public Tank
{
public:
    PanzerIV(int);
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

#endif // PANZERIV_H
