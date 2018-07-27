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
 * @param *g graph with all informations
 */
int kruskal(Graph_t *g);

Set_t* make_set();

void destroy(Set_t *s);

void insert_on_set(Set_t *s, int elem);

int find_in_set(Set_t *s, int elem);

Set_t* union_set(Set_t *s1, Set_t *s2);

int compare_sets(Set_t *s1, Set_t *s2);

void sort(Graph_t *g);

void merge_sets(Set_t *s1, Set_t *s2, Set_t **vSets);

int main() {
   	Graph_t *g = malloc(sizeof(Graph_t));
	assert(g);
	
	int i, d, minDistance = 0;

	do {
		scanf("%d", &g->v); //vortexes
		scanf("%d", &g->e); //edges
		
		if(g->v == g->e && g->e == 0)
			exit(0);

		g->x = malloc(sizeof(int) * g->v);
		g->y = malloc(sizeof(int) * g->v);
		g->distances = malloc(sizeof(int) * g->e);
		
		for(i = 0; i < g->e; ++i) {
			scanf("%d %d %d", &g->x[i], &g->y[i], &g->distances[i]);
			if(g->x[i] > g->y[i])
				exit(1);
		}

		d = kruskal(g);
		minDistance += d;
		printf("%d\n", minDistance);
		minDistance = 0;
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
int kruskal(Graph_t *g) {
	Set_t *solution;
	solution = make_set();
	Set_t **vSets = malloc(sizeof(Set_t*) * g->v);
	assert(vSets);
	
	int i;
	
	sort(g);
	
	for(i = 0; i < g->v; ++i) {
		vSets[i] = make_set();
		insert_on_set(vSets[i], i);
	}
	
	i = 0; //count edges
	int distance = 0;
	while(solution->size < (g->v)-1) {
		int origin = g->x[i];
		int dest = g->y[i];
		
		if(compare_sets(vSets[origin], vSets[dest]) == 0 ) {
			merge_sets(vSets[origin], vSets[dest], vSets);
			(solution->size)++;
			distance += g->distances[i];
		}
		++i;
	}
	return distance;
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
/* 0 means diferent */
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

void sort(Graph_t *g) {
	int i, j, tmp1, tmp2, tmp3;

	for(i = 1; i < g->e; ++i) { //i starts in 1 
		tmp1 = g->x[i]; //tmp is the current value
		tmp2 = g->y[i];
		tmp3 = g->distances[i];

		for(j = i - 1; (j >= 0) && (tmp3 < g->distances[j]); --j) { //j starts one before i, j is between 0 and current
			g->distances[j+1] = g->distances[j]; //change places of the elements
			g->x[j+1] = g->x[j];
			g->y[j+1] = g->y[j];
		}
		g->distances[j+1] = tmp3;
		g->x[j+1] = tmp1;
		g->y[j+1] = tmp2;
	}
}

void merge_sets(Set_t *s1, Set_t *s2, Set_t **vSets) {
	int i, j;
	//origem	
	for(i = 0; i < s1->size; ++i){
		for(j = 0; j < s2->size; ++j){
			insert_on_set(vSets[s1->arr[i]], s2->arr[j]);
		}
	}

	for(i = 0; i < s2->size; ++i) {
		for(j = 0; j < s1->size; ++j) {
			insert_on_set(vSets[s2->arr[i]], s1->arr[j]);
		}
	}
}
