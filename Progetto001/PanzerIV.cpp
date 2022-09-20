#include "PanzerIV.h"
#include <string>
#include <iostream>

#include "PanzerIV.h"


        PanzerIV::PanzerIV(int ID)
        {
            name = "Infantry division";
            type = 2;
            attack = 15;
            defence = 10;
            TerritoryID = ID;
        };
        void PanzerIV::move(int finalID)
        {
            std::cout << "La divisione si sta muovendo" << std::endl;
            TerritoryID = finalID;
        };

        void PanzerIV::changeHealth(double damage )
        {
            health = health - damage;
        };

        int PanzerIV::getTerritoryID()
        {
            return TerritoryID;
        };
        int PanzerIV::getDivisionType()
        {
            return type;
        };
        double PanzerIV::getAttack()
        {
            return attack;
        };
        double PanzerIV::getDefense()
        {
            return defence;
        };
        string PanzerIV::getName()
        {
            return name;
        };
