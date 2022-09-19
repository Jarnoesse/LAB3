#include "T34.h"
#include <string>
#include <iostream>

T34::T34()
{
    public:
        T34(int ID)
        {
            name = "Infantry division";
            type = 2;
            attack = 15;
            defense = 10;
            Terrytory ID = ID;
        };
        virtual void move(int finalID)
        {
            cout << "La divisione si sta muovendo" << endl;
            TerritoryID = finalID;
        };

        virtual void changeHealth(double damage )
        {
            health = health - damage;
        };

        virtual int getTerritoryID()
        {
            return TerritoryID;
        };
        virtual int getDivisionType()
        {
            return type;
        };
        virtual double getAttack()
        {
            return attack;
        };
        virtual double getDefense()
        {
            return defence;
        };
        virtual string getName()
        {
            return name;
        };
    private:
        int TerritoryID;
        double health;
        string name;
        double attack;
        double defence;
        double type;
    };
}
