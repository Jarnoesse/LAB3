#ifndef RUSSIANFACTORY_H
#define RUSSIANFACTORY_H

#include <vector>
using std::vector;
#include "Division.h"
#include "Abstract_Factory.h"
class RussianFactory : public Abstract_Factory{

public:
 RussianFactory(int,int,int);
 ~RussianFactory();
 int sizeArmy() const;
 vector<Division*>::const_iterator beginArmy() const;
 vector<Division*>::const_iterator endArmy() const;
 vector<Division*> getArmy() const;
private:
 vector<Division*> army;

};

#endif // RUSSIANFACTORY_H
