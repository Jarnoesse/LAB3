#include "GermanInfantry.h"
#include <string>
#include <iostream>


        GermanInfantry(int ID)
        {
            name = "Infantry division";
            type = 1;
            attack = 10;
            defense = 12;
            Terrytory ID = ID;
        };
        virtual void GermanInfantry::move(int finalID)
        {
            cout << "La divisione si sta muovendo" << endl;
            TerritoryID = finalID;
        };

        virtual void GermanInfantry::changeHealth(double damage )
        {
            health = health - damage;
        };

        virtual int GermanInfantry::getTerritoryID()
        {
            return TerritoryID;
        };
        virtual int gGermanInfantry::etDivisionType()
        {
            return type;
        };
        virtual double GermanInfantry::getAttack()
        {
            return attack;
        };
        virtual double GermanInfantry::getDefense()
        {
            return defence;
        };
        virtual string GermanInfantry::getName()
        {
            return name;
        };
