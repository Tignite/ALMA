#include "Datenbank.h"
#include <time.h> 		/* time */

#include "Student.h"
class Student;

using namespace std;

Datenbank::Datenbank(){
			n = 10000;
			create();
			matnrRegister = new long[n];
		}
Datenbank::Datenbank(int n){
			this->n = n;
			create();
			matnrRegister = new long[n];
		}
Datenbank::~Datenbank(){
			for(int i=n-1; i >= 0; i--){
			    delete array[i];
			}
			delete array;
			delete[] matnrRegister;
			delete[] aufsteigendBuffer;
			delete[] aufsteigendMatnr;
			delete[] aufsteigendGeb;
		}
		void Datenbank::print(int m){
			int index;
			for(int i = 0; i < n; i++){
				if(m == 0){
					index = i;
					array[index]->print();
				}
				else if(m == 1){
					index = aufsteigendMatnr[i];
					cout<<"\t"<<array[index]->getMatnr()<<endl;
				}
				else if(m == 2){
					index = aufsteigendGeb[i];
					cout<<"\t"<<array[index]->getGeb()<<endl;
				}
			}
		}
		void Datenbank::sort(){
			clock_t start, end;
			double elapsed_secs;
			start = clock();
			sortMatnr(0,n);
			end = clock();
			elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
			cout<<"Sortiere "<<n<<" Studenten in "<<elapsed_secs<<endl;
			start = clock();
			sortGeb(0,n);
			end = clock();
			elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
			cout<<"Sortiere "<<n<<" Studenten in "<<elapsed_secs<<endl;
		}
		//private
		void Datenbank::create(){
			array = new Student*[n]();
			matnrRegister = new long[n];
			aufsteigendBuffer = new int[n];
			aufsteigendMatnr = new int[n];
			aufsteigendGeb = new int[n];
			for(int i = 0; i < n; i++){
				matnrRegister[i] = 0;
				array[i] = new Student();
				while(reg(array[i]->getMatnr()) == true) array[i]->randMatnr();
				matnrRegister[i] = array[i]->getMatnr();
				aufsteigendBuffer[i] = i;
				aufsteigendMatnr[i] = i;
				aufsteigendGeb[i] = i;
			}
		}
		//matrikelnummer registrieren -> eindeutigkeit
		bool Datenbank::reg(long matnr){
			for(int i = 0; i < n; i++){
				if(matnrRegister[i] == 0){
					matnrRegister[i] = matnr;
					return true;
				}
				else if(matnrRegister[i] == matnr) return false;
			}
			//Durchlauf falls voll
			return false;
		}
		void Datenbank::sortMatnr(int s, int n){
			long matnrA = 0, matnrB = 0;
			int s1, s2, n1, n2, counter;
			s1 = s;
			counter = s;
			if(n%2 == 0){
				s2 = s + n/2;
				n1 = n/2;
				n2 = n/2;
			}
			else{
				s2 = s + 1 + n/2;
				n1 = n/2 + 1;
				n2 = n/2;
			}
			if(n == 1){
				aufsteigendMatnr[s] = aufsteigendBuffer[s];
			}
			else if(n == 2){
				matnrA = array[aufsteigendBuffer[s]]->getMatnr();
				matnrB = array[aufsteigendBuffer[s+1]]->getMatnr();
				if(matnrA > matnrB){
					aufsteigendMatnr[s] = aufsteigendBuffer[s+1];
					aufsteigendMatnr[s+1] = aufsteigendBuffer[s];
				}
				else{
					aufsteigendMatnr[s] = aufsteigendBuffer[s];
					aufsteigendMatnr[s+1] = aufsteigendBuffer[s+1];
				}

			}
			else{
				sortMatnr(s1, n1);
				sortMatnr(s2, n2);
				int a = s1, b = s2;
				while(counter < (s + n)){
					matnrA = array[aufsteigendBuffer[a]]->getMatnr();
					matnrB = array[aufsteigendBuffer[b]]->getMatnr();
					if(matnrA > matnrB){
						aufsteigendMatnr[counter] = aufsteigendBuffer[b];
						if(b < (s2 + n2 - 1)){
							b++;
						}
						else{
							counter++;
							while(counter < (s + n)){
								aufsteigendMatnr[counter] = aufsteigendBuffer[a];
								counter++;
								a++;
							}
						}
					}
					else{
						aufsteigendMatnr[counter] = aufsteigendBuffer[a];
						if(a < (s1 + n1 - 1)){
							a++;
						}
						else{
							counter++;
							while(counter < (s + n)){
								aufsteigendMatnr[counter] = aufsteigendBuffer[b];
								counter++;
								b++;
							}
						}
					}
					counter++;
				}
			}

			//Array Updaten
			for(counter = s;counter < s + n; counter++){
				aufsteigendBuffer[counter] = aufsteigendMatnr[counter];
			}

		}
		void Datenbank::sortGeb(int s, int n){
			long gebA = 0, gebB = 0;
			int s1, s2, n1, n2, counter;
			s1 = s;
			counter = s;
			if(n%2 == 0){
				s2 = s + n/2;
				n1 = n/2;
				n2 = n/2;
			}
			else{
				s2 = s + 1 + n/2;
				n1 = n/2 + 1;
				n2 = n/2;
			}
			if(n == 1){
				aufsteigendGeb[s] = aufsteigendBuffer[s];
			}
			else if(n == 2){
				gebA = array[aufsteigendBuffer[s]]->getGebLong();
				gebB = array[aufsteigendBuffer[s+1]]->getGebLong();
				if(gebA < gebB){
					aufsteigendGeb[s] = aufsteigendBuffer[s+1];
					aufsteigendGeb[s+1] = aufsteigendBuffer[s];
				}
				else{
					aufsteigendGeb[s] = aufsteigendBuffer[s];
					aufsteigendGeb[s+1] = aufsteigendBuffer[s+1];
				}

			}
			else{
				sortGeb(s1, n1);
				sortGeb(s2, n2);
				int a = s1, b = s2;
				while(counter < (s + n)){
					gebA = array[aufsteigendBuffer[a]]->getGebLong();
					gebB = array[aufsteigendBuffer[b]]->getGebLong();
					if(gebA < gebB){
						aufsteigendGeb[counter] = aufsteigendBuffer[b];
						if(b < (s2 + n2 - 1)){
							b++;
						}
						else{
							counter++;
							while(counter < (s + n)){
								aufsteigendGeb[counter] = aufsteigendBuffer[a];
								counter++;
								a++;
							}
						}
					}
					else{
						aufsteigendGeb[counter] = aufsteigendBuffer[a];
						if(a < (s1 + n1 - 1)){
							a++;
						}
						else{
							counter++;
							while(counter < (s + n)){
								aufsteigendGeb[counter] = aufsteigendBuffer[b];
								counter++;
								b++;
							}
						}
					}
					counter++;
				}
			}

			//Array Updaten
			for(counter = s;counter < s + n; counter++){
				aufsteigendBuffer[counter] = aufsteigendGeb[counter];
			}

		}
