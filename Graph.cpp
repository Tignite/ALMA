#include <iostream>
using namespace std;

typedef struct node{
    unsigned int id;
    unsigned int degree;
    unsigned int *neighbors;
}Node;
 
typedef struct graph{
    unsigned int num_nodes;
    Node nodes[];
}Graph;
 
Graph create_graph(unsigned int n);
void initialize_node(Node *node, unsigned int id);

Graph create_graph(unsigned int n){
    unsigned int k;
    Graph *g = new Graph;    
    g->num_nodes=n;
    g->&nodes=new Node [n];
    for (k=0;k<n;k++){
        initialize_node(&(g.nodes[k]),k);
    }
    return &g;
}
void initialize_node(Node *node, unsigned int id){
    node->id=id;
    node->degree=0;
    node->neighbors=new unsigned int[n-1];
}

bool test (Node *node, unsigned int id) {
    unsigned int i=0;
    while (i<node->degree) {
        if (node->neighbors[i]=id) {
            return true;
        }
        else i++;
    }
    return false;
}

void edge (Node *nodeA, Node *nodeB){
    if (test (nodeA, nodeB->id)==false) {
        nodeA->neighbors[nodeA->degree]=nodeB->id;
        nodeB->neighbors[nodeB->degree]=nodeA->id;
        nodeA->degree++;
        nodeB->degree++;
    }
}

void ausgabe (Graph *G) {
    Node buffer = G->nodes[0];
    unsigned int i = 0;
    while(buffer != NULL){
        cout << buffer->id << "{" ;
        unsigned int k = 0:
        while(k < buffer->degree) {
            cout << buffer->neighbors[k] << ", ";
            k++;
        }
        cout << "}" << endl;
        buffer = G->nodes[++i];
    }
}

int main() {
    unsigned int n=6;
    Graph *G = create_graph(n);
    edge (G->nodes[0], G->nodes[1]);
    ausgabe (G);
    return 0;
}
