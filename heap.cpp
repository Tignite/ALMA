#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

template <class T>
class Heap {
public:
	Heap(){
		size = 0;
		array = NULL;
	}
	Heap(size_t size){
		this->size = size;
		array = new T[size];
		init();
	}
	~Heap(){
		if(size > 0) delete[](array);
	}

	void print(){
		if(size < 17){
			int depth = 0, index = 2;
			while (index <= size){
				index = index * 2;
				depth++;
			}
			for(int ebene = 0; ebene <= depth; ebene++){
				int start = pow(2, ebene-1);
				int end = 2*start + 1;
				for(int k = start; k < end; k++){
					for(int space = 0; space < depth - 1; space++){
						cout<<"\t";
					}
					cout<<array[k]<<" ";
				}
				cout<<endl;
			}
		}
	}

	size_t size;
	T* array;
private:
	void init(){
		for(int i = 0; i < size; i++){
			array[i] = i;
		}
	}

};

int main(int argc, char** argv){
	Heap<int>* intHeap = new Heap<int>(7);
	intHeap->print();
	return 0;
}
