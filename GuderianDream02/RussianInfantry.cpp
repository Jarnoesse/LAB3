#include "RussianInfantry.h"
#include <string>
#include <iostream>


        RussianInfantry(int ID)
        {
            name = "Infantry division";
            type = 1;
            attack = 10;
            defense = 12;
            Terrytory ID = ID;
        };
        virtual void RussianInfantry::move(int finalID)
        {
            cout << "La divisione si sta muovendo" << endl;
            TerritoryID = finalID;
        };

        virtual void RussianInfantry::changeHealth(double damage )
        {
            health = health - damage;
        };

        virtual int RussianInfantry::getTerritoryID()
        {
            return TerritoryID;
        };
        virtual int RussianInfantry::getDivisionType()
        {
            return type;
        };
        virtual double RussianInfantry::getAttack()
        {
            return attack;
        };
        virtual double RussianInfantry::getDefense()
        {
            return defence;
        };
        virtual string RussianInfantry::getName()
        {
            return name;
        };

