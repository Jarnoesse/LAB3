#include <vector>

using std:: vector;

#include "RussianFactory.h"
#include "T34.h"
#include "Yak3.h"
#include "RussianInfantry.h"

RussianFactory::RussianFactory()
{
    Division.push_back(new RussianInfantry(0))
    Division.push_back(new RussianInfantry(0))

    Division.push_back(new T34(0))
    Division.push_back(new T34(0))

    Division.push_back(new Yak3(0))
    Division.push_back(new Yak3(0))
}

RussianFactory::~RussianFactory()
{
    vector< Division*>::iterator i;
    for(i=Division.begin(); i!=Division.end();i++)
    {
        delete *i;
    }
}

int RussianFactory::sizeArmy() const
{
    return Division.size();
}
vector<Division*>::const_iterator RussianFactory::beginArmy() const
{
    return Division.begin();
}
vector<Division*>::const_iterator RussianFactory::endArmy() const
{
    return Division.end();
}
vector<Division*>::const_iterator RussianFactory::getArmy() const
{
    return Division;
}
