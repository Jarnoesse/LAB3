#include "Bf109.h"
#include <string>
#include <iostream>


        Bf109::Bf109(int ID)
        {
            name = "Airplane division";
            type = 3;
            attack = 20;
            defense = 20;
            Terrytory ID = ID;
        };
        virtual void Bf109::move(int finalID)
        {
            cout << "La divisione si sta muovendo" << endl;
            TerritoryID = finalID;
        };

        virtual void Bf109::changeHealth(double damage )
        {
            health = health - damage;
        };

        virtual int Bf109::getTerritoryID()
        {
            return TerritoryID;
        };
        virtual int Bf109::getDivisionType()
        {
            return type;
        };
        virtual double Bf109::getAttack()
        {
            return attack;
        };
        virtual double Bf109::getDefense()
        {
            return defence;
        };
        virtual string Bf109::getName()
        {
            return name;
        };
