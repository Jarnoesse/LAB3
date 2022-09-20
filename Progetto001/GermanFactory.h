#ifndef GERMANFACTORY_H
#define GERMANFACTORY_H

#include <vector>
using std::vector;

#include "Division.h"
#include "Abstract_Factory.h"

class GermanFactory : public Abstract_Factory{

public:
 GermanFactory(int,int,int);
 ~GermanFactory();
 int sizeArmy() const;
 vector<Division*>::const_iterator beginArmy() const;
 vector<Division*>::const_iterator endArmy() const;
 vector<Division*> getArmy() const;
private:
 vector<Division*> army;

};


#endif // GERMANFACTORY_H
