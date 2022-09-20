#include "GermanInfantry.h"
#include <string>
#include <iostream>


        GermanInfantry::GermanInfantry(int givenID)
        {
            name = "Infantry division";
            type = 1;
            attack = 10;
            defence = 12;
            TerritoryID = givenID;
        };
        void GermanInfantry::move(int finalID)
        {
            std::cout << "La divisione si sta muovendo" << std::endl;
            TerritoryID = finalID;
        };

        void GermanInfantry::changeHealth(double damage )
        {
            health = health - damage;
        };

        int GermanInfantry::getTerritoryID()
        {
            return TerritoryID;
        };
        int GermanInfantry::getDivisionType()
        {
            return type;
        };
        double GermanInfantry::getAttack()
        {
            return attack;
        };
        double GermanInfantry::getDefence()
        {
            return defence;
        };
        string GermanInfantry::getName()
        {
            return name;
        };
