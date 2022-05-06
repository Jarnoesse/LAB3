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


void read2(string input, double *x,double *y, int nBins){
  
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
  
void read9(string input, double *a,double *b,double *c,double *d,double *e,double *f,double *g,double *h,double *ii, int nBins){
  
  ifstream parInput(input.c_str());
  int i = 0;

  if (parInput.is_open()) {
    while ( parInput.good() ) {
      parInput >> a[i] >> b[i]>> c[i]>> d[i]>> e[i]>> f[i]>> g[i]>> h[i]>> ii[i];   
      i++;   if (i == nBins) break;
    }
    parInput.close();
  }
  }
  
  
void amplificatore(){
	int nPoints=30;
	double measureN[nPoints];
	double tacche[nPoints];    // tacche a cui si sono prese le diverse misure. Sarà la nostra x, va convertita in nanometri
	double errtacche[nPoints];
	double V0fd[nPoints];      // tensione di riferimento (senza campione)
	double V0fderr[nPoints];
	double Vfd[nPoints];       // tensione in uscita dal fotodiodo
	double Vfderr[nPoints];
	double Vfc[nPoints];       // tensione relativa alla fotocorrente prodotta per effetto fotoelettrico
	double Vfcerr[nPoints];
	
	read9("dati_trasmittanza&fotocorrente_oscilloscopio.txt",measureN,tacche,errtacche,V0fd,V0fderr,Vfd,Vfderr,Vfc,Vfcerr,nPoints);

	// modifica l'errore sulle tacche
	
	for(int i=0;i<nPoints;i++){
		errtacche[i]=0.1;
	}


	// Trasformazione da tacche a nanometri tramite relazione di calibrazione del monocromatore
	
	double q =-5.35182e+01;
  	double qerr=1.86663e+01;
  	double m =1.00485e+00;
  	double merr =3.34814e-02;
  	
  	// tacche -> nanometri
  	
  	double l[nPoints];
  	double lerr[nPoints];
  	
  	for(int i=0;i<nPoints;i++){
  	l[i]= m*tacche[i]+q;
  	double lerrSq;
  	double lm= tacche[i]*merr;
  	double lq= 1*qerr;
  	double lx= m* errtacche[i];
  	
  	lerrSq = lm*lm+lq*lq+lx*lx;
  	lerr[i]= sqrt(lerrSq);
  	}
  	
  	// Grafico la V0fd e la Trasmittanza T=Vfd/V0fd in funzione di lambda
	
	TCanvas* cIntensity = new TCanvas("Intensità lampada V0 su oscilloscopio VS #lambda", "Intensità lampada V0 su oscilloscopio VS #lambda", 600,400);
  cIntensity->SetFillColor(0);
  cIntensity->SetGrid();
  cIntensity->cd();
  
  TGraphErrors* gIntensity = new TGraphErrors(nPoints, l, V0fd,lerr, V0fderr);
  gIntensity->SetMarkerSize(0.6);
  gIntensity->SetMarkerStyle(21);
  gIntensity->SetTitle("Intensità lampada V0 su oscilloscopio VS #lambda");
  gIntensity->GetXaxis()->SetTitle("#lambda (nm)");
  gIntensity->GetYaxis()->SetTitle("#V_{0} (mV)");
	
  gIntensity->Draw();
  cIntensity->Print("Intensità_mV_VS_lambda.png");
  
  
  	// Grafico la Trasmittanza in funzione di lambda. Prima converto gli errori
  	
  	double T[nPoints];
  	double Terr[nPoints];
  	
  	for(int i=0;i<nPoints;i++){
  		T[i]=Vfd[i]/V0fd[i];
  		
  	double TerrSq;
  	double Tv = Vfderr[i]/V0fd[i];
  	double T0 = (Vfd[i]/(V0fd[i]*V0fd[i]))*(Vfd[i]/(V0fd[i]*V0fd[i]))*V0fderr[i];
  	TerrSq= Tv*Tv+T0*T0;
  	Terr[i]= sqrt(TerrSq);
  	cout << "trasmittanza " << T[i] << " +- " << Terr[i] << "     errore relativo: " << Terr[i]/T[i] <<  endl;
  	}
  	
  	
  TCanvas* cTrasmittanza = new TCanvas("Trasmittanza su oscilloscopio VS #lambda", "Trasmittanza su oscilloscopio VS #lambda", 600,400);
  cTrasmittanza->SetFillColor(0);
  cTrasmittanza->SetGrid();
  cTrasmittanza->cd();
  
  TGraphErrors* gTrasmittanza = new TGraphErrors(nPoints, l, T,lerr, Terr);
  gTrasmittanza->SetMarkerSize(0.6);
  gTrasmittanza->SetMarkerStyle(21);
  gTrasmittanza->SetTitle("Trasmittanza su oscilloscopio VS #lambda");
  gTrasmittanza->GetXaxis()->SetTitle("#lambda (nm)");
  gTrasmittanza->GetYaxis()->SetTitle("Trasmittanza");
	
  gTrasmittanza->Draw();
  cTrasmittanza->Print("Trasmittanza_VS_lambda.png");
	
	
}

