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
	Datenbank* Test = new Datenbank(35);
	Test->print(0);
	Test->sort();
	cout<<"\n\t~Sortiert~\n";
	Test->print(1);
	delete Test;
	return 0;
}
