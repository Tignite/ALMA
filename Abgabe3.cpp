#include <math.h>		/* pow, sqrt */
#include <iostream>		/* cin, cout */
#include <new>			/* new */
#include <string>		/* string */
#include <stdlib.h>     	/* srand, rand */
#include <time.h>       	/* time */

using namespace std;

/*
a. das komponentenweise Maximum VDMAX(z,x,y,n)
zi = max{xi
, yi} fur i = 1, . . . , n,
*/

void VDMAX(double* res, double* x, double* y, int n){
	for(int i = 0; i < n; i++){
		if( x[i] >= y[i] ) res[i] =x[i];
		else res[i] = y[i];
	}
}

/*
b. die komponentenweisen Addition PLUS(z,x,y,n)
zi = xi + yi fur i = 1, . . . , n,
*/

void PLUS(double* res, double* x, double* y, int n){
	for(int i = 0; i < n; i++){
		res[i] = x[i] + y[i];
	}
}

/*
c. die komponentenweise Multiplikation MULTVEKTOR(z,x,y,n)
zi = xi
· yi fur i = 1, . . . , n,
*/

void MULTVEKTOR(double* res, double* x, double* y, int n){
	for(int i = 0; i < n; i++){
		res[i] = x[i] * y[i];
	}
}

/*
d. die Multiplikation MULTZAHL(z,x,α,n) des Vektors x mit der Zahl α
zi = αxi fur i = 1, . . . , n,
*/

void MULTZAHL(double* res, double* x, double a, int n){
	for(int i = 0; i < n; i++){
		res[i] = x[i] * a;
	}
}

/*
e. das euklidischen Skalarprodukt SCALPR(β,x,y,n) mit dem Ergebnis β ∈ R
β =
Sum(i=1,n)
xiyi
*/

void SCALPR(double* res, double* x, double* y, int n){
	res[0] = 0.0;
	for(int i = 0; i < n; i++){
		res[0] += x[i] * y[i];
	}
}

/*
f. die komponentenweise Division DIVVEKTOR(z,x,y,n)
zi =
(
xi/yi
, falls yi 6= 0,
0,       falls yi = 0,      fur i = 1, . . . , n,
*/

void DIVVEKTOR(double* res, double* x, double* y, int n){
	for(int i = 0; i < n; i++){
		if ( y[i] != 0 ) res[i] = x[i] / y[i];
		else res[i] = 0;
	}
}

/*
g. die euklidische Norm (Lange) eines Vektors NORM(l,x,n)
l =
( Sum(i=1,n) |xi|^2 )^1/2
*/

void NORM(double* res, double* x, int n){
	res[0] = 0.0;
	for(int i = 0; i < n; i++){
		res[0] += pow(x[i], 2);
	}
	res[0] = sqrt(res[0]);
}

/*
Testen Sie ihre Funktionen anschließend, indem Sie ein C/C++-Programm schrei-
ben, dass zun¨achst eine L¨ange n (Dimension) einliest. Anschließend werden Zufalls-
vektoren aus [0, 1]^n
erzeugt und eine Zahl α ∈ (0, 1) eingelesen und die Operatio-
nen a)-g) durchfuhrt. Bennutzen Sie die Funktionen ¨ rand() und srand() aus der C-
Standardbibliothek.
*/

void eingabeInt(int* n){
	cout<<"Bitte Ganzzahl fuer die Laenge eingeben:\n";
	cin>>*n;
	if(*n < 0) eingabeInt(n);
}

void eingabeDouble(double* a){
	cout<<"Bitte Kommazahl als Skalar eingeben (0 < a < 1):\n";
	cin>>*a;
	if (*a >= 1 || *a <= 0) eingabeDouble(a);
}

void initRand(double* x, int n){
	for(int i = 0; i < n; i++){
		x[i] = (((double) rand()) / ((double) RAND_MAX));
	}
}

void createArray(double* &x, int n){
	if (n > 0){
		x = new double[n];
		initRand(x, n);
	}
}

void copyArray(double* &res, double* x, int n){
	createArray(res, n);
	for(int i = 0; i < n; i++){
		res[i] = x[i];
	}
}

void printArray(double* x, int n){
	if (x != NULL){
	cout<<"(\n";
	for(int i = 0; i < n; i++){
		if(i+1 == n) cout<<", "<<x[i];
		else if ((i % 5) == 0) cout<<x[i];
		else if ( ((i+1) % 5) == 0 ){
			cout<<", "<<x[i]<<"\n";
		}
		else {
			cout<<", "<<x[i];
		}
	}
	cout<<"\n)\n";
	}
	else cout<<"\nError: pointer = NULL\n";
}

void routine(double* res, double* x, double* y, int n, double a){
	//Arrays fuer die Ausgabe
	double* results[7];
	string names[7] = {"VDMAX", "PLUS", "MULTVEKTOR", "MULTZAHL", "DIVVEKTOR", "SCALPR",
			"NORM"};

	//Arrays erstellen
	createArray(x, n);
	createArray(y, n);
	createArray(res, n);

	//Berechnen und im Array speichern
	VDMAX(res, x, y, n);
	copyArray(results[0], res, n);
	PLUS(res, x, y, n);
	copyArray(results[1], res, n);
	MULTVEKTOR(res, x, y, n);
	copyArray(results[2], res, n);
	MULTZAHL(res, x, a, n);
	copyArray(results[3], res, n);
	DIVVEKTOR(res, x, y, n);
	copyArray(results[4], res, n);
	SCALPR(res, x, y, n);
	copyArray(results[5], res, n);
	NORM(res, x, n);
	copyArray(results[6], res, 1);

	//Ausgabe Ergebnisse
	printArray(x, n);
	printArray(y, n);
	for(int i = 0; i < 7; i++){
		cout<<names[i]<<endl;
		if(i > 4) printArray(results[i], 1);
		else printArray(results[i], n);
	}

	//Loeschen
	delete[] x;
	delete[] y;
	for(int i = 0; i < 7; i++){
		delete[] results[i];
	}
	delete results;
}

/*
Lesen Sie außerdem eine Zahl “Anzahl der Versuche” ein und starten Sie folgendes
(Zufalls-)Experiment. Bestimmen Sie die relative H¨aufigkeit, dass m unabh¨angig gezo-
gene Zufallsvektoren aus [0, 1]n
eine Lange (Norm) kleiner oder gleich 1 haben? Was
beobachten Sie mit wachsender Dimension n?
*/

long long int bin(unsigned int n, unsigned int k){
	long long int res = 1;
	if(k == 0 || k == n) return 1;
	else if( n >= k){
		for(long long int  i = 1; i <= k; i++){
			res *= ((n) + 1 - i) / i;
		}
	}
	else return 0;
	return res;
}

void newArray(double** x, unsigned int v, unsigned int n){
	for(unsigned int i = 0; i < v; i++){
		double* ptr = x[i];
		createArray(ptr,n);
		x[i] = ptr;
	}
}
void experiment(double** vektorArray, unsigned int dim){
	unsigned int v = 200, n = dim;
	//eingabeInt(&n);
	cout<<"Dimension n = "<<n<<"\nAnzahl Versuche v = "<<v<<endl;
	//Erstellen der Vektoren

	vektorArray = new double*[v];
	newArray(vektorArray, v, n);

	//Berechnen der Norm

	double res[] = {0.0};
	int counter = 0;
	for(unsigned int i = 0; i < v; i++){
		NORM(res, vektorArray[i], n);
		//Anzahl Vorkommen
		if( res[0] <= 1.0 ) counter++;
	}



	/*
	//Auswertung
	 * Für m unabhängige Zufallsvektoren aus [0, 1]^n gilt:
	 * P = (n über m) * p^m * (1 - p)^(n-m)
	 * mit p = Vorkommen / Gesamtanzahl
	 * Anzahl Vorkommen = counter
	 * Gesamtanzahl = v
	 */
	double p = ((double) counter) / ((double) v);
	/*
	 * Binomialverteilung
	 * wegen Binomialkoeffizient ziemlich schnell ein Overflow
	double* array = NULL;
	createArray(array, v);
	for(unsigned int i = 1; i <= v; i++ ){
		long long int binom = bin(v,i);
		long double pPowM = pow(p, (long double) i);
		long double onePowNM = pow((1-p), (v-i));
		array[i-1] = binom * pPowM * onePowNM;
	}
	long double sum = 0.0;
	for(unsigned int i = 0; i < v; i++){
		sum += array[i];
	}
	sum = sum/(double)v;
	*/
	cout<<"Relative Haufigkeit = "<<p<<endl;
	//Loeschen
	for(unsigned int i = 0; i < v; i++){
		double* ptr = vektorArray[i];
		delete[] ptr;
	}
}
int main(int argc, char** argv){
	srand (time(NULL));
	double** vektorArray = NULL;
	int n = 2000;
	double a = 1.0;
	double* x = NULL;
	double* y = NULL;
	double* res = NULL;
	//eingabeInt(&n);
	cout<<"Laenge n = "<<n<<endl;
	//eingabeDouble(&a);
	cout<<"Skalar a = "<<a<<endl;
	
	//routine(res, x, y, n, a);
	for(int i = 1; i < 15; i++){
		experiment(vektorArray, i);
	}
	delete vektorArray;
	return 0;
}
