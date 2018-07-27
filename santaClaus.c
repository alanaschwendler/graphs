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

typedef struct set {
	int size;
	int *arr;
} Set_t;

/*
 * Kruskal's algorithm
 * @param *set set with solution
 * @param *g graph with all informations
 */
void kruskal(int *set, Graph_t *g);

Set_t* make_set();

void destroy(Set_t *s);

void insert_on_set(Set_t *s, int elem);

int find_in_set(Set_t *s, int elem);

int main() {
   	Graph_t *g = malloc(sizeof(Graph_t));
	assert(g);
	
	int i;

	do {
		printf("Vortexes: ");
		scanf("%d", &g->v); //vortexes
		printf("Edges: ");
		scanf("%d", &g->e); //edges
	
		g->x = malloc(sizeof(int) * g->v);
		g->y = malloc(sizeof(int) * g->v);
		g->distances = malloc(sizeof(int) * g->e);
		
		for(i = 0; i < g->v; ++i) {
			make_set();
		}

	} while(g->v != 0 && g->e != 0);
	
	free(g->x);
	free(g->y);
	free(g->distances);
	free(g);
	return 0;
}

/* 
 * Kruskal's algorithm
 */
void kruskal(int *set, Graph_t *g) {
}

Set_t* make_set() {
	Set_t *s;
	s = malloc(sizeof(Set_t));
	assert(s);
	s->size = 0;
	s->arr = NULL;
	return s;
}

void destroy(Set_t *s) {
	if(s->arr != NULL) 
		free(s->arr);
	
	free(s);
}

void insert_on_set(Set_t *s, int elem) {

	if(find_in_set(s, elem) == 0) {
		s->size += 1;
		s->arr = realloc(s->arr, sizeof(int) * s->size);
		assert(s->arr);
		s->arr[(s->size)-1] = elem;
	} 
}


int find_in_set(Set_t *s, int elem) {
	int i;
	for(i = 0; i < s->size; ++i) {
		if(s->arr[i] == elem) {
			return 1;
		}
	}
	return 0;
}

Set_t* union_set(Set_t *s1, Set_t *s2) {
	int i;

	Set_t *s = make_set();

	for(i = 0; i < s1->size; ++i) 
		insert_on_set(s, s1->arr[i]);

	for(i = 0; i < s2->size; ++i)
		insert_on_set(s, s2->arr[i]);
	
	return s;
}

int compare_sets(Set_t *s1, Set_t *s2) {
	int i, aux;
	
	if(s1->size > s2->size) {
		for(i = 0; i < s2->size; ++i) {
			aux = find_in_set(s1, s2->arr[i]);
			if(aux == 0)
				return 0;
		} 
		return 1;
	} else {
		for(i = 0; i < s1->size; ++i) {
			aux = find_in_set(s2, s1->arr[i]);
			if(aux == 0)
				return 0;
		}
		return 1;
	}
}
