#include "Bf109.h"
#include <string>
#include <iostream>

Bf109::Bf109()
{
    public:
        Bf109(int ID)
        {
            name = "Airplane division";
            type = 3;
            attack = 20;
            defense = 20;
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
