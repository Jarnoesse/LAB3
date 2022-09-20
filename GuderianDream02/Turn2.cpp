#include <string>
#include <vector>
#include <iostream>
using std::string;
#include "Territory.h"
#include "Abstract_Factory.h"
#include "GermanFactory.h"
#include "RussianFactory.h"
#include <random>

void Turn2(vector<Territory*> map, vector<Division*> fpArmy, vector<Division*> spArmy) {   // Nota: sarebbe da implementare un modo per far alternare i turni di gioco, in modo che non sia sempre lo stesso giocatore a muovere
    // itero sui giocatori il

    int mapsize= map.size();
    int Army1size= fpArmy.size();
    int Army2size= spArmy.size();

        // prima fase del turno: mette a video lista dei territori e rispettive divisioni
        std::cout << "Territori dei giocatori e rispettive divisioni al loro interno: " << std::endl;



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


    std::cout << nameTerr << " è dell'armata " << map[j]->getProprietaryID() << " ed ha al suo interno: " << TerrInfantry << " divisioni di fanteria, "<< TerrTanks << " divisioni corazzate, " << TerrAir << " stormi."<< std::endl;
}


std::cout << "..." << std::endl;
std::cout << "..." << std::endl;
std::cout << "..." << std::endl;

std::cout << "Adesso tocca al giocatore 2 muoversi e attaccare." << std::endl;
std::cout << "..." << std::endl;

std::cout << "Il giocatore 2 scelga quali divisioni muovere e dove spostarle:" << std::endl;

std::cout << "Di seguito viene stampata una lista dei territori a tua disposizione, il rispettivo ID e con chi confinano:" << std::endl;
for(int i=0;i<mapsize;i++){
    if(map[i]->getProprietaryID()==2){
    std::cout << map[i]->getTerritoryName() << " ha l'ID numero: " << map[i]->getTerritoryID() << " e confina con: ";
    std::vector<int> BorderStatesID = map[i]->getTerritoryConnections();

    for (int j=0;j<(int)BorderStatesID.size();j++){   // qui c'è un avviso, non dovrebbe dare problemi
        for(int k=0;k<mapsize;k++){
        if(map[k]->getTerritoryID()==BorderStatesID[j]){                 // è una funzione modello, perchè posso applicare questo metodo anche in altri casi
        std::cout << map[k]->getTerritoryName() << ", " << std::endl;}   // questa funzione è stata difficile, potrei avere sbagliato qualcosa
    }
    }
}
}

std::cout << "Ora si sceglierà come muovere le truppe..." << std::endl;

int movesnumber2 = (Army2size/2)+1;
for(int k=0;k<movesnumber2;k++){
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
    for(int g=0;g<(int)PermittedIDs.size();g++){
        if(IDarrival==PermittedIDs[g]){
            checkConnections=1;
            std::cout << "Il territorio d'arrivo è collegato a quello di partenza" << std::endl;
        }
    }

    // determino l'ID della divisione che si muove
    int checkDivision=200;   // ATTENZIONE se la divisione cercata non è nel territorio di partenza selezionato, si finisce in un loop infinito e buon natale
    for(int y=0;y<(int)spArmy.size();y++){
        if(spArmy[y]->getDivisionType()==movingdivisionType && spArmy[y]->getTerritoryID()==IDstart){
            checkDivision=y;  // ho trovato l'ID della divisione che si muove (in realtà trovo tutti quelli possibili, fino a che ne ho)
        }
    }



    if(map[IDarrival]->getProprietaryID()==2 && checkConnections==1 && checkDivision<(int)spArmy.size()){
        spArmy[checkDivision]->move(IDarrival);
        std::cout << "La divisione è in marcia..." << std::endl;
            }
            if(map[IDarrival]->getProprietaryID()==1 || checkConnections==0 || checkDivision>=(int)spArmy.size() ){
                std::cout << "L'ordine di movimento è sbagliato, il turno è saltato!" << std::endl;
      }


}
std::cout << "-------------------------------------------------------------------" << std::endl;
std::cout << "                       " << std::endl;
std::cout << "                       " << std::endl;
std::cout << "Il giocatore 2 ha finito i suoi movimenti, ora può scegliere un territorio nemico da attaccare..." << std::endl;

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
        if(map[h]->getProprietaryID()==2){checkStartAttack=1;}  // controlla che io stia partendo da un territorio del giocatore 1
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
            for(int e=0;e<(int)checkTerritoryBorder.size();e++){if(IDbegin==checkTerritoryBorder[e]){checkBorders=1;}}

            if(map[h]->getProprietaryID()==1 && checkBorders==1){checkObjective=1;}  // controlla che io stia partendo da un territorio del giocatore 1
        }
    }

}


std::cout << "..." << std::endl;
std::cout << "..." << std::endl;
std::cout << "Avviene ora la simulazione della battaglia..." << std::endl;

std::vector<Division*> army1;
std::vector<Division*> army2;

// riempio l'armata 1 e nel frattempo sommo attacco, difesa complessivi -> a quel punto uso una probabilità pesata per decidere chi vince
int w=0;
double TotalAttackArmy2=0;   // questo conta quando attacco

for(int q=0;q< (int)Army2size;q++){
    if(spArmy[q]->getTerritoryID()==IDbegin){

        TotalAttackArmy2=TotalAttackArmy2+spArmy[q]->getAttack();

    }
}

int r=0;
double TotalDefenceArmy1=0;   // questo conta quando attacco

for(int q=0;q< Army1size;q++){
    if(fpArmy[q]->getTerritoryID()==IDbegin){

        TotalDefenceArmy1=TotalDefenceArmy1+fpArmy[q]->getDefence();

    }
}
int topValue=0;
int bottomValue=0;
if(TotalAttackArmy2>=TotalDefenceArmy1){
    topValue = TotalAttackArmy2;
    bottomValue=TotalDefenceArmy1;
}
if(TotalAttackArmy2<TotalDefenceArmy1){
    bottomValue = TotalAttackArmy2;
    topValue=TotalDefenceArmy1;
}


int limitValue= (bottomValue*50)/topValue;    // se bottom è 0, il limite è 0, se bottom è circa top, il limite è 50


// Calcolo gli esiti della battaglia:

std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist100(1,100); // distribution in range [1, 6]

     int value= dist100(rng);
     int ProprietaryIDWinner=0;
     int ProprietaryIDLoser=0;

     if(TotalAttackArmy2>=TotalDefenceArmy1){
         if( value <= limitValue){ProprietaryIDWinner=1;ProprietaryIDLoser=2;}
         if( value > limitValue){ProprietaryIDWinner=2;ProprietaryIDLoser=1;}
     }

     if(TotalAttackArmy2<TotalDefenceArmy1){
         if( value <= limitValue){ProprietaryIDWinner=2;ProprietaryIDLoser=1;}
         if( value > limitValue){ProprietaryIDWinner=1;ProprietaryIDLoser=2;}
     }

     if(ProprietaryIDWinner==2){   // Se vince 1, 2 perde tutte le unità in quella zona
         std::cout << "Ha vinto il giocatore 2!" << std::endl;
        for(int t=0;t<Army1size;t++){
            if(fpArmy[t]->getTerritoryID()==IDObjective){ fpArmy.erase(fpArmy.begin()+t);}
            //if(fpArmy[t]->getTerritoryID()==IDbegin){ fpArmy.erase(fpArmy.begin()+t);}   dovrei implementare una roba tipo la salute

        }
     }

     if(ProprietaryIDWinner==1){   // Se vince 1, 2 perde tutte le unità in quella zona
         std::cout << "Ha vinto il giocatore 1!" << std::endl;
        for(int t=0;t<Army1size;t++){
            if(spArmy[t]->getTerritoryID()==IDbegin){ spArmy.erase(spArmy.begin()+t);}
            //if(spArmy[t]->getTerritoryID()==IDObjective){ spArmy.erase(spArmy.begin()+t);}   dovrei implementare una roba tipo la salute

        }
     }



     std::cout << " Adesso è il turno del primo giocatore!" << std::endl;















}  // fine di tuttoooooooooo
