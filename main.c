#include<stdio.h>
#include<stdlib.h>
#include "search.h"
#include "stats.h"

int compare(char* a, char* b);

int main(int argc, char** argv)
{
	if (argc == 1) {
		printf("error!\n");
		return 0;
	}
	char help[3] = "-h";
	char graph[3] = "-g";
	char stats[3] = "-s";
	char paint[3] = "-j";
	char search[4] = "-sp";
	char s_edges[6] = "edges";
	char s_vertices[9] = "vertices";
	char s_freeman[8] = "freeman";
	char s_closeness[10] = "closeness";

	if (compare(argv[2], help)) {
		printf("-g FILE_PATH -s include edges, vertices, freeman, closeness.\n");
		printf("-g FILE_PATH -sp include DFS, BFS, Dijkstra.\n");
		return 0;
	}
	else if (compare(argv[2], paint)) {
		printf("   \\/   \n");
		printf("   ||   \n");
		printf("  _/\\_  \n");
		printf("( @ @  )\n");
		printf(" \\_-__/ \n");
		return 0;
	}
	else if (compare(argv[4], stats)) {
		if (compare(argv[5], s_edges)) {
			printf("%d", numberOfEdges(argv[2]));
			return 0;
		}
		else if (compare(argv[5], s_vertices)) {
			printf("%d", numberOfVertices(argv[2]));
			return 0;
		}
		else if (compare(argv[5], s_freeman)) {
			//printf("%d", freemanNetworkCentrality(argv[2]));
			return 0;
		}
		
	}
	else if (compare(argv[4], search)) {
		char* path = shortestPath(atoi(argv[7]), atoi(argv[9]), argv[5], argv[3]);
		puts(path);
	}

	return 0;
}

int compare(char* a, char* b)
{
	int length_a = 0;
	int length_b = 0;
	int i = 0;
	while(a[i] != '\0') {
		length_a++;
		i++;
	}
	i = 0;
	while(b[i] != '\0') {
		length_b++;
		i++;
	}
	i = 0;
	if(length_a == length_b) {
		while(a[i] != '\0' && b[i] != '\0') {
			if(a[i] == b[i]) {
				i++;
				continue;
			}
			else {
				return 0;
			}
		}
		if(i == length_a) {
			return 1;
		}
	}
	else {
		return 0;
	}
}
