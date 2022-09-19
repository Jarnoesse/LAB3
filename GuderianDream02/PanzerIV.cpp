#include "PanzerIV.h"
#include <string>
#include <iostream>



        PanzerIV(int ID)
        {
            name = "Infantry division";
            type = 2;
            attack = 15;
            defense = 10;
            Terrytory ID = ID;
        };
        virtual void PanzerIV::move(int finalID)
        {
            cout << "La divisione si sta muovendo" << endl;
            TerritoryID = finalID;
        };

        virtual void PanzerIV::changeHealth(double damage )
        {
            health = health - damage;
        };

        virtual int PanzerIV::getTerritoryID()
        {
            return TerritoryID;
        };
        virtual int PanzerIV::getDivisionType()
        {
            return type;
        };
        virtual double PanzerIV::getAttack()
        {
            return attack;
        };
        virtual double PanzerIV::getDefense()
        {
            return defence;
        };
        virtual string PanzerIV::getName()
        {
            return name;
        };
