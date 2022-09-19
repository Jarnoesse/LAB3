#ifndef GERMANINFANTRY_H
#define GERMANINFANTRY_H

#include "Infantry.h"

class GermanInfantry : public Infantry
{
public:
    GermanInfantry();
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

#endif // GERMANINFANTRY_H
