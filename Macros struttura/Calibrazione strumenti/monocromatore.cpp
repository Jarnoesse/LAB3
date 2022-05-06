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
  
  void analizzo_picco( double *x_CHN, double *y_counts, int nBins, double left_limit, double right_limit, double results[][7], int result_number, const char *title1,const char *title2){
  
  /*TCanvas* cpicco = new TCanvas(title1, title1, 600, 400);
  cpicco->SetFillColor(0);
  cpicco->SetGrid();
  cpicco->cd();*/
  
  	TH1F *picco = new TH1F("picco n","picco n",nBins,x_CHN[0]-0.5,x_CHN[nBins-1]+0.5);  
  for (int j=0;j<nBins;j++) {
    picco->SetBinContent(j+1,y_counts[j]);
  }
  
  TF1 *g1  = new TF1("g1","gaus",left_limit,right_limit);
  g1->SetParameters(1000.,1500,25);
  
  picco->Fit("g1","RMS","e1",left_limit,right_limit);
  
  double mean;
  double mean_err;
  double stddev;
  double stddev_err;
  double chisquared;
  double DoF;
  double probability;
  
  mean = g1->GetParameter(1);
  mean_err = g1->GetParError(1);
  stddev = g1->GetParameter(2);
  stddev_err = g1->GetParError(2);
  chisquared = g1->GetChisquare();
  DoF = g1->GetNDF();
  probability = g1->GetProb();
  
  results[result_number][0]=mean;
  results[result_number][1]=mean_err;
  results[result_number][2]=stddev;
  results[result_number][3]=stddev_err;
  results[result_number][4]=chisquared;
  results[result_number][5]=DoF;
  results[result_number][6]=probability;
  
  /*picco->Draw("e");
  cpicco->Print(title2);*/
  
  
  }
  
  // ho una ventina di grafici spettrali, ognuno dei quali necessiterà di un fit gaussiano in una certa regione (variabile)
  // mi piacerebbe automatizzare il processo di lettura grafici e fittaggio, lasciando come unici parametri liberi i limiti dell'intervallo
  // la macro dovrebbe resituirmi array con valori medi, deviazioni, chiquadri, dof, p-values
  // ottenuti questi valori, sparerò fuori il grafico che associa una #lambda ad ogni valore di tacca e il suo fit
  
  // ora la domanda è: posso girare un ciclo for e usare un arrai di caratteri per selezionare il file corretto?
  
void monocromatore(){


int nPoints = 24;
double results[25][7]; //creo un doppio array per i risultati
char labels[][20]={"484_0","494_0","504_0","514_0","524_0","534_0","544_0","554_0","563_8","574_2",
"584_0","591_4","604_0","614_0","624_0","634_2","644_0","654_0","664_0","674_0","683_8","901_0","915_0","934_6"};

double left_limit[]={ 680,705,732, 760,792,820, 851,876,906, 932,963,983,  1021,1051,1081, 1112,1140,1171, 1197,1229,1256, 1950,2002,1110};
double right_limit[]={695,725,753, 782,810,838, 867,895,923, 952,982,1000, 1040,1068,1097, 1130,1159,1187, 1215,1246,1276, 1968,2017,1140};

 	for(int i=0;i<nPoints;i++){   // current set permette di scegliere quale hist analizzare
	char name[30]={".txt"};
	char png[30]={".png"};
	char tacca[20]={labels[i][0], labels[i][1], labels[i][2], labels[i][3],labels[i][4]};
	
	int nBins=2048;
	double chan[nBins];
	double freq[nBins];
	read(strcat(tacca,name),chan,freq,nBins);
	analizzo_picco(chan,freq,nBins,left_limit[i],right_limit[i],results,i, tacca,strcat(tacca,png));
	
	
	}
	
	
	double means[nPoints];
	double dev_std[nPoints];
	
	for(int d=0;d<nPoints;d++){
	means[d]= results[d][0];
	dev_std[d]= results[d][2];
	//cout << "La probabilità del " << d << "-esimo fit è: " << results[d][6] << endl;
	//cout << "Il suo chi quadro è: " << results[d][4] << endl;
	//cout << endl;
	}
	
	// kekw i fit vengono tutti... ora tocca alla conversione da canali a lunghezza d'onda dei valori medi e delle dev std!
	// dopodichè dovrò fare la conversione da tacche a lunghezza d'onda (ossia canali)
	
	// copio incollo i parametri della relazione #CHN -> #lambda
	double d=1.76632e+02;  // parametro di grado 0
	double derr=1.81144e+00;
	double b=-1.86146e-05;  // parametro di grado 2
	double berr=7.57965e-06;
	double c= -1.15821e-09;  // parametro di grado 3
	double cerr= 2.53283e-09;
	double a=3.85866e-01;  // parametro di grado 1
	double aerr=6.83579e-03;
	
	// le mie x sono le medie, i loro errori sono la dev std. Calcolo #lambda e il suo errore in un ciclo for
	double lambda[nPoints];
	double lambda_err[nPoints];
	
	for(int i=0;i< nPoints;i++){
	double x= means[i];
	double xerr= dev_std[i];
	
	lambda[i]= a*x+b*x*x+c*x*x*x+d;
	double fa = x* aerr;
	double fb = x*x*berr;
	double fc = x*x*x*cerr;
	double fx = (a+2*b*x+3*c*x*x)*xerr;
	double ferr_on_f= sqrt(fa*fa+fb*fb+fc*fc+fx*fx);
	lambda_err[i]=ferr_on_f;
	
	}
	
  double ntacche[]={484.0,494.0,504.0,514.0,524.0,534.0,544.0,554.0,563.8,574.2,584.0,591.4,604.0,614.0,624.0,634.2,644.0,654.0,664.0,674.0,683.8,901.0,915.0,934.6};
	
  double ntacche_err[nPoints];
  for(int i=0;i<nPoints;i++){
  ntacche_err[i]=1.;
  }
	
  TCanvas* cMono = new TCanvas("Monocromatore #lambda VS # tacche", "Monocromatore #lambda VS # tacche", 600,400);
  cMono->SetFillColor(0);
  cMono->SetGrid();
  cMono->cd();
  
  TGraphErrors* gMono = new TGraphErrors(nPoints-1, ntacche, lambda,ntacche_err, lambda_err);
  gMono->SetMarkerSize(0.6);
  gMono->SetMarkerStyle(21);
  gMono->SetTitle("Monocromatore #lambda VS #tacche ");
  gMono->GetYaxis()->SetTitle("#lambda (nm)");
  gMono->GetXaxis()->SetTitle("tacche");
  
  TF1* fMono = new TF1("fMono", "pol1",0,2100);
  fMono->SetParameter(0, 0.5);
  fMono->SetParameter(1, 5); 
  fMono->SetLineColor(6);
  gMono->Fit(fMono, "R");
  
  cout << "Fit delle lunghezze d'onda in funzione del numero di tacche sul monocromatore: " << endl;
  cout << "Chi^2:" << fMono->GetChisquare() << ", number of DoF: " << fMono->GetNDF() << " (Probability: " << fMono->GetProb() << ").\n" << endl;
  
  gMono->Draw("AP");
  cMono->Print("Monocromatore_lambda_VS_tacche.png");
 
	
	
	
	
	
	
	
	
	
	
	

}

