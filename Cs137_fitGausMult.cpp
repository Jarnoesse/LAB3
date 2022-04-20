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



void MultiGaussLims(double *chan, double *freq, int *Fit_limit_sx,int *Fit_limit_dx,int *Fit_mid_point,int start_point, int nBins,int nFits){
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
		
		while(not_max){
			int check=0;
			for(int k=1;k<5;k++){  // questo k<qlcs mi dice quanti devono essere i punti successivi minori di questo per 						          considerarlo un massimo
				if(freq[position]>freq[position+k]){
					check++;
				}
			}
			if(check==4){
				not_max=false;
				maxPoint=position;
				Fit_mid_point[j]=freq[position];
			}
			position++;
		}
		
		while(not_min){
			int check=0;
			for(int k=1;k<5;k++){  // questo k<qlcs mi dice quanti devono essere i punti successivi minori di questo per 						          considerarlo un massimo
				if(freq[position]<freq[position+k]){
					check++;
				}
			}
			if(check==4){
				not_min=false;
				minPointdx=position;
				Fit_limit_dx[j]=chan[position];
				Fit_limit_sx[j+1]=chan[position];
			}
			position++;
		}	
	}
	
		
}


void Cs137_fitGausMult(){

	double chan[]={5.04000000e+02,5.12000000e+02,5.20000000e+02,5.28000000e+02,5.36000000e+02,5.44000000e+02,5.52000000e+02,5.60000000e+02,5.68000000e+02,5.76000000e+02,5.84000000e+02,5.92000000e+02,6.00000000e+02,6.08000000e+02,6.16000000e+02,6.24000000e+02,6.32000000e+02,6.40000000e+02,6.48000000e+02,6.56000000e+02,6.64000000e+02,6.72000000e+02,6.80000000e+02,6.88000000e+02,6.96000000e+02,7.04000000e+02,7.12000000e+02,7.20000000e+02,7.28000000e+02,7.36000000e+02,7.44000000e+02,7.52000000e+02,7.60000000e+02,7.68000000e+02,7.76000000e+02,7.84000000e+02,7.92000000e+02,8.00000000e+02,8.08000000e+02,8.16000000e+02,8.24000000e+02,8.32000000e+02,8.40000000e+02,8.48000000e+02,8.56000000e+02,8.64000000e+02,8.72000000e+02,8.80000000e+02,8.88000000e+02,8.96000000e+02,9.04000000e+02,9.12000000e+02,9.20000000e+02,9.28000000e+02,9.36000000e+02,9.44000000e+02,9.52000000e+02,9.60000000e+02,9.68000000e+02,9.76000000e+02,9.84000000e+02,9.92000000e+02,1.00000000e+03,1.00800000e+03,1.01600000e+03,1.02400000e+03,1.03200000e+03,1.04000000e+03,1.04800000e+03,1.05600000e+03,1.06400000e+03,1.07200000e+03,1.08000000e+03,1.08800000e+03,1.09600000e+03,1.10400000e+03,1.11200000e+03,1.12000000e+03,1.12800000e+03,1.13600000e+03,1.14400000e+03,1.15200000e+03,1.16000000e+03,1.16800000e+03,1.17600000e+03,1.18400000e+03,1.19200000e+03,1.20000000e+03,1.20800000e+03,1.21600000e+03,1.22400000e+03,1.23200000e+03,1.24000000e+03,1.24800000e+03,1.25600000e+03,1.26400000e+03,1.27200000e+03,1.28000000e+03,1.28800000e+03,1.29600000e+03,1.30400000e+03,1.31200000e+03,1.32000000e+03,1.32800000e+03,1.33600000e+03,1.34400000e+03,1.35200000e+03,1.36000000e+03,1.36800000e+03,1.37600000e+03,1.38400000e+03,1.39200000e+03,1.40000000e+03,1.40800000e+03,1.41600000e+03,1.42400000e+03,1.43200000e+03,1.44000000e+03,1.44800000e+03,1.45600000e+03,1.46400000e+03,1.47200000e+03,1.48000000e+03,1.48800000e+03,1.49600000e+03,1.50400000e+03,1.51200000e+03,1.52000000e+03,1.52800000e+03,1.53600000e+03,1.54400000e+03,1.55200000e+03,1.56000000e+03,1.56800000e+03,1.57600000e+03,1.58400000e+03,1.59200000e+03,1.60000000e+03,1.60800000e+03,1.61600000e+03,1.62400000e+03,1.63200000e+03,1.64000000e+03,1.64800000e+03,1.65600000e+03,1.66400000e+03,1.67200000e+03,1.68000000e+03,1.68800000e+03,1.69600000e+03,1.70400000e+03,1.71200000e+03,1.72000000e+03,1.72800000e+03,1.73600000e+03,1.74400000e+03,1.75200000e+03,1.76000000e+03,1.76800000e+03,1.77600000e+03,1.78400000e+03,1.79200000e+03,1.80000000e+03,1.80800000e+03,1.81600000e+03,1.82400000e+03,1.83200000e+03,1.84000000e+03,1.84800000e+03,1.85600000e+03,1.86400000e+03,1.87200000e+03,1.88000000e+03,1.88800000e+03,1.89600000e+03,1.90400000e+03,1.91200000e+03,1.92000000e+03,1.92800000e+03,1.93600000e+03,1.94400000e+03,1.95200000e+03,1.96000000e+03,1.96800000e+03,1.97600000e+03,1.98400000e+03,1.99200000e+03,2.00000000e+03,2.00800000e+03,2.01600000e+03,2.02400000e+03,2.03200000e+03,2.04000000e+03,2.04800000e+03,2.05600000e+03,2.06400000e+03,2.07200000e+03,2.08000000e+03,2.08800000e+03,2.09600000e+03,2.10400000e+03,2.11200000e+03,2.12000000e+03,2.12800000e+03,2.13600000e+03,2.14400000e+03,2.15200000e+03,2.16000000e+03,2.16800000e+03,2.17600000e+03,2.18400000e+03,2.19200000e+03,2.20000000e+03,2.20800000e+03,2.21600000e+03,2.22400000e+03,2.23200000e+03,2.24000000e+03,2.24800000e+03,2.25600000e+03,2.26400000e+03,2.27200000e+03,2.28000000e+03,2.28800000e+03,2.29600000e+03,2.30400000e+03,2.31200000e+03,2.32000000e+03,2.32800000e+03,2.33600000e+03,2.34400000e+03,2.35200000e+03,2.36000000e+03,2.36800000e+03,2.37600000e+03,2.38400000e+03,2.39200000e+03,2.40000000e+03,2.40800000e+03,2.41600000e+03,2.42400000e+03,2.43200000e+03,2.44000000e+03,2.44800000e+03,2.45600000e+03,2.46400000e+03,2.47200000e+03,2.48000000e+03,2.48800000e+03,2.49600000e+03,2.50400000e+03,2.51200000e+03,2.52000000e+03,2.52800000e+03,2.53600000e+03,2.54400000e+03,2.55200000e+03,2.56000000e+03,2.56800000e+03,2.57600000e+03,2.58400000e+03,2.59200000e+03,2.60000000e+03,2.60800000e+03,2.61600000e+03,2.62400000e+03,2.63200000e+03,2.64000000e+03,2.64800000e+03,2.65600000e+03,2.66400000e+03,2.67200000e+03,2.68000000e+03,2.68800000e+03,2.69600000e+03,2.70400000e+03,2.71200000e+03,2.72000000e+03,2.72800000e+03,2.73600000e+03,2.74400000e+03,2.75200000e+03,2.76000000e+03,2.76800000e+03,2.77600000e+03,2.78400000e+03,2.79200000e+03,2.80000000e+03,2.80800000e+03,2.81600000e+03,2.82400000e+03,2.83200000e+03,2.84000000e+03,2.84800000e+03,2.85600000e+03,2.86400000e+03,2.87200000e+03,2.88000000e+03,2.88800000e+03,2.89600000e+03,2.90400000e+03,2.91200000e+03,2.92000000e+03,2.92800000e+03,2.93600000e+03,2.94400000e+03,2.95200000e+03,2.96000000e+03,2.96800000e+03,2.97600000e+03,2.98400000e+03,2.99200000e+03,3.00000000e+03,3.00800000e+03,3.01600000e+03,3.02400000e+03,3.03200000e+03,3.04000000e+03,3.04800000e+03,3.05600000e+03,3.06400000e+03,3.07200000e+03,3.08000000e+03,3.08800000e+03,3.09600000e+03,3.10400000e+03,3.11200000e+03,3.12000000e+03,3.12800000e+03,3.13600000e+03,3.14400000e+03,3.15200000e+03,3.16000000e+03,3.16800000e+03,3.17600000e+03,3.18400000e+03,3.19200000e+03,3.20000000e+03,3.20800000e+03,3.21600000e+03,3.22400000e+03,3.23200000e+03,3.24000000e+03,3.24800000e+03,3.25600000e+03,3.26400000e+03,3.27200000e+03,3.28000000e+03,3.28800000e+03,3.29600000e+03,3.30400000e+03,3.31200000e+03,3.32000000e+03,3.32800000e+03,3.33600000e+03,3.34400000e+03,3.35200000e+03,3.36000000e+03,3.36800000e+03,3.37600000e+03,3.38400000e+03,3.39200000e+03,3.40000000e+03,3.40800000e+03,3.41600000e+03,3.42400000e+03,3.43200000e+03,3.44000000e+03,3.44800000e+03,3.45600000e+03,3.46400000e+03,3.47200000e+03,3.48000000e+03,3.48800000e+03,3.49600000e+03,3.50400000e+03,3.51200000e+03,3.52000000e+03,3.52800000e+03,3.53600000e+03,3.54400000e+03,3.55200000e+03,3.56000000e+03,3.56800000e+03,3.57600000e+03,3.58400000e+03,3.59200000e+03,3.60000000e+03,3.60800000e+03,3.61600000e+03,3.62400000e+03,3.63200000e+03,3.64000000e+03,3.64800000e+03,3.65600000e+03,3.66400000e+03,3.67200000e+03,3.68000000e+03,3.68800000e+03,3.69600000e+03,3.70400000e+03,3.71200000e+03,3.72000000e+03,3.72800000e+03,3.73600000e+03,3.74400000e+03,3.75200000e+03,3.76000000e+03,3.76800000e+03,3.77600000e+03,3.78400000e+03,3.79200000e+03,3.80000000e+03,3.80800000e+03,3.81600000e+03,3.82400000e+03,3.83200000e+03,3.84000000e+03,3.84800000e+03,3.85600000e+03,3.86400000e+03,3.87200000e+03,3.88000000e+03,3.88800000e+03,3.89600000e+03,3.90400000e+03,3.91200000e+03,3.92000000e+03,3.92800000e+03,3.93600000e+03,3.94400000e+03,3.95200000e+03,3.96000000e+03,3.96800000e+03,3.97600000e+03,3.98400000e+03,3.99200000e+03,4.00000000e+03,4.00800000e+03,4.01600000e+03,4.02400000e+03,4.03200000e+03,4.04000000e+03,4.04800000e+03,4.05600000e+03,4.06400000e+03,4.07200000e+03,4.08000000e+03,4.08800000e+03,4.09600000e+03,4.10400000e+03,4.11200000e+03,4.12000000e+03,4.12800000e+03,4.13600000e+03,4.14400000e+03,4.15200000e+03,4.16000000e+03,4.16800000e+03,4.17600000e+03,4.18400000e+03,4.19200000e+03,4.20000000e+03,4.20800000e+03,4.21600000e+03,4.22400000e+03,4.23200000e+03,4.24000000e+03,4.24800000e+03,4.25600000e+03,4.26400000e+03,4.27200000e+03,4.28000000e+03,4.28800000e+03,4.29600000e+03,4.30400000e+03,4.31200000e+03,4.32000000e+03,4.32800000e+03,4.33600000e+03,4.34400000e+03,4.35200000e+03,4.36000000e+03,4.36800000e+03,4.37600000e+03,4.38400000e+03,4.39200000e+03,4.40000000e+03,4.40800000e+03,4.41600000e+03,4.42400000e+03,4.43200000e+03,4.44000000e+03,4.44800000e+03,4.45600000e+03,4.46400000e+03,4.47200000e+03,4.48000000e+03,4.48800000e+03,4.49600000e+03,4.50400000e+03,4.51200000e+03,4.52000000e+03,4.52800000e+03,4.53600000e+03,4.54400000e+03,4.55200000e+03,4.56000000e+03,4.56800000e+03,4.57600000e+03,4.58400000e+03,4.59200000e+03};
	double freq[]={1.00000000e+00,1.00000000e+00,3.00000000e+00,2.00000000e+00,1.00000000e+00,2.00000000e+00,3.00000000e+00,3.00000000e+00,3.00000000e+00,2.00000000e+00,2.00000000e+00,2.00000000e+00,1.00000000e+00,7.00000000e+00,1.10000000e+01,3.00000000e+00,1.00000000e+00,4.00000000e+00,7.00000000e+00,7.00000000e+00,8.00000000e+00,1.20000000e+01,9.00000000e+00,1.00000000e+01,1.00000000e+01,8.00000000e+00,1.00000000e+01,1.30000000e+01,1.70000000e+01,1.30000000e+01,1.40000000e+01,1.90000000e+01,2.70000000e+01,2.10000000e+01,3.00000000e+01,3.00000000e+01,2.70000000e+01,3.50000000e+01,5.30000000e+01,4.60000000e+01,4.70000000e+01,4.30000000e+01,5.00000000e+01,6.30000000e+01,5.60000000e+01,7.20000000e+01,7.90000000e+01,8.40000000e+01,9.90000000e+01,1.11000000e+02,1.23000000e+02,1.22000000e+02,1.12000000e+02,1.47000000e+02,1.45000000e+02,1.65000000e+02,1.73000000e+02,2.07000000e+02,2.12000000e+02,2.16000000e+02,2.30000000e+02,2.56000000e+02,2.59000000e+02,2.73000000e+02,2.89000000e+02,2.97000000e+02,3.46000000e+02,3.64000000e+02,3.83000000e+02,4.22000000e+02,4.57000000e+02,4.86000000e+02,4.86000000e+02,4.72000000e+02,5.05000000e+02,6.32000000e+02,6.50000000e+02,6.64000000e+02,6.95000000e+02,8.06000000e+02,8.81000000e+02,9.20000000e+02,1.00400000e+03,1.07200000e+03,1.14300000e+03,1.25400000e+03,1.37500000e+03,1.51400000e+03,1.59700000e+03,1.59000000e+03,1.77700000e+03,1.80400000e+03,1.88700000e+03,2.03900000e+03,2.09700000e+03,2.20100000e+03,2.26900000e+03,2.53000000e+03,2.57200000e+03,2.68000000e+03,2.94900000e+03,3.12300000e+03,3.30900000e+03,3.40500000e+03,3.50700000e+03,3.65000000e+03,3.57800000e+03,3.64300000e+03,3.83100000e+03,3.77000000e+03,3.90100000e+03,3.90700000e+03,4.24000000e+03,4.33200000e+03,4.50900000e+03,4.57600000e+03,4.79500000e+03,4.88300000e+03,4.92900000e+03,4.97400000e+03,4.97500000e+03,4.92200000e+03,4.91500000e+03,5.05100000e+03,5.08700000e+03,5.10000000e+03,5.32400000e+03,5.28300000e+03,5.50700000e+03,5.56600000e+03,5.78200000e+03,5.87500000e+03,5.73500000e+03,5.84600000e+03,5.64900000e+03,5.67400000e+03,5.63900000e+03,5.65900000e+03,5.62600000e+03,5.76800000e+03,5.70400000e+03,5.84300000e+03,5.98000000e+03,5.99900000e+03,6.02900000e+03,6.20300000e+03,6.19700000e+03,6.01100000e+03,6.02900000e+03,5.89400000e+03,5.87500000e+03,5.80900000e+03,6.06600000e+03,5.90800000e+03,6.05200000e+03,6.17100000e+03,6.09700000e+03,6.32500000e+03,6.22500000e+03,6.38100000e+03,6.30800000e+03,6.30500000e+03,6.20900000e+03,6.09300000e+03,5.98600000e+03,6.05000000e+03,6.10500000e+03,6.06100000e+03,6.06100000e+03,6.16200000e+03,6.40700000e+03,6.40600000e+03,6.34300000e+03,6.40800000e+03,6.34200000e+03,6.37700000e+03,6.24100000e+03,6.04700000e+03,6.06600000e+03,6.06900000e+03,6.15000000e+03,6.31400000e+03,6.23500000e+03,6.32700000e+03,6.42400000e+03,6.29000000e+03,6.30100000e+03,6.40600000e+03,6.30800000e+03,6.27300000e+03,6.38400000e+03,6.18300000e+03,6.13100000e+03,6.22900000e+03,6.17600000e+03,6.34900000e+03,6.43000000e+03,6.53800000e+03,6.65600000e+03,6.42000000e+03,6.40600000e+03,6.42700000e+03,6.35000000e+03,6.30600000e+03,6.30400000e+03,6.32300000e+03,6.08400000e+03,6.21500000e+03,6.35200000e+03,6.30500000e+03,6.35500000e+03,6.39800000e+03,6.42000000e+03,6.58400000e+03,6.36600000e+03,6.34100000e+03,6.28300000e+03,6.37600000e+03,6.22000000e+03,6.23300000e+03,6.24200000e+03,6.33400000e+03,6.36400000e+03,6.24300000e+03,6.39100000e+03,6.47100000e+03,6.57600000e+03,6.47100000e+03,6.38200000e+03,6.40500000e+03,6.48300000e+03,6.29100000e+03,6.21800000e+03,6.31500000e+03,6.32100000e+03,6.14300000e+03,6.40100000e+03,6.46900000e+03,6.55500000e+03,6.68000000e+03,6.61900000e+03,6.45100000e+03,6.52700000e+03,6.57400000e+03,6.53100000e+03,6.32400000e+03,6.22400000e+03,6.24400000e+03,6.26400000e+03,6.16800000e+03,6.30500000e+03,6.39400000e+03,6.52400000e+03,6.48200000e+03,6.48300000e+03,6.49000000e+03,6.47400000e+03,6.45300000e+03,6.39300000e+03,6.42000000e+03,6.40100000e+03,6.17300000e+03,6.41300000e+03,6.41500000e+03,6.44900000e+03,6.51000000e+03,6.44200000e+03,6.57300000e+03,6.31500000e+03,6.38200000e+03,6.43800000e+03,6.41700000e+03,6.36200000e+03,6.31100000e+03,6.37600000e+03,6.29100000e+03,6.25900000e+03,6.38500000e+03,6.48700000e+03,6.44200000e+03,6.48300000e+03,6.39100000e+03,6.52400000e+03,6.48300000e+03,6.50500000e+03,6.41600000e+03,6.37700000e+03,6.21600000e+03,6.34400000e+03,6.32900000e+03,6.27900000e+03,6.33800000e+03,6.36500000e+03,6.39200000e+03,6.47200000e+03,6.47200000e+03,6.29600000e+03,6.37000000e+03,6.23200000e+03,6.27500000e+03,6.50700000e+03,6.38300000e+03,6.34800000e+03,6.31700000e+03,6.28100000e+03,6.28200000e+03,6.28500000e+03,6.38700000e+03,6.43300000e+03,6.30000000e+03,6.35300000e+03,6.45700000e+03,6.16900000e+03,6.25300000e+03,6.26700000e+03,6.23700000e+03,6.05100000e+03,6.28700000e+03,6.22900000e+03,6.19300000e+03,6.29100000e+03,6.44100000e+03,6.32100000e+03,6.43300000e+03,6.27400000e+03,6.27500000e+03,6.25500000e+03,6.29400000e+03,6.35800000e+03,6.42900000e+03,6.07900000e+03,6.24700000e+03,6.31300000e+03,6.37500000e+03,6.39400000e+03,6.46600000e+03,6.36200000e+03,6.38700000e+03,6.29800000e+03,6.27300000e+03,6.05000000e+03,6.13000000e+03,6.18800000e+03,6.23000000e+03,6.10900000e+03,6.22000000e+03,6.21300000e+03,6.22000000e+03,6.34300000e+03,6.15000000e+03,6.26300000e+03,6.39300000e+03,6.28000000e+03,6.35900000e+03,6.19900000e+03,6.04400000e+03,6.18400000e+03,6.20500000e+03,6.10300000e+03,6.07800000e+03,6.25000000e+03,6.25100000e+03,6.30300000e+03,6.16200000e+03,6.20100000e+03,6.30500000e+03,6.07100000e+03,6.16700000e+03,6.12700000e+03,6.10200000e+03,6.13800000e+03,6.04600000e+03,6.20100000e+03,6.15800000e+03,6.15500000e+03,6.19300000e+03,6.07900000e+03,6.33100000e+03,6.20300000e+03,6.06500000e+03,6.03300000e+03,6.08200000e+03,6.00600000e+03,5.93000000e+03,5.98900000e+03,6.05100000e+03,6.14200000e+03,6.07300000e+03,6.19400000e+03,5.98300000e+03,6.16000000e+03,6.27300000e+03,6.13900000e+03,5.94900000e+03,6.00000000e+03,6.09600000e+03,5.95700000e+03,5.92400000e+03,5.79500000e+03,6.09500000e+03,6.02600000e+03,5.96600000e+03,5.94300000e+03,6.05800000e+03,5.98600000e+03,5.95700000e+03,6.05300000e+03,6.00900000e+03,6.08500000e+03,5.98200000e+03,5.87800000e+03,5.96400000e+03,5.92900000e+03,6.09600000e+03,5.89500000e+03,5.94200000e+03,6.05100000e+03,5.96700000e+03,5.87600000e+03,5.97800000e+03,5.97600000e+03,5.80900000e+03,5.88900000e+03,5.74500000e+03,5.90500000e+03,5.85200000e+03,5.76400000e+03,5.78000000e+03,5.80700000e+03,5.82800000e+03,5.84600000e+03,5.90000000e+03,5.82900000e+03,5.81900000e+03,5.85000000e+03,5.71700000e+03,5.67000000e+03,5.83700000e+03,5.70000000e+03,5.63900000e+03,5.79200000e+03,5.87800000e+03,5.78900000e+03,5.87300000e+03,5.79000000e+03,5.84000000e+03,5.83600000e+03,5.78400000e+03,5.58300000e+03,5.77600000e+03,5.65600000e+03,5.70400000e+03,5.52000000e+03,5.71200000e+03,5.60800000e+03,5.75100000e+03,5.86900000e+03,5.74700000e+03,5.73200000e+03,5.66400000e+03,5.63900000e+03,5.75700000e+03,5.54800000e+03,5.59300000e+03,5.59000000e+03,5.61700000e+03,5.59000000e+03,5.62600000e+03,5.49400000e+03,5.64800000e+03,5.57600000e+03,5.67700000e+03,5.78700000e+03,5.50200000e+03,5.53300000e+03,5.49800000e+03,5.35300000e+03,5.42600000e+03,5.37400000e+03,5.26900000e+03,5.44700000e+03,5.31900000e+03,5.37700000e+03,5.49800000e+03,5.42500000e+03,5.42400000e+03,5.47400000e+03,5.41300000e+03,5.43000000e+03,5.43000000e+03,5.45600000e+03,5.44600000e+03,5.35800000e+03,5.44800000e+03,5.32100000e+03,5.34100000e+03,5.32500000e+03,5.31700000e+03,5.32700000e+03,5.23200000e+03,5.36700000e+03,5.50300000e+03,5.38600000e+03,5.34700000e+03,5.18900000e+03,5.24400000e+03,5.19700000e+03,5.24200000e+03,5.29700000e+03,5.22300000e+03,5.24700000e+03,5.24300000e+03};
	int nBins= 512 ;
	
	// come si riempie un TH1
  TCanvas* cCs = new TCanvas("cCs", "Cs_137_small", 200, 10, 600, 400);
  cCs->SetFillColor(0);
  cCs->SetGrid();
  cCs->cd();
	
  TH1F *Cs137mult = new TH1F("Cs137mult","Cs137mult",nBins,chan[0]-4,chan[nBins-1]+4);  
  for (int j=0;j<nBins;j++) {
    Cs137mult->SetBinContent(j+1,freq[j]);
  } 
  
  
  //inizio algoritmo per limiti fit gaussiani
  
  int start_point=1504;
  int nFits=9;
  int Fit_limit_sx[nFits];   
  int Fit_limit_dx[nFits];
  int Fit_mid_point[nFits];
  MultiGaussLims(chan,freq,Fit_limit_sx, Fit_limit_dx, Fit_mid_point, start_point, nBins, nFits);
  	
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
  
  Cs137mult->Fit("g1","R","e1",start_point,Fit_limit_dx[0]);
  Cs137mult->Fit("g2","R+","e1",Fit_limit_sx[1],Fit_limit_dx[1]);
  Cs137mult->Fit("g3","R++","e1",Fit_limit_sx[2],Fit_limit_dx[2]);
  Cs137mult->Fit("g4","R+++","e1",Fit_limit_sx[3],Fit_limit_dx[3]);
  Cs137mult->Fit("g5","R++++","e1",Fit_limit_sx[4],Fit_limit_dx[4]);
  Cs137mult->Fit("g6","R+++++","e1",Fit_limit_sx[5],Fit_limit_dx[5]);
  Cs137mult->Fit("g7","R++++++","e1",Fit_limit_sx[6],Fit_limit_dx[6]);
  Cs137mult->Fit("g8","R+++++++","e1",Fit_limit_sx[7],Fit_limit_dx[7]);
  Cs137mult->Fit("g9","R++++++++","e1",Fit_limit_sx[8],Fit_limit_dx[8]);
  
  Cs137mult->Draw("e");
  cCs->Print("Cs137_multigaus.png");
 
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
  
  
  TCanvas* cPP = new TCanvas("cPP", "delta_pp", 200, 10, 600, 400);
  cPP->SetFillColor(0);
  cPP->SetGrid();
  cPP->cd();
  
  TGraphErrors* gPP = new TGraphErrors(nFits-1, delta_pp_number, delta_pp, delta_00, delta_pp_err);
  gPP->SetMarkerSize(0.6);
  gPP->SetMarkerStyle(21);
  gPP->SetTitle("Distanze picco-picco spettro Cs137");
  gPP->GetYaxis()->SetTitle("distanza picco-picco");
  gPP->GetXaxis()->SetTitle("Numero picco-picco");
  
  TF1* PPf = new TF1("PPf", "[0] + [1]*x", 1.5, nFits-1.5);
  PPf->SetParameter(0, 500);
  PPf->SetParameter(1, 0); 
  PPf->SetLineColor(4);
  gPP->Fit(PPf, "RMS+");
  
  cout << "Fit delle distanze picco-picco con linea costante: " << endl;
  cout << "Chi^2:" << PPf->GetChisquare() << ", number of DoF: " << PPf->GetNDF() << " (Probability: " << PPf->GetProb() << ").\n" << endl;
  
  gPP->Draw("AP");
  cPP->Print("picco_picco_Cs137.png");
  
  Ztest(8.14973e-01, 0,1.07244e+00,0,0.05);
  
  
  // calcolo della delta picco picco media -> quindi se divido il numero di canali totale per tale distanza trovo il numero di celle accese -> oppure, con delta pp in energie, divido l'energia a cui mi trovo per delta pp in energie
  
  
  double delta_pp_sum=0;
  double nmeas=9;
  double delta_pp_squared_err_sum=0;
  
  for(int g=0;g<nmeas;g++){
  	delta_pp_sum=delta_pp[g]+delta_pp_sum;
  	delta_pp_squared_err_sum=delta_pp_squared_err_sum+(delta_pp_err[g]*delta_pp_err[g]);
  }
  
  double delta_pp_mean= delta_pp_sum/nmeas;
  double delta_pp_mean_err = sqrt(delta_pp_squared_err_sum)/nmeas;
  double k_factor=0.0514137; // K: (0.0514137 +- 0.00641083 ) keV/CHN
  double k_err=0.00641083;
  double delta_pp_mean_energy= delta_pp_mean*k_factor;
  double delta_pp_mean_err_energy = (delta_pp_mean*k_factor)*sqrt( (k_err/k_factor)*(k_err/k_factor) +(delta_pp_mean_err/delta_pp_mean)*(delta_pp_mean_err/delta_pp_mean));
  
  cout << "La distanza media picco-picco in CHN è: (" << delta_pp_mean << " +- " << delta_pp_mean_err << ") CHN;" << endl;
  cout << "La distanza media picco-picco in energia è: (" << delta_pp_mean_energy << " +- " << delta_pp_mean_err_energy << ") keV;" << endl;


	// calcolo della risoluzione ecc
	
// lavoro sulla risoluzione del picco in canali ; ricorda:
// La distanza media picco-picco in CHN è: (108.212 +- 2.00905) CHN;
// La distanza media picco-picco in energia è: (5.56357 +- 0.701375) keV;
// mean_CHN  stddev_CHN  mean_CHN_err  stddev_CHN_err

// risoluzione numero 1: R = delta(CHN)/CHN (va bene in canali o devo averlo per forza in energia???)


// faccio la media delle risoluzioni dei vari picchi

double mean_CHN[nFits];
double mean_CHN_err[nFits];
double stddev_CHN[nFits];
double stddev_CHN_err[nFits];
double CHN_resolution[nFits];
double CHN_resolution_err[nFits];
double mean_resolution=0;
double mean_variance=0;
cout << "\n" << endl;
for(int y=0;y<nFits;y++){
	mean_CHN[y]=peaks[y];
	mean_CHN_err[y]=peaks_err[y];
	stddev_CHN[y]=variances[y];
	stddev_CHN_err[y]=variances_err[y];
	CHN_resolution[y] = 2.355*((stddev_CHN[y])/(mean_CHN[y]));
	CHN_resolution_err[y]=2.355*((stddev_CHN[y])/(mean_CHN[y]))*sqrt( (stddev_CHN_err[y]/stddev_CHN[y])*(stddev_CHN_err[y]/stddev_CHN[y]
	) + (mean_CHN_err[y] /mean_CHN[y])*(mean_CHN_err[y]/mean_CHN[y]) );
	
	
	
	mean_resolution = mean_resolution+CHN_resolution[y];
	mean_variance = mean_variance+(CHN_resolution_err[y]*CHN_resolution_err[y]);
}

double mean_devstd;
mean_devstd = sqrt(mean_variance)/nFits;
mean_resolution=mean_resolution/nFits;






// risoluzione numero 2: R = 1/sqrt(N), dove N = numero celle accese (in corrispondenza del valore medio???)
double pois_resolution[nFits];
double pois_resolution_err[nFits];
double delta_pp_CHN=delta_pp_mean;   // questa è in CHN   
double delta_pp_CHN_err=delta_pp_mean_err;
double activated_cells[nFits]; 
double activated_cells_err[nFits];

for(int i=0;i<nFits;i++){
	activated_cells[i] = mean_CHN[i]/delta_pp_CHN;
	activated_cells_err[i] = (mean_CHN[i]/delta_pp_CHN)*sqrt( (stddev_CHN[i]/mean_CHN[i])*(stddev_CHN[i]/mean_CHN[i]) + (delta_pp_CHN_err /delta_pp_CHN)*(delta_pp_CHN_err/delta_pp_CHN)  );
	pois_resolution[i] =1./sqrt(activated_cells[i]);
	pois_resolution_err[i]=0.5*(activated_cells_err[i])/(sqrt(activated_cells[i]*activated_cells[i]*activated_cells[i]));

	

}
for(int i=0;i<nFits;i++){
cout << " Le celle attivate per il picco " << i << " sono: (" << activated_cells[i] << " +- " << activated_cells_err[i] << ") " << endl;

cout << " La deviazione std del picco " << i << " è: (" << stddev_CHN[i] << " +- " << stddev_CHN_err[i] << ") " << endl;
cout << " La media del picco " << i << " è: (" << mean_CHN[i] << " +- " << mean_CHN_err[i] << ") " << endl;
	cout << " La risoluzione ottenuta dalla deviazione std del picco " << i << " divisa per i suo valore medio è: (" << CHN_resolution[i] << " +- " << CHN_resolution_err[i] << ") " << endl;
	cout << "La risoluzione secondo R = 1/sqrt(N) del picco " << i << " è: (" << pois_resolution[i] <<  " +- " << pois_resolution_err[i] << ");" << endl;
	Ztest(CHN_resolution[i],pois_resolution[i],CHN_resolution_err[i],pois_resolution_err[i],0.05);
	cout << "\n" << endl;
}



}
