#ifndef RUSSIANINFANTRY_H
#define RUSSIANINFANTRY_H

#include "Infantry.h"

class RussianInfantry : public Infantry
{
public:
    RussianInfantry();
    virtual void move();
    virtual void changeHealth();
    virtual int getTerritoryID();
    virtual int getDivisionType();
    virtual double getAttack();
    virtual double getDefense();
    virtual string getName();
private:
    int TerritoryID;
    double health;
    string name;
    double attack;
    double defence;
    double type;
};
#endif // RUSSIANINFANTRY_H
