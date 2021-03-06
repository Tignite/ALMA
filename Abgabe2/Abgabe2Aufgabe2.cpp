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

int a2Main(int argc, char** argv){
	//int e = 30;
	//long long int n = pow(2,e);
	//cout<<harmonicAlt(e, n);
	//compare(e,n);
	cout<<mascheroni(24); //mascheroni(24) = 0.577215 harmonicAltLong(i,e)
	return 0;
}

long double harmonicAltLong(int e, long long int n){
	long double summe = 1.0;
	long double index = 2.0;
	if(n == 0 || n == 1) return 1;
	while(index<=n){
		for(long long int i = 0; i+1 <= n; i++){
			long long int blockSize = pow(2,i);
			long double partialSumme = 0.0;
			for(long long int k = 1; k <= blockSize; k++){
				if(index > n) break;
				partialSumme += 1.0/index;
				index++;
			}
			summe += partialSumme;
			//cout<<summe<<"\t"<<partialSumme<<endl;
		}
	}
	return summe;
}

void compare(int e, long long int n){
	cout<<"Vergleich:\nn\tNormal\t\tPartial\t\tLong\n\n";
	bool Standard = false, Alt = false, Harmonic = false;
	float standardBackup, altBackup, harmonicBackup;
	for(int i = 1; i <= 40; i++){
		n = pow(2,i);
		float standard, alt, harmonicLong;
		if(Standard == false) standard = harmonic(i,n);
		if(Alt == false) alt = harmonicAlt(e,n);;
		if(Harmonic == false) harmonicLong = harmonicAltLong(e,n);
		cout<<n<<"\t"<<standard<<"\t\t"<<alt<<"\t\t"<<harmonicLong<<endl;
		if(standardBackup != standard) standardBackup = standard;
		else Standard = true;
		if(altBackup != alt) altBackup = alt;
		else Alt = true;
		if(harmonicBackup != harmonicLong) harmonicBackup = harmonicLong;
		else Harmonic = true;
	}
}
