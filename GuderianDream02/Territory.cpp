#include <string>
#include <vector>
using std::string;
#include "Territory.h"


Territory::Territory(){

    ProprietaryID =0;
    TerritoryName = "Null";
    TerritoryID = 0;
}
void Territory::setTerritoryID(int newID){
    TerritoryID = newID;
}
void Territory::setTerritoryName(string name){
    TerritoryName=name;
}
void Territory::setTerritoryConnections(std::vector<int> connect){
    Connections=connect;
}
void Territory::setProprietaryID(int newProprietary){
    ProprietaryID=newProprietary;
}
int Territory::getTerritoryID(){
    return TerritoryID;
}
string Territory::getTerritoryName(){
        return TerritoryName;
    }
std::vector<int> Territory::getTerritoryConnections(){
    return Connections;
}
int Territory::getProprietaryID(){
    return ProprietaryID;
}



