#include <iostream>
#include <string>
#include <list>
#include <climits>		//int_max
#include <vector>
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;



struct Edge{
	int target;
	int capacity;
	int flow;
	struct Edge *next;
	Edge(int t){
		target = t;
		capacity = 1;
		flow = 0;
		next = nullptr;
	}
};

struct UEFA{
	const int size = 8;
	const int sizeMatrix = (2*size) + 2;
	vector<vector<string>> Teams;
	int** flussnetz;
	int** flow;
	UEFA(){
		read_teams();
		if(!Teams.empty()){
			init_flussnetz();
			init_flow();
		}
		else{
			flussnetz = nullptr;
			flow = nullptr;
		}
	}
	~UEFA(){
		for(int i = 0; i < sizeMatrix; i++){
			delete[] (flussnetz[i]);
			delete[] (flow[i]);
		}
		delete[] (flussnetz);
		delete[] (flow);
	}

	void print_teams(){
		for(vector<string> x: Teams){
			std::cout << x[0] << ": " << x[1] << std::endl;
		}
	}
	void print_matrix(int** matrix){
		for(int i = 0; i < sizeMatrix; i++){
			cout << endl;
			for(int j = 0; j < sizeMatrix; j++){
				cout << matrix[i][j];
				if(j < sizeMatrix - 1)
					cout << " ";
			}
		}
	}
	void finale(bool print_steps){
		vector<int> weg;
		while(BFS(&weg)){
			for(int i = 0; i < weg.size(); i++){
				int a = weg[i];
				if(a < (sizeMatrix - 1)){
					int b = weg[i+1];
					flow[a][b] = 1;
					if(a > 0){
						flussnetz[b][a] = 1;
					}
				}
			}
			if(print_steps){
				cout << endl << "Netz" << endl;
				print_matrix(flussnetz);
				cout << endl << "Fluss" << endl;
				print_matrix(flow);
			}
		}
		print_matchup();
	}
private:
	bool BFS(vector<int> *weg){
		if(weg->size() > 0){
			weg->clear();
		}
		int edge = 0;
		weg->push_back(edge);
		while(edge < (sizeMatrix - 1)){
			int start = 1;
			int end = start + size;
			if((edge > 0) && (edge < size+1)){
				start += size;
				end += size;
			}
			else if(edge > size){
				end = sizeMatrix;
			}
			for(int i = end - 1; i >= start; i--){
				if((flussnetz[edge][i] == 1) &&
						(flow[edge][i] == 0)){
					weg->push_back(i);
					edge = i;
					if(i == sizeMatrix-1){
						return true;
					}
					break;
				}
				else if(i == start){
					return false;
				}
			}
		}
		return false;
	}
	void print_matchup(){
		cout << "\nViertelfinale Matchup:\n";
		for(int i = 1; i < size+1; i++){
			for(int j = size+1; j < sizeMatrix -1; j++){
				if((flow[i][j] == 1) && (flow[j][i] == 0))
				cout << number_to_name(i) << " vs "
						<< number_to_name(j) << endl;
			}
		}
	}
	void read_teams(){
		//Öffne Datei und prüfe auf Erfolg
		ifstream myfile("teams.txt");
		assert(myfile);

		string line;

		for(int i = 0; i < size*2; i++){
			vector<string> ref(2);
			stringstream ss;
			assert(getline(myfile, line));
			ss << line;
			ss >> ref[0] >> ref[1];
			Teams.push_back(ref);
		}
		myfile.close();
	}
	void init_flow(){
		flow = init_matrix(sizeMatrix);
		for(int i = 0; i < sizeMatrix; i++){
			for(int j = 0; j < sizeMatrix; j++){
				flow[i][j] = 0;
			}
		}
	}
	void init_flussnetz(){
		flussnetz = init_matrix(sizeMatrix);
		for(int i = 0; i < sizeMatrix; i++){
			int count = index(i);
			for(int j = 0; j < sizeMatrix; j++){
				if(i == j){
					flussnetz[i][j] = 0;
				}
				//Quelle
				else if(i == 0){
					//Gruppensieger?
					if(j > 0 && j < size +1){
						flussnetz[i][j] = 1;
					}
					else{
						flussnetz[i][j] = 0;
					}
				}
				//Gruppensieger
				else if(count < size){
					//Gruppenzweiter?
					if((j >= size+1) && (j < sizeMatrix - 1)){
						// NOT gleiches Land?
						if(Teams[count][1] != Teams[index(j)][1]){
							flussnetz[i][j] = 1;
						}
						else{
							flussnetz[i][j] = 0;
						}
					}
					else{
						flussnetz[i][j] = 0;
					}
				}
				//Gruppenzweite
				else if(i < sizeMatrix -1){
					if(j < sizeMatrix -1){
						flussnetz[i][j] = 0;
					}
					//Senke
					else{
						flussnetz[i][j] = 1;
					}
				}
				//Senke
				else{
					flussnetz[i][j] = 0;
				}
			}
		}
	}
	int index(int i){
		return --i;
	}
	int index_up(int i){
		return ++i;
	}
	int **init_matrix(int n)
	{
		assert(n > 0);

		int** mat = new int *[n];
		for (int i = 0; i < n; i++)
		{
			mat[i] = new int[n]();
		}
		return mat;
	}
	string number_to_name(int n){
		if( n > 0 && n < sizeMatrix-1)
			return Teams[index(n)][0];
		else
			return "";
	}
};

int main(){
	UEFA *t = new UEFA();
	t->print_teams();
	t->print_matrix(t->flussnetz);
	cout << endl;
	t->print_matrix(t->flow);
	t->finale(true);
	return 0;
}
