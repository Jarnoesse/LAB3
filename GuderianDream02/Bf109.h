#ifndef BF109_H
#define BF109_H

#include "Airplane.h"

class Yak3 : public Airplane
{
public:
    Yak3();
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
#endif // BF109_H
