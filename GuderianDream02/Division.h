#ifndef DIVISION_H
#define DIVISION_H

#include <string>
using std::string;
class Division {

public:
 virtual ~Division(){};
 virtual void move() = 0;
 virtual void changeHealth() = 0;
 virtual int getTerritoryID() = 0;
 virtual int getDivisionType() =0;
 virtual double getAttack() =0;
 virtual double getDefense()=0;
 virtual string getName() = 0;
};

#endif // DIVISION_H
