#include <iostream>
#include <string>
#include <list>
#include <climits>		//int_max

#include "gph_io.h"

using namespace std;

struct erdos{
public:
	graph *g;
	int **adj_matrix;
	int count;

	erdos(){
		g = read_edges_file("erdosgraph.txt");
		count = 0;
		if(g != nullptr){
			count = g->node_count;
			adj_matrix = list_to_matrix();
		}
		else
			adj_matrix = nullptr;
	}
	~erdos(){
		delete(g);
	}

	bool connected(){
		int** matrix = add_matrix(adj_matrix, transpose(adj_matrix));
		matrix = add_matrix(matrix, unit_matrix());
		int** buffer = matrix;
		cout << "Starting multiplication...\n";
		for(int i = 0; i < count-1; i++){
			buffer = multiply_matrix(buffer, matrix);
			cout << i;
			if(i % 10 == 1) cout << endl;
		}
		for(int i = 0; i < count; i++){
			for(int j = 0; j < count; j++){
				if(buffer[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int collaboration_distance(string nameA, string nameB){
		int start = name_to_number(nameA);
		int target = name_to_number(nameB);
		int** matrix = add_matrix(adj_matrix, unit_matrix());
		int** buffer = matrix;
		int counter = 1;
		while(counter < count){
			if(buffer[start][target] != 0)
				break;
			buffer = multiply_matrix(buffer, matrix);
			counter++;
		}
		if(counter == count)
			counter = -1;
		for(int i = 0; i < count; i++){
			delete[] (matrix[i]);
			delete[] (buffer[i]);
		}
		delete matrix;
		delete buffer;
		return counter;
	}

	void max_collab_dist_in_connections(){
		int **dist = floyd_warshall();
		list<int*> components;
		list<int> visited;
		for(int i = 0; i < count; i++){
			int distance = 0;
			if(search_list(&visited, index_up(i)) == true)
				continue;
			else{
				visited.push_back(index_up(i));
				list<int> neighbors;
				for(int k = 0; k < count; k++){
					if(adj_matrix[i][k] == 1){
						neighbors.push_back(k);
					}
					int val = dist[i][k];
					if((val != INT_MAX) && (val > distance))
						distance = val;
				}
				while(neighbors.empty() == false){
					int element = neighbors.front();
					neighbors.pop_front();

					for(int k = 0; k < count; k++){
						if((adj_matrix[element][k] == 1 ) &&
								search_list(&neighbors, k) == false &&
										search_list(&visited, k) == false)
							neighbors.push_back(k);
						int val = dist[element][k];
						if((val != INT_MAX) && (val > distance))
							distance = val;
					}
					visited.push_back(element);
				}
				int *vector = new int[2];
				vector[0] = i;
				vector[1] =  distance;
				components.push_back(vector);
			}
		}
		//Ausgabe
		cout << "Maximale Collaboration Distance:\n";
		for(int *x: components){
			cout << "\nKomponente enthaelt:\n" << number_to_name(x[0]);
			cout << "\nMaximale Distanz innerhalb = " << x[1] << endl;
			delete[](x);
		}

		delete[] (dist);
	}

private:
	int **floyd_warshall(){
		int **predecessor = unit_matrix();
		int **distance = init_matrix(count);
		//vorbelegen mit sich selbst
		//index_up(i) damit werte 1-511
		//sonst 0 vergaenger von allen
		for(int i = 0; i < count; i++){
			for(int j = 0; j < count; j++){
				if(i == j){
					predecessor[i][i] = index_up(i);
					distance[i][j] = 0;
				}
				else{
					int val = adj_matrix[i][j];
					if(val == 0){
						predecessor[i][j] = 0;
						distance[i][j] = INT_MAX;
					}
					else{
						predecessor[i][j] = index_up(i);
						distance[i][j] = 1;
					}
				}
			}
		}

		for(int k = 0; k < count; k++){
			for(int i = 0; i < count; i++){
				for(int j = 0; j < count; j++){
					int dist = distance[i][k] + distance[k][j];
					if((dist >= 0) && (dist < distance[i][j])){
						distance[i][j] = dist;
						predecessor[i][j] = predecessor[k][j];
					}
				}
			}
		}
		delete[] (predecessor);
		return distance;
	}

	int index_up(int i){
		return i+1;
	}

	int **transpose(int** matrix){
		int** ret = init_matrix(count);
		for(int i = 0; i < count; i++){
			for(int j = 0; j < count; j++){
				ret[i][j] = matrix[j][i];
			}
		}
		return ret;
	}

	int **list_to_matrix(){
		int** matrix = init_matrix(count);
		for(int i = 0; i < count; i++){
			edge *node = g->nodes[i];
			int position = -1;
			if(node != nullptr)
				position = index(node->target);
			for(int j = count - 1; j >= 0; j--){
				if(j == position){
					matrix[i][j] = 1;
					if(node->next != nullptr){
						node = node->next;
						position = index(node->target);
					}
				}
				else matrix[i][j] = 0;
			}
		}
		return matrix;
	}

	int **unit_matrix(){
		int** matrix = init_matrix(count);
		for(int i = 0; i < count; i++){
			for(int j = 0; j < count; j++){
				if(i == j){
					matrix[i][j] = 1;
				}
				else matrix[i][j] = 0;
			}
		}
		return matrix;
	}

	int **add_matrix(int** matrixA, int** matrixB){
		int** ret = init_matrix(count);
		for(int i = 0; i < count; i++){
			for(int j = 0; j < count; j++){
				ret[i][j] = matrixA[i][j] + matrixB[i][j];
			}
		}
		return ret;
	}

	int **multiply_matrix(int** matrixA, int** matrixB){
		int** ret = init_matrix(count);
		for(int i = 0; i < count; i++){
			for(int j = 0; j < count; j++){
				ret[i][j] = 0;
				for(int k = 0; k < count; k++){
					ret[i][j] += matrixA[i][k] * matrixB[k][j];
				}
			}
		}
		return ret;
	}

	int name_to_number(string name){
		string filename = "legende.txt";
		string line;
		int ret = -1;

		//Öffne Datei und prüfe auf Erfolg
		ifstream myfile(filename);
		assert(myfile);
		for (int i = 0; i < count; i++){
			getline(myfile, line);
			if (line.compare(name) == 0){
				ret = i;
				break;
			}
		}
		myfile.close();
		return ret;
	}

	string number_to_name(int number){
		string filename = "legende.txt";
		string line;
		string ret;

		//Öffne Datei und prüfe auf Erfolg
		ifstream myfile(filename);
		assert(myfile);
		for (int i = 0; i < count; i++){
			getline(myfile, line);
			if(i == number){
				ret = line;
				break;
			}
		}
		myfile.close();
		return ret;
	}

	//Gibt das erste Vorkommen vom Autor zurueck
	int find_author_position(int author){
		for(int i = 0; i < g->edge_count; i++){
			if(g->nodes[i]->target == author)
				return i;
		}
		return -1;
	}

	void print_matrix(int** matrix){
		for(int i = 0; i < count; i++){
			cout << endl;
			for(int j = 0; j < count; j++){
				if(j != 0) cout << "\t";
				cout << matrix[i][j];
			}
		}
	}

	bool search_list(list<int> *l, int n){
		list<int> lis = *l;
		for(int x: lis){
			if(x == n)
				return true;
		}
		return false;
	}
};

int main(){
	erdos *e = new erdos();
	string personA = "ABBOTT, HARVEY LESLIE";
	string personB = "AGOH, TAKASHI";
	e->max_collab_dist_in_connections();
	//cout << e->collaboration_distance(personA, personB);
	//cout << endl << e->legende[0] << e->legende[1];
	//cout << e->connected();
	return 0;
}

