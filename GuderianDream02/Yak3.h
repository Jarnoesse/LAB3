#ifndef YAK3_H
#define YAK3_H

#include "Airplane.h"

class Yak3 : public Airplane
{
public:
    Yak3(int);
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
#endif // YAK3_H
