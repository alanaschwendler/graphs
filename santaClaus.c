#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct graph {
	int v;
	int e;
	int *x;
	int *y;
	int *distances;
} Graph_t;

/*
 * Kruskal's algorithm
 * @param *set set with solution
 * @param *g graph with all informations
 */
void kruskal(int *set, Graph_t *g);

int main() {
	int *set = malloc(sizeof(int));
	assert(set);
   	Graph_t *g = malloc(sizeof(Graph_t));
	assert(g);

	printf("Vortexes: ");
	scanf("%d", &g->v); //vortexes
	printf("Edges: ");
	scanf("%d", &g->e); //edges
	
	g->x = malloc(sizeof(int) * g->v);
	g->y = malloc(sizeof(int) * g->v);
	g->distances = malloc(sizeof(int) * g->e);
	
	if((g->v == g->e) && (g->e == 0)) {
		exit(1);
	} else {
		kruskal(set, g);
	}
	free(set);
	free(g);
	return 0;
}

/* 
 * Kruskal's algorithm
 */
void kruskal(int *set, Graph_t *g) {
}
