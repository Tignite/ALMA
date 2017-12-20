#include "input.h"
#include "graphen.h"
#include "GraphenList.h"

int ** sum(int **mat1 , int **mat2 , int n , int m);
int ** product(int  **mat1 , int  **mat2 ,
int n1 , int m1 , int n2 , int m2);


int main() {

	/*
	int **matrix1, **matrix2, **matrix3, **matrixErgebnis, n1, m1, n2, m2;
	//Einlesen der Matrix aus graph1.dat
	matrix1 = read_matrix_file("graph1.dat", &n1, &m1);
	matrix2 = read_matrix_file("graph2.dat", &n2, &m2);
	matrix3 = read_matrix_file("graph2.dat", &n2, &m2);
	//Ausgeben der Matrix in der Konsole
	//cout<<"Matrix 1:\n";
	//print_matrix(matrix1,n1,m1);
	cout<<"Matrix 2:\n";
	print_matrix(matrix2,n2,m2);
	matrixErgebnis = sum(matrix3, matrix2, n2, m2);
	cout<<"Matrix Summe:\n";
	print_matrix(matrixErgebnis,n2,m2);

	delete_matrix(matrixErgebnis, n2, m2);
	matrixErgebnis = product(matrix2, matrix2, n2, m2, n2, m2);
	cout<<"Matrix Product:\n";
	print_matrix(matrixErgebnis,n2,m2);


	delete_matrix(matrix1, n1, m1);
	delete_matrix(matrix2, n2, m2);
	delete_matrix(matrix3, n2, m2);
	delete_matrix(matrixErgebnis, n2, m2);
	return 0;

	Aufgabe 2
	*/
	Graphen *G1 = new Graphen("graph1.dat");
	Graphen *G2 = new Graphen("graph2.dat");
	G1->print();
	G1->wegExist(10, 0, 3);
	G1->kreisExist();
	G1->zusammenhang();
	G2->print();
	G2->wegExist(10, 4, 3);
	G2->kreisExist();
	G2->zusammenhang();
	delete G1;
	delete G2;
	return 0;
}

int ** sum(int **mat1 , int **mat2 , int n , int m) {
	//Pruefen ausserhalb der Funktion auf gleiche Dimension?!
	int** ergebnis = init_matrix(n, m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			ergebnis[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
	return ergebnis;
}

int ** product(int  **mat1 , int  **mat2 ,
int n1 , int m1 , int n2 , int m2) {
	int** ergebnis = NULL;
	if(m1 == n2){
		ergebnis = init_matrix(n1, m2);
		for(int i = 0; i < n1; i++){
			for(int j = 0; j < m2; j++){
				ergebnis[i][j] = 0;
				for(int k = 0; k < n2; k++){
					ergebnis[i][j] += mat1[i][k] + mat2[k][j];
				}
			}
		}
	}
	return ergebnis;
}
