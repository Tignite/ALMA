#include <iostream>
#include <math.h>
using namespace std;

#include "Abgabe2Aufgabe2.h"

float harmonic(int e, long long int n){
	float summe = 1;
	if(n == 1) return 1;
	for(int i = 2; i <= n; i++){
		summe += 1.0/((float)i);
	}
	return summe;
}

float harmonicAlt(int e, long long int n){
	if(n == 0 || n == 1) return 1;
	float summe = 1;
	float index = 2;
	for(int i = 0; i+1 < n; i++){
		int blockSize = pow(2,i);
		float partialSumme = 0;
		for(int k = 1; k <= blockSize; k++){
			partialSumme += 1.0/index;
			index++;
			if(index > n) break;
		}
		summe += partialSumme;
	}
	return summe;
}
/*
  	Euler-Mascheronischeschen Konstante
	lim (sn − ln(n))
	n→∞
*/
float mascheroni(int i){
	long long int e = pow(2,i);
	float mascheroni = harmonicAlt(i,e);
	mascheroni -= log(e);
	return mascheroni;
}

int main(int argc, char** argv){
	//int e = 30;
	//long long int n = pow(2,e);
	//cout<<harmonic(e, n);
	//cout<<harmonicAlt(e, n);
	cout<<mascheroni(24); //mascheroni(24) = 0.577215 harmonicAltLong(i,e)
	return 0;
}
