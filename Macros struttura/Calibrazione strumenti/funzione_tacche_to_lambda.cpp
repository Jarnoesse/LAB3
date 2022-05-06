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
