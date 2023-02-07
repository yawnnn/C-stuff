#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int id;
    int edges;
    int *weights;
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
    int free_neighbor;
    int idx_free_neighbor;
    int size_available_neighbors;

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
            graph->nodes[i].edges = randr(1, size - 1);
            graph->nodes[i].weights = (int*)malloc(sizeof(int) * graph->nodes[i].edges);
            graph->nodes[i].neighbors = (Node**)malloc(sizeof(Node*) * graph->nodes[i].edges);
            memset(graph->nodes[i].neighbors, 0, sizeof(Node**) * graph->nodes[i].edges);
        }

        for (int i = 0; i < size; i++) {
            size_available_neighbors = 0;

            for (int j = 0; j < size; j++) {
                free_neighbor = 0;

                for (int k = 0; k < graph->nodes[j].edges && !free_neighbor; k++) {
                    if (graph->nodes[j].neighbors[k] == NULL && i != j) {
                        free_neighbor = 1;
                        idx_free_neighbor = k;
                    }
                }

                if (free_neighbor) {
                    available_neighbors[size_available_neighbors] = &graph->nodes[j];
                    size_available_neighbors++;
                }
            }

            for (int j = 0; j < graph->nodes[i].edges; j++) {
                idx = randr(0, size_available_neighbors - 1 - j);
                graph->nodes[i].neighbors[j] = available_neighbors[idx];
                available_neighbors[idx]->neighbors[??] = &graph->nodes[i];
                available_neighbors[idx] = available_neighbors[size_available_neighbors - 1 - j];
            }
        }
    } else {
        graph->nodes[0].edges = 0;
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