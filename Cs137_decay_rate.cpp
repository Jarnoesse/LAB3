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

double fitf(double *x,double *par) {
   double arg = 0;
   double fitval = par[0]*TMath::Poisson(x[0],par[1]);
   return fitval;
}


void Cs137_decay_rate(){

	float counts[]={6.63512000e+03,6.66337000e+03,6.69162000e+03,6.71987000e+03,6.74812000e+03,6.77637000e+03,6.80462000e+03,6.83287000e+03,6.86112000e+03,6.88937000e+03,6.91762000e+03,6.94587000e+03,6.97412000e+03,7.00237000e+03,7.03062000e+03,7.05887000e+03,7.08712000e+03,7.11537000e+03,7.14362000e+03,7.17187000e+03};
	double freq[]={1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,6.00000000e+00,6.00000000e+00,7.00000000e+00,2.10000000e+01,1.90000000e+01,2.90000000e+01,2.30000000e+01,2.30000000e+01,2.10000000e+01,2.00000000e+01,1.00000000e+01,8.00000000e+00,1.00000000e+00,4.00000000e+00,1.00000000e+00};
	int nBins= 20 ;
	int totcounts;
	
	// come si riempie un TH1
	
  TCanvas* cCsrate = new TCanvas("cCsrate", "Cs_137_rate", 200, 10, 600, 400);
  cCsrate->SetFillColor(0);
  cCsrate->SetGrid();
  cCsrate->cd();
	
  TH1F *Cs137rate = new TH1F("Cs137rate","Cs137rate",nBins,counts[0]-14.125,counts[nBins-1]+14.125);  
  for (int j=0;j<nBins;j++) {
    Cs137rate->SetBinContent(j+1,freq[j]);
  }
  
  
   //FIT   prima con poissoniana, poi con gaussiana
  TF1* fCs137rate = new TF1("fCs137rate", fitf, 6600, 7200,2);
  
  fCs137rate->SetParName(0,"Ampl_pois");                                                
  fCs137rate->SetParName(1,"#mu_pois");
  
  fCs137rate->SetParameter(0, 444);
  fCs137rate->SetParameter(1, 6900);
  //fCs137rate->SetParameter(2, 1);
  fCs137rate->SetLineColor(4);
  Cs137rate->Fit(fCs137rate, "R+");
  
  TF1* fCs137rategauss = new TF1("fCs137rategauss", "gaus", 6600, 7200);
  
  fCs137rategauss->SetParName(0,"Ampl_gauss");                                                
  fCs137rategauss->SetParName(1,"#mu_gauss");
  fCs137rategauss->SetParName(2,"#sigma_gauss");
  
  fCs137rategauss->SetParameter(0, 444);
  fCs137rategauss->SetParameter(1, 6900);
  //fCs137rate->SetParameter(2, 1);
  fCs137rategauss->SetLineColor(7);
  Cs137rate->Fit(fCs137rategauss, "R+");
  
  
  
  
  
  Cs137rate->Draw();
  cCsrate->Print("Cs137_decay_rate.png");

  cout << "Chi^2 pois:" << fCs137rate->GetChisquare() << ", number of DoF pois: " << fCs137rate->GetNDF() << " (Probability pois: " << fCs137rate->GetProb() << ").\n" << endl;
  cout << "Chi^2 gauss:" << fCs137rategauss->GetChisquare() << ", number of DoF gauss: " << fCs137rategauss->GetNDF() << " (Probability gauss: " << fCs137rategauss->GetProb() << ").\n" << endl;
  
  // calcolo il decay rate sperimentale e la sua incertezza (in eventi al secondo). Uso i dati della poissoniana
  
  double mean_counts;
  double mean_err;
  mean_counts= fCs137rate->GetParameter(1);
  mean_err=sqrt(mean_counts);
  
  double gate=1; // è in secondi
  
  double rate = mean_counts/gate;
  double rate_err = mean_err/gate;
  
  cout << "Il decay rate del Cs137 è: (" << rate << " +- " << rate_err << ") eventi/s" << endl;
  
  
  // stimo l'efficienza  (manca errore)
  
  double t = 3.28; // anni dalla misura di A0
  double G=0.469;
  double tau=43.52; //anni
  double eff;
  double A0= 37000;
  double A;
  
  A=A0*exp(-t/tau);
  eff= (rate)/(2*A*G);
  
  cout << "L'efficienza è: " << eff << endl;
  
  
  


}
