#include "Yak3.h"
#include <string>
#include <iostream>

#include "Yak3.h"

        Yak3::Yak3(int ID)
        {
            name = "Airplane division";
            type = 3;
            attack = 20;
            defence = 20;
            TerritoryID = ID;
        };
        void Yak3::move(int finalID)
        {
            std::cout << "La divisione si sta muovendo" << std::endl;
            TerritoryID = finalID;
        };

        void Yak3::changeHealth(double damage )
        {
            health = health - damage;
        };

        int Yak3::getTerritoryID()
        {
            return TerritoryID;
        };
        int Yak3::getDivisionType()
        {
            return type;
        };
        double Yak3::getAttack()
        {
            return attack;
        };
        double Yak3::getDefence()
        {
            return defence;
        };
        string Yak3::getName()
        {
            return name;
        };

