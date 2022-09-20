
#include <string>
#include <vector>
#include <iostream>
using std::string;
#include "Territory.h"
#include "Abstract_Factory.h"
#include "GermanFactory.h"
#include "RussianFactory.h"

void Turn(vector<Territory*> map, vector<Division*> fpArmy, vector<Division*> spArmy) {   // Nota: sarebbe da implementare un modo per far alternare i turni di gioco, in modo che non sia sempre lo stesso giocatore a muovere
    // itero sui giocatori il turno

        // prima fase del turno: mette a video lista dei territori e rispettive divisioni
        std::cout << "Territori dei giocatori e rispettive divisioni al loro interno: " << std::endl;

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


    std::cout << nameTerr << " è dell'armata " << TerrProprietary << " ed ha al suo interno: " << TerrInfantry << " divisioni di fanteria, "<< TerrTanks << " divisioni corazzate, " << TerrAir << " stormi."<< std::endl;
}


std::cout << "..." << std::endl;
std::cout << "..." << std::endl;
std::cout << "..." << std::endl;

std::cout << "Adesso tocca al giocatore 1 muoversi e attaccare." << std::endl;
std::cout << "..." << std::endl;

std::cout << "Il giocatore 1 scelga quali divisioni muovere e dove spostarle:" << std::endl;

std::cout << "Di seguito viene stampata una lista dei territori a tua disposizione, il rispettivo ID e con chi confinano:" << std::endl;
for(int i=0;i<mapsize;i++){
    if(map[i]->getProprietaryID()==1){
    std::cout << map[i]->getTerritoryName() << " ha l'ID numero: " << map[i]->getTerritoryID() << " e confina con: ";
    std::vector<int> BorderStatesID = map[i]->getTerritoryConnections();

    for (int j=0;j<BorderStatesID.size();j++){   // qui c'è un avviso, non dovrebbe dare problemi
        for(int k=0;k<mapsize;k++){
        if(map[k]->getTerritoryID()==BorderStatesID[j]){                 // è una funzione modello, perchè posso applicare questo metodo anche in altri casi
        std::cout << map[k]->getTerritoryName() << ", " << std::endl;}   // questa funzione è stata difficile, potrei avere sbagliato qualcosa
    }
    }
}
}

std::cout << "Ora si sceglierà come muovere le truppe..." << std::endl;

int movesnumber1 = (Army1size/2)+1;
for(int k=0;k<movesnumber1;k++){
    string startingterr;
    string movingdivision="padelle";
    int movingdivisionType;
    string arrivalterr;

    std::cout << "Si inserisca il nome del territorio di partenza della divisione: ";
    std::cin >> startingterr;
    std::cout <<"  "<<std::endl;
    while(movingdivision!="fanteria" && movingdivision != "corazzati" && movingdivision != "stormo"){  // breve controllo affinchè si inserisca la giusta parola
    std::cout << "Si inserisca il tipo di divisione che si vuole spostare ( fanteria , corazzati, stormo ): ";
    std::cin >> movingdivision;}
    if(movingdivision=="fanteria"){movingdivisionType=1;}
    if(movingdivision=="corazzati"){movingdivisionType=2;}
    if(movingdivision=="stormo"){movingdivisionType=3;}
    std::cout <<"  "<<std::endl;
    std::cout << "Si inserisca il nome del territorio di arrivo della divisione (attenzione: deve essere collegato, in caso di errori si perde il turno): ";
    std::cin >> arrivalterr;

    //determino gli ID dei territori di partenza e di arrivo
    int IDstart;
    int IDarrival;
    for(int h=0;h<mapsize;h++){
        if(map[h]->getTerritoryName()==startingterr){IDstart=map[h]->getTerritoryID();}
        if(map[h]->getTerritoryName()==arrivalterr){IDarrival=map[h]->getTerritoryID();}
    }
    std::vector<int> PermittedIDs = map[IDstart]->getTerritoryConnections();
    int checkConnections=0;
    for(int g=0;g<PermittedIDs.size();g++){
        if(IDarrival==PermittedIDs[g]){
            checkConnections=1;
            std::cout << "Il territorio d'arrivo è collegato a quello di partenza" << std::endl;
        }
    }

    // determino l'ID della divisione che si muove
    int checkDivision=200;   // ATTENZIONE se la divisione cercata non è nel territorio di partenza selezionato, si finisce in un loop infinito e buon natale
    for(int y=0;y<fpArmy.size();y++){
        if(fpArmy[y]->getDivisionType()==movingdivisionType && fpArmy[y]->getTerritoryID()==IDstart){
            checkDivision=y;  // ho trovato l'ID della divisione che si muove (in realtà trovo tutti quelli possibili, fino a che ne ho)
        }
    }



    if(map[IDarrival]->getProprietaryID()==1 && checkConnections==1 && checkDivision<fpArmy.size()){
        fpArmy[checkDivision]->move(IDarrival);
        std::cout << "La divisione è in marcia..." << std::endl;
            }
            if(map[IDarrival]->getProprietaryID()==2 || checkConnections==0 || checkDivision>=fpArmy.size() ){
                std::cout << "L'ordine di movimento è sbagliato, il turno è saltato!" << std::endl;
      }


}
std::cout << "-------------------------------------------------------------------" << std::endl;
std::cout << "                       " << std::endl;
std::cout << "                       " << std::endl;
std::cout << "Il giocatore 1 ha finito i suoi movimenti, ora può scegliere un territorio nemico da attaccare..." << std::endl;

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


    std::cout << nameTerr << " è dell'armata " << TerrProprietary << " ed ha al suo interno: " << TerrInfantry << " divisioni di fanteria, "<< TerrTanks << " divisioni corazzate, " << TerrAir << " stormi."<< std::endl;
}
 // si riporta qui sopra la mappa completa aggiornata per avere un'idea precisa

std::cout << "..." << std::endl;
std::cout << "..." << std::endl;
std::cout << "..." << std::endl;


string startAttack;
int IDbegin;
int checkStartAttack=0;
while(checkStartAttack==0){
std::cout << "Si inserisca il nome del territorio di partenza dell'attacco ";
std::cin >> startAttack;
for(int h=0;h<mapsize;h++){
    if(map[h]->getTerritoryName()==startAttack){
        IDbegin=map[h]->getTerritoryID();
        if(map[h]->getProprietaryID()==1){checkStartAttack=1;}  // controlla che io stia partendo da un territorio del giocatore 1
    }
}}

string Objective;
int IDObjective;
int checkObjective=0;
while(checkObjective==0){
    std::cout << "Si inserisca il nome del territorio che si vuole attaccare (tutte le divisioni nei due territori verranno automaticamente coinvolte) ";
    std::cin >> Objective;
    for(int h=0;h<mapsize;h++){
        if(map[h]->getTerritoryName()==Objective){

            IDObjective=map[h]->getTerritoryID();   // assegno l'ID al territorio che si chiama così

            std::vector<int> checkTerritoryBorder = map[h]->getTerritoryConnections();   // controllo i confini
            int checkBorders =0;
            for(int e=0;e<checkTerritoryBorder.size();e++){if(map[h]->getTerritoryID()==checkTerritoryBorder[e]){checkBorders=1;}}

            if(map[h]->getProprietaryID()==2 && checkBorders==1){checkObjective=1;}  // controlla che io stia partendo da un territorio del giocatore 1
        }
    }

}


std::cout << "..." << std::endl;
std::cout << "..." << std::endl;
std::cout << "Avviene ora la simulazione della battaglia..." << std::endl;

std::vector<Division*> army1;
std::vector<Division*> army2;

















}  // fine di tuttoooooooooo















