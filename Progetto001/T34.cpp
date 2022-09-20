#include "T34.h"
#include <string>
#include <iostream>


        T34::T34(int givenID)
        {
            name = "Infantry division";
            type = 2;
            attack = 15;
            defence = 10;
            TerritoryID = givenID;
        };
        void T34::move(int finalID)
        {
            std::cout << "La divisione si sta muovendo" << std::endl;
            TerritoryID = finalID;
        };

        void T34::changeHealth(double damage )
        {
            health = health - damage;
        };

        int T34::getTerritoryID()
        {
            return TerritoryID;
        };
        int T34::getDivisionType()
        {
            return type;
        };
        double T34::getAttack()
        {
            return attack;
        };
        double T34::getDefence()
        {
            return defence;
        };
        string T34::getName()
        {
            return name;
        };
