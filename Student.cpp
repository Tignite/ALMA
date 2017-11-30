#include <iostream>		/* cin, cout */
#include <stdlib.h>     /* srand, rand */
#include <string>		/* string */

#include "Student.h"

using namespace std;
	//long matnr, short geb[3], s studienfach, s fachsemester
Student::Student(){
		randMatnr();
		randGeb();
		studienfach = pseudoRand(99) + 1;
		fachsemester = pseudoRand(99) + 1;
	}
Student::Student(long matnr, short* geb, short studienfach, short fachsemester){
		this->matnr = matnr;
		this->geb[0] = geb[0];
		this->geb[1] = geb[1];
		this->geb[2] = geb[2];
		this->studienfach = studienfach;
		this->fachsemester = fachsemester;
	}
Student::~Student(){
	}
	void Student::print(){
		cout<<"\nMatrikelnummer = "<<matnr<<endl;
		cout<<"Geburtstag = "<<geb[0]<<"."<<geb[1]<<"."<<geb[2]<<endl;
		cout<<"Studienfach = "<<studienfach<<endl;
		cout<<"Fachsemester = "<<fachsemester<<endl;
	}
	bool Student::setMatnr(long matnr){
		if((matnr < 1000000) && (matnr >= 100000)) this->matnr = matnr;
		else return false;
		return true;
	}
	bool Student::setGeb(short* geb){
		//Zu grosse und zu kleine Werte abfangen
		if((geb[0] < 0) || (geb[1] < 0) || (geb[2] < 0) || (geb[1] > 12) || (geb[0] > 31)) return false;

		//Tag zu Monat Abgleich
		if(geb[0] > 28){
			if(geb[1] == 2){
				if(geb[0] > 29) return false;
				else if((geb[0] == 29) && (geb[1] == 2) && (schaltjahr(geb[2]) == false)) return false;
			}
			else{
				if(geb[0] == 31){
					if((geb[1] < 9) && (geb[1] % 2 == 1))return false;
					else if((geb[1] >= 9) && (geb[1] % 2 == 0))	return false;
				}
			}
		}
		this->geb[0] = geb[0];
		this->geb[1] = geb[1];
		this->geb[2] = geb[2];
		return true;
	}
	bool Student::setStudienfach(short studienfach){
		if((studienfach <= 100) && (studienfach >= 1)) this->studienfach = studienfach;
		else return false;
		return true;
	}
	bool Student::setFachsemester(short fachsemester){
		if((fachsemester <= 100) && (fachsemester >= 1)) this->fachsemester = fachsemester;
		else return false;
		return true;
	}
	long Student::getMatnr(){
		return matnr;
	}
	string Student::getGeb(){
		return (to_string(geb[0]) + "." + to_string(geb[1]) + "." + to_string(geb[2]));
	}
	short* Student::getGebShort(){
		return geb;
	}
	short Student::getStudienfach(){
		return studienfach;
	}
	short Student::getFachsemester(){
		return fachsemester;
	}
	void Student::randMatnr(){
		matnr = 0;
		for(int i = 0; i < 6; i++){
			//Erste Ziffer garantiert nicht 0
			if(i == 0) while (matnr == 0) matnr = ((double) rand() / (double) RAND_MAX) * 10;
			else matnr += ((double) rand() / (double) RAND_MAX) * 10;
			if(i != 5) matnr *= 10;
		}
	}

	//private
	int Student::pseudoRand(int limit){
		return ((double) rand() / (double) RAND_MAX) * limit;
	}
	bool Student::schaltjahr(short n){
		if((n % 4 == 0) && ((n % 100 != 0) || (n % 400 == 0))) return true;
		else return false;
	}
	void Student::randGeb(){
		geb[2] = pseudoRand(100) + 1900;
		geb[1] = pseudoRand(11) + 1;
		if(geb[1] == 2){
			if(schaltjahr(geb[2]) == true) geb[0] = pseudoRand(28) + 1;
			else geb[0] = pseudoRand(27) + 1;
		}
		else if((geb[1] < 9) && (geb[1] % 2 == 1)){
			geb[0] = pseudoRand(30) + 1;
		}
		else if((geb[1] >= 9) && (geb[1] % 2 == 0)){
			geb[0] = pseudoRand(30) + 1;
		}
		else geb[0] = pseudoRand(29) + 1;
	}
