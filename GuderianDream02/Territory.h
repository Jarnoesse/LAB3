#ifndef TERRITORY_H
#define TERRITORY_H
#include <string>
#include <vector>
using std::string;

class Territory {

public:
    Territory();
    void setTerritoryID();
    void setTerritoryName(string);
    void setTerritoryConnections();
    void setProprietaryID();
    int getTerritoryID();
    string getTerritoryName();
    std::vector<int> getTerritoryConnections();
    int getProprietaryID();

private:
    int TerritoryID;
    int ProprietaryID;
    string TerritoryName;
    std::vector<int> Connections;

};


#endif // TERRITORY_H
