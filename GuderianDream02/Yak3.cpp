#include "Yak3.h"
#include <string>
#include <iostream>


        Yak3(int ID)
        {
            name = "Airplane division";
            type = 3;
            attack = 20;
            defense = 20;
            Terrytory ID = ID;
        };
        virtual void Yak3::move(int finalID)
        {
            cout << "La divisione si sta muovendo" << endl;
            TerritoryID = finalID;
        };

        virtual void Yak3::changeHealth(double damage )
        {
            health = health - damage;
        };

        virtual int Yak3::getTerritoryID()
        {
            return TerritoryID;
        };
        virtual int Yak3::getDivisionType()
        {
            return type;
        };
        virtual double Yak3::getAttack()
        {
            return attack;
        };
        virtual double Yak3::getDefense()
        {
            return defence;
        };
        virtual string Yak3::getName()
        {
            return name;
        };

