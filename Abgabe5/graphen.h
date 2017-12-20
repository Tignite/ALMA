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
			dimension = 0;
		}
		Array(size_t n){
			size = n;
			used = 0;
			data = new int[size];
			dimension = sqrt(size);
		}
		~Array(){
			delete[] data;
			data = 0;
			size = 0;
			used = 0;
			dimension = 0;
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
		int search(int element){
			for(size_t i = 0; i < used; i++){
				if(data[i] == element) return i;
			}
			return -1;
		}
		bool insert(int element){
			if(used < size){
				data[used] = element;
				used++;
				return true;
			}
			else return false;
		}
		bool set(int element, size_t index){
			if(index < size){
				data[index] = element;
				if(index < used) used++;
				return true;
			}
			else return false;
		}
		bool set(int element, size_t i, size_t j){
			return set(element, i*dimension + j);
		}
		int get(size_t index){
			if(index < used) return data[index];
			else return 0;
		}
		int get(size_t i, size_t j){
			return get(i*dimension + j);
		}
		int getSize() {return size;}
		int getUsed() {return used;}
		int getDim() {return dimension;}

		//Removes the element with given index
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
		bool removeIndex(size_t i, size_t j){
			return removeIndex(i*dimension + j);
		}

		//Removes the given element if found
		bool removeElement(int element){
			for(size_t i = 0; i < used; i++){
				if(data[i] == element){
					return removeIndex(i);
				}
			}
			return false;
		}

		void clear(){
			while(used > 0){
				removeIndex(used -1);
			}
		}

	private:
		size_t size;
		size_t used;
		size_t dimension;
		int *data;
	}Array;
	//Array Ende

private:
	int **adjMatrix;
	int n, m;
	bool gerichtet;

private:
	int getGrad(int start){
		int grad = 0;
		for(int i = 0; i < n; i++){
			if(adjMatrix[start][i] == 1) grad++;
		}
		return grad;
	}
	Array* findNachbarn(int start, int *grad, Array *Besucht){
		Array *Nachbarn = new Array(*grad);
		for(int i = 0; i < n; i++){
			if(adjMatrix[start][i] == 1){
				if(Besucht->search(i) == -1){
					Nachbarn->insert(i);
				}
				else{
					*grad = (*grad) - 1;
				}
			}
			if(*grad == 0){
				delete Nachbarn;
				return nullptr;
			}
		}
		return Nachbarn;
	}

	bool weg(int maxLaenge, int start, int *ziel, Array *Besucht, bool mode){
		if(mode == false) Besucht->removeElement(*ziel);
		else{
			mode = false;
		}
		int grad = getGrad(start);
		if(start == *ziel) return true;
		if( (grad == 0) || (maxLaenge == 0) ) return false;
		Array *Nachbarn = findNachbarn(start, &grad, Besucht);
		if(Besucht->search(start) == -1) Besucht->insert(start);
		if(Nachbarn != nullptr){
			for(int i = 0; i < grad; i++){
				if(weg(maxLaenge - 1, Nachbarn->get(i), ziel, Besucht, mode) == true ){
					return true;
				}
				else if (i == grad - 1){
					if(findNachbarn(start, &grad, Besucht) != nullptr){
						Besucht->removeElement(start);
					}
				}
			}
		}
		return false;
	}
	bool hatKreise(){
		Array *Besucht = new Array(n*n);
		for(int i = 0; i < n; i++){
			int grad = getGrad(i);
			if (grad > 1){
				int ziel = i;
				Besucht->insert(i);
				Array *FirstNachbarn = findNachbarn(i, &grad, Besucht);
				if(FirstNachbarn != nullptr){
					for(int k = 0; k < grad; k++){
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
	bool gesamtZusammenhang(int start, Array *Besucht){
		Besucht->insert(start);
		if(Besucht->getUsed() == n){
			return true;
		}
		int grad = getGrad(start);
		if(grad > 0) {
			Array *Nachbarn = findNachbarn(start, &grad, Besucht);
			while(grad > 0){
				if(gesamtZusammenhang(Nachbarn->get(grad - 1), Besucht) == true){
					delete Nachbarn;
					return true;
				}
				else{
					grad--;
				}
			}
			delete Nachbarn;
			return false;
		}
		else return false;
	}

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
			//gehe rekursiv vor
			Array *Besucht = new Array(n);// = new Array<int>(n);
			Array *Fertig = new Array(n);// = new Array<int>(n);
			bool ret = weg(maxLaenge, start, &ziel, Besucht, 0);
			delete Besucht;
			delete Fertig;
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
		}
		if(ret == true){
			if(gerichtet == false){
				cout << "\nGraph ist stark zusammenhaengend" << endl;
			}
			else{
				for(int i = 0; i < n; i++){
					for(int j = i; j < n; j++){
						bool wegA = wegExist(n, i, j);
						bool wegB = wegExist(n, j, i);
						if(wegA != wegB){
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
