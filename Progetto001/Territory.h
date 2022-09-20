#ifndef TERRITORY_H
#define TERRITORY_H
#include <string>
#include <vector>
using std::string;

class Territory {



public:
    Territory();
    void setTerritoryID(int);
    void setTerritoryName(string);
    void setTerritoryConnections(std::vector<int>);
    void setProprietaryID(int);
    int getTerritoryID();
    string getTerritoryName();
    std::vector<int> getTerritoryConnections();
    int getProprietaryID();
    string getNameFromID(int);

private:
    int TerritoryID;
    int ProprietaryID;
    string TerritoryName;
    std::vector<int> Connections;

};




#endif // TERRITORY_H
