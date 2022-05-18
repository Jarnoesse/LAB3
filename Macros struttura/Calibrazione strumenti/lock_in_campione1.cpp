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
   double fitval = par[0] + par[1]/(1 + exp( (x[0]-par[2])/par[3]   ));
   return fitval;
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
  
  
void read10(string input, double *a,double *b,double *c,double *d,double *e,double *f,double *g,double *h,double *ii,double *l, int nBins){
  
  ifstream parInput(input.c_str());
  int i = 0;

  if (parInput.is_open()) {
    while ( parInput.good() ) {
      parInput >> a[i] >> b[i]>> c[i]>> d[i]>> e[i]>> f[i]>> g[i]>> h[i]>> ii[i]>>l[i];   
      i++;   if (i == nBins) break;
    }
    parInput.close();
  }
  }

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



void MultiGaussLims(double *chan, double *freq,double *background_freq, double *Fit_limit_sx, int * sx_lim_bin ,double *Fit_limit_dx, int * dx_lim_bin,double *Fit_mid_point,double start_point, int nBins,int nFits){
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
				sx_lim_bin[j]=position;
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
				
				if(freq[position+h]<background_freq[j]){
					control++;
				}}
			if(control==19){
				not_right_end=false;
				minPointsx=position;
				Fit_limit_dx[j]=chan[position];
				dx_lim_bin[j]=position;
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

void MultiGausSpectrum(double *chan, double *freq, double* Fit_limit_sx,double* Fit_limit_dx,double* Fit_mid_point,const char *title1 ,const char *title2, int nBins, double start, double *mean_results, double *dev_std_results,double *mean_results_err, double *dev_std_results_err, int interesting_results, double *chisquared_results, double *DoF_results, double *probability_results){	
	// come si riempie un TH1

	
  TCanvas* cled = new TCanvas(title1, title1, 600, 400);
  cled->SetFillColor(0);
  cled->SetGrid();
  cled->cd();
	
  TH1F *LEDmult = new TH1F("LEDmult","LEDmultiple",nBins,chan[0]-0.5,chan[nBins-1]+0.5);  
  for (int j=0;j<nBins;j++) {
    LEDmult->SetBinContent(j+1,freq[j]);
  } 
  
  // qui posso escludere dei punti dal fit assegnando loro un errore pari a 0!
  LEDmult->SetBinError(203,0);
  
  
  
  
  //inizio algoritmo per limiti fit gaussiani
  
  double start_point=start;
  int nFits=9;
 // double Fit_limit_sx[nFits];   
 // double Fit_limit_dx[nFits];
  int sx_lim_bin[nFits];   
  int dx_lim_bin[nFits];
  // double Fit_mid_point[nFits];
  // MultiGaussLims(chan,freq,background,Fit_limit_sx,sx_lim_bin, Fit_limit_dx, dx_lim_bin ,Fit_mid_point, start_point, nBins, nFits);
  
  //fine algoritmo per limiti fit gaussiani
  
  
  TF1 *g1    = new TF1("g1","gaus",Fit_limit_sx[0],Fit_limit_dx[0]);
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
  //TF1 *g5    = new TF1("g5",fitf,Fit_limit_sx[4],Fit_limit_dx[4],3);
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
  
  LEDmult->Fit("g1","RMS","e1",Fit_limit_sx[0],Fit_limit_dx[0]);
  LEDmult->Fit("g2","RMS+","e1",Fit_limit_sx[1],Fit_limit_dx[1]);
  LEDmult->Fit("g3","RMS++","e1",Fit_limit_sx[2],Fit_limit_dx[2]);
  LEDmult->Fit("g4","RMS+++","e1",Fit_limit_sx[3],Fit_limit_dx[3]);
  LEDmult->Fit("g5","RMS++++","e1",Fit_limit_sx[4],Fit_limit_dx[4]);
  LEDmult->Fit("g6","RMS+++++","e1",Fit_limit_sx[5],Fit_limit_dx[5]);
  LEDmult->Fit("g7","RMS++++++","e1",Fit_limit_sx[6],Fit_limit_dx[6]);
  LEDmult->Fit("g8","RMS+++++++","e1",Fit_limit_sx[7],Fit_limit_dx[7]);
  LEDmult->Fit("g9","RMS++++++++","e1",Fit_limit_sx[8],Fit_limit_dx[8]);
  
  LEDmult->Draw("e");
  cled->Print(title2);
  
  double chisquared[nFits];
  double DoF[nFits];
  double probability[nFits];
  
  chisquared[0] = g1->GetChisquare();
  chisquared[1] = g2->GetChisquare();
  chisquared[2] = g3->GetChisquare();
  chisquared[3] = g4->GetChisquare();
  chisquared[4] = g5->GetChisquare();
  chisquared[5] = g6->GetChisquare();
  chisquared[6] = g7->GetChisquare();
  chisquared[7] = g8->GetChisquare();
  chisquared[8] = g9->GetChisquare();
  
  DoF[0] = g1->GetNDF();
  DoF[1] = g2->GetNDF();
  DoF[2] = g3->GetNDF();
  DoF[3] = g4->GetNDF();
  DoF[4] = g5->GetNDF();
  DoF[5] = g6->GetNDF();
  DoF[6] = g7->GetNDF();
  DoF[7] = g8->GetNDF();
  DoF[8] = g9->GetNDF();
  
  probability[0] = g1->GetProb();
  probability[1] = g2->GetProb();
  probability[2] = g3->GetProb();
  probability[3] = g4->GetProb();
  probability[4] = g5->GetProb();
  probability[5] = g6->GetProb();
  probability[6] = g7->GetProb();
  probability[7] = g8->GetProb();
  probability[8] = g9->GetProb();
  
  
 
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
 
  
   
  double variances[nFits];
  double variances_err[nFits];
  
  variances[0] = g1->GetParameter(2);   // qui in realtà ottengo le deviazioni standard dai fit gaussiani
  variances[1] = g2->GetParameter(2);
  variances[2] = g3->GetParameter(2);
  variances[3] = g4->GetParameter(2);
  variances[4] = g5->GetParameter(2);
  variances[5] = g6->GetParameter(2);
  variances[6] = g7->GetParameter(2);
  variances[7] = g8->GetParameter(2);
  variances[8] = g9->GetParameter(2);
  
  variances_err[0] = g1->GetParError(2);
  variances_err[1] = g2->GetParError(2);
  variances_err[2] = g3->GetParError(2);
  variances_err[3] = g4->GetParError(2);
  variances_err[4] = g5->GetParError(2);
  variances_err[5] = g6->GetParError(2);
  variances_err[6] = g7->GetParError(2);
  variances_err[7] = g8->GetParError(2);
  variances_err[8] = g9->GetParError(2);
  
  for(int y=0;y<interesting_results;y++){
  	mean_results[y]=peaks[y];
  	mean_results_err[y]=peaks_err[y];
  	dev_std_results[y]=variances[y];
  	dev_std_results_err[y]=variances_err[y];
  	chisquared_results[y]=chisquared[y];
  	DoF_results[y]=DoF[y];
  	probability_results[y]=probability[y];
  	
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
  
  picco->Fit("g1","QRMS","e1",left_limit,right_limit);
  
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
  
  //picco->Draw("e");
  //cpicco->Print(title2);
  
  
  }



void lock_in_campione1(){

cout << "INIZIO L'ANALISI DATI PER SPETTROMETRO, MONOCORMATORE E SEMICONDUTTORE CON TRASMITTANZA E FOTOCORRENTE IN CASO SNEZA LOCK-IN" << endl;
cout << endl;
cout << endl;
cout << endl;


	int nBins= 2048;
	double chan1[nBins];
	double freq1[nBins];
	double limit_dx_1[]={194,692,1007, 0,0,0, 0,0,0};
	double limit_sx_1[]={201.5,699,1012, 0,0,0, 0,0,0};
	double mid_point_1[]={200,696,1010, 0,0,0, 0,0,0};
	int interesting_points1 = 1;
	double mean1[interesting_points1];
	double mean_err1[interesting_points1];
	double stddev1[interesting_points1];
	double stddev_err1[interesting_points1];
	double chisquared1[interesting_points1];
	double DoF1[interesting_points1];
	double Probability1[interesting_points1];
	read("9800_us_15_scans_processed.txt",chan1,freq1,nBins);
	MultiGausSpectrum(chan1,freq1,limit_dx_1,limit_sx_1,mid_point_1,"Calibrazione spettrometro picchi alti","Calibrazione_spettrometro_high.png",nBins,0.,mean1, stddev1,mean_err1, stddev_err1, interesting_points1,chisquared1, DoF1,Probability1);
	
	double chan2[nBins];
	double freq2[nBins];
	double limit_dx_2[]={357,495,605, 692,1008,1457,1667, 0,0};
	double limit_sx_2[]={362,505.5,613, 697,1011,1461,1671.5, 0,0};
	double mid_point_2[]={359,500,610, 696,1010,1460,1670, 0,0};
	int interesting_points2 = 7;
	double mean2[interesting_points2];
	double mean_err2[interesting_points2];
	double stddev2[interesting_points2];
	double stddev_err2[interesting_points2];
	double chisquared2[interesting_points2];
	double DoF2[interesting_points2];
	double Probability2[interesting_points2];
	read("35_ms_15_scans_processed.txt",chan2,freq2,nBins);
	MultiGausSpectrum(chan2,freq2,limit_dx_2,limit_sx_2,mid_point_2,"Calibrazione spettrometro picchi medi","Calibrazione_spettrometro_mediums.png",nBins,0.,mean2, stddev2,mean_err2, stddev_err2, interesting_points2,chisquared2, DoF2,Probability2);
	
	double chan3[nBins];
	double freq3[nBins];
	double limit_dx_3[]={1553,1588,1696, 0,0,0, 0,0,0};
	double limit_sx_3[]={1557,1591,1700, 0,0,0, 0,0,0};
	double mid_point_3[]={1556,1589,1698, 0,0,0, 0,0,0};
	int interesting_points3 = 3;
	double mean3[interesting_points3];
	double mean_err3[interesting_points3];
	double stddev3[interesting_points3];
	double stddev_err3[interesting_points3];
	double chisquared3[interesting_points3];
	double DoF3[interesting_points3];
	double Probability3[interesting_points3];
	read("85_ms_15_scans_processed.txt",chan3,freq3,nBins);
	MultiGausSpectrum(chan3,freq3,limit_dx_3,limit_sx_3,mid_point_3,"Calibrazione spettrometro picchi bassi","Calibrazione_spettrometro_low.png",nBins,0.,mean3, stddev3,mean_err3, stddev_err3, interesting_points3,chisquared3, DoF3,Probability3);
	
	cout << chisquared3[2] << endl;

	int tot_fit = interesting_points3+interesting_points2+interesting_points1;
	double mean_tot[tot_fit];
	double mean_err_tot[tot_fit];
	double stddev_tot[tot_fit];
	double stddev_err_tot[tot_fit];
	double chisquared_tot[tot_fit];
	double DoF_tot[tot_fit];
	double Probability_tot[tot_fit];
	
	for( int i=0;i<interesting_points1;i++){
	mean_tot[i]=mean1[i];
	mean_err_tot[i]=mean_err1[i];
	stddev_tot[i]=stddev1[i];
	stddev_err_tot[i]=stddev_err1[i];
	chisquared_tot[i]=chisquared1[i];
	DoF_tot[i]=DoF1[i];
	Probability_tot[i]=Probability1[i];
	
	}
	
	for( int i=0;i<interesting_points2;i++){
	mean_tot[interesting_points1+i]=mean2[i];
	mean_err_tot[interesting_points1+i]=mean_err2[i];
	stddev_tot[interesting_points1+i]=stddev2[i];
	stddev_err_tot[interesting_points1+i]=stddev_err2[i];
	chisquared_tot[interesting_points1+i]=chisquared2[i];
	DoF_tot[interesting_points1+i]=DoF2[i];
	Probability_tot[interesting_points1+i]=Probability2[i];
	
	}
	
	for( int i=0;i<interesting_points3;i++){
	mean_tot[interesting_points1+interesting_points2+i]=mean3[i];
	mean_err_tot[interesting_points1+interesting_points2+i]=mean_err3[i];
	stddev_tot[interesting_points1+interesting_points2+i]=stddev3[i];
	stddev_err_tot[interesting_points1+interesting_points2+i]=stddev_err3[i];
	chisquared_tot[interesting_points1+interesting_points2+i]=chisquared3[i];
	DoF_tot[interesting_points1+interesting_points2+i]=DoF3[i];
	Probability_tot[interesting_points1+interesting_points2+i]=Probability3[i];
	
	}
	
	
	
	for(int p=0;p< tot_fit;p++){
	cout << endl;
	cout << " Parametri del fit numero " << p+1 << ": " <<endl;
	cout << "Valore medio del picco : " <<mean_tot[p]<< endl;
	cout << "errore sul valor medio : " <<mean_err_tot[p]<< endl;
	cout << "Deviazione std : " <<stddev_tot[p]<< endl;
	cout << "Errore sulla #sigma : " <<stddev_err_tot[p]<< endl;
	cout << "#chi^{2} : " <<chisquared_tot[p]<< endl;
	cout << "DoF : " <<DoF_tot[p]<< endl;
	cout << "p-value del fit: " <<Probability_tot[p]<< endl;
	}
	
double lambda_picco[]={253.65 , 313.16 , 365.01 , 404.66 , 435.84 , 546.08, 696.54, 763.51 , 727.29 , 738.40 , 772.40       };
double zeros11[]={0,0,0, 0,0,0, 0,0,0,0,0};

	TCanvas* cSpettro = new TCanvas("Spettro #lambda VS #CHN", "Spettro #lambda VS #CHN", 600,400);
  cSpettro->SetFillColor(0);
  cSpettro->SetGrid();
  cSpettro->cd();
  
  TGraphErrors* gSpettro = new TGraphErrors(tot_fit-1, mean_tot, lambda_picco,stddev_tot, zeros11);
  gSpettro->SetMarkerSize(0.6);
  gSpettro->SetMarkerStyle(21);
  gSpettro->SetTitle("Spettro #lambda VS #CHN ");
  gSpettro->GetYaxis()->SetTitle("#lambda (nm)");
  gSpettro->GetXaxis()->SetTitle("# CHN");
  
  TF1* fSpettro = new TF1("fSpettro", "pol2",0,2100);
  fSpettro->SetParameter(0, 0.5);
  fSpettro->SetParameter(1, 5); 
  fSpettro->SetLineColor(6);
  gSpettro->Fit(fSpettro, "R");
  cout << "------------------------------------------------------------------------------------" <<endl;
  cout << "Fit delle lunghezze d'onda in funzione del numero di canali: " << endl;
  cout << "Chi^2:" << fSpettro->GetChisquare() << ", number of DoF: " << fSpettro->GetNDF() << " (Probability: " << fSpettro->GetProb() << ").\n" << endl;
  
  gSpettro->Draw("AP");
  cSpettro->Print("Spettro_lambda_VS_CHN.png");
  
  // copio incollo i parametri della relazione #CHN -> #lambda
	double d=fSpettro->GetParameter(0);  // parametro di grado 0
	double derr=fSpettro->GetParError(0);
	double a=fSpettro->GetParameter(1); // parametro di grado 1
	double aerr=fSpettro->GetParError(1);
	double b=fSpettro->GetParameter(2);  // parametro di grado 2
	double berr=fSpettro->GetParError(2);
	//double c= fSpettro->GetParameter(3);  // parametro di grado 3
	//double cerr= fSpettro->GetParError(3);
	
	
	  cout << "------------------------------------------------------------------------------------" <<endl;
  

//cout << "Ora ho la linea di fit che mette in relazione il numero di canali detti dallo spettrometro con la loro lunghezza d'onda"<<endl;
  
  // Adesso, per calibrare il monocromatore, utilizzerò questi parametri per trovare la #lambda relativa a diverse "tacche" in unità arbitrarie. Si prosegue sul file monocromatore.cpp, copia-incollando i parametri della polinomiale
  
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
	cout << "La dev std del " << d << "-esimo fit è: " << results[d][2] << endl;
	cout << "La probabilità del " << d << "-esimo fit è: " << results[d][6] << endl;
	cout << "Il suo chi quadro è: " << results[d][4] << endl;
	cout << endl;
	}
	
	// kekw i fit vengono tutti... ora tocca alla conversione da canali a lunghezza d'onda dei valori medi e delle dev std!
	// dopodichè dovrò fare la conversione da tacche a lunghezza d'onda (ossia canali)
	
	
	
	// le mie x sono le medie, i loro errori sono la dev std. Calcolo #lambda e il suo errore in un ciclo for
	double lambda[nPoints];
	double lambda_err[nPoints];
	
	/*per polinomio grado 1
	for(int i=0;i< nPoints;i++){
	double x= means[i];
	double xerr= dev_std[i];
	
	lambda[i]= a*x+d;
	double fa = x* aerr;
	double fx = (a)*xerr;
	double ferr_on_f= sqrt(fa*fa+fx*fx);
	lambda_err[i]=ferr_on_f;
	
	}*/
	
	//per polinomio grado 2
	for(int i=0;i< nPoints;i++){
	double x= means[i];
	double xerr= dev_std[i];
	
	lambda[i]= a*x+b*x*x+d;
	double fa = x* aerr;
	double fb = x*x*berr;
	double fx = (a+2*b*x)*xerr;
	double ferr_on_f= sqrt(fa*fa+fb*fb+fx*fx);
	lambda_err[i]=ferr_on_f;
	
	}
	
	
	/*  per polinomio grado 3
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
	
	}*/
	
  double ntacche[]={484.0,494.0,504.0,514.0,524.0,534.0,544.0,554.0,563.8,574.2,584.0,591.4,604.0,614.0,624.0,634.2,644.0,654.0,664.0,674.0,683.8,901.0,915.0,934.6};
	
  double ntacche_err[nPoints];
  for(int i=0;i<nPoints;i++){
  ntacche_err[i]=0.5;
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
  
  TF1* fMono = new TF1("fMono", "pol1",0,2000);
  fMono->SetParameter(0, 0.5);
  fMono->SetParameter(1, 5); 
  fMono->SetLineColor(6);
  gMono->Fit(fMono, "R");
    cout << "------------------------------------------------------------------------------------" <<endl;
  
  cout << "Fit delle lunghezze d'onda in funzione del numero di tacche sul monocromatore: " << endl;
  cout << "Chi^2:" << fMono->GetChisquare() << ", number of DoF: " << fMono->GetNDF() << " (Probability: " << fMono->GetProb() << ").\n" << endl;
    cout << "------------------------------------------------------------------------------------" <<endl;
  
  gMono->Draw("AP");
  cMono->Print("Monocromatore_lambda_VS_tacche.png");
  
	double q=fMono->GetParameter(0);  // parametro di grado 0
	double qerr=fMono->GetParError(0);
	double m=fMono->GetParameter(1); // parametro di grado 1
	double merr=fMono->GetParError(1);
	//double f=fMono->GetParameter(2); // parametro di grado 2
	//double ferr=fMono->GetParError(2);



	// INIZIA PARTE AMPLIFICATORE



	int PointsNumber=30;
	double measureN[PointsNumber];
	double tacche[PointsNumber];    // tacche a cui si sono prese le diverse misure. Sarà la nostra x, va convertita in nanometri
	double errtacche[PointsNumber];
	double V0fd[PointsNumber];      // tensione di riferimento (senza campione)
	double V0fderr[PointsNumber];
	double Vfd[PointsNumber];       // tensione in uscita dal fotodiodo
	double Vfderr[PointsNumber];
	double Vfc0[PointsNumber];       // tensione relativa alla fotocorrente prodotta per effetto fotoelettrico sfasata a 0 gradi
	double Vfc0err[PointsNumber];
	double Vfc90[PointsNumber];       // tensione relativa alla fotocorrente prodotta per effetto fotoelettrico sfasata a 90 gradi
	double Vfc90err[PointsNumber];
	
	double Vfc[PointsNumber];       // tensione relativa alla fotocorrente prodotta per effetto fotoelettrico
	double Vfcerr[PointsNumber];
	
	read10("dati_lock_in_campione_1.txt",measureN,tacche,V0fd,V0fderr,Vfd,Vfderr,Vfc0,Vfc0err,Vfc90,Vfc90err,PointsNumber);

	



	// Trovo come media in quadratura il valore della tensione di fotocorrente
	for(int i=0;i<PointsNumber;i++){
		Vfc[i]= sqrt(Vfc0[i]*Vfc0[i] + Vfc90[i]*Vfc90[i]);
		double Vsq = sqrt( Vfc0[i]*Vfc0[i] + Vfc90[i]*Vfc90[i]);
		
		double VV0 = Vfc0[i]*Vfc0err[i];
		double VV90= Vfc90[i]*Vfc90err[i];
		double VfcerrSquared= VV0*VV0 + VV90*VV90;
		Vfcerr[i]=sqrt(VfcerrSquared)/Vsq;
	}
	
	for(int i=0;i<14;i++){
		Vfc[i]=Vfc[i];
		
	}



	// modifica l'errore sulle tacche
	
	for(int i=0;i<PointsNumber;i++){
		errtacche[i]=0.5;
		
	}


	// Trasformazione da tacche a nanometri tramite relazione di calibrazione del monocromatore	
  	// tacche -> nanometri
  	
  	double l[PointsNumber];
  	double lerr[PointsNumber];
  	
  	// per polinomio di grado 1
  	for(int i=0;i<PointsNumber;i++){
  	l[i]= m*tacche[i]+q;
  	double lerrSq;
  	double lm= tacche[i]*merr;
  	double lq= 1*qerr;
  	double lx= m* errtacche[i];
  	
  	lerrSq = lm*lm+lq*lq+lx*lx;
  	lerr[i]= sqrt(lerrSq);
  	}
  	
  	/* per polinomio di grado 2
  	for(int i=0;i<PointsNumber;i++){
  	l[i]= f*tacche[i]*tacche[i]+m*tacche[i]+q;
  	double lerrSq;
  	double lf = tacche[i]*tacche[i]*ferr;
  	double lm= tacche[i]*merr;
  	double lq= 1*qerr;
  	double lx= m* errtacche[i];
  	
  	lerrSq = lm*lm+lq*lq+lx*lx+lf*lf;
  	lerr[i]= sqrt(lerrSq);
  	}*/
  	
  	
  	
  	
  	// Grafico la V0fd e la Trasmittanza T=Vfd/V0fd in funzione di lambda
	
	TCanvas* cIntensity = new TCanvas("Intensità lampada V0 su oscilloscopio VS #lambda", "Intensità lampada V0 su oscilloscopio VS #lambda", 600,400);
  cIntensity->SetFillColor(0);
  cIntensity->SetGrid();
  cIntensity->cd();
  
  TGraphErrors* gIntensity = new TGraphErrors(PointsNumber, l, V0fd,lerr, V0fderr);
  gIntensity->SetMarkerSize(0.6);
  gIntensity->SetMarkerStyle(21);
  gIntensity->SetTitle("Intensità lampada V0 su oscilloscopio VS #lambda");
  gIntensity->GetXaxis()->SetTitle("#lambda (nm)");
  gIntensity->GetYaxis()->SetTitle("#V_{0} (mV)");
	
  gIntensity->Draw("AP");
  cIntensity->Print("Intensità_mV_VS_lambda.png");
  
  
  	// Grafico la Trasmittanza in funzione di lambda. Prima converto gli errori
  	
  	double T[PointsNumber];
  	double Terr[PointsNumber];
  	
  	for(int i=0;i<PointsNumber;i++){
  		T[i]=Vfd[i]/V0fd[i];
  		
  	double TerrSq;
  	double Tv = Vfderr[i]/V0fd[i];
  	double T0 = (Vfd[i]/(V0fd[i]*V0fd[i]))*(Vfd[i]/(V0fd[i]*V0fd[i]))*V0fderr[i];
  	TerrSq= Tv*Tv+T0*T0;
  	Terr[i]= sqrt(TerrSq);
  	//cout << "trasmittanza " << T[i] << " +- " << Terr[i] << "     errore relativo: " << Terr[i]/T[i] <<  endl;
  	}
  	
  	
  TCanvas* cTrasmittanza = new TCanvas("Trasmittanza su oscilloscopio VS #lambda", "Trasmittanza su oscilloscopio VS #lambda", 600,400);
  cTrasmittanza->SetFillColor(0);
  cTrasmittanza->SetGrid();
  cTrasmittanza->cd();
  
  TGraphErrors* gTrasmittanza = new TGraphErrors(PointsNumber, l, T,lerr, Terr);
  gTrasmittanza->SetMarkerSize(0.6);
  gTrasmittanza->SetMarkerStyle(21);
  gTrasmittanza->SetTitle("Trasmittanza su oscilloscopio VS #lambda (campione 1, lock-in)");
  gTrasmittanza->GetXaxis()->SetTitle("#lambda (nm)");
  gTrasmittanza->GetYaxis()->SetTitle("Trasmittanza");
  
  TF1* fTrasmittanza = new TF1("fTrasmittanza", fitf,500,700,4);  // dsfaihfkfvh
  fTrasmittanza->SetParameter(0, 0.01);
  fTrasmittanza->SetParameter(1, 0.6); 
  fTrasmittanza->SetParameter(2, 630);
  fTrasmittanza->SetParameter(3, -0.5); 
    fTrasmittanza->SetParName(0, "offset");
  fTrasmittanza->SetParName(1, "Amplitude"); 
  fTrasmittanza->SetParName(2, "#lambda_{0}");
  fTrasmittanza->SetParName(3, "#DeltaLambda");  
  fTrasmittanza->SetLineColor(2);
  gTrasmittanza->Fit(fTrasmittanza, "R");
    cout << "------------------------------------------------------------------------------------" <<endl;
  
  cout << "Fit della Trasmittanza in funzione della lunghezza d'onda del raggio incidente " << endl;
  cout << "Chi^2:" << fTrasmittanza->GetChisquare() << ", number of DoF: " << fTrasmittanza->GetNDF() << " (Probability: " << fTrasmittanza->GetProb() << ").\n" << endl;
    cout << "------------------------------------------------------------------------------------" <<endl;
  
	
  gTrasmittanza->Draw("AP");
  cTrasmittanza->Print("Lock_in_Trasmittanza_VS_lambda_campione1.png");
	

TCanvas* cFotocorrente = new TCanvas("Fotocorrente su oscilloscopio VS #lambda", "Fotocorrente su oscilloscopio VS #lambda", 600,400);
  cFotocorrente->SetFillColor(0);
  cFotocorrente->SetGrid();
  cFotocorrente->cd();
  
  TGraphErrors* gFotocorrente = new TGraphErrors(PointsNumber, l, Vfc,lerr, Vfcerr);
  gFotocorrente->SetMarkerSize(0.6);
  gFotocorrente->SetMarkerStyle(21);
  gFotocorrente->SetTitle("Fotocorrente su oscilloscopio VS #lambda (campione 1, lock-in)");
  gFotocorrente->GetXaxis()->SetTitle("#lambda (nm)");
  gFotocorrente->GetYaxis()->SetTitle("Fotocorrente (#muV)");
  
  TF1* fFotocorrente = new TF1("fFotocorrente", fitf,627,700,4);  // dsfaihfkfvh
  fFotocorrente->SetParameter(0, 0.01);
  fFotocorrente->SetParameter(1, 0.6); 
  fFotocorrente->SetParameter(2, 625);
  fFotocorrente->SetParameter(3, 0.4);
    fFotocorrente->SetParName(0, "offset");
  fFotocorrente->SetParName(1, "Amplitude"); 
  fFotocorrente->SetParName(2, "#lambda_{0}");
  fFotocorrente->SetParName(3, "#DeltaLambda");  
  fFotocorrente->SetLineColor(2);
  gFotocorrente->Fit(fFotocorrente, "R");
    cout << "------------------------------------------------------------------------------------" <<endl;
  
  cout << "Fit della Fotocorrente in funzione della lunghezza d'onda del raggio incidente " << endl;
  cout << "Chi^2:" << fFotocorrente->GetChisquare() << ", number of DoF: " << fFotocorrente->GetNDF() << " (Probability: " << fFotocorrente->GetProb() << ").\n" << endl;
    cout << "------------------------------------------------------------------------------------" <<endl;
  
	
  gFotocorrente->Draw("AP");
  cFotocorrente->Print("Lock_in_Fotocorrente_VS_lambda_campione1.png");
  
  double l0T= fTrasmittanza->GetParameter(2);
  double l0Terr=fTrasmittanza->GetParameter(3);
  double l0fc= fFotocorrente->GetParameter(2);
  double l0fcerr=fFotocorrente->GetParameter(3);
  
  cout << "--------------------------------------------------------------------" << endl;
  cout << " Studio dei due risultati di #lambda_{0} ottenuti da Trasmittanza e Fotocorrente" << endl;
  cout << endl;
  cout << "Lunghezza d'onda da trasmittanza: " << l0T << " +- " << l0Terr << endl;
  cout << "Lunghezza d'onda da fotocorrente: " << l0fc << " +- " << l0fcerr << endl;
  cout << endl;
  cout << "Test Z sulle due lunghezze d'onda: " << endl;
  
  
  Ztest(l0T,l0fc,l0Terr,l0fcerr,0.05);
  
  cout << "--------------------------------------------------------------------------" << endl;
  cout << " Riflessione sul senso degli errori " << endl;
  
  // guardo quanto vale 1 canale in nanometri. Considero che le deviazioni standard dei picchi sono di circa 5 canali
  	double ss= 1;
  	double bb= 2;
	double sserr= 0.1;
	
	double kk= abs(a*bb+b*bb*bb+d)-abs(a*ss+b*ss*ss+d);
	double ffa = ss* aerr;
	double ffb = ss*ss*berr;
	double ffx = (a+2*b*ss)*sserr;
	double fferr_on_f= sqrt(ffa*ffa+ffb*ffb+ffx*ffx);
	double kkerr=fferr_on_f;
	double ppo = kk*6;
	
	//cout << " Un canale corrisponde a " << kk << " nanometri " << endl;
	//cout << "Allora una sigma di 6 CHN corrisponde a un errore di " << ppo << " nanometri" << endl;
  
  
	

}
