#include <string>
#include <vector>
#include <iostream>
using std::string;
#include "Territory.h"
#include "Abstract_Factory.h"
#include "GermanFactory.h"
#include "RussianFactory.h"
#include "GameManager.h"
#include "Turn.h"
#include "Turn2.h"

void GameManager(){

    std::cout<< "Inizializzazione del gioco..."<< std::endl;
    std::cout<< "Creazione della mappa di gioco..."<< std::endl;

    std::vector<string> TerritoryNames({"Germany", "Poland", "Yugoslavia", "Russia", "Baltic states", "Ukraine"});
    std::vector<int> TerritoryIDs({0,1,2,3,4,5});  // potrei assegnare a ogni territorio una coordinata (definita tramite classe) tramite una MAPPA della STL
    std::vector<int> conn01({02,03});  // Germania confina con Polonia e Yugoslavia
    std::vector<int> conn02({01,03,04,05,06}); // Polonia confina un po' con tutti
    std::vector<int> conn03({02,06});
    std::vector<int> conn04({02,05,06});
    std::vector<int> conn05({02,04});
    std::vector<int> conn06({02,03,04});  //Ucraina confina con Polonia, Russia e Yugoslavia
    std::vector<std::vector<int>> TerritoryConnections({conn01,conn02,conn03,conn04,conn05,conn06});
    std::vector<int> TerritoryStartingProprietary({1,1,1,2,2,2});

    std::vector<Territory*> Map;
    int TerritoryNumber= 6;   // Variabile utile per ciclare sui territori
    for(int i=0;i<TerritoryNumber;i++){
    Map.push_back(new Territory());
    Map[i]->setTerritoryName(TerritoryNames[i]) ;  //inserire i vari attributi dei diversi territori (eventualmente leggere da vettore di stringhe con nomi territori e loro connessioni)
    Map[i]->setTerritoryID(TerritoryIDs[i]) ;
    Map[i]->setTerritoryConnections(TerritoryConnections[i]);
    Map[i]->setProprietaryID(TerritoryStartingProprietary[i]);
    }

    std::cout<< "La mappa è stata creata con successo. I territori hanno nome, ID, connessioni e proprietario "<< std::endl;

    std::cout<< "Creazione degli eserciti... "<< std::endl;

    // definisco numero divisioni creabili all'interno dell'esercito
    // eventualmente valutare regola per somma pesata delle divisioni (balancing)

    int InfantryNumberGer=4; int TankNumberGer=2; int AirNumberGer=1;
    int InfantryNumberRus=4; int TankNumberRus=2; int AirNumberRus=1;
    int DivisionsNumberGer= InfantryNumberGer+TankNumberGer+AirNumberGer;  // Variabili utili per ciclare sulle divisioni
    int DivisionsNumberRus= InfantryNumberRus+TankNumberRus+AirNumberRus;


    //Creo l'esercito con le sue varie divisioni

    Abstract_Factory* CreaGermania;
    Abstract_Factory* CreaRussia;

    CreaGermania = new GermanFactory(InfantryNumberGer,TankNumberGer,AirNumberGer);
    CreaRussia = new RussianFactory(InfantryNumberRus,TankNumberRus,AirNumberRus);
     vector<Division*> GermanArmy ;
     vector<Division*> RussianArmy ;
     GermanArmy = CreaGermania->getArmy();
     RussianArmy = CreaRussia->getArmy();
     int GermanSize=GermanArmy.size();
     int RussianSize=RussianArmy.size();


    std::cout << "Assegnazione delle divisioni ai territori... " << std::endl;
    // si assegnano alle divisioni i territori in cui le si vuole mettere tramite ciclo for e controllo esterno su vettori GermanArmy e RussianArmy
    std::cout << "Giocatore 1: decidi dove posizionare le tue truppe! " << std::endl;
    std::cout << "Di seguito viene stampata una lista dei territori a tua disposizione e il rispettivo ID:" << std::endl;
    for(int i=0;i<TerritoryNumber;i++){
        if(Map[i]->getProprietaryID()==1){
        std::cout << Map[i]->getTerritoryName() << " ha l'ID numero: " << Map[i]->getTerritoryID() << " e confina con: ";
        std::vector<int> BorderStatesID = Map[i]->getTerritoryConnections();

        for (int j=0;j<BorderStatesID.size();j++){   // qui c'è un avviso, non dovrebbe dare problemi
            for(int k=0;k<TerritoryNumber;k++){
            if(Map[k]->getTerritoryID()==BorderStatesID[j]){                 // è una funzione modello, perchè posso applicare questo metodo anche in altri casi
            std::cout << Map[k]->getTerritoryName() << ", " << std::endl;}   // questa funzione è stata difficile, potrei avere sbagliato qualcosa
        }
        }
    }
    }

    std::cout << "Giocatore 1: ora, dovrai decidere dove mandare ogni tua divisione! Per farlo, scrivi lo Stato in cui vuoi mandare la divisione e clicca invio" << std::endl;
        for(int p=0;p<GermanSize;p++){
            int check=0;
            while(check==0){
            string TerritoryToGo;
            std::cout << "In che territorio si desidera inserire la " << p+1 << "° divisione, di tipo " << GermanArmy[p]->getDivisionType() << "?" << std::endl;
            std::cin >> TerritoryToGo;


            // ciclo sui territori per vedere che il territorio in cui va la divisione sia di giocatore 1 e trovarne l'ID, e assegnarlo alla divisione
            for(int i=0;i<TerritoryNumber;i++){
                if(Map[i]->getTerritoryName()==TerritoryToGo){
                    if(Map[i]->getProprietaryID()==1){
                        GermanArmy[p]->move(Map[i]->getTerritoryID());
                        std::cout << "La divisione è in marcia..." << std::endl;
                        check=1;
                    }
                    if(Map[i]->getProprietaryID()==2){
                        std::cout << "Il territorio selezionato non è tuo!" << std::endl;
                    }
                }
            }
            }
        }

//--------------------------------------------------------------------------------------------------------------//
        std::cout << "Ora tocca al giocatore 2 scegliere!" << std::endl;

        std::cout << "Giocatore 2: decidi dove posizionare le tue truppe! " << std::endl;
        std::cout << "Di seguito viene stampata una lista dei territori a tua disposizione e il rispettivo ID:" << std::endl;
        for(int i=0;i<TerritoryNumber;i++){
            if(Map[i]->getProprietaryID()==2){
            std::cout << Map[i]->getTerritoryName() << " ha l'ID numero: " << Map[i]->getTerritoryID() << " e confina con: ";
            std::vector<int> BorderStatesID = Map[i]->getTerritoryConnections();

            for (int j=0;j<BorderStatesID.size();j++){   // qui c'è un avviso, non dovrebbe dare problemi
                for(int k=0;k<TerritoryNumber;k++){
                if(Map[k]->getTerritoryID()==BorderStatesID[j]){                 // è una funzione modello, perchè posso applicare questo metodo anche in altri casi
                std::cout << Map[k]->getTerritoryName() << ", " << std::endl;}   // questa funzione è stata difficile, potrei avere sbagliato qualcosa
            }
            }
        }
        }

        std::cout << "Giocatore 2: ora, dovrai decidere dove mandare ogni tua divisione! Per farlo, scrivi lo Stato in cui vuoi mandare la divisione e clicca invio" << std::endl;
            for(int p=0;p<RussianSize;p++){
                int check=0;
                while(check==0){
                string TerritoryToGo;
                std::cout << "In che territorio si desidera inserire la " << p+1 << "° divisione, di tipo " << RussianArmy[p]->getDivisionType() << "?" << std::endl;
                std::cin >> TerritoryToGo;


                // ciclo sui territori per vedere che il territorio in cui va la divisione sia di giocatore 1 e trovarne l'ID, e assegnarlo alla divisione
                for(int i=0;i<TerritoryNumber;i++){
                    if(Map[i]->getTerritoryName()==TerritoryToGo){
                        if(Map[i]->getProprietaryID()==2){
                            RussianArmy[p]->move(Map[i]->getTerritoryID());
                            std::cout << "La divisione è in marcia..." << std::endl;
                            check=1;
                        }
                        if(Map[i]->getProprietaryID()==1){
                            std::cout << "Il territorio selezionato non è tuo!" << std::endl;
                        }
                    }
                }
                }
            }


         std::cout << "Ogni divisione è assegnata al suo territorio! Ora si combatte!" << std::endl;
         std:: cout << "Preparazione..." << std::endl;
         std:: cout << "Preparazione..." << std::endl;
         std:: cout << "Preparazione..." << std::endl;
         std:: cout << "Preparazione..." << std::endl;
         std:: cout << "Preparazione..." << std::endl;



    string winner;

    //Ora si gioca:
    bool exit;
    while(exit != true){
    Turn1(Map, GermanArmy, RussianArmy );
    if( GermanArmy.size()==0 || RussianArmy.size()==0){
        if(GermanArmy.size()==0){ winner = " l'unione sovietica";}
        if(RussianArmy.size()==0){ winner = " la germania";}

        exit=true;

    };
    Turn2(Map, GermanArmy, RussianArmy );
    if( GermanArmy.size()==0 || RussianArmy.size()==0){
        if(GermanArmy.size()==0){ winner = " l'unione sovietica";}
        if(RussianArmy.size()==0){ winner = " la germania";}

        exit=true;

    };
    }



}
