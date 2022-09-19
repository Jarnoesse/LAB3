#include <string>
#include <vector>
#include <iostream>
using std::string;
#include "Territory.h"
#include "Abstract_Factory.h"
#include "GermanFactory.h"
#include "RussianFactory.h"
#include "GameManager.h"

void GameManager(){

    std::cout<< "Inizializzazione del gioco..."<< std::endl;
    std::cout<< "Creazione della mappa di gioco..."<< std::endl;

    std::vector<Territory*> Map;
    for(int i=0;i<6;i++){
    Map.push_back(new Territory());
    Map[i]->cosevariesettaggio   //inserire i vari attributi dei diversi territori (eventualmente leggere da vettore di stringhe con nomi territori e loro connessioni)
    }

    std::cout<< "Creazione degli eserciti... "<< std::endl;

    // definisco numero divisioni creabili all'interno dell'esercito
    // eventualmente valutare regola per somma pesata delle divisioni (balancing)
    int InfantryNumberGer=4; int TankNumberGer=2; int AirNumberGer=1;
    int InfantryNumberRus=4; int TankNumberRus=2; int AirNumberRus=1;

    //Creo l'esercito con le sue varie divisioni

    Abstract_Factory* CreaGermania;
    Abstract_Factory* CreaRussia;

    CreaGermania = new GermanFactory(InfantryNumberGer,TankNumberGer,AirNumberGer);
    CreaRussia = new RussianFactory(InfantryNumberRus,TankNumberRus,AirNumberRus);
     vector<Division*> GermanArmy ;
     vector<Division*> RussianArmy ;
     GermanArmy = CreaGermania->getArmy();
     RussianArmy = CreaRussia->getArmy();


    std::cout << "Assegnazione delle divisioni ai territori... " << std::endl;
    // si assegnano alle divisioni i territori in cui le si vuole mettere tramite ciclo for e controllo esterno su vettori GermanArmy e RussianArmy

    //Ora si gioca:
    bool exit;
    while(exit != true){
    Turn(*Map; *GermanArmy; *RussianArmy );
    }



}
