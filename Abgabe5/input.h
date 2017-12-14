#ifndef _input_h_
#define _input_h_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;


//Speicher allokieren
//Parameter: Dimension der Matrix
//Rueckgabewert: zweidimensionales Array (Pointer)
int** init_matrix(int n, int m) {
	int **mat,i;
	mat = new int*[n];
	for (i=0;i<n;i++) {
		mat[i] = new int [m];
	}
	return mat;
}

//Speicher freigeben
void delete_matrix(int ** mat, int n, int m) {
	int i;
	for (i=0;i<n;i++) {
		delete[] mat[i];mat[i] = NULL; 
	}
	delete[] mat; 
}

//Ausgabe der Matrix auf der Konsole
void print_matrix(int **mat, int n, int m) {
	int i,j;
	for (i=0;i<n;i++) {
		for (j=0;j<m;j++) {
			cout << mat[i][j] << " ";
		}
	cout << endl;
	}	
}


/*Einlesen der Matrix aus der Datei filename. Die Matrix und die Dimensionen 
 werden zurueckgeben*/
 int** read_matrix_file(string filename, int *n, int* m) {
	int** adj_matrix;
	string line, token, delimiter = ",";
	int tok,i,j;
	ifstream myfile (filename.c_str());
	if (myfile.is_open()) {
		getline(myfile,line);
		size_t pos = line.find(delimiter);
		token = line.substr(0, pos);
		*n = atoi(token.c_str());
		line.erase(0, pos + delimiter.length());
		*m = atoi(line.c_str());
		adj_matrix = init_matrix(*n,*m);
		i=0;
		while ( (getline (myfile,line)) && (i<*n) ) {
			j=0;
			pos = 0;
			while (((pos = line.find(delimiter)) != string::npos) && (j<*m)) {
				token = line.substr(0, pos);
				tok = atoi(token.c_str());
				adj_matrix[i][j] = tok;
				line.erase(0, pos + delimiter.length());
				j++;
			}
			tok = atoi(line.c_str());
			if ((j<*m) && (i<*n)) adj_matrix[i][j] = tok;
			i++;
		}	
		myfile.close();
	} else cout << "Unable to open file";
	return adj_matrix;
}

#endif
