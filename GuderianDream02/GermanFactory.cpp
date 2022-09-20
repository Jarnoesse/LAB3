#include <vector>

using std::vector;

#include "GermanFactory.h"
#include "PanzerIV.h"
#include "Bf109.h"
#include "GermanInfantry.h"

GermanFactory::GermanFactory(int infantry, int tank, int airplane)
{
    army.push_back(new GermanInfantry(0));
    army.push_back(new GermanInfantry(0));

    army.push_back(new PanzerIV(0));
    army.push_back(new PanzerIV(0));

    army.push_back(new Bf109(0));
    army.push_back(new Bf109(0));
}

GermanFactory::~GermanFactory()
{
    vector< Division*>::iterator i;
    for(i=army.begin(); i!=army.end();i++)
    {
        delete *i;
    }
}

int GermanFactory::sizeArmy() const
{
    return army.size();
}
vector<Division*>::const_iterator GermanFactory::beginArmy() const
{
    return army.begin();
}
vector<Division*>::const_iterator GermanFactory::endArmy() const
{
    return army.end();
}
vector<Division*> GermanFactory::getArmy() const
{
    return army;
}
