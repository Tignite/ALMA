#include  <iostream>
#include  <limits.h>

using namespace std;
/*
 * 	Programmieraufgabe 1.
	(Fibonacci)
a.  Implementieren Sie eine rekursive C/C++ Funktion, die fuer ein Argument
	n die n-te Fibonaccizahl ausgibt.
*/
long long int fibonacciRek(int n){
	if(n == 1 || n == 2) return 1;
	else return fibonacciRek(n-1) + fibonacciRek(n-2);
}

void fibonacciRekursiv(int n){
	cout<<fibonacciRek(n);
}

/*
b.  Implementieren Sie eine Funktion, die fur ein Argument n die ersten
	n Fibonaccizahlen in einem array speichert und anschließend ausgibt.
	Dafur soll das array als  Parameter ubergeben  werden.
	Implementieren  Sie  zwei  Varianten.  Die  eine Implementierung soll
	Teilaufgabe a) benutzen und die andere moglichst effizient vorgehen.
*/

void fibonacciA(int n, long long int *array){
	cout<<"\nFibonacci - Teilaufgabe a\n";
	for(int i = 1; i <= n; i++){
		array[i-1] = fibonacciRek(i);
	}
	for(int i = 1; i <= n; i++){
		cout<<array[i-1]<<"\t";
		if(i % 5 == 0) cout<<endl;
	}
	cout<<endl;
}

void fibonacciB(int n, long long int *array){
	cout<<"\nFibonacci - effizient\n";
	if(n <= 0) return;
	else if(n == 1) array[0] = 1;
	else {
		array[0] = array[1] = 1;
		for(int i = 2; i < n; i++){
			array[i] = array[i-1] + array[i-2];
		}
	}
	for(int i = 1; i <= n; i++){
		cout<<array[i-1]<<"\t";
		if(i % 5 == 0) cout<<endl;
	}
	cout<<endl;
}

void fibonacci(int n, long long int *array){
	fibonacciB(n, array);
	fibonacciA(n, array);
}

/*
	Programmieraufgabe 2.
	(Addition mit Listen)
	Gegeben sei folgendes Beispielprogramm:

	#include  <limits.h>
	#include  <iostream >

	using  namespace  std;

	int  main(){
		unsigned  int i = UINT_MAX;
		unsigned  int j = UINT_MAX;
		cout  << i+j;
	}



	Kompilieren Sie dieses Programm und schauen Sie sich die Ausgabe an.
	Was bemerken Sie? In  manchen  Fallen  wollen  Sie  auch  ganze
	Zahlen,  die uber  die  maximalen  Werte  der Standarddatentypen
	gehen, verwenden. Hierfur eignen sich dynamische Datenstrukturen,
	wie  einfach  verkettete  Listen.  In  diesen  Listen  konnen
	sehr  große  Ganzzahlen  in folgender Form gespeichert werden:

	127(b10) = 1·10^2 + 2·10^1 + 7·10^0   ⇒  Liste  7 → 2 → 1

	Mit dieser Darstellung der Ganzzahl konnen nun beliebig große
	Zahlen addiert werden:

		7 → 2 → 1
	+ 	7 → 0 → 0

	Nun kann man, wie gewohnt aus Grundschulzeiten, von hinten die Zahlen
	in der Liste addieren und den Ubertrag zur nachsten Stelle weiter reichen.

	Erste Stelle: 	7 + 7 = 14		Ubertrag: 1
	Zweite Stelle: 	2 + 0 + 1 = 3	Ubertrag: 0
	Dritte Stelle: 1 + 0 + 0 = 1	Ubertrag: 0

	In der resultierenden Liste steht nun das Ergebnis

	134 =  4 → 3 → 1.

a.  Definieren Sie den Datentyp	struct element, der eine Ziffer und einen
	Zeiger auf das nachste Element enthalt (einfach verkettete Liste).
*/
typedef struct element{
public:
	element(){
		ziffer = 0;
		next = 0;
	}
	element(unsigned short ziffer){
		this->ziffer = ziffer;
		next = 0;
	}
	element(unsigned short ziffer, element* next){
		this->ziffer = ziffer;
		this->next = next;
	}
	void setZiffer(unsigned short ziffer){
		if(ziffer < 10)	this->ziffer = ziffer;
	}
	void setNext(element* next){
		this->next = next;
	}
	unsigned short getZiffer(){
		return ziffer;
	}
	element* getNext(){
		return next;
	}
	void printZiffer(){
		cout<<ziffer;
	}
private:
	unsigned short ziffer;
	element* next;
}element;


typedef struct myLong{
public:
	myLong(){
		first = NULL;
		length = 0;
	}
	myLong(long long unsigned int* array, int length){
		long long unsigned int n = array[length - 1];
		if(n < 10){
			first = new element(n);
			this->length = 1;
		}
		else{
			long long unsigned int buffer = n;
			first = new element(n % 10);
			element* next = first;
			this->length = 1;
			while(buffer > 9){
				buffer = buffer / 10;
				unsigned short ziffer = buffer % 10;
				next->setNext(new element(ziffer));
				next = next->getNext();
				this->length++;
			}
			//transform
		}
		if(length > 1){
			for(int i = length - 2; i >= 0; i--){
				verlaengern(new myLong(&array[i], 1));
			}
		}
	}

	element* getFirst(){
		return first;
	}

	unsigned int getLength(){
		return length;
	}

	void print(){
		if(length == 0) return;
		else if(length == 1) first->printZiffer();
		else{
			element* buffer = first;
			unsigned short array[length];
			for(int i = length - 1; i >= 0; i--){
				array[i] = buffer->getZiffer();
				buffer = buffer->getNext();
			}
			for(unsigned int i = 0; i < length; i++){
				cout<<array[i];
			}
		}
		cout<<endl;
	}

	void add(myLong* A, myLong* B){
		cout<<"Addition grosser Zahlen:\n\t";
		A->print();
		cout<<"+\t";
		B->print();
		element* bufferA = A->getFirst();
		element* bufferB = B->getFirst();
		element* work = NULL;
		element* bufferThis = first;
		unsigned int overflow = 0;
		if(bufferA == NULL && bufferB == NULL) return;
		else if(bufferA != NULL && bufferB != NULL){
			first = new element(bufferA->getZiffer() + bufferA->getZiffer());
			element* bufferThis = first;
			bufferA = bufferA->getNext();
			bufferB = bufferB->getNext();
			this->length = 1;
			if(bufferThis->getZiffer() > 9){
				bufferThis->setZiffer(bufferThis->getZiffer() - 10);
				overflow = 1;
			}
			while(bufferA != NULL && bufferB != NULL){
				unsigned int a = bufferA->getZiffer();
				unsigned int b = bufferB->getZiffer();
				unsigned int sum = overflow + a + b;
				if(overflow == 1) overflow = 0;
				if(sum > 9){
					sum = sum - 10;
					overflow = 1;
				}
				bufferThis->setNext(new element(sum));
				this->length += 1;

				bufferA = bufferA->getNext();
				bufferB = bufferB->getNext();
				bufferThis = bufferThis->getNext();

				if(bufferA == NULL && bufferB != NULL){
					bufferThis->setNext(new element(overflow + bufferB->getZiffer()));
					bufferB = bufferB->getNext();
					this->length += 1;
				}
				else if(bufferA != NULL && bufferB == NULL){
					bufferThis->setNext(new element(overflow + bufferA->getZiffer()));
					bufferA = bufferA->getNext();
					this->length += 1;
				}
				else if(bufferA == NULL && bufferB == NULL && overflow == 1){
					bufferThis->setNext(new element(1));
					this->length += 1;
				}
			}
			if(bufferA == NULL) work = bufferB;
			else work = bufferA;
		}
		else if(bufferA == NULL && bufferB != NULL){
			first = new element(bufferB->getZiffer());
			this->length = 1;
			work = bufferB;
		}
		else{
			first = new element(bufferA->getZiffer());
			this->length = 1;
			work = bufferA;
		}
		while(work != NULL){
			bufferThis->setNext(new element(work->getZiffer()));
			this->length += 1;
			work = work->getNext();
			bufferThis = bufferThis->getNext();
		}
		cout<<"=\t";
		this->print();
	}
private:
	element* first;
	unsigned int length;

	void verlaengern(myLong* part){
		element* ziffer = first;
		while(ziffer->getNext() != NULL){
			ziffer = ziffer->getNext();
		}
		ziffer->setNext(part->getFirst());
		length += part->getLength();
	}
}myLong;

/*
b.  Addieren Sie folgenden Zahlen mit ihrem neuen Datentyp:

	(a)  65535 + 65535
	(b)  18446744073709551615 + 9223372036854775807

c.  Wie konnte man eine Langzahlmultiplikation implementieren?

	Ueber eine stellenweise Multiplikation, pro Dezimalstelle der zweiten Zahl
	wird jede Stelle der ersten Zahl mit der Dezimalstelle multipliziert.
	Dabei werd jeweils in der n-ten Dezimalstelle der zweiten Zahl vor der
	tatsachlichen Multiplikation n Dezimalstellen mit Nullen aufgefullt.
	Endgultig mussen die Ergebnisse addiert werden.

Hinweise:
a.  Die aktuelle Ziffer bekommen Sie mittels
	(ziffer1 + ziffer2 + ?) % 10.

b.  Den Ubertrag bekommen Sie mittels
	(int)((ziffer1 + ziffer2 + ?) / 10).*/


int main(int argc, char** argv){
	/*	Aufgabe 1
	int n = 45;
	long long int array[n];
	fibonacci(n, array);
	*/
	long long unsigned int arrayA[1] = {65535};
	long long unsigned int arrayB1[3] = {184467440,737095516,15};
	long long unsigned int arrayB2[3] = {922337203,685477580,7};
	//myLong* A = new myLong(array, 6);
	//A->print();
	//myLong* A = new myLong(18446744073709551615);
	//A->print();
	myLong* A = new myLong(arrayA, 1);
	myLong* B = new myLong(arrayA, 1);
	myLong* res = new myLong();
	res->add(A, B);
	//res->print();
	A = new myLong(arrayB1, 3);
	B = new myLong(arrayB2, 3);
	res = new myLong();
	res->add(A, B);

	return 0;
}
