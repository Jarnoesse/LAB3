#include "T34.h"
#include <string>
#include <iostream>


        T34(int ID)
        {
            name = "Infantry division";
            type = 2;
            attack = 15;
            defense = 10;
            Terrytory ID = ID;
        };
        virtual void T34::move(int finalID)
        {
            cout << "La divisione si sta muovendo" << endl;
            TerritoryID = finalID;
        };

        virtual void T34::changeHealth(double damage )
        {
            health = health - damage;
        };

        virtual int T34::getTerritoryID()
        {
            return TerritoryID;
        };
        virtual int T34::getDivisionType()
        {
            return type;
        };
        virtual double T34::getAttack()
        {
            return attack;
        };
        virtual double T34::getDefense()
        {
            return defence;
        };
        virtual string T34::getName()
        {
            return name;
        };
