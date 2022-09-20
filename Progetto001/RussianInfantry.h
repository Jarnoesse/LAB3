#ifndef RUSSIANINFANTRY_H
#define RUSSIANINFANTRY_H

#include "Infantry.h"

class RussianInfantry : public Infantry
{
public:
    RussianInfantry(int);
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

#endif // RUSSIANINFANTRY_H
