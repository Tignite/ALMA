#include <iostream>		/* cin, cout */

using namespace std;

/*
 Bei diesem Spiel gibt es drei Stäbe A, B und C.
 Auf den Stab A werden n verschieden große Scheiben der
 Größe nach gestapelt. Ziel ist es, diese Scheiben der Größe nach
 auf den Stab C umzusortieren. Es dürfen nur kleinere Scheiben auf
 größere gelegt werden und  alle  Scheiben  müssen  stets  im  Spiel  bleiben.
 Dies  geht  natürlich  nicht,  ohne  den Stab B zu Hilfe zu nehmen.
 Definieren Sie eine rekursive Funktion
 	 bewege (Zahl n, Stab A, Stab B, Stab C)
 die n Scheiben von Stab A (über Stab B) nach Stab C gemäss obiger Regeln verschiebt.
 */
typedef struct Hanoi{
public:
	Hanoi(int n){
		if(n > 0) this->n = n;
		else this->n = 1;
		create();
		print();
		bewege();
	}
	~Hanoi(){
		delete[](A);
		delete[](B);
		delete[](C);
	}

	unsigned int n, *A, *B, *C;

	void bewege(){
		bewege(n, A, B, C);
	}

	void print(){
		cout<<"A\tB\tC"<<endl;
		for(unsigned int i = 0; i < n; i++){
			cout<<A[i]<<"\t"<<B[i]<<"\t"<<C[i]<<endl;
		}
		cout<<endl;
	}

private:
	void create(){
		A = new unsigned int[n];
		B = new unsigned int[n];
		C = new unsigned int[n];
		for(unsigned int i = 0; i < n; i++){
			A[i] = i+1;
			B[i] = 0;
			C[i] = 0;
		}
	}

	void bewege(unsigned int n, unsigned int* X, unsigned int* Y, unsigned int* Z){
		if(n == 1){
			unsigned int q = 0, z = this->n - 1;
			while(z >= 0 && Z[z] != 0) z--; //Zielhöhe bestimmen
			while(q < this->n && X[q] == 0) q++; //Quellhöhe bestimmen
			if(Z[z-1] == 0 || X[q] < Z[z-1]){
				Z[z] = X[q];
				X[q] = 0;
				cout<<"\nStep\n";
				print();
			}
			else{
				cout<<"\nError ~ Falsche Scheibengroesse\n";
			}
		}
		else{
			bewege(n-1, X, Z, Y);
			bewege(1, X, Y, Z);
			bewege(n-1, Y, X, Z);
		}
	}

}Hanoi;

int main(int argc, char** argv){

	Hanoi* T = new Hanoi(10);
	return 0;
}
