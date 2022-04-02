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

void new_Sr90_spettro(){

	double chan[]={5.25000000e+02,5.75000000e+02,6.25000000e+02,6.75000000e+02,7.25000000e+02,7.75000000e+02,8.25000000e+02,8.75000000e+02,9.25000000e+02,9.75000000e+02,1.02500000e+03,1.07500000e+03,1.12500000e+03,1.17500000e+03,1.22500000e+03,1.27500000e+03,1.32500000e+03,1.37500000e+03,1.42500000e+03,1.47500000e+03,1.52500000e+03,1.57500000e+03,1.62500000e+03,1.67500000e+03,1.72500000e+03,1.77500000e+03,1.82500000e+03,1.87500000e+03,1.92500000e+03,1.97500000e+03,2.02500000e+03,2.07500000e+03,2.12500000e+03,2.17500000e+03,2.22500000e+03,2.27500000e+03,2.32500000e+03,2.37500000e+03,2.42500000e+03,2.47500000e+03,2.52500000e+03,2.57500000e+03,2.62500000e+03,2.67500000e+03,2.72500000e+03,2.77500000e+03,2.82500000e+03,2.87500000e+03,2.92500000e+03,2.97500000e+03,3.02500000e+03,3.07500000e+03,3.12500000e+03,3.17500000e+03,3.22500000e+03,3.27500000e+03,3.32500000e+03,3.37500000e+03,3.42500000e+03,3.47500000e+03,3.52500000e+03,3.57500000e+03,3.62500000e+03,3.67500000e+03,3.72500000e+03,3.77500000e+03,3.82500000e+03,3.87500000e+03,3.92500000e+03,3.97500000e+03,4.02500000e+03,4.07500000e+03,4.12500000e+03,4.17500000e+03,4.22500000e+03,4.27500000e+03,4.32500000e+03,4.37500000e+03,4.42500000e+03,4.47500000e+03,4.52500000e+03,4.57500000e+03,4.62500000e+03,4.67500000e+03,4.72500000e+03,4.77500000e+03,4.82500000e+03,4.87500000e+03,4.92500000e+03,4.97500000e+03,5.02500000e+03,5.07500000e+03,5.12500000e+03,5.17500000e+03,5.22500000e+03,5.27500000e+03,5.32500000e+03,5.37500000e+03,5.42500000e+03,5.47500000e+03,5.52500000e+03,5.57500000e+03,5.62500000e+03,5.67500000e+03,5.72500000e+03,5.77500000e+03,5.82500000e+03,5.87500000e+03,5.92500000e+03,5.97500000e+03,6.02500000e+03,6.07500000e+03,6.12500000e+03,6.17500000e+03,6.22500000e+03,6.27500000e+03,6.32500000e+03,6.37500000e+03,6.42500000e+03,6.47500000e+03,6.52500000e+03,6.57500000e+03,6.62500000e+03,6.67500000e+03,6.72500000e+03,6.77500000e+03,6.82500000e+03,6.87500000e+03,6.92500000e+03,6.97500000e+03,7.02500000e+03,7.07500000e+03,7.12500000e+03,7.17500000e+03,7.22500000e+03,7.27500000e+03,7.32500000e+03,7.37500000e+03,7.42500000e+03,7.47500000e+03,7.52500000e+03,7.57500000e+03,7.62500000e+03,7.67500000e+03,7.72500000e+03,7.77500000e+03,7.82500000e+03,7.87500000e+03,7.92500000e+03,7.97500000e+03,8.02500000e+03,8.07500000e+03,8.12500000e+03,8.17500000e+03,8.22500000e+03,8.27500000e+03,8.32500000e+03,8.37500000e+03,8.42500000e+03,8.47500000e+03,8.52500000e+03,8.57500000e+03,8.62500000e+03,8.67500000e+03,8.72500000e+03,8.77500000e+03,8.82500000e+03,8.87500000e+03,8.92500000e+03,8.97500000e+03,9.02500000e+03,9.07500000e+03,9.12500000e+03,9.17500000e+03,9.22500000e+03,9.27500000e+03,9.32500000e+03,9.37500000e+03,9.42500000e+03,9.47500000e+03,9.52500000e+03,9.57500000e+03,9.62500000e+03,9.67500000e+03,9.72500000e+03,9.77500000e+03,9.82500000e+03,9.87500000e+03,9.92500000e+03,9.97500000e+03,1.00250000e+04,1.00750000e+04,1.01250000e+04,1.01750000e+04,1.02250000e+04,1.02750000e+04,1.03250000e+04,1.03750000e+04,1.04250000e+04,1.04750000e+04,1.05250000e+04,1.05750000e+04,1.06250000e+04,1.06750000e+04,1.07250000e+04,1.07750000e+04,1.08250000e+04,1.08750000e+04,1.09250000e+04,1.09750000e+04,1.10250000e+04,1.10750000e+04,1.11250000e+04,1.11750000e+04,1.12250000e+04,1.12750000e+04,1.13250000e+04,1.13750000e+04,1.14250000e+04,1.14750000e+04,1.15250000e+04,1.15750000e+04,1.16250000e+04,1.16750000e+04,1.17250000e+04,1.17750000e+04,1.18250000e+04,1.18750000e+04,1.19250000e+04,1.19750000e+04,1.20250000e+04,1.20750000e+04,1.21250000e+04,1.21750000e+04,1.22250000e+04,1.22750000e+04,1.23250000e+04,1.23750000e+04,1.24250000e+04,1.24750000e+04,1.25250000e+04,1.25750000e+04,1.26250000e+04,1.26750000e+04,1.27250000e+04,1.27750000e+04,1.28250000e+04,1.28750000e+04,1.29250000e+04,1.29750000e+04,1.30250000e+04,1.30750000e+04,1.31250000e+04,1.31750000e+04,1.32250000e+04,1.32750000e+04,1.33250000e+04,1.33750000e+04,1.34250000e+04,1.34750000e+04,1.35250000e+04,1.35750000e+04,1.36250000e+04,1.36750000e+04,1.37250000e+04,1.37750000e+04,1.38250000e+04,1.38750000e+04,1.39250000e+04,1.39750000e+04,1.40250000e+04,1.40750000e+04,1.41250000e+04,1.41750000e+04,1.42250000e+04,1.42750000e+04,1.43250000e+04,1.43750000e+04,1.44250000e+04,1.44750000e+04,1.45250000e+04,1.45750000e+04,1.46250000e+04,1.46750000e+04,1.47250000e+04,1.47750000e+04,1.48250000e+04,1.48750000e+04,1.49250000e+04,1.49750000e+04,1.50250000e+04,1.50750000e+04,1.51250000e+04,1.51750000e+04,1.52250000e+04,1.52750000e+04,1.53250000e+04,1.53750000e+04,1.54250000e+04,1.54750000e+04,1.55250000e+04,1.55750000e+04,1.56250000e+04,1.56750000e+04,1.57250000e+04,1.57750000e+04,1.58250000e+04,1.58750000e+04,1.59250000e+04,1.59750000e+04,1.60250000e+04,1.60750000e+04,1.61250000e+04,1.61750000e+04,1.62250000e+04,1.62750000e+04,1.63250000e+04,1.63750000e+04,1.64250000e+04,1.64750000e+04,1.65250000e+04,1.65750000e+04,1.66250000e+04,1.66750000e+04,1.67250000e+04,1.67750000e+04,1.68250000e+04,1.68750000e+04,1.69250000e+04,1.69750000e+04,1.70250000e+04,1.70750000e+04,1.71250000e+04,1.71750000e+04,1.72250000e+04,1.72750000e+04,1.73250000e+04,1.73750000e+04,1.74250000e+04,1.74750000e+04,1.75250000e+04,1.75750000e+04,1.76250000e+04,1.76750000e+04,1.77250000e+04,1.77750000e+04,1.78250000e+04,1.78750000e+04,1.79250000e+04,1.79750000e+04,1.80250000e+04,1.80750000e+04,1.81250000e+04,1.81750000e+04,1.82250000e+04,1.82750000e+04,1.83250000e+04,1.83750000e+04,1.84250000e+04,1.84750000e+04,1.85250000e+04,1.85750000e+04,1.86250000e+04,1.86750000e+04,1.87250000e+04,1.87750000e+04,1.88250000e+04,1.88750000e+04,1.89250000e+04,1.89750000e+04,1.90250000e+04,1.90750000e+04,1.91250000e+04,1.91750000e+04,1.92250000e+04,1.92750000e+04,1.93250000e+04,1.93750000e+04,1.94250000e+04,1.94750000e+04,1.95250000e+04,1.95750000e+04,1.96250000e+04,1.96750000e+04,1.97250000e+04,1.97750000e+04,1.98250000e+04,1.98750000e+04,1.99250000e+04,1.99750000e+04,2.00250000e+04,2.00750000e+04,2.01250000e+04,2.01750000e+04,2.02250000e+04,2.02750000e+04,2.03250000e+04,2.03750000e+04,2.04250000e+04,2.04750000e+04,2.05250000e+04,2.05750000e+04,2.06250000e+04,2.06750000e+04,2.07250000e+04,2.07750000e+04,2.08250000e+04,2.08750000e+04,2.09250000e+04,2.09750000e+04,2.10250000e+04,2.10750000e+04,2.11250000e+04,2.11750000e+04,2.12250000e+04,2.12750000e+04,2.13250000e+04,2.13750000e+04,2.14250000e+04,2.14750000e+04,2.15250000e+04,2.15750000e+04,2.16250000e+04,2.16750000e+04,2.17250000e+04,2.17750000e+04,2.18250000e+04,2.18750000e+04,2.19250000e+04,2.19750000e+04,2.20250000e+04,2.20750000e+04,2.21250000e+04,2.21750000e+04,2.22250000e+04,2.22750000e+04,2.23250000e+04,2.23750000e+04,2.24250000e+04,2.24750000e+04,2.25250000e+04,2.25750000e+04,2.26250000e+04,2.26750000e+04,2.27250000e+04,2.27750000e+04,2.28250000e+04,2.28750000e+04,2.29250000e+04,2.29750000e+04,2.30250000e+04,2.30750000e+04,2.31250000e+04,2.31750000e+04,2.32250000e+04,2.32750000e+04,2.33250000e+04,2.33750000e+04,2.34250000e+04,2.34750000e+04,2.35250000e+04,2.35750000e+04,2.36250000e+04,2.36750000e+04,2.37250000e+04,2.37750000e+04,2.38250000e+04,2.38750000e+04,2.39250000e+04,2.39750000e+04,2.40250000e+04,2.40750000e+04,2.41250000e+04,2.41750000e+04,2.42250000e+04,2.42750000e+04,2.43250000e+04,2.43750000e+04,2.44250000e+04,2.44750000e+04,2.45250000e+04,2.45750000e+04,2.46250000e+04,2.46750000e+04,2.47250000e+04,2.47750000e+04,2.48250000e+04,2.48750000e+04,2.49250000e+04,2.49750000e+04,2.50250000e+04,2.50750000e+04,2.51250000e+04,2.51750000e+04,2.52250000e+04,2.52750000e+04,2.53250000e+04,2.53750000e+04,2.54250000e+04,2.54750000e+04,2.55250000e+04,2.55750000e+04,2.56250000e+04,2.56750000e+04,2.57250000e+04,2.57750000e+04,2.58250000e+04,2.58750000e+04,2.59250000e+04,2.59750000e+04,2.60250000e+04,2.60750000e+04,2.61250000e+04,2.61750000e+04,2.62250000e+04,2.62750000e+04,2.63250000e+04,2.63750000e+04,2.64250000e+04,2.64750000e+04,2.65250000e+04,2.65750000e+04,2.66250000e+04,2.66750000e+04,2.67250000e+04,2.67750000e+04,2.68250000e+04,2.68750000e+04,2.69250000e+04,2.69750000e+04,2.70250000e+04,2.70750000e+04,2.71250000e+04,2.71750000e+04,2.72250000e+04,2.72750000e+04,2.73250000e+04,2.73750000e+04,2.74250000e+04,2.74750000e+04,2.75250000e+04,2.75750000e+04,2.76250000e+04,2.76750000e+04,2.77250000e+04,2.77750000e+04,2.78250000e+04,2.78750000e+04,2.79250000e+04,2.79750000e+04,2.80250000e+04,2.80750000e+04,2.81250000e+04,2.81750000e+04,2.82250000e+04,2.82750000e+04,2.83250000e+04,2.83750000e+04,2.84250000e+04,2.84750000e+04,2.85250000e+04,2.85750000e+04,2.86250000e+04,2.86750000e+04,2.87250000e+04,2.87750000e+04,2.88250000e+04,2.88750000e+04,2.89250000e+04,2.89750000e+04,2.90250000e+04,2.90750000e+04,2.91250000e+04,2.91750000e+04,2.92250000e+04,2.92750000e+04,2.93250000e+04,2.93750000e+04,2.94250000e+04,2.94750000e+04,2.95250000e+04,2.95750000e+04,2.96250000e+04,2.96750000e+04,2.97250000e+04,2.97750000e+04,2.98250000e+04,2.98750000e+04,2.99250000e+04,2.99750000e+04,3.00250000e+04,3.00750000e+04,3.01250000e+04,3.01750000e+04,3.02250000e+04,3.02750000e+04,3.03250000e+04,3.03750000e+04,3.04250000e+04,3.04750000e+04,3.05250000e+04,3.05750000e+04,3.06250000e+04,3.06750000e+04,3.07250000e+04,3.07750000e+04,3.08250000e+04,3.08750000e+04,3.09250000e+04,3.09750000e+04,3.10250000e+04,3.10750000e+04,3.11250000e+04,3.11750000e+04,3.12250000e+04,3.12750000e+04,3.13250000e+04,3.13750000e+04,3.14250000e+04,3.14750000e+04,3.15250000e+04,3.15750000e+04,3.16250000e+04,3.16750000e+04,3.17250000e+04,3.17750000e+04,3.18250000e+04,3.18750000e+04,3.19250000e+04,3.19750000e+04,3.20250000e+04,3.20750000e+04,3.21250000e+04,3.21750000e+04,3.22250000e+04,3.22750000e+04,3.23250000e+04,3.23750000e+04,3.24250000e+04,3.24750000e+04,3.25250000e+04,3.25750000e+04,3.26250000e+04,3.26750000e+04,3.27250000e+04,3.27750000e+04,3.28250000e+04,3.28750000e+04,3.29250000e+04,3.29750000e+04,3.30250000e+04,3.30750000e+04,3.31250000e+04,3.31750000e+04,3.32250000e+04,3.32750000e+04,3.33250000e+04,3.33750000e+04,3.34250000e+04,3.34750000e+04,3.35250000e+04,3.35750000e+04,3.36250000e+04,3.36750000e+04,3.37250000e+04,3.37750000e+04,3.38250000e+04,3.38750000e+04,3.39250000e+04,3.39750000e+04,3.40250000e+04,3.40750000e+04,3.41250000e+04,3.41750000e+04,3.42250000e+04,3.42750000e+04,3.43250000e+04,3.43750000e+04,3.44250000e+04,3.44750000e+04,3.45250000e+04,3.45750000e+04,3.46250000e+04,3.46750000e+04,3.47250000e+04,3.47750000e+04,3.48250000e+04,3.48750000e+04,3.49250000e+04,3.49750000e+04,3.50250000e+04,3.50750000e+04,3.51250000e+04,3.51750000e+04,3.52250000e+04,3.52750000e+04,3.53250000e+04,3.53750000e+04,3.54250000e+04,3.54750000e+04,3.55250000e+04,3.55750000e+04,3.56250000e+04,3.56750000e+04,3.57250000e+04,3.57750000e+04,3.58250000e+04,3.58750000e+04,3.59250000e+04,3.59750000e+04,3.60250000e+04,3.60750000e+04,3.61250000e+04,3.61750000e+04,3.62250000e+04,3.62750000e+04,3.63250000e+04,3.63750000e+04,3.64250000e+04,3.64750000e+04,3.65250000e+04,3.65750000e+04,3.66250000e+04,3.66750000e+04,3.67250000e+04,3.67750000e+04,3.68250000e+04,3.68750000e+04,3.69250000e+04,3.69750000e+04,3.70250000e+04,3.70750000e+04,3.71250000e+04,3.71750000e+04,3.72250000e+04,3.72750000e+04,3.73250000e+04,3.73750000e+04,3.74250000e+04,3.74750000e+04,3.75250000e+04,3.75750000e+04,3.76250000e+04,3.76750000e+04,3.77250000e+04,3.77750000e+04,3.78250000e+04,3.78750000e+04,3.79250000e+04,3.79750000e+04,3.80250000e+04,3.80750000e+04,3.81250000e+04,3.81750000e+04,3.82250000e+04,3.82750000e+04,3.83250000e+04,3.83750000e+04,3.84250000e+04,3.84750000e+04,3.85250000e+04,3.85750000e+04,3.86250000e+04,3.86750000e+04,3.87250000e+04,3.87750000e+04,3.88250000e+04,3.88750000e+04,3.89250000e+04,3.89750000e+04,3.90250000e+04,3.90750000e+04,3.91250000e+04,3.91750000e+04,3.92250000e+04,3.92750000e+04,3.93250000e+04,3.93750000e+04,3.94250000e+04,3.94750000e+04,3.95250000e+04,3.95750000e+04,3.96250000e+04,3.96750000e+04,3.97250000e+04,3.97750000e+04,3.98250000e+04,3.98750000e+04,3.99250000e+04,3.99750000e+04,4.00250000e+04,4.00750000e+04,4.01250000e+04,4.01750000e+04,4.02250000e+04,4.02750000e+04,4.03250000e+04,4.03750000e+04,4.04250000e+04,4.04750000e+04,4.05250000e+04,4.05750000e+04,4.06250000e+04,4.06750000e+04,4.07250000e+04,4.07750000e+04,4.08250000e+04,4.08750000e+04,4.09250000e+04,4.09750000e+04,4.10250000e+04,4.10750000e+04,4.11250000e+04,4.11750000e+04,4.12250000e+04,4.12750000e+04,4.13250000e+04,4.13750000e+04,4.14250000e+04,4.14750000e+04,4.15250000e+04,4.15750000e+04,4.16250000e+04,4.16750000e+04,4.17250000e+04,4.17750000e+04,4.18250000e+04,4.18750000e+04,4.19250000e+04,4.19750000e+04,4.20250000e+04,4.20750000e+04,4.21250000e+04,4.21750000e+04,4.22250000e+04,4.22750000e+04,4.23250000e+04,4.23750000e+04,4.24250000e+04,4.24750000e+04,4.25250000e+04,4.25750000e+04,4.26250000e+04,4.26750000e+04,4.27250000e+04,4.27750000e+04,4.28250000e+04,4.28750000e+04,4.29250000e+04,4.29750000e+04,4.30250000e+04,4.30750000e+04,4.31250000e+04,4.31750000e+04,4.32250000e+04,4.32750000e+04,4.33250000e+04,4.33750000e+04,4.34250000e+04,4.34750000e+04,4.35250000e+04,4.35750000e+04,4.36250000e+04,4.36750000e+04,4.37250000e+04,4.37750000e+04,4.38250000e+04,4.38750000e+04,4.39250000e+04,4.39750000e+04,4.40250000e+04,4.40750000e+04,4.41250000e+04,4.41750000e+04,4.42250000e+04,4.42750000e+04,4.43250000e+04,4.43750000e+04,4.44250000e+04,4.44750000e+04,4.45250000e+04,4.45750000e+04,4.46250000e+04,4.46750000e+04,4.47250000e+04,4.47750000e+04,4.48250000e+04,4.48750000e+04,4.49250000e+04,4.49750000e+04,4.50250000e+04,4.50750000e+04,4.51250000e+04,4.51750000e+04,4.52250000e+04,4.52750000e+04,4.53250000e+04,4.53750000e+04,4.54250000e+04,4.54750000e+04,4.55250000e+04,4.55750000e+04,4.56250000e+04,4.56750000e+04,4.57250000e+04,4.57750000e+04,4.58250000e+04,4.58750000e+04,4.59250000e+04,4.59750000e+04,4.60250000e+04,4.60750000e+04,4.61250000e+04,4.61750000e+04,4.62250000e+04,4.62750000e+04,4.63250000e+04,4.63750000e+04,4.64250000e+04,4.64750000e+04,4.65250000e+04,4.65750000e+04,4.66250000e+04,4.66750000e+04,4.67250000e+04,4.67750000e+04,4.68250000e+04,4.68750000e+04,4.69250000e+04,4.69750000e+04,4.70250000e+04,4.70750000e+04,4.71250000e+04,4.71750000e+04,4.72250000e+04,4.72750000e+04,4.73250000e+04,4.73750000e+04,4.74250000e+04,4.74750000e+04,4.75250000e+04,4.75750000e+04,4.76250000e+04,4.76750000e+04,4.77250000e+04,4.77750000e+04,4.78250000e+04,4.78750000e+04,4.79250000e+04,4.79750000e+04,4.80250000e+04,4.80750000e+04,4.81250000e+04,4.81750000e+04,4.82250000e+04,4.82750000e+04,4.83250000e+04,4.83750000e+04,4.84250000e+04,4.84750000e+04,4.85250000e+04,4.85750000e+04,4.86250000e+04,4.86750000e+04,4.87250000e+04,4.87750000e+04,4.88250000e+04,4.88750000e+04,4.89250000e+04,4.89750000e+04,4.90250000e+04,4.90750000e+04,4.91250000e+04,4.91750000e+04,4.92250000e+04,4.92750000e+04,4.93250000e+04,4.93750000e+04,4.94250000e+04,4.94750000e+04,4.95250000e+04,4.95750000e+04,4.96250000e+04,4.96750000e+04,4.97250000e+04,4.97750000e+04,4.98250000e+04,4.98750000e+04,4.99250000e+04,4.99750000e+04,5.00250000e+04,5.00750000e+04,5.01250000e+04,5.01750000e+04,5.02250000e+04,5.02750000e+04,5.03250000e+04,5.03750000e+04,5.04250000e+04,5.04750000e+04,5.05250000e+04,5.05750000e+04,5.06250000e+04,5.06750000e+04,5.07250000e+04,5.07750000e+04,5.08250000e+04,5.08750000e+04,5.09250000e+04,5.09750000e+04,5.10250000e+04,5.10750000e+04,5.11250000e+04,5.11750000e+04,5.12250000e+04,5.12750000e+04,5.13250000e+04,5.13750000e+04,5.14250000e+04,5.14750000e+04,5.15250000e+04,5.15750000e+04,5.16250000e+04,5.16750000e+04};
	double freq[]={2.00000000e+00,1.00000000e+00,4.00000000e+00,1.10000000e+01,1.50000000e+01,2.40000000e+01,3.00000000e+01,7.10000000e+01,1.12000000e+02,1.84000000e+02,2.39000000e+02,3.44000000e+02,5.14000000e+02,7.71000000e+02,1.10600000e+03,1.56900000e+03,2.05900000e+03,2.39800000e+03,2.69600000e+03,2.80100000e+03,3.28800000e+03,3.12900000e+03,3.46200000e+03,3.39600000e+03,3.55000000e+03,3.63700000e+03,3.72800000e+03,3.75200000e+03,3.85400000e+03,3.87900000e+03,3.77400000e+03,3.94500000e+03,3.94700000e+03,3.98700000e+03,3.94000000e+03,4.20000000e+03,4.09800000e+03,4.13000000e+03,4.23000000e+03,4.23500000e+03,4.19700000e+03,4.20400000e+03,4.33600000e+03,4.33100000e+03,4.30300000e+03,4.34700000e+03,4.39600000e+03,4.23200000e+03,4.34400000e+03,4.41300000e+03,4.52800000e+03,4.51700000e+03,4.41400000e+03,4.57700000e+03,4.65300000e+03,4.61000000e+03,4.56500000e+03,4.62300000e+03,4.64700000e+03,4.58400000e+03,4.62400000e+03,4.66400000e+03,4.59800000e+03,4.50200000e+03,4.74700000e+03,4.69300000e+03,4.74400000e+03,4.57900000e+03,4.73800000e+03,4.63200000e+03,4.67400000e+03,4.58500000e+03,4.79700000e+03,4.54900000e+03,4.62700000e+03,4.63900000e+03,4.57500000e+03,4.71700000e+03,4.66600000e+03,4.66300000e+03,4.66000000e+03,4.63900000e+03,4.70600000e+03,4.70000000e+03,4.65300000e+03,4.60000000e+03,4.50100000e+03,4.65200000e+03,4.57900000e+03,4.61900000e+03,4.56700000e+03,4.61600000e+03,4.52200000e+03,4.58000000e+03,4.60800000e+03,4.56000000e+03,4.42600000e+03,4.49000000e+03,4.56100000e+03,4.36100000e+03,4.52700000e+03,4.52300000e+03,4.39500000e+03,4.45800000e+03,4.41100000e+03,4.51800000e+03,4.22000000e+03,4.49400000e+03,4.37100000e+03,4.28800000e+03,4.40100000e+03,4.37500000e+03,4.23800000e+03,4.08600000e+03,4.29400000e+03,4.22000000e+03,4.20300000e+03,4.24600000e+03,4.21000000e+03,4.29600000e+03,4.29900000e+03,4.22700000e+03,4.25600000e+03,4.21700000e+03,4.14600000e+03,4.16200000e+03,4.16300000e+03,4.21900000e+03,4.17000000e+03,4.16300000e+03,4.13600000e+03,4.12600000e+03,4.06500000e+03,4.12500000e+03,4.07700000e+03,4.03500000e+03,3.99900000e+03,4.08600000e+03,4.07500000e+03,3.93200000e+03,4.07200000e+03,4.08500000e+03,3.98900000e+03,4.00400000e+03,4.01000000e+03,3.98500000e+03,3.92300000e+03,4.07200000e+03,3.87500000e+03,3.81600000e+03,3.99800000e+03,4.05200000e+03,3.95200000e+03,3.90400000e+03,3.92400000e+03,3.89600000e+03,3.98100000e+03,3.89900000e+03,3.91600000e+03,3.94400000e+03,3.97100000e+03,3.82300000e+03,3.91100000e+03,3.95800000e+03,3.96900000e+03,4.04000000e+03,3.81800000e+03,3.89300000e+03,3.91700000e+03,3.86900000e+03,3.87000000e+03,3.90200000e+03,3.93000000e+03,3.97200000e+03,3.77400000e+03,3.93700000e+03,3.84100000e+03,3.89500000e+03,3.85000000e+03,3.84300000e+03,3.85400000e+03,3.81400000e+03,3.89100000e+03,3.85900000e+03,4.00400000e+03,3.76600000e+03,3.81400000e+03,3.80500000e+03,3.77700000e+03,3.91000000e+03,3.85300000e+03,3.74500000e+03,3.84000000e+03,3.82300000e+03,3.93100000e+03,3.80900000e+03,3.76000000e+03,3.85400000e+03,3.71800000e+03,3.85900000e+03,3.84900000e+03,3.71100000e+03,3.81100000e+03,3.78100000e+03,3.86300000e+03,3.81200000e+03,3.72400000e+03,3.81600000e+03,3.83800000e+03,3.89100000e+03,3.73500000e+03,3.71400000e+03,3.84900000e+03,3.80400000e+03,3.76000000e+03,3.86800000e+03,3.75700000e+03,3.77200000e+03,3.67400000e+03,3.66300000e+03,3.80400000e+03,3.72500000e+03,3.71200000e+03,3.84500000e+03,3.77800000e+03,3.78800000e+03,3.83800000e+03,3.89700000e+03,3.69500000e+03,3.75900000e+03,3.65700000e+03,3.79400000e+03,3.77200000e+03,3.60800000e+03,3.71600000e+03,3.79900000e+03,3.66800000e+03,3.67200000e+03,3.62200000e+03,3.67500000e+03,3.58900000e+03,3.69500000e+03,3.73200000e+03,3.64800000e+03,3.71600000e+03,3.76500000e+03,3.63500000e+03,3.74500000e+03,3.65900000e+03,3.68900000e+03,3.68100000e+03,3.71200000e+03,3.66500000e+03,3.57200000e+03,3.72300000e+03,3.66900000e+03,3.65900000e+03,3.61700000e+03,3.63700000e+03,3.68000000e+03,3.65200000e+03,3.63600000e+03,3.78500000e+03,3.66900000e+03,3.54600000e+03,3.62400000e+03,3.63600000e+03,3.56300000e+03,3.59700000e+03,3.58700000e+03,3.55000000e+03,3.59400000e+03,3.61000000e+03,3.53800000e+03,3.59100000e+03,3.55500000e+03,3.57000000e+03,3.65400000e+03,3.48800000e+03,3.54700000e+03,3.55800000e+03,3.57800000e+03,3.64500000e+03,3.59100000e+03,3.47300000e+03,3.52300000e+03,3.57100000e+03,3.52700000e+03,3.48400000e+03,3.53400000e+03,3.56100000e+03,3.48300000e+03,3.45000000e+03,3.52700000e+03,3.52100000e+03,3.54000000e+03,3.43500000e+03,3.37700000e+03,3.33800000e+03,3.46700000e+03,3.47300000e+03,3.48200000e+03,3.43100000e+03,3.42400000e+03,3.38800000e+03,3.41500000e+03,3.40900000e+03,3.34800000e+03,3.42800000e+03,3.35900000e+03,3.46100000e+03,3.37500000e+03,3.39900000e+03,3.36000000e+03,3.38900000e+03,3.40600000e+03,3.40200000e+03,3.34900000e+03,3.41100000e+03,3.26000000e+03,3.32000000e+03,3.34200000e+03,3.38900000e+03,3.26400000e+03,3.29500000e+03,3.32100000e+03,3.30400000e+03,3.37000000e+03,3.26800000e+03,3.26300000e+03,3.24900000e+03,3.31300000e+03,3.30200000e+03,3.20900000e+03,3.26100000e+03,3.22900000e+03,3.24800000e+03,3.20500000e+03,3.23000000e+03,3.28600000e+03,3.32000000e+03,3.24400000e+03,3.21700000e+03,3.21200000e+03,3.21300000e+03,3.19600000e+03,3.13500000e+03,3.13700000e+03,3.13600000e+03,3.19000000e+03,3.24300000e+03,3.18400000e+03,3.14700000e+03,3.19700000e+03,3.23400000e+03,3.16400000e+03,3.13700000e+03,3.16700000e+03,3.08600000e+03,3.08600000e+03,3.19600000e+03,3.18500000e+03,3.13300000e+03,3.07300000e+03,3.12000000e+03,3.09500000e+03,3.04100000e+03,3.03100000e+03,3.03400000e+03,3.17900000e+03,2.97300000e+03,3.02600000e+03,3.09300000e+03,3.13500000e+03,3.11200000e+03,3.00400000e+03,3.07000000e+03,3.02700000e+03,3.02500000e+03,3.03900000e+03,3.04400000e+03,2.96500000e+03,2.93300000e+03,3.05400000e+03,2.96500000e+03,3.00300000e+03,2.90200000e+03,2.96600000e+03,3.04400000e+03,2.97800000e+03,2.96300000e+03,2.91800000e+03,2.88200000e+03,3.02600000e+03,2.92600000e+03,2.92500000e+03,2.83800000e+03,2.91600000e+03,2.88100000e+03,2.88800000e+03,2.90400000e+03,2.81800000e+03,2.87300000e+03,2.79500000e+03,2.89600000e+03,2.88100000e+03,2.85200000e+03,2.84400000e+03,2.82800000e+03,2.76700000e+03,2.81000000e+03,2.81400000e+03,2.88100000e+03,2.85000000e+03,2.66100000e+03,2.69400000e+03,2.79800000e+03,2.83800000e+03,2.73100000e+03,2.76500000e+03,2.83700000e+03,2.69300000e+03,2.76500000e+03,2.82300000e+03,2.76000000e+03,2.76900000e+03,2.74100000e+03,2.70500000e+03,2.73100000e+03,2.66000000e+03,2.66400000e+03,2.75000000e+03,2.68000000e+03,2.67900000e+03,2.69800000e+03,2.63200000e+03,2.64300000e+03,2.71500000e+03,2.54600000e+03,2.61800000e+03,2.66500000e+03,2.53100000e+03,2.53400000e+03,2.64100000e+03,2.53400000e+03,2.56300000e+03,2.52300000e+03,2.52300000e+03,2.56700000e+03,2.55300000e+03,2.56000000e+03,2.66500000e+03,2.56200000e+03,2.58900000e+03,2.56500000e+03,2.54000000e+03,2.58600000e+03,2.57000000e+03,2.53700000e+03,2.49700000e+03,2.41200000e+03,2.50200000e+03,2.52300000e+03,2.59100000e+03,2.51800000e+03,2.49500000e+03,2.43400000e+03,2.41600000e+03,2.39400000e+03,2.43600000e+03,2.42400000e+03,2.39100000e+03,2.42400000e+03,2.35300000e+03,2.34800000e+03,2.30500000e+03,2.40100000e+03,2.29500000e+03,2.33300000e+03,2.32600000e+03,2.37700000e+03,2.36400000e+03,2.37700000e+03,2.25000000e+03,2.31400000e+03,2.32100000e+03,2.29800000e+03,2.29400000e+03,2.35100000e+03,2.22100000e+03,2.24600000e+03,2.24800000e+03,2.27700000e+03,2.23300000e+03,2.15100000e+03,2.20600000e+03,2.13600000e+03,2.22800000e+03,2.14800000e+03,2.11300000e+03,2.17300000e+03,2.10200000e+03,2.13700000e+03,2.14800000e+03,2.17000000e+03,2.17300000e+03,2.13800000e+03,2.13200000e+03,2.10400000e+03,2.18300000e+03,2.18200000e+03,2.05400000e+03,2.09600000e+03,1.99800000e+03,2.09500000e+03,2.07700000e+03,2.04800000e+03,2.06500000e+03,1.96700000e+03,1.96100000e+03,2.00400000e+03,2.07300000e+03,2.04300000e+03,1.87800000e+03,1.92200000e+03,1.93400000e+03,1.97700000e+03,1.92100000e+03,2.02000000e+03,1.95500000e+03,1.88900000e+03,1.87600000e+03,1.91200000e+03,1.94400000e+03,1.95300000e+03,1.92900000e+03,1.80200000e+03,1.82900000e+03,1.85600000e+03,1.79200000e+03,1.90400000e+03,1.86500000e+03,1.81100000e+03,1.80300000e+03,1.78400000e+03,1.77100000e+03,1.72700000e+03,1.77600000e+03,1.71100000e+03,1.83400000e+03,1.71800000e+03,1.71100000e+03,1.75700000e+03,1.72000000e+03,1.71000000e+03,1.66900000e+03,1.70600000e+03,1.73100000e+03,1.75000000e+03,1.69500000e+03,1.67600000e+03,1.58700000e+03,1.61000000e+03,1.58100000e+03,1.62400000e+03,1.58700000e+03,1.55900000e+03,1.57700000e+03,1.55600000e+03,1.57100000e+03,1.56500000e+03,1.59700000e+03,1.58100000e+03,1.55700000e+03,1.50700000e+03,1.49600000e+03,1.47300000e+03,1.47800000e+03,1.44600000e+03,1.42500000e+03,1.49300000e+03,1.44200000e+03,1.40700000e+03,1.39000000e+03,1.46500000e+03,1.41900000e+03,1.41400000e+03,1.32300000e+03,1.37800000e+03,1.33900000e+03,1.36900000e+03,1.28300000e+03,1.39600000e+03,1.33400000e+03,1.33700000e+03,1.26800000e+03,1.22900000e+03,1.33400000e+03,1.33300000e+03,1.24900000e+03,1.23500000e+03,1.17300000e+03,1.14900000e+03,1.17500000e+03,1.23900000e+03,1.15200000e+03,1.24600000e+03,1.13100000e+03,1.11500000e+03,1.22400000e+03,1.12600000e+03,1.11300000e+03,1.06900000e+03,1.14400000e+03,1.11400000e+03,1.07900000e+03,1.12400000e+03,1.06900000e+03,1.08400000e+03,1.05700000e+03,1.04900000e+03,1.05500000e+03,1.05000000e+03,1.02400000e+03,1.00200000e+03,1.01600000e+03,8.97000000e+02,9.54000000e+02,9.51000000e+02,9.29000000e+02,9.20000000e+02,8.95000000e+02,8.98000000e+02,8.72000000e+02,8.35000000e+02,8.62000000e+02,8.80000000e+02,8.73000000e+02,8.43000000e+02,8.30000000e+02,7.91000000e+02,8.10000000e+02,8.08000000e+02,7.91000000e+02,7.64000000e+02,7.41000000e+02,7.67000000e+02,7.18000000e+02,7.46000000e+02,7.09000000e+02,7.36000000e+02,7.00000000e+02,6.58000000e+02,6.97000000e+02,6.22000000e+02,6.69000000e+02,6.43000000e+02,7.04000000e+02,6.27000000e+02,6.26000000e+02,6.06000000e+02,6.36000000e+02,5.49000000e+02,5.64000000e+02,5.96000000e+02,5.73000000e+02,5.38000000e+02,5.78000000e+02,5.47000000e+02,5.71000000e+02,4.88000000e+02,5.11000000e+02,4.87000000e+02,4.92000000e+02,5.14000000e+02,4.63000000e+02,4.70000000e+02,4.84000000e+02,4.44000000e+02,4.39000000e+02,4.62000000e+02,4.12000000e+02,3.98000000e+02,4.14000000e+02,4.14000000e+02,4.10000000e+02,4.11000000e+02,4.22000000e+02,3.65000000e+02,3.63000000e+02,3.58000000e+02,3.70000000e+02,3.51000000e+02,3.35000000e+02,3.50000000e+02,3.51000000e+02,3.31000000e+02,3.25000000e+02,3.45000000e+02,3.31000000e+02,3.20000000e+02,3.00000000e+02,2.79000000e+02,2.94000000e+02,2.69000000e+02,2.62000000e+02,2.83000000e+02,2.69000000e+02,2.59000000e+02,2.50000000e+02,2.48000000e+02,2.49000000e+02,2.19000000e+02,2.47000000e+02,2.21000000e+02,2.37000000e+02,1.96000000e+02,1.94000000e+02,2.19000000e+02,2.07000000e+02,1.88000000e+02,1.91000000e+02,1.93000000e+02,1.81000000e+02,1.84000000e+02,1.61000000e+02,1.74000000e+02,1.84000000e+02,1.63000000e+02,1.45000000e+02,1.55000000e+02,1.30000000e+02,1.42000000e+02,1.52000000e+02,1.40000000e+02,1.28000000e+02,1.28000000e+02,1.26000000e+02,1.29000000e+02,1.17000000e+02,9.50000000e+01,1.17000000e+02,1.20000000e+02,1.06000000e+02,1.17000000e+02,9.80000000e+01,1.03000000e+02,8.90000000e+01,1.11000000e+02,8.00000000e+01,9.40000000e+01,6.40000000e+01,8.60000000e+01,8.30000000e+01,6.80000000e+01,7.70000000e+01,7.30000000e+01,8.40000000e+01,7.20000000e+01,7.10000000e+01,7.00000000e+01,6.30000000e+01,5.80000000e+01,5.80000000e+01,6.70000000e+01,6.80000000e+01,6.90000000e+01,6.40000000e+01,5.80000000e+01,4.50000000e+01,6.40000000e+01,4.60000000e+01,3.80000000e+01,5.20000000e+01,4.10000000e+01,3.80000000e+01,4.70000000e+01,3.50000000e+01,3.10000000e+01,4.80000000e+01,4.00000000e+01,3.80000000e+01,3.30000000e+01,3.80000000e+01,2.40000000e+01,3.00000000e+01,2.80000000e+01,2.70000000e+01,1.80000000e+01,2.40000000e+01,2.30000000e+01,2.30000000e+01,1.80000000e+01,2.60000000e+01,2.10000000e+01,2.40000000e+01,1.50000000e+01,3.00000000e+01,2.00000000e+01,2.40000000e+01,2.30000000e+01,1.80000000e+01,1.90000000e+01,1.50000000e+01,2.00000000e+01,8.00000000e+00,1.00000000e+01,1.40000000e+01,1.30000000e+01,2.40000000e+01,1.10000000e+01,7.00000000e+00,1.20000000e+01,1.30000000e+01,7.00000000e+00,8.00000000e+00,6.00000000e+00,7.00000000e+00,1.50000000e+01,1.60000000e+01,8.00000000e+00,9.00000000e+00,1.60000000e+01,7.00000000e+00,6.00000000e+00,5.00000000e+00,1.30000000e+01,5.00000000e+00,7.00000000e+00,7.00000000e+00,5.00000000e+00,4.00000000e+00,7.00000000e+00,5.00000000e+00,4.00000000e+00,9.00000000e+00,6.00000000e+00,5.00000000e+00,3.00000000e+00,4.00000000e+00,4.00000000e+00,4.00000000e+00,9.00000000e+00,6.00000000e+00,7.00000000e+00,2.00000000e+00,1.00000000e+00,2.00000000e+00,2.00000000e+00,1.00000000e+00,0.00000000e+00,3.00000000e+00,3.00000000e+00,2.00000000e+00,3.00000000e+00,1.00000000e+00,1.00000000e+00,2.00000000e+00,1.00000000e+00,2.00000000e+00,1.00000000e+00,0.00000000e+00,2.00000000e+00,1.00000000e+00,1.00000000e+00,1.00000000e+00,2.00000000e+00,2.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,2.00000000e+00,0.00000000e+00,2.00000000e+00,2.00000000e+00,2.00000000e+00,1.00000000e+00,2.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,2.00000000e+00,1.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,2.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,3.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,2.00000000e+00,1.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,2.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00,1.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,2.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,2.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,1.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00,0.00000000e+00};
	int nBins= 1024 ;
	
	// come si riempie un TH1
	
TCanvas* cSr = new TCanvas("cSr", "Sr_tot", 200, 10, 600, 400);
  cSr->SetFillColor(0);
  cSr->SetGrid();
  cSr->cd();
	
  TH1F *Sr90tot = new TH1F("Sr90tot","Sr90tot",nBins,chan[0]-25,chan[nBins-1]+25);  
  for (int j=0;j<nBins;j++) {
    Sr90tot->SetBinContent(j+1,freq[j]);
  } 
  Sr90tot->Draw("e1");
  cSr->Print("Sr90_tot_CHN.png");
  
  // K: (0.0514137 +- 0.00641083 ) keV/CHN
double k_factor=0.0514137;
double k_err=0.00641083;

double energy[1024];

for(int i=0; i<nBins;i++){
	energy[i]=k_factor*chan[i];
}

double energy_half_step;
energy_half_step=25*k_factor;


  //  al canale 600 corrisponde energia di 1569 keV, siamo verso fine spettro

// ora vorrei rebinnare il tutto -> creo nuovi vettori

int start = 874;
int new_length;
new_length= nBins - start; // qua ho 1024 - 624 ossia un vettore da 400 elementi. 
double new_energy[new_length];
double new_freq[new_length];

for(int i=0; i < new_length;i++){
	new_energy[i]=energy[start+i];
	new_freq[i]=freq[start+i];
}

TCanvas* cSr_zoom = new TCanvas("cSr_zoom", "Sr_zoom", 200, 10, 600, 400);
  cSr_zoom->SetFillColor(0);
  cSr_zoom->SetGrid();
  cSr_zoom->cd();
	
  TH1F *Sr90_zoom = new TH1F("Sr90_zoom","Sr90_zoom",new_length,new_energy[0]-energy_half_step,new_energy[new_length-1]+energy_half_step);  
  for (int j=0;j<new_length;j++) {
    Sr90_zoom->SetBinContent(j+1,new_freq[j]);
  } 
  Sr90_zoom->Rebin(25);  // così dovrei avere 16 bins in cui ne ho accorpati 25
  Sr90_zoom->Draw("e1");
  cSr_zoom->Print("Sr90__zoom.png");
  
  

double energy_step=2*energy_half_step;

// rebinning
int bins=8;
double rebin_energy[bins];
double rebin_freq[bins];
double rebin_energy_err[bins];
double rebin_freq_err[bins];
double curie[bins];
double curie_err[bins];

for(int i=0;i<bins;i++){
	rebin_energy[i]=Sr90_zoom->GetBinCenter(i+1);
	rebin_freq[i]=Sr90_zoom->GetBinContent(i+1);
	rebin_freq_err[i]=Sr90_zoom->GetBinError(i+1);
	curie[i]= sqrt(rebin_freq[i])/rebin_energy[i];
	cout << "Bin number: " << i+1 << ":  Rebin central energy: " << rebin_energy[i] << ", Rebin content : " << rebin_freq[i] << ", Curie point: " << curie[i] << endl;
}

double rebin_width= rebin_energy[1]-rebin_energy[0];

for(int i=0;i<bins;i++){
	rebin_energy_err[i]=rebin_width*0.69;
	double term1= (rebin_freq_err[i])*(rebin_freq_err[i])/(4*rebin_freq[i]);
	double term2=(rebin_freq[i]*(rebin_energy_err[i])*(rebin_energy_err[i]))/((rebin_energy[i])*(rebin_energy[i]));
	curie_err[i]=(1/rebin_energy[i])*sqrt(   10*term1  *  10*term2   );
	term1=0;
	term2=0;
}


// implemento il grafico di sqrt(conteggi)/E in funzione di E.. speriamo bene


TCanvas* cEnd = new TCanvas("cEnd", "end_point_Y", 200, 10, 700, 400);
  cEnd->SetFillColor(0);
  cEnd->SetGrid();
  cEnd->cd();
  
  TGraphErrors* gEnd = new TGraphErrors(bins-2, rebin_energy, curie, rebin_energy_err, curie_err);
  gEnd->SetMarkerSize(0.6);
  gEnd->SetMarkerStyle(21);
  gEnd->SetTitle("End point 90Y con Curie");
  gEnd->GetYaxis()->SetTitle("sqrt(N)/Energy");
  gEnd->GetXaxis()->SetTitle("m(E0 - E)");
  
  TF1* Curief = new TF1("Curief", "pol1",rebin_energy[0] , rebin_energy[bins-1]);
  Curief->SetParameter(0, 500);
  Curief->SetParameter(1, 0); 
  //Curief->SetLineColor(6);
  gEnd->Fit(Curief, "R+");
  
  cout << "Fit del plot di Curie: " << endl;
  cout << "Chi^2:" << Curief->GetChisquare() << ", number of DoF: " << Curief->GetNDF() << " (Probability: " << Curief->GetProb() << ").\n" << endl;
  
  gEnd->Draw("AP");
  cEnd->Print("Spettro_energie_end_point_90Y.png"); 
 
  

  

}
