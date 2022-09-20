#include "RussianInfantry.h"
#include <string>
#include <iostream>


        RussianInfantry::RussianInfantry(int givenID)
        {
            name = "Infantry division";
            type = 1;
            attack = 10;
            defence = 12;
            TerritoryID = givenID;
        };
        void RussianInfantry::move(int finalID)
        {
            std::cout << "La divisione si sta muovendo" << std::endl;
            TerritoryID = finalID;
        };

        void RussianInfantry::changeHealth(double damage )
        {
            health = health - damage;
        };

        int RussianInfantry::getTerritoryID()
        {
            return TerritoryID;
        };
        int RussianInfantry::getDivisionType()
        {
            return type;
        };
        double RussianInfantry::getAttack()
        {
            return attack;
        };
        double RussianInfantry::getDefence()
        {
            return defence;
        };
        string RussianInfantry::getName()
        {
            return name;
        };

