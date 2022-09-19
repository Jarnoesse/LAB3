#ifndef PANZERIV_H
#define PANZERIV_H

#include "Tank.h"

class PanzerIV : public Tank
{
public:
    PanzerIV();
    virtual void move();
    virtual void changeHealth();
    virtual int getTerritoryID();
    virtual int getDivisionType();
    virtual double getAttack();
    virtual double getDefense();
    virtual string getName();
private:
    int TerritoryID;
    string name;
    double attack;
    double defence;
    double type;
};
#endif // PANZERIV_H
