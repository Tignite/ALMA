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
		size_t getSize() {return size;}
		size_t getUsed() {return used;}
		size_t getDim() {return dimension;}

		//Removes the element with given index
		bool removeIndex(size_t index){
			if(index < used){
				for(size_t i = index; i < used - 1; i++){
					data[i] = data[i + 1];
				}
				data[used - 1] = -1;
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
public:
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
					/*
					 * Debug:
					 */
					cout << "Weg gefunden " << start << "->" << *ziel << "\tLaenge =" << maxLaenge << endl;
					/*
					 * Debug:
					 */
					return true;
				}
				else{
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
	}
	Graphen(){
		adjMatrix = read_matrix_file("circle.dat", &n, &m);
	}
	~Graphen(){
		delete_matrix(adjMatrix, n, m);
	}

	void print(){
		print_matrix(adjMatrix,n,m);
	}

	auto getDim(){
		auto dim = { n, m };
		return dim;
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
			return ret;
		}
		else return false;
	}

	bool kreisExist(){
		bool ref = hatKreise();
		if(ref == true) cout << "\nGraph hat Kreise" << endl;
		else cout << "\nGraph hat keine Kreise" << endl;
		return ref;
	}

}Graphen;


#endif /* GRAPHEN_H_ */
