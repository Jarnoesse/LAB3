#include <string>
#include <vector>
#include <iostream>
using std::string;
#include "Territory.h"
#include "Abstract_Factory.h"
#include "GermanFactory.h"
#include "RussianFactory.h"

void Turn(vector<Territory*> map, vector<Division*> fpArmy, vector<Division*> spArmy) {
    // itero sui giocatori il turno

        // prima fase del turno: mette a video lista dei territori e rispettive divisioni
        std::cout << "Territori dei giocatori e rispettive divisioni al loro interno: " << std::endl;

        std::vector<Territory*>::iterator iterTerr;
        std::vector<Division*>::iterator iterDiv;
        int mapsize= map.size();
        int Army1size= fpArmy.size();
        int Army2size= spArmy.size();

for (int j=0; j<mapsize; j++) {

    string nameTerr = map[j]->getTerritoryName();
    int TerrID = map[j]->getTerritoryID();
    int TerrProprietary=0;
    int TerrInfantry=0;
    int TerrTanks=0;
    int TerrAir=0;

        for (int p = 0; p<Army1size; p++) {
            int checkID = fpArmy[p]->getTerritoryID();
            if(checkID == TerrID){
                TerrProprietary = 1;
                if(fpArmy[p]->getDivisionType()==1){TerrInfantry++;}
                if(fpArmy[p]->getDivisionType()==2){TerrTanks++;}
                if(fpArmy[p]->getDivisionType()==3){TerrAir++;}
            }
         }
        for (int t = 0; t<Army2size; t++) {
            int checkID = spArmy[t]->getTerritoryID();
            if(checkID == TerrID){
                TerrProprietary = 2;
                if(spArmy[t]->getDivisionType()==1){TerrInfantry++;}
                if(spArmy[t]->getDivisionType()==2){TerrTanks++;}
                if(spArmy[t]->getDivisionType()==3){TerrAir++;}
            }
         }

    string x;
    std::cout << nameTerr << "è dell'armata " << x << " ed ha al suo interno: " << TerrInfantry << " divisioni di fanteria, "<< TerrTanks << " divisioni corazzate, " << TerrAir << " stormi."<< std::endl;
}




}
