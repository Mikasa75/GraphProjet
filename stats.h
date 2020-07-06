#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define inf 0x0fffffff

int numberOfEdges(char name[])

{
	int i = 0;
	char vertex[8000];
	char edge[8000];
	int j = 0, k = 0;
	while (name[i] != NULL) {
		vertex[j] = name[i];
		vertex[j + 1] = name[i + 1];
		edge[k] = name[i + 2];
		i = i + 3;
		j = j + 2;
		k = k + 1;
	}
	int numberOfEdges = sizeof(edge) / sizeof(char);
	return numberOfEdges;
}

int numberOfVertices(char name[])
{
	int i = 0;
	int l;
	char vertex[8000] = { 0 };
	char edge[8000];
	int j = 0, k = 0;

	while (name[i] != NULL) {
		vertex[j] = name[i];
		vertex[j + 1] = name[i + 1];
		edge[k] = name[i + 2];
		i = i + 3;
		j = j + 2;
		k = k + 1;
	}
	int b;
	int n1 = 0;
	int n = sizeof(vertex) / sizeof(char);
	for (i = 1; i < n; i++) {
		for (l = 0, b = 0; l < i; l++) {
			if (vertex[i] == vertex[l]) {
				b = 1;
				break;
			}
			if (b == 0) {
				n1++;
			}

		}
	}
	return n1;
}

AdjGraph* creatGraph2(AdjGraph* graph, char name[])
{
	int tem1, tem2, tem3, i;
	FILE* pFile = fopen(name, "r");
	if (pFile == NULL)
	{
		return 0;
	}
	int N = numberOfVertices(name);
	int M = numberOfEdges(name);

	ArcNode* temA, * temB[8000];
	graph = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0; i < N; i++) {
		graph->adjlist[i] = (ArcNode*)malloc(sizeof(ArcNode));
		graph->adjlist[i]->adjvex = i;
		graph->adjlist[i]->weight = inf;
		temB[i] = graph->adjlist[i];
	}
	for (i = 0; i < M; i++) {
		fscanf(pFile, "%d %d %d", &tem1, &tem2, &tem3);

		temA = (ArcNode*)malloc(sizeof(ArcNode));
		temA->adjvex = tem2;
		temA->weight = tem3;
		temA->weightbfs = tem3;
		temB[tem1]->nextarc = temA;
		temB[tem1] = temA;
	}
	for (i = 0; i < N; i++) {
		temB[i]->nextarc = NULL;
	}
	for (i = 0; i < N; i++) {
		graph->visited[i] = 0;
	}
	fclose(pFile);

	return graph;
}

int minDistance(int distance[], int pathCheck[]) //算法改编自https://github.com/farukcolak53/friendshipgraph-fc53/blob/master/graph.c
{



	int min = INT_MAX;

	int indexOfMin;

	int i;

	for (i = 0; i < 10; i++) {

		if ((pathCheck[i] == 0) && (distance[i] <= min)) {

			min = distance[i];

			indexOfMin = i;

		}

	}

	return indexOfMin;

}



float closenessCentrality(int node, char name[])  //算法改编自https://github.com/farukcolak53/friendshipgraph-fc53/blob/master/graph.c
{

	AdjGraph* graph;
	graph = creatGraph2(graph, name);

	int distance[1000];

	int pathCheck[1000];

	int i;

	for (i = 0; i < 10; i++) {

		distance[i] = INT_MAX;

		pathCheck[i] = 0;

	}



	distance[node] = 0; //Distance of node to itself is 0 



	for (i = 0; i < (10 - 1); i++) {

		int u = minDistance(distance, pathCheck);

		int k;

		ArcNode* temp = graph;

		for (k = 0; k < u; k++) {

			temp = temp->nextarc;

		}

		pathCheck[u] = 1;

		int v;

		for (v = 0; v < 10; v++) {

			ArcNode* temp2 = graph;

			for (k = 0; k < v; k++) {

				temp2 = temp2->nextarc;

			}

			int x = 0;
			int counter = numberOfVertices(name);


			if (((distance[u] + x) < distance[v]) && x && (distance[u] != INT_MAX)) {

				distance[v] = distance[u] + x;

			}

		}

	}



	float result = 0;

	for (i = 0; i < 10; i++) {

		result = result + distance[i];

	}



	return result;

}
