#ifndef GRAPHEN_H_
#define GRAPHEN_H_

#include "input.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>




typedef struct Graphen{

	typedef struct Array{
	public:
		Array(){
			data = 0;
			size = 0;
			used = 0;
		}
		Array(size_t n){
			size = n;
			used = 0;
			data = new int[size];
		}
		~Array(){
			delete[] data;
			data = 0;
			size = 0;
			used = 0;
		}
		void print(){
			if(used > 0){
				cout << "{";
				for(size_t i = 0; i < used; i++){
					cout << data[i];
					if(i < used - 1) cout << ", ";
				}
				cout << "}";
			}
			else{
				cout << "Debug: Empty Array\n" << size << endl << used << endl;
			}
		}
		size_t search(int element){
			for(size_t i = 0; i < used; i++){
				if(data[i] == element) return i;
			}
			return -1;
		}
		//haengt das element an die erste freie stelle
		bool insert(int element){
			if(used < size){
				data[used] = element;
				used++;
				return true;
			}
			else return false;
		}
		//ersetzt das element an gegebener stelle
		bool set(int element, size_t index){
			if(index < size){
				data[index] = element;
				if(index < used) used++;
				return true;
			}
			else return false;
		}
		int get(size_t index){
			if(index < used) return data[index];
			else return 0;
		}
		int getSize() {return size;}
		int getUsed() {return used;}

		//ersetzt sukzessiv durch den folgenden wert
		bool removeIndex(size_t index){
			if(index < used){
				if(index >= 0){
					for(size_t i = index; i < used - 1; i++){
						data[i] = data[i + 1];
					}
					data[used - 1] = -1;
				}
				else{
					data[0] = -1;
				}
				used--;
				return true;
			}
			return false;
		}

		//element entfernen wenn gefunden
		bool removeElement(int element){
			for(size_t i = 0; i < used; i++){
				if(data[i] == element){
					return removeIndex(i);
				}
			}
			return false;
		}

		//leert das array, falls nicht bereits leer
		void clear(){
			while(used > 0){
				removeIndex(used -1);
			}
		}

	private:
		size_t size;
		size_t used;
		int *data;
	}Array;
	//Array Ende

private:
	int **adjMatrix;
	int n, m;
	bool gerichtet;

private:
	//grad eines knotens bestimmen
	int getGrad(int start){
		int grad = 0;
		for(int i = 0; i < n; i++){
			if(adjMatrix[start][i] == 1) grad++;
		}
		return grad;
	}

	//alle nachbarn bestimmen, die noch nicht besucht wurden
	Array* findNachbarn(int start, int *grad, Array *Besucht){
		Array *Nachbarn = new Array(*grad);
		for(int i = 0; i < n; i++){
			if(adjMatrix[start][i] == 1){
				if(Besucht->search(i) == -1){
					Nachbarn->insert(i);
				}
				else{
					//falls der nachbar bereits besucht wurde
					*grad = (*grad) - 1;
				}
			}
			//falls jetzt keine nachbarn mehr da sind
			if(*grad == 0){
				delete Nachbarn;
				return nullptr;
			}
		}
		return Nachbarn;
	}

	//finde einen weg vom start zum ziel rekursiv
	//mode ist zum unterscheiden ob nach normalen wegen (0),
	//oder nach kreisen (1) gesucht wird
	bool weg(int maxLaenge, int start, int *ziel, Array *Besucht, bool mode){
		//Kreis? Ja -> ziel ist in besucht, mache weiter und andere mode
		//ansonsten bilden 2 benachbarte knoten einen kreis
		if(mode == true) {
			mode = false;
		}
		//kein kreis, dann bewirkt das remove nichts,
		//ansonsten wird das ziel entfernt, damit es erreicht werden kann
		else{
			Besucht->removeElement(*ziel);
		}
		//angekommen? dann return
		if(start == *ziel) return true;
		int grad = getGrad(start);
		//maximal laenge erreicht?
		if(maxLaenge == 0) return false;
		//alles nicht der fall, dann finde die nachbarn
		Array *Nachbarn = findNachbarn(start, &grad, Besucht);
		//damit nicht versehentlich knoten doppelt eingetragen werden
		if(Besucht->search(start) == -1) Besucht->insert(start);
		//Isolierter Knoten oder Nachbarn schon besucht?
		if(Nachbarn != nullptr){
			for(int i = 0; i < grad; i++){
				//Laufe alle Nachbarn ab
				if(weg(maxLaenge - 1, Nachbarn->get(i), ziel, Besucht, mode) == true ){
					delete Nachbarn;
					return true;
				}
				else if (i == grad - 1){
					//alle nachbarn probiert, kein weg gefunden
					if(findNachbarn(start, &grad, Besucht) != nullptr){
						//falls alle wege sackgassen waren werden keine nachbarn gefunden
						//wenn der weg nur zu lang wurde werden nachbarn gefunden und
						//das element start wird aus der Besucht Liste entfernt
						Besucht->removeElement(start);
					}
				}
			}
			delete Nachbarn;
		}
		return false;
	}
	bool hatKreise(){
		Array *Besucht = new Array(n);
		for(int i = 0; i < n; i++){
			int grad = getGrad(i);
			if (grad > 1){
				int ziel = i;
				Besucht->insert(i);
				//Nachbarn vom Start bestimmen
				Array *FirstNachbarn = findNachbarn(i, &grad, Besucht);
				if(FirstNachbarn != nullptr){
					for(int k = 0; k < grad; k++){
						//Suche einen weg vom Nachbarn zum start, ohne direkt zurueck zu gehen
						if(weg(n, FirstNachbarn->get(k), &ziel, Besucht, 1) == true){
							delete Besucht;
							delete FirstNachbarn;
							return true;
						}
					}
					delete FirstNachbarn;
				}
				Besucht->insert(i);
			}
		}
		delete Besucht;
		return false;
	}
	//pruefe auf symmetrie und setze member
	void checkGerichtet(){
		gerichtet = false;
		for(int i = 0; i < n; i++){
			for(int j = i; j < n; j++){
				if(adjMatrix[i][j] != adjMatrix[j][i]){
					gerichtet = true;
					break;
				}
			}
		}
	}

	//bestimme rekursiv den zusammenhang
	bool gesamtZusammenhang(int start, Array *Besucht){
		Besucht->insert(start);
		if(Besucht->getUsed() == n){
			//letzter knoten gefunden
			return true;
		}
		int grad = getGrad(start);
		if(grad > 0) {
			//bestimme die nachbarn und iteriere ueber den grad
			Array *Nachbarn = findNachbarn(start, &grad, Besucht);
			while(grad > 0){
				//sobald der letzte knoten gefunden wird reiche true durch
				if(gesamtZusammenhang(Nachbarn->get(grad - 1), Besucht) == true){
					delete Nachbarn;
					return true;
				}
				//ansonsten gehe den naechsten nachbarn ab
				else{
					grad--;
				}
			}
			//sackgasse
			delete Nachbarn;
			return false;
		}
		else return false;
	}
//Interfaces
public:
	Graphen(string dateiName){
		adjMatrix = read_matrix_file(dateiName, &n, &m);
		if(n != m){
			//nicht symmetrisch -> keine adjMatrix
			delete_matrix(adjMatrix, n, m);
			adjMatrix = NULL;
			n = 0;
			m = 0;
			cout << "Matrix fehlerhaft, nicht symmetrisch\n";
		}
		checkGerichtet();
	}
	Graphen(){
		adjMatrix = read_matrix_file("circle.dat", &n, &m);
		checkGerichtet();
	}
	~Graphen(){
		delete_matrix(adjMatrix, n, m);
	}

	void print(){
		if(gerichtet == true) cout << "\nGerichteter Graph:\n";
		else cout << "\nUngerichteter Graph:\n";
		print_matrix(adjMatrix,n,m);
	}

	bool getGerichtet(){
		if(gerichtet == true) return true;
		return false;
	}

	bool wegExist(int maxLaenge, int start, int ziel){
		//triviales ausschliessen
		if( (start >= 0) && (start < n) &&
				(ziel >= 0) && (ziel < n) ){
			//alle bereits besuchten knoten speichern
			Array *Besucht = new Array(n);
			//benutze rekursive methode
			bool ret = weg(maxLaenge, start, &ziel, Besucht, 0);
			delete Besucht;
			if(ret == true){
				cout << "Weg gefunden " << start << "->" << ziel << "\tMaxLaenge =" << maxLaenge << endl;
			}
			else{
				cout << "Kein Weg gefunden " << start << "->" << ziel << "\tMaxLaenge =" << maxLaenge << endl;
			}

			return ret;
		}
		else return false;
	}

	bool kreisExist(){
		bool ret = hatKreise();
		if(ret == true) cout << "\nGraph hat Kreise" << endl;
		else cout << "\nGraph hat keine Kreise" << endl;
		return ret;
	}

	bool zusammenhang(){
		Array *Besucht = new Array(n);
		bool ret = false;
		for(int start = 0; start < n; start++){
			ret = gesamtZusammenhang(start, Besucht);
			Besucht->clear();
			if(ret == true) break;
			//ungerichtet -> muss bei 0 bereits true/false sein
			if(gerichtet == false) break;
		}
		//starker oder schwacher zusammenhang?
		if(ret == true){
			//ungerichtet und zusammenhaengend immer stark
			if(gerichtet == false){
				cout << "\nGraph ist stark zusammenhaengend" << endl;
			}
			else{
				for(int i = 0; i < n; i++){
					for(int j = i; j < n; j++){
						bool wegA = wegExist(n, i, j);
						bool wegB = wegExist(n, j, i);
						if(wegA != wegB){
							//erste nicht starke komponente
							delete Besucht;
							cout << "\nGraph ist nicht stark zusammenhaengend" << endl;
							return ret;
						}
					}
				}
				cout << "\nGraph ist stark zusammenhaengend" << endl;
			}

		}
		else cout << "\nGraph ist nicht zusammenhaengend" << endl;
		return ret;
	}

}Graphen;

#endif /* GRAPHEN_H_ */
