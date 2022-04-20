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

void cosmic_rays(){

	double chan[]={-8.00000000e+02,-4.00000000e+02,0.00000000e+00,4.00000000e+02,8.00000000e+02,1.20000000e+03,1.60000000e+03,2.00000000e+03,2.40000000e+03,2.80000000e+03,3.20000000e+03,3.60000000e+03,4.00000000e+03,4.40000000e+03,4.80000000e+03,5.20000000e+03,5.60000000e+03,6.00000000e+03,6.40000000e+03,6.80000000e+03,7.20000000e+03,7.60000000e+03,8.00000000e+03,8.40000000e+03,8.80000000e+03,9.20000000e+03,9.60000000e+03,1.00000000e+04,1.04000000e+04,1.08000000e+04,1.12000000e+04,1.16000000e+04,1.20000000e+04,1.24000000e+04,1.28000000e+04,1.32000000e+04,1.36000000e+04,1.40000000e+04,1.44000000e+04,1.48000000e+04,1.52000000e+04,1.56000000e+04,1.60000000e+04,1.64000000e+04,1.68000000e+04,1.72000000e+04,1.76000000e+04,1.80000000e+04,1.84000000e+04,1.88000000e+04,1.92000000e+04,1.96000000e+04,2.00000000e+04,2.04000000e+04,2.08000000e+04,2.12000000e+04,2.16000000e+04,2.20000000e+04,2.24000000e+04,2.28000000e+04,2.32000000e+04,2.36000000e+04,2.40000000e+04,2.44000000e+04,2.48000000e+04,2.52000000e+04,2.56000000e+04,2.60000000e+04,2.64000000e+04,2.68000000e+04,2.72000000e+04,2.76000000e+04,2.80000000e+04,2.84000000e+04,2.88000000e+04,2.92000000e+04,2.96000000e+04,3.00000000e+04,3.04000000e+04,3.08000000e+04,3.12000000e+04,3.16000000e+04,3.20000000e+04,3.24000000e+04,3.28000000e+04,3.32000000e+04,3.36000000e+04,3.40000000e+04,3.44000000e+04,3.48000000e+04,3.52000000e+04,3.56000000e+04,3.60000000e+04,3.64000000e+04,3.68000000e+04,3.72000000e+04,3.76000000e+04,3.80000000e+04,3.84000000e+04,3.88000000e+04,3.92000000e+04,3.96000000e+04,4.00000000e+04,4.04000000e+04,4.08000000e+04,4.12000000e+04,4.16000000e+04,4.20000000e+04,4.24000000e+04,4.28000000e+04,4.32000000e+04,4.36000000e+04,4.40000000e+04,4.44000000e+04,4.48000000e+04,4.52000000e+04,4.56000000e+04,4.60000000e+04,4.64000000e+04,4.68000000e+04,4.72000000e+04,4.76000000e+04,4.80000000e+04,4.84000000e+04,4.88000000e+04,4.92000000e+04,4.96000000e+04,5.00000000e+04};
	double freq[]={0.00000000e+00,7.50000000e+01,200,8.00000000e+01,3.00000000e+00,2.00000000e+00,3.00000000e+00,8.00000000e+00,3.00000000e+00,6.00000000e+00,9.00000000e+00,1.00000000e+00,3.00000000e+00,3.00000000e+00,3.00000000e+00,6.00000000e+00,5.00000000e+00,1.00000000e+00,2.00000000e+00,2.00000000e+00,3.00000000e+00,3.00000000e+00,2.00000000e+00,7.00000000e+00,5.00000000e+00,2.00000000e+00,4.00000000e+00,4.00000000e+00,2.00000000e+00,1.00000000e+00,3.00000000e+00,3.00000000e+00,4.00000000e+00,3.00000000e+00,5.00000000e+00,3.00000000e+00,2.00000000e+00,6.00000000e+00,5.00000000e+00,7.00000000e+00,8.00000000e+00,9.00000000e+00,1.10000000e+01,1.70000000e+01,1.00000000e+01,1.80000000e+01,2.10000000e+01,2.00000000e+01,1.60000000e+01,2.50000000e+01,2.20000000e+01,1.60000000e+01,1.50000000e+01,2.20000000e+01,1.10000000e+01,2.60000000e+01,2.70000000e+01,1.90000000e+01,2.30000000e+01,1.30000000e+01,1.80000000e+01,1.50000000e+01,1.50000000e+01,9.00000000e+00,1.20000000e+01,7.00000000e+00,1.00000000e+01,1.00000000e+01,1.10000000e+01,8.00000000e+00,9.00000000e+00,9.00000000e+00,8.00000000e+00,7.00000000e+00,8.00000000e+00,6.00000000e+00,4.00000000e+00,6.00000000e+00,9.00000000e+00,7.00000000e+00,8.00000000e+00,9.00000000e+00,2.00000000e+00,3.00000000e+00,3.00000000e+00,5.00000000e+00,6.00000000e+00,9.00000000e+00,1.00000000e+00,7.00000000e+00,0.00000000e+00,6.00000000e+00,1.00000000e+00,4.00000000e+00,2.00000000e+00,7.00000000e+00,3.00000000e+00,7.00000000e+00,7.00000000e+00,5.00000000e+00,2.00000000e+00,1.00000000e+00,2.00000000e+00,4.00000000e+00,4.00000000e+00,3.00000000e+00,2.00000000e+00,3.00000000e+00,0.00000000e+00,3.00000000e+00,1.00000000e+00,1.00000000e+00,2.00000000e+00,4.00000000e+00,3.00000000e+00,3.00000000e+00,1.00000000e+00,4.00000000e+00,2.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00};
	int nBins= 128 ;
	
	
// istogramma dei conteggi per canali: 128 bin	
	
TCanvas* ccosmic = new TCanvas("ccosmic", "cosmic_tot", 200, 10, 600, 400);
  ccosmic->SetFillColor(0);
  ccosmic->SetGrid();
  ccosmic->cd();
	
  TH1F *cosmictot = new TH1F("cosmictot","cosmictot",nBins,chan[0]-200,chan[nBins-1]+200);  
  for (int j=0;j<nBins;j++) {
    cosmictot->SetBinContent(j+1,freq[j]);
  } 
  
  
// fit dell'istogramma in canali con una gaussiana sulla parte sinistra della zona di rilascio dell'energia
// intervallo di fit in CHN: 10000 : 21800
  
  TF1* ffit = new TF1("ffit","gaus(0)",0.,50000);
  ffit->SetParameter(0, 0.5);
  ffit->SetParameter(1, 13000); 
  ffit->SetParLimits(0,0.,100.);
  ffit->SetParLimits(1,10000,25000);
  //ffit->SetParLimits(2,0.,1);
  ffit->SetParNames("Ampl","#mu","#sigma");
  cosmictot->Fit("ffit","","e1",12000,21800);
  
  cout << "Fit del plot di cosmic_rays in zona di massimo: " << endl;
  cout << "Chi^2:" << ffit->GetChisquare() << ", number of DoF: " << ffit->GetNDF() << " (Probability: " << ffit->GetProb() << ").\n" << endl;
  double mean_CHN = ffit->GetParameter(1);
  double stddev_CHN = ffit->GetParameter(2);
  double mean_CHN_err = ffit->GetParError(1);
  double stddev_CHN_err = ffit->GetParError(2);
  
  cosmictot->Draw();
  ccosmic->Print("cosmic_tot_CHN.png");
  
  
// creazione dell'istogramma conteggi-energie tramite fattore di calibrazione k e altre conversioni varie
  
  double k_factor=0.0514137; // K: (0.0514137 +- 0.00641083 ) keV/CHN
  double k_err=0.00641083;
  
  
// conversione in energia del valore medio di energia depositata nello scintillatore e del suo errore  
  
  double Tmax_CHN = ffit -> GetParameter(1);
  double Tmax_err_CHN = ffit -> GetParError(1);
  double Tmax = Tmax_CHN*k_factor;
  double Tmax_err= Tmax*sqrt( (Tmax_err_CHN/Tmax_CHN)*(Tmax_err_CHN/Tmax_CHN) + (k_err/k_factor)*(k_err/k_factor) );
  cout << "L'energia con massima frequenza è: (" << Tmax << " +- " << Tmax_err << ");" << endl; 
  
  
// creo l'istogramma in energie
  
double energy[1024];

for(int i=0; i<nBins;i++){
	energy[i]=k_factor*chan[i];
}

double energy_half_step;
energy_half_step=200*k_factor;

TCanvas* ccosmicEn = new TCanvas("ccosmicEn", "cosmic_tot_En", 200, 10, 600, 400);
  ccosmicEn->SetFillColor(0);
  ccosmicEn->SetGrid();
  ccosmicEn->cd();
	
  TH1F *cosmictotEn = new TH1F("cosmictotEn","cosmictotEn",nBins,energy[0]-energy_half_step,energy[nBins-1]+energy_half_step);  
  for (int j=0;j<nBins;j++) {
    cosmictotEn->SetBinContent(j+1,freq[j]);
  } 
  cosmictotEn->Draw("e1");
  ccosmicEn->Print("cosmic_tot_En.png");


// creo l'istogramma in energie in cui faccio lo zoom nella regione di maggiore deposito dell'energia

TCanvas* ccosmic_zoom = new TCanvas("ccosmic_zoom", "cosmic_zoom", 200, 10, 600, 400);
  ccosmic_zoom->SetFillColor(0);
  ccosmic_zoom->SetGrid();
  ccosmic_zoom->cd();
	
  TH1F *cosmic_zoom = new TH1F("cosmic90_zoom","cosmic90_zoom",39,10000.-200,25200.+200);  
  for (int j=0;j<39;j++) {
    cosmic_zoom->SetBinContent(j+1,freq[27+j]);
  } 
  cosmic_zoom->Draw("e1");
  ccosmic_zoom->Print("cosmic__zoom.png");
  
  
// lavoro sulla risoluzione del picco in canali ; ricorda:
// La distanza media picco-picco in CHN è: (96.8362 +- 10.9433) CHN
// La distanza media picco-picco in energia è: (5.56357 +- 0.701375) keV;
// mean_CHN  stddev_CHN  mean_CHN_err  stddev_CHN_err

// risoluzione numero 1: R = delta(CHN)/CHN (va bene in canali o devo averlo per forza in energia???)

double CHN_resolution;
double CHN_resolution_err;
CHN_resolution = ((stddev_CHN)/(mean_CHN));
CHN_resolution_err=((stddev_CHN)/(mean_CHN))*sqrt( (stddev_CHN_err/stddev_CHN)*(stddev_CHN_err/stddev_CHN) + (mean_CHN_err /mean_CHN)*(mean_CHN_err/mean_CHN) );


// risoluzione numero 2: R = 1/sqrt(N), dove N = numero celle accese (in corrispondenza del valore medio???)
double pois_resolution;
double pois_resolution_err;
double delta_pp_CHN=96.8362;   // questa è in CHN   
double delta_pp_CHN_err=10.9433;
double activated_cells = mean_CHN/delta_pp_CHN;  // che cosa uso come errore sulla media? la dev std, la FWHM, l'errore sul parametro?
double activated_cells_err = (mean_CHN/delta_pp_CHN)*sqrt( (stddev_CHN/mean_CHN)*(stddev_CHN/mean_CHN) + (delta_pp_CHN_err /delta_pp_CHN)*(delta_pp_CHN_err/delta_pp_CHN)  );

pois_resolution =1./sqrt(activated_cells);
pois_resolution_err=0.5*(activated_cells_err)/(sqrt(activated_cells*activated_cells*activated_cells));

Ztest(CHN_resolution,pois_resolution,CHN_resolution_err,pois_resolution_err,0.05);

cout << "La risoluzione secondo R = delta(CHN)/CHN è: (" << CHN_resolution <<  " +- " << CHN_resolution_err << ");" << endl;
cout << "La risoluzione secondo R = 1/sqrt(N) è: (" << pois_resolution <<  " +- " << pois_resolution_err << ");" << endl;



  

}
