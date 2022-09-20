#ifndef BF109_H
#define BF109_H

#include "Airplane.h"

class Bf109 : public Airplane
{
public:
    Bf109(int);
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
#endif // BF109_H
