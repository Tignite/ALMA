#include <iostream>
#include <math.h>

using namespace std;

double vorwaertsRekursion(double startWert, double i){
	return 1.0 - startWert;
}

double rueckwaertsRekursion(double startWert, double i){
	return ( (1.0) / (i + 1.0) ) * (1.0 - startWert);
}

void schleife(double i, double k, double startWertVorwaerts, double startWertRueckwaerts, double startWertRueckwaersSchlecht){
	double vorne = vorwaertsRekursion(startWertVorwaerts, 0);
	double rueck = rueckwaertsRekursion(startWertRueckwaerts, 20-0);
	double schlecht = rueckwaertsRekursion(startWertRueckwaersSchlecht, 20-0);
	for(int j = 0; j <= 20; j++){
		if(j != 0){
			vorne = vorwaertsRekursion(vorne, 0);
			rueck = rueckwaertsRekursion(rueck, 20-0);
			schlecht = rueckwaertsRekursion(schlecht, 20-0);
		}
		cout<<vorne<<"\t"<<rueck<<"\t"<<schlecht<<endl;
	}
}

int main(int* argc, int** argv){
	double i = 0.0;
	double k = 20.0;
	double expo = exp(1);
	double startWertVorwaerts = (expo - 1.0) / (expo);
	double startWertRueckwaerts = (0.5)*(( (1.0) / ( expo * (k + 1) ) + (1.0/(k + 1.0))));
	double startWertRueckwaersSchlecht = pow(10,6);
	schleife(i, k, startWertVorwaerts, startWertRueckwaerts, startWertRueckwaersSchlecht);
	return 0;
}
