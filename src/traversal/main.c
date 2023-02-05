#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int id;
    int links;
    struct node **neighbors;
} Node;

typedef struct graph {
    Node *nodes;
    int size;
} Graph;

/* Calculate rand() in range [beg, end] */
int randr(unsigned int beg, unsigned int end) {
    if (beg > end)
        return -1;
    else if (end - beg + 1 == 0)
        return beg;

    return (rand() % (end - beg + 1)) + beg;
}

Graph *generate_graph(int size) {
    Graph *graph;
    Node **available_neighbors;
    int idx;

    srand(time(NULL));

    if (size < 1)
        return NULL;

    graph = (Graph*)malloc(sizeof(Graph));
    graph->nodes = (Node*)malloc(sizeof(Node) * size);
    available_neighbors = (Node**)malloc(sizeof(Node*) * size);
    graph->size = size;

    for (int i = 0; i < size; i++) {
        graph->nodes[i].id = i;    
    }

    if (size > 1) {
        for (int i = 0; i < size; i++) {
            graph->nodes[i].links = randr(1, size - 1);
            graph->nodes[i].neighbors = (Node**)malloc(sizeof(Node*) * graph->nodes[i].links);

            for (int j = 0; j < size; j++) {
                available_neighbors[j] = &graph->nodes[j];
            }
            available_neighbors[i] = available_neighbors[size - 1];

            for (int j = 0; j < graph->nodes[i].links; j++) {
                idx = randr(0, size - 2 - j);
                graph->nodes[i].neighbors[j] = available_neighbors[idx];
                available_neighbors[idx] = available_neighbors[size - 2 - j];
            }

        }
    } else {
        graph->nodes[0].links = 0;
        graph->nodes[0].neighbors = NULL;
    }

    free(available_neighbors);

    return graph;
}

void free_node(Node *node) {
    free(node->neighbors);
    free(node);
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->size; i++) {
        free(graph->nodes[i].neighbors);
    }

    free(graph->nodes);
    free(graph);
}

void print_graph(Graph *graph) {
    for (int i = 0; i < graph->size; i++) {
        printf("%d -> (", graph->nodes[i].id);
        
        for (int j = 0; j < graph->nodes[i].links; j++) {
            printf("%d, ", graph->nodes[i].neighbors[j]->id);
        }

        printf(")\n");
    }
}

int main() {
    Graph *network = generate_graph(5);

    print_graph(network);
    free_graph(network);
}