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


void Sr90_decay_rate(){

	double counts[]={1.42417000e+03,1.43453000e+03,1.44487000e+03,1.45523000e+03,1.46558000e+03,1.47592000e+03,1.48628000e+03,1.49662000e+03,1.50698000e+03,1.51733000e+03,1.52767000e+03,1.53803000e+03,1.54837000e+03,1.55873000e+03,1.56908000e+03,1.57942000e+03,1.58978000e+03,1.60012000e+03,1.61048000e+03,1.62083000e+03};
	double freq[]={2.00000000e+00,2.00000000e+00,5.00000000e+00,4.00000000e+00,4.00000000e+00,8.00000000e+00,1.00000000e+01,1.80000000e+01,2.30000000e+01,2.20000000e+01,2.80000000e+01,1.30000000e+01,1.80000000e+01,1.20000000e+01,1.40000000e+01,7.00000000e+00,4.00000000e+00,3.00000000e+00,1.00000000e+00,2.00000000e+00};
	int nBins= 20 ;
	int totcounts;
	
	// come si riempie un TH1
	
  TCanvas* cSrrate = new TCanvas("cSrrate", "Sr_90_rate", 200, 10, 600, 400);
  cSrrate->SetFillColor(0);
  cSrrate->SetGrid();
  cSrrate->cd();
	
  TH1F *Sr90rate = new TH1F("Sr90rate","Sr90rate",nBins,counts[0]-5.18,counts[nBins-1]+5.18);  
  for (int j=0;j<nBins;j++) {
    Sr90rate->SetBinContent(j+1,freq[j]);
  }
  
  
   //FIT   prima con poissoniana, poi con gaussiana
  TF1* fSr90rate = new TF1("fSr90rate", fitf, 1420,1620,2);
  
  fSr90rate->SetParName(0,"Ampl_pois");                                                
  fSr90rate->SetParName(1,"#mu_pois");
  
  fSr90rate->SetParameter(0, 20);
  fSr90rate->SetParameter(1, 1520);
  //fSr90rate->SetParameter(2, 1);
  fSr90rate->SetLineColor(4);
  Sr90rate->Fit(fSr90rate, "R+");
  
  TF1* fSr90rategauss = new TF1("fSr90rategauss", "gaus", 1420,1620);
  
  fSr90rategauss->SetParName(0,"Ampl_gauss");                                                
  fSr90rategauss->SetParName(1,"#mu_gauss");
  fSr90rategauss->SetParName(2,"#sigma_gauss");
  
  fSr90rategauss->SetParameter(0, 20);
  fSr90rategauss->SetParameter(1, 1520);
  //fSr90rate->SetParameter(2, 1);
  fSr90rategauss->SetLineColor(7);
  Sr90rate->Fit(fSr90rategauss, "R+");
  
  
  
  
  
  Sr90rate->Draw();
  cSrrate->Print("Sr90_decay_rate.png");

  cout << "Chi^2 pois:" << fSr90rate->GetChisquare() << ", number of DoF pois: " << fSr90rate->GetNDF() << " (Probability pois: " << fSr90rate->GetProb() << ").\n" << endl;
  cout << "Chi^2 gauss:" << fSr90rategauss->GetChisquare() << ", number of DoF gauss: " << fSr90rategauss->GetNDF() << " (Probability gauss: " << fSr90rategauss->GetProb() << ").\n" << endl;
  
  // calcolo il decay rate sperimentale e la sua incertezza (in eventi al secondo). Uso i dati della poissoniana
  
  double mean_counts;
  double mean_err;
  mean_counts= fSr90rate->GetParameter(1);
  mean_err=sqrt(mean_counts);
  
  double gate=1; // è in secondi
  
  double rate = mean_counts/gate;
  double rate_err = mean_err/gate;
  
  cout << "Il decay rate del Sr90 è: (" << rate << " +- " << rate_err << ") eventi/s" << endl;
  
  // Calcolo dell'attività
  double A0 = 2.7e3; // kBq
  double A0_err = 1.1e3;
  double t = (365.*3. + 1. - (15.-30.-31.-30.-16.))/365.25; // [y] 15/07/2019 -> 21/03/2022 3y - 5(1/12) + 6(1/365)
  double t_err = 0.01;
  double tau = 28.79 / TMath::Log(2.); //[y]
  double tau_err = 0.01;
  double G=0.469;
  double G_err = 0.001;



  double A=A0*exp(-t/tau);
  double A_err = sqrt(pow(A0_err*exp(-t/tau),2) + pow(t_err*A0*exp(-t/tau)/tau,2) + pow(tau_err*A0*exp(-t/tau)*t/pow(tau,2),2));
  double eff= (rate)/(2*A*G);
  double eff_err = sqrt(pow(rate_err/(2*A*G),2) + pow(A_err*rate/(2*A*A*G),2) + pow(G_err*rate/(2*A*G*G),2));
  cout << "L'Attività è: (" << A << " +- " << A_err << ") Bq \n" << endl
  	<< "L'efficienza è: (" << eff << " +- " << eff_err << ") boh \n" << endl;



 
  
  
  


}
