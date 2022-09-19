#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>

using std::string;

class Airplane public Division
{
public:
    virtual ~Airplane(){};
    virtual void move() = 0;
    virtual void changeHealth() = 0;
    virtual int getTerritoryID() = 0;
    virtual int getDivisionType() =0;
    virtual double getAttack() =0;
    virtual double getDefense()=0;
    virtual string getName() = 0;
}

#endif // AIRPLANE_H
