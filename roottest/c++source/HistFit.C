#include <iostream>
#include <fstream>
#include <string>
#include<cmath>

#include<TGraphErrors.h>
#include<TAxis.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TH1F.h>
#include<TRandom3.h>
#include<TMath.h>
#include<TLegend.h>

//Questa funzione restituisce il massimo.
double FindMax(double *array, int dimension)
{
    double max = array[0];
    for(int i=0;i<dimension;i++)
        if(array[i]>max)
            max = array[i];

    return max;

}

double FindMin(double *array, int dimension)
{
    double min = array[0];
    for(int i=0;i<dimension;i++)
        if(array[i]<min)
            min = array[i];

    return min;

}

void HistFit()
{
    // inizializzzazione variabili
        std::string str;
        int lines=0;

        std::string filename = "np.txt" ;
        std::string outputfilename = "HistFit.txt";


        std::ifstream inputfile;
        std::ofstream outputfile;
        inputfile.open(filename);

    //Conto il numero di righe nel file txt (numero di bin praticamente)
        if(inputfile.is_open())
            {
                while(inputfile.peek()!=EOF)
                {
                    getline(inputfile, str);
                    lines++;
                }
                inputfile.close();
                std::cout << "Number of lines in the file are: " << lines << std::endl;
            }
            else
                std::cout << "Couldn't open the file\n";

    //devo riaprire il file dall' inizio
        inputfile.open(filename);

    //inizializzo gli array dinamici
        //bin = x counts = y
        double t[lines];
        double count[lines];

        int tot = lines;
        lines = 0;

    //loop per leggere effettivamente il file e riempire gli array
        while(inputfile&&lines<tot)
        {

            inputfile >> t[lines];
            inputfile >>count[lines];

            std::cout << t[lines] << " "<< count[lines] << std::endl;
            lines++;
        }
        //setto il canvas
        TCanvas *c1 = new TCanvas("c1","different scales hists",600,400);

        //creo l'istogramma
        TH1F *grafico = new TH1F("h1","my histogram",20,FindMin(count,tot),FindMax(count,tot));

        //fillo l'istogramma
        for (int i = 0;i<tot;i++)grafico->Fill(count[i]);

        grafico->Draw();
        c1->Update();

        // TF1 *funzione = new TF1("gauss",FindMin(bin,tot), FindMax(bin,tot));
         TF1 *funzione = new TF1("funzione","gaus(0)",FindMin(count,tot), FindMax(count,tot));

         grafico->Fit(funzione);
         std::cout << "Function fitted correctly" << std::endl;

         double pvalue = funzione->GetProb();
         std::cout << "Fit Probability is: " << pvalue << std::endl;

         outputfile.open(outputfilename);
         if(outputfile.is_open())
         {
             outputfile << funzione->GetProb() << "," << funzione->GetParameter(0) << "," << funzione->GetParError(0) << "," << funzione->GetParameter(1) << "," << funzione->GetParError(1)<< "," << funzione->GetParameter(2)<<","<<funzione->GetParError(2);
             std::cout << "File saved succsessfully" << std::endl;
         }
         else
         {
             std::cout << "Unable to open the file" << std::endl;
         }

         std::cout << "Macro executed correctly" << std::endl;

}

int main()
{
    HistFit();
    return 1;
}
