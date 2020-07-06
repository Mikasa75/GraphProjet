#include<stdio.h>
#include<stdlib.h>

#define inf 0x0fffffff

typedef struct ANode
{
	int adjvex;//终点编号 
	int weight;//权值 
	int weightbfs;//bfs专用权值 
	struct ANode* nextarc;//下一条边 
}ArcNode;

typedef struct
{
	ArcNode* adjlist[10000];
	int visited[10000];
	int path[10000][10000];
}AdjGraph;

int judge(AdjGraph* graph, int aim);
AdjGraph* creatGraph(AdjGraph* graph, char name[]);
char* shortestPath(int u, int v, char algorithm[], char name[]);
void DFS(AdjGraph* graph, int u, int v, int* result);
void BFS(AdjGraph* graph, int u, int v, int* result);
void Dijkstra(AdjGraph* graph, int u, int v);

int N, M;//结点数，边数 
char path[10000];//最终路径 
int r = 0, count[10000] = { 0 };//结果数组计数 
int flag = 0;
int que[1000000], pre[1000000];//bfs用队列 
int head = 0, tail = 1;//队首，尾 
int cost = 0;//bfs用的cost 

char* shortestPath(int u, int v, char algorithm[], char name[])
{
	int i = 0, j, k;
	char temc[1000];
	int result[1000];
	AdjGraph* graph;
	graph = creatGraph(graph, name);
	switch (algorithm[0]) {
	case 'D':
		if (algorithm[1] == 'i') {
			Dijkstra(graph, u, v);
			for (j = 0; j < count[v]; j++) {
				if (graph->path[v][j] == 0) {
					path[i] = '0'; i++;
					if (j < count[v] - 1) {
						path[i] = '-'; i++;
						path[i] = '>'; i++;
					}
					continue;
				}
				k = 0;
				while (graph->path[v][j]) {
					temc[k] = graph->path[v][j] % 10 + '0';
					k++;
					graph->path[v][j] /= 10;
				}
				k--;
				for (; k >= 0; k--) {
					path[i] = temc[k]; i++;
				}
				if (j < count[v] - 1) {
					path[i] = '-'; i++;
					path[i] = '>'; i++;
				}
			}
			path[i] = '\n'; i++;
			path[i] = 'c'; i++;
			path[i] = 'o'; i++;
			path[i] = 's'; i++;
			path[i] = 't'; i++;
			path[i] = ':'; i++;
			j = 0;
			while (graph->adjlist[v]->weight) {
				temc[j] = graph->adjlist[v]->weight % 10 + '0';
				j++;
				graph->adjlist[v]->weight /= 10;
			}
			j--;
			for (; j >= 0; j--) {
				path[i] = temc[j]; i++;
			}
			path[i] = '\0';
		}
		else {
			DFS(graph, u, v, result);
			for (j = r - 1; j >= 0; j--) {
				if (result[j] == 0) {
					path[i] = '0'; i++;
					if (i < count[v] - 1) {
						path[i] = '-'; i++;
						path[i] = '>'; i++;
					}
					continue;
				}
				k = 0;
				while (result[j]) {
					temc[k] = result[j] % 10 + '0';
					k++;
					result[j] /= 10;
				}
				k--;
				for (; k >= 0; k--) {
					path[i] = temc[k]; i++;
				}
				if (i > 0) {
					path[i] = '-'; i++;
					path[i] = '>'; i++;
				}
			}
			path[i] = '\0';
		}
		break;
	case 'B':
		BFS(graph, u, v, result);
		j = r - 1;
		ArcNode* tem = graph->adjlist[result[j]]->nextarc;
		while (j > 0) {
			if (tem->adjvex == result[j - 1]) {
				cost += tem->weight;
				tem = graph->adjlist[result[j - 1]]->nextarc;
				j--;
				continue;
			}
			tem = tem->nextarc;
		}
		for (j = r - 1; j >= 0; j--) {
			if (result[j] == 0) {
				path[i] = '0'; i++;
				if (j > 0) {
					path[i] = '-'; i++;
					path[i] = '>'; i++;
				}
				continue;
			}
			k = 0;
			while (result[j]) {
				temc[k] = result[j] % 10 + '0';
				k++;
				result[j] /= 10;
			}
			k--;
			for (; k >= 0; k--) {
				path[i] = temc[k]; i++;
			}
			if (j > 0) {
				path[i] = '-'; i++;
				path[i] = '>'; i++;
			}
		}
		path[i] = '\n'; i++;
		path[i] = 'c'; i++;
		path[i] = 'o'; i++;
		path[i] = 's'; i++;
		path[i] = 't'; i++;
		path[i] = ':'; i++;
		j = 0;
		while (cost) {
			temc[j] = cost % 10 + '0';
			j++;
			cost /= 10;
		}
		j--;
		for (; j >= 0; j--) {
			path[i] = temc[j]; i++;
		}
		path[i] = '\0';
		break;
	default:printf("Input error!\n");
		return NULL;
	}

	return path;
}

int judge(AdjGraph* graph, int aim)
{
	ArcNode* tem = graph->adjlist[aim]->nextarc;
	while (tem != NULL)
	{
		if (graph->visited[tem->adjvex] == 0)
		{
			return 0;
		}
		tem = tem->nextarc;
	}
	return 1;
}

AdjGraph* creatGraph(AdjGraph* graph, char name[])
{
	int tem1, tem2, tem3, i;
	FILE* pFile = fopen(name, "r");
	if (pFile == NULL)
	{
		return 0;
	}

	fscanf(pFile, "%d %d", &N, &M);
	ArcNode* temA, * temB[N];
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

void DFS(AdjGraph* graph, int u, int v, int* result)
{
	if (flag == 1) {
		return;
	}
	graph->visited[u] = 1;
	if (u == v) {
		flag = 1;
		result[r] = u;
		r++;
		return;
	}
	else if (judge(graph, u)) {
		return;
	}
	result[r++] = u;
	ArcNode* tem = graph->adjlist[u]->nextarc;
	while (tem) {
		if (graph->visited[tem->adjvex] == 0) {
			DFS(graph, tem->adjvex, v, result);
		}
		tem = tem->nextarc;
	}
}

void BFS(AdjGraph* graph, int u, int v, int* result)
{
	graph->adjlist[u]->weight = 0;
	graph->visited[u] = 1;
	que[0] = u;
	pre[0] = -1;
	while (1) {
		int P = head;
		u = que[head];
		head++;
		if (u == v) {
			head--;
			while (pre[head] != -1) {
				if (result[r - 1] != que[head]) {
					result[r] = que[head];
					r++;
				}
				head = pre[head];
			}
			return;
		}
		else if (head - 1 == tail) {
			return;
		}
		flag = 0;
		ArcNode* tem = graph->adjlist[u]->nextarc;
		while (tem) {
			if (tem->weightbfs != 1) {
				tem->weightbfs--;
				if (flag == 0) {
					flag = 1;
					que[tail] = u;
					pre[tail] = P;
					tail++;
				}
			}
			else if (graph->visited[tem->adjvex] == 0) {
				graph->visited[tem->adjvex] = 1;
				que[tail] = tem->adjvex;
				pre[tail] = P;
				tail++;
			}
			tem = tem->nextarc;
		}
	}
}

void Dijkstra(AdjGraph* graph, int u, int v)
{
	graph->adjlist[u]->weight = 0;
	graph->path[u][0] = u;
	count[u] = 1;
	while (1) {
		graph->visited[u] = 1;
		if (u == v) {
			return;
		}
		else if (judge(graph, u)) {
			return;
		}
		ArcNode* tem = graph->adjlist[u]->nextarc;
		int min[2] = { inf, u };
		while (tem) {
			if (graph->adjlist[tem->adjvex]->weight > tem->weight + graph->adjlist[u]->weight) {
				graph->adjlist[tem->adjvex]->weight = tem->weight + graph->adjlist[u]->weight;
				int i;
				for (i = 0; i < count[u]; i++) {
					graph->path[tem->adjvex][i] = graph->path[u][i];
				}
				count[tem->adjvex] = i + 1;
				graph->path[tem->adjvex][i] = tem->adjvex;
			}
			if (graph->adjlist[tem->adjvex]->weight < min[0] && graph->visited[tem->adjvex] == 0) {
				min[0] = graph->adjlist[tem->adjvex]->weight;
				min[1] = tem->adjvex;
			}
			tem = tem->nextarc;
		}
		u = min[1];
	}
}
