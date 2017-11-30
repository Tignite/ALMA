#include <iostream>		/* cin, cout */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 		/* time */
#include <string>		/* string */
#include <cstdlib>		/* RAND_MAX */

#include "Student.h"
#include "Datenbank.h"

using namespace std;


/*
 * Definieren Sie als erstes den struct Student. Die Matrikelnummer ist eine
 * sechs-stellige Zahl und das Geburtsdatum ein dreielementiges Array{Tag,Monat,Jahr}
 * aus Integern. Studienfach und Fachsemester ist jeweils durch eine Zahl zwischen
 * 1und 100 kodiert.
 */


int main(int argc, char** argv){
	srand(time(NULL));
	Datenbank* Test = new Datenbank(100000);
	//Test->print(0);
	Test->sort();
	//cout<<"\n\t~Sortiert - Matnr~\n";
	//Test->print(1);
	//cout<<"\n\t~Sortiert - Geb~\n";
	//Test->print(2);
	cout<<"done\n";
	delete Test;
	return 0;
}
