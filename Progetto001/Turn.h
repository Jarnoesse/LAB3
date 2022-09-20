#ifndef TURN_H
#define TURN_H
#include <string>
#include <vector>
#include <iostream>
using std::string;
#include "Territory.h"
#include "Abstract_Factory.h"
#include "GermanFactory.h"
#include "RussianFactory.h"

void Turn(vector<Territory*>, vector<Division*> , vector<Division*> );

#endif // TURN_H
