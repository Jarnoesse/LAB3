#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <vector>
using std::vector;
#include "Division.h"
class Abstract_Factory {

public:
 virtual ~Abstract_Factory(){};
 virtual vector<Division*> getArmy() const = 0;
};

#endif // ABSTRACT_FACTORY_H
