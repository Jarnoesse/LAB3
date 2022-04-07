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

// questa funzione trova la posizione del massimo all' interno dell' array
int FindMaxPosition(double *array, int dimension)
{
    double max=0;
    int position;
    for(int i=0;i<dimension;i++)
    {
        if(array[i]>max)
        {
            max = array[i];
            position = i;
        }
    }
    return position;
}

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

int ExpFit(){

// inizializzzazione variabili
    double data;
    std::string str;
    int lines=0;

    std::string filename = "bridge.txt" ;
    std::string outputfilename = "ExpFit.txt";


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
    double bin[lines];
    double count[lines];
    double bin_errors[lines];
    double count_errors[lines];
    int tot = lines;
    lines = 0;

//loop per leggere effettivamente il file e riempire gli array
    while(inputfile&&lines<tot)
    {

        inputfile >> count[lines];
        inputfile >> count_errors[lines];

        inputfile >> bin[lines];
        inputfile >> bin_errors[lines];
        lines++;
    }

    for(int i=0;i<lines;i++)
    {
        std::cout << " i " << i << " bin " << bin[i] << " value " << count[i] << std::endl;
    }

//Creo la canvas
    TCanvas *canvas = new TCanvas("nome","nome",200,10,600,400);
        canvas->SetFillColor(0);
        canvas->cd();

//creo il grafico
    TGraphErrors *grafico = new TGraphErrors(lines,bin,count,bin_errors,count_errors);

//Setto il grafico
    grafico->SetMarkerStyle(8);
    grafico->SetMarkerSize(1);

    grafico->SetTitle("Assorbimento");
    grafico->GetXaxis()->SetTitle("1/s [mm^-1]");
    grafico->GetYaxis()->SetTitle("1/s' [mm^-1]");

    grafico->Draw("AP");

//definisco la funzione da fittare

   // TF1 *funzione = new TF1("gauss",FindMin(bin,tot), FindMax(bin,tot));
    TF1 *funzione = new TF1("funzione","[0]*exp(-[1]*x)",FindMin(bin,tot), FindMax(bin,tot));
//setto i parametri
    grafico->Fit(funzione);
    std::cout << "Function fitted correctly" << std::endl;

    double pvalue = funzione->GetProb();
    std::cout << "Fit Probability is: " << pvalue << std::endl;



    outputfile.open(outputfilename);
    if(outputfile.is_open())
    {
        outputfile << funzione->GetProb() << "," << funzione->GetParameter(0) << "," << funzione->GetParError(0) << "," << funzione->GetParameter(1) << "," << funzione->GetParError(1);
        std::cout << "File saved succsessfully" << std::endl;
    }
    else
    {
        std::cout << "Unable to open the file" << std::endl;
    }

    std::cout << "Macro executed correctly" << std::endl;
    return 1;
}

//questo è per poi compilarlo correttamente
int main()
{
    ExpFit();
    return 1;
}
