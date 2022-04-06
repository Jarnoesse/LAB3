#include <iostream>
#include <cmath>
#include <string.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iomanip>
#include <TFitResultPtr.h>
#include <TFitResult.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TMath.h>
using namespace std;

void Ztest(double x1,double x2, double err1, double err2, double alpha){

	double z = abs(x1 - x2) / sqrt(pow(err1, 2) + pow(err2, 2));  //definisco la variabile Z
	
	double prob_z;
	double pvalue_z;
	prob_z = (ROOT::Math::normal_cdf(z,1,0) - 0.5)*2;
	pvalue_z = (1-ROOT::Math::normal_cdf(z,1,0))*2;
	
	
	if(pvalue_z > alpha){
		cout 	<< "Test Z con livello di significativita alpha " << alpha << endl
		<< "Valore di Z = " << z << endl
		<< "Probabilita di avere tale Z o valore minore ( se è maggiore di 1-alpha fallisce): "<< prob_z << endl
		<< "p-value di Z, ossia probabilita di ottenere |Z| maggiore di quanto osservato: "<< pvalue_z <<endl
		<< "Poiche p-value > alpha, H0 non viene rigettata. Il test ha successo." << endl;
	}
	
	if(pvalue_z <= alpha){
		cout 	<< "Test Z con livello di significativita alpha " << alpha << endl
		<< "Valore di Z = " << z << endl
		<< "Probabilita di avere tale Z o valore minore ( se è maggiore di 1-alpha fallisce): "<< prob_z << endl
		<< "p-value di Z, ossia probabilita di ottenere |Z| maggiore di quanto osservato: "<< pvalue_z <<endl
		<< "Poiche p-value < alpha, H0 viene rigettata. Il test non ha successo. La differenza tra i due valori di Z non puo essere attribuita interamente a fattori aleatori." << endl;
	}


}



void MultiGaussLims(double *chan, double *freq,double *background_freq, int *Fit_limit_sx,int *Fit_limit_dx,int *Fit_mid_point,double start_point, int nBins,int nFits){
	int start_bin;
	for(int i=0;i<nBins;i++){   // giro sul numero di bins per trovare il numero del bin a cui corrisponde il mio punto d'inizio
		if(chan[i]==start_point){
		start_bin=i;};
		
	};
	/*int Fit_limit_sx[nFits];   // creo i vettori di limiti sinistri e destri del fit
	int Fit_limit_dx[nFits];
	int Fit_mid_point[nFits];*/
	
	Fit_limit_sx[0]=start_bin;  // assegno al primo limite sinistro il numero del bin di partenza
	int position = start_bin; // creo la variabile che mi dice il limite sx da cui partire per fittare e che aggiorno nel for
	
	
	for(int j=0;j<nFits;j++){  // giro sul numero di fit che voglio fare e implemento l'algoritmo per trovare max, min e mid
		int minPointsx=position;
		int maxPoint=0;
		int minPointdx=0;
		bool not_max=true;
		bool not_min=true;
		bool not_left_start=true;
		bool not_right_end=true;
		
		
		
		while(not_left_start){
		int control=0;
			for(int h=0;h<20;h++){
			
			if(freq[position+h]>background_freq[j]){
				control++;
				}}
			if(control==19){
				not_left_start=false;
				minPointsx=position;
				Fit_limit_sx[j]=chan[position];
				}
				
			
			position++;
		}
		/*
		while(not_max){
			int check=0;
			for(int k=1;k<100;k++){  // questo k<qlled mi dice quanti devono essere i punti successivi minori di questo per 						          considerarlo un massimo
				if(freq[position]>freq[position+k]){
					check++;
				}
			}
			if(check==99){
				not_max=false;
				maxPoint=position;
				Fit_mid_point[j]=freq[position];
			}
			position++;
		} */  //trovare il massimo in verità non mi serve, perchè sceglierò l'apice del fit gaussiano come massimo
		
		while(not_right_end){
		int control=0;
			for(int h=0;h<20;h++){
				
				if(freq[position+h]<background_freq[j]-5){
					control++;
				}}
			if(control==19){
				not_right_end=false;
				minPointsx=position;
				Fit_limit_dx[j]=chan[position];
			}
			position++;
		}
		
		/*while(not_min){   
			int check=0;
			for(int k=1;k<100;k++){  // questo k<qlled mi dice quanti devono essere i punti successivi minori di questo per 						          considerarlo un massimo
				if(freq[position]<freq[position+k]){
					check++;
				}
			}
			if(check==99){
				not_min=false;
				minPointdx=position;
				Fit_limit_dx[j]=chan[position];
				Fit_limit_sx[j+1]=chan[position];
			}
			position++;
		}*/   // utilizzo un metodo più brutale per trovare il minimo!	
	}
	
		
}

void read(string input, double *x,double *y, int nBins){
  
  ifstream parInput(input.c_str());
  int i = 0;

  if (parInput.is_open()) {
    while ( parInput.good() ) {
      parInput >> x[i] >> y[i];   
      i++;   if (i == nBins) break;
    }
    parInput.close();
  }
  }

void MultiGausLED(double *chan, double *freq, double* background,const char *title1 ,const char *title2, int nBins, double start){	
	// come si riempie un TH1

	
  TCanvas* cled = new TCanvas(title1, title1, 600, 400);
  cled->SetFillColor(0);
  cled->SetGrid();
  cled->cd();
	
  TH1F *LEDmult = new TH1F("LEDmult","LEDmultiple",nBins,chan[0]-0.5,chan[nBins-1]+0.5);  
  for (int j=0;j<nBins;j++) {
    LEDmult->SetBinContent(j+1,freq[j]);
  } 
  
  
  
  
  //inizio algoritmo per limiti fit gaussiani
  
  double start_point=start;
  int nFits=9;
  int Fit_limit_sx[nFits];   
  int Fit_limit_dx[nFits];
  int Fit_mid_point[nFits];
  MultiGaussLims(chan,freq,background,Fit_limit_sx, Fit_limit_dx, Fit_mid_point, start_point, nBins, nFits);
  	
  //fine algoritmo per limiti fit gaussiani
  
  
  TF1 *g1    = new TF1("g1","gaus",start_point,Fit_limit_dx[0]);
  g1->SetParameters(1000.,Fit_mid_point[0],25);
  g1->SetLineColor(kCyan);
  TF1 *g2    = new TF1("g2","gaus",Fit_limit_sx[1],Fit_limit_dx[1]);
  g2->SetParameters(1000.,Fit_mid_point[1],25);
  g2->SetLineColor(kBlue);
  TF1 *g3    = new TF1("g3","gaus",Fit_limit_sx[2],Fit_limit_dx[2]);
  g3->SetParameters(1000.,Fit_mid_point[2],25);
  g3->SetLineColor(kRed);
  TF1 *g4    = new TF1("g4","gaus",Fit_limit_sx[3],Fit_limit_dx[3]);
  g4->SetParameters(1000.,Fit_mid_point[3],25);
  g4->SetLineColor(kGreen); 
  TF1 *g5    = new TF1("g5","gaus",Fit_limit_sx[4],Fit_limit_dx[4]);
  g5->SetParameters(1000.,Fit_mid_point[4],25);
  g5->SetLineColor(kYellow);
  TF1 *g6    = new TF1("g6","gaus",Fit_limit_sx[5],Fit_limit_dx[5]);
  g6->SetParameters(1000.,Fit_mid_point[5],25);
  g6->SetLineColor(kBlack);
  TF1 *g7    = new TF1("g7","gaus",Fit_limit_sx[6],Fit_limit_dx[6]);
  g7->SetParameters(1000.,Fit_mid_point[6],25);
  g7->SetLineColor(kOrange);
  TF1 *g8    = new TF1("g8","gaus",Fit_limit_sx[7],Fit_limit_dx[7]);
  g8->SetParameters(1000.,Fit_mid_point[7],25);
  g8->SetLineColor(kYellow);
  TF1 *g9    = new TF1("g9","gaus",Fit_limit_sx[8],Fit_limit_dx[8]);
  g9->SetParameters(1000.,Fit_mid_point[8],25);
  g9->SetLineColor(kMagenta);
  
  LEDmult->Fit("g1","R","e1",start_point,Fit_limit_dx[0]);
  LEDmult->Fit("g2","R+","e1",Fit_limit_sx[1],Fit_limit_dx[1]);
  LEDmult->Fit("g3","R++","e1",Fit_limit_sx[2],Fit_limit_dx[2]);
  LEDmult->Fit("g4","R+++","e1",Fit_limit_sx[3],Fit_limit_dx[3]);
  LEDmult->Fit("g5","R++++","e1",Fit_limit_sx[4],Fit_limit_dx[4]);
  LEDmult->Fit("g6","R+++++","e1",Fit_limit_sx[5],Fit_limit_dx[5]);
  LEDmult->Fit("g7","R++++++","e1",Fit_limit_sx[6],Fit_limit_dx[6]);
  LEDmult->Fit("g8","R+++++++","e1",Fit_limit_sx[7],Fit_limit_dx[7]);
  LEDmult->Fit("g9","R++++++++","e1",Fit_limit_sx[8],Fit_limit_dx[8]);
  
  LEDmult->Draw("e");
  cled->Print(title2);
 
  cout << "Chi^2:" << g1->GetChisquare() << ", number of DoF: " << g1->GetNDF() << " (Probability: " << g1->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g2->GetChisquare() << ", number of DoF: " << g2->GetNDF() << " (Probability: " << g2->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g3->GetChisquare() << ", number of DoF: " << g3->GetNDF() << " (Probability: " << g3->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g4->GetChisquare() << ", number of DoF: " << g4->GetNDF() << " (Probability: " << g4->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g5->GetChisquare() << ", number of DoF: " << g5->GetNDF() << " (Probability: " << g5->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g6->GetChisquare() << ", number of DoF: " << g6->GetNDF() << " (Probability: " << g6->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g7->GetChisquare() << ", number of DoF: " << g7->GetNDF() << " (Probability: " << g7->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g8->GetChisquare() << ", number of DoF: " << g8->GetNDF() << " (Probability: " << g8->GetProb() << ").\n" << endl;
  cout << "Chi^2:" << g9->GetChisquare() << ", number of DoF: " << g9->GetNDF() << " (Probability: " << g9->GetProb() << ").\n" << endl;


  // misuro le distanze picco-picco, faccio il grafico distanze VS #picco e fitto con retta costante
  // attenzione! qui le distanze picco-picco sono ancora in canali!
  
  double peaks[nFits];
  double peaks_err[nFits];
  peaks[0] = g1->GetParameter(1);
  peaks[1] = g2->GetParameter(1);
  peaks[2] = g3->GetParameter(1);
  peaks[3] = g4->GetParameter(1);
  peaks[4] = g5->GetParameter(1);
  peaks[5] = g6->GetParameter(1);
  peaks[6] = g7->GetParameter(1);
  peaks[7] = g8->GetParameter(1);
  peaks[8] = g9->GetParameter(1);
  
  peaks_err[0] = g1->GetParError(1);
  peaks_err[1] = g2->GetParError(1);
  peaks_err[2] = g3->GetParError(1);
  peaks_err[3] = g4->GetParError(1);
  peaks_err[4] = g5->GetParError(1);
  peaks_err[5] = g6->GetParError(1);
  peaks_err[6] = g7->GetParError(1);
  peaks_err[7] = g8->GetParError(1);
  peaks_err[8] = g9->GetParError(1);
  
  double delta_pp[nFits-1];
  
  for(int l=0;l<nFits-1;l++){
  	delta_pp[l]= peaks[l+1]-peaks[l];
  };
  
  double delta_pp_err[nFits-1];
  for(int l=0;l<nFits-1;l++){
  	delta_pp_err[l]= sqrt(peaks_err[l+1]*peaks_err[l+1] + peaks_err[l]*peaks_err[l]);
  }
  
  double delta_pp_number[]={1,2,3,4,5,6,7,8};
  double delta_00[]={0,0,0,0,0,0,0,0};   
  
  
  
  
  // qui dovremo fare grafico di varianze in funzione del numero di picco
  
  


  // qui facciamo l'istogramma con le celle accese (counts = integrale delle gaussiane) che poi fittiamo con poissoniana
}



void LED_intensity_var(){

	int nBins= 4096;
	double chan1[nBins];
	double freq1[nBins];
	double background1[]={10,10,15,30,45,60,85,55,50};
	read("54v28int.txt",chan1,freq1,nBins);
	MultiGausLED(chan1,freq1,background1,"cled_54_28","LED_54v28int_tot.png",nBins,-99.5);
	
	double chan2[nBins];
	double freq2[nBins];
	double background2[]={10,30,55,170,150,150,120,85,50};
	read("54v30int.txt",chan2,freq2,nBins);
	MultiGausLED(chan2,freq2,background2,"cled_54_30","LED_54v30int_tot.png",nBins,-99.5);
	
	double chan3[nBins];
	double freq3[nBins];
	double background3[]={10,50,100,150,150,180,130,100,100};
	read("54v32int.txt",chan3,freq3,nBins);
	MultiGausLED(chan3,freq3,background3,"cled_54_32","LED_54v32int_tot.png",nBins,-99.5);
	
	
	

}
