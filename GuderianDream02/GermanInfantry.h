#ifndef GERMANINFANTRY_H
#define GERMANINFANTRY_H

#include "Infantry.h"

class GermanInfantry : public Infantry
{
public:
    GermanInfantry(int);
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

#endif // GERMANINFANTRY_H
