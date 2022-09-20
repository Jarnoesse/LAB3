#include "Bf109.h"
#include <string>
#include <iostream>

#include "Bf109.h"

        Bf109::Bf109(int givenID)
        {
            name = "Airplane division";
            type = 3;
            attack = 20;
            defence = 20;
            TerritoryID = givenID;
        };
        void Bf109::move(int finalID)
        {
            std::cout << "La divisione si sta muovendo" << std::endl;
            TerritoryID = finalID;
        };

        void Bf109::changeHealth(double damage)
        {
            health = health - damage;
        };

        int Bf109::getTerritoryID()
        {
            return TerritoryID;
        };
        int Bf109::getDivisionType()
        {
            return type;
        };
        double Bf109::getAttack()
        {
            return attack;
        };
        double Bf109::getDefence()
        {
            return defence;
        };
        string Bf109::getName()
        {
            return name;
        };
