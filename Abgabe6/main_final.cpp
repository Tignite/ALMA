#include <iostream>
#include <string>
#include <list>
#include <climits>		//int_max
#include <vector>

#include "gph_io.h"

using namespace std;


struct erdos{
public:
	graph *g;
	int **adj_matrix;
	int **dist;
	int count;

	erdos(){
		g = read_edges_file("erdosgraph.txt");
		count = 0;
		if(g != nullptr){
			count = g->node_count;
			adj_matrix = list_to_matrix();
			dist = floyd_warshall();
		}
		else{
			adj_matrix = nullptr;
			dist = nullptr;
		}
	}
	~erdos(){
		if(g != nullptr){
			delete(g);
			for(int i = 0; i < count; i++){
				delete[] (dist[i]);
			}
			delete[] (dist);
			g = nullptr;
			adj_matrix = nullptr;
			dist = nullptr;
		}
		count = 0;
	}

	bool connected_floyd_warshall(){
		for(int i = 0; i < count; i++){
			if(dist[0][i] == INT_MAX)
				return false;
		}
		return true;
	}

	int collab_distance_floyd_warshall(string nameA, string nameB){
		int start = name_to_number(nameA);
		int target = name_to_number(nameB);
		return dist[start][target];
	}

	int max_collab_dist(){
		vector<bool> visited(count, false);
		list<int> neighbors;
		int max = 0;
		for(int i = 0; i < count; i++){
			if(visited[i] == false){
				visited[i] = true;
				neighbors.push_back(i);
				while(neighbors.empty() == false){
					int row = neighbors.front();
					neighbors.pop_front();
					visited[row] = true;
					for(int j = 0; j < count; j++){
						int point = dist[row][j];
						if((visited[j] == false) &&
								(adj_matrix[row][j] == 1)){
							neighbors.push_back(j);
						}
						if((point != INT_MAX) &&
								(point > max)){
							max = point;
						}
					}
				}
			}
		}
		delete (&visited);
		delete (&neighbors);
		return max;
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
		for (int i = 0; i < count; ++i)
		{
			delete[] predecessor[i];
		}
		delete[] (predecessor);
		return distance;
	}

	int index_up(int i){
		return i+1;
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
};

int main(){
	erdos *e = new erdos();
	string personA = "ABBOTT, HARVEY LESLIE";
	string personB = "AGOH, TAKASHI";
	//cout << e->connected_floyd_warshall();
	cout << endl << e->max_collab_dist();
	//cout << e->collaboration_distance(personA, personB);
	//cout << endl << e->legende[0] << e->legende[1];
	return 0;
}
