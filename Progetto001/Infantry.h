#ifndef INFANTRY_H
#define INFANTRY_H

#include "Division.h"
#include <string>

using std::string;

class Infantry : public Division
{
public:
    virtual ~Infantry(){};
    virtual void move(int) = 0;
    virtual void changeHealth(double) = 0;
    virtual int getTerritoryID() = 0;
    virtual int getDivisionType() =0;
    virtual double getAttack() =0;
    virtual double getDefence()=0;
    virtual string getName() = 0;
};

#endif // INFANTRY_H
