#include <vector>

using std:: vector;

#include "GermanFactory.h"
#include "PanzerIV.h"
#include "Bf109.h"
#include "GermanInfantry.h"
#include "Division.h"

GermanFactory::GermanFactory()
{
    army.push_back(new GermanInfantry());
    Division.push_back(new GermanInfantry(0))

    Division.push_back(new Tiger(0))
    Division.push_back(new Tiger(0))

    Division.push_back(new Bf109(0))
    Division.push_back(new Bf109(0))
}

GermanFactory::~GermanFactory()
{
    vector< Division*>::iterator i;
    for(i=Division.begin(); i!=Division.end();i++)
    {
        delete *i;
    }
}

int GermanFactory::sizeArmy() const
{
    return Division.size();
}
vector<Division*>::const_iterator GermanFactory::beginArmy() const
{
    return Division.begin();
}
vector<Division*>::const_iterator GermanFactory::endArmy() const
{
    return Division.end();
}
vector<Division*>::const_iterator GermanFactory::getArmy() const
{
    return Division;
}
