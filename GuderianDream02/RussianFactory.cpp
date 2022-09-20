#include <vector>

using std::vector;

#include "RussianFactory.h"
#include "T34.h"
#include "Yak3.h"
#include "RussianInfantry.h"

RussianFactory::RussianFactory(int infantry, int tank, int airplane)
{
    army.push_back(new RussianInfantry(0));
    army.push_back(new RussianInfantry(0));

    army.push_back(new T34(0));
    army.push_back(new T34(0));

    army.push_back(new Yak3(0));
    army.push_back(new Yak3(0));
}

RussianFactory::~RussianFactory()
{
    vector< Division*>::iterator i;
    for(i=army.begin(); i!=army.end();i++)
    {
        delete *i;
    }
}

int RussianFactory::sizeArmy() const
{
    return army.size();
}
vector<Division*>::const_iterator RussianFactory::beginArmy() const
{
    return army.begin();
}
vector<Division*>::const_iterator RussianFactory::endArmy() const
{
    return army.end();
}
vector<Division*> RussianFactory::getArmy() const
{
    return army;
}
