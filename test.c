
#include <limits.h>
//#include <stdbool.h>
#include <stdio.h>

struct airport
{
    int num_id;
    const char *airport_name;
};
typedef struct airport airport_t;

/*
 * The connection represents the details of an edge in the connection graph.
 * graph[i][j] will be a connection structure containg the time and distance
 * from airport with id=i to airport with id=j.
 */
struct connection
{
    int distance;
    int time;
};
typedef struct connection connection_t;

struct pair
{
    int first;
    int second;
};
typedef struct pair pair_t;
// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int n,int key[], int mstSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < n; v++)
		if (mstSet[v] == 0 && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]


int primMST(int n, pair_t edges[n - 1], connection_t connections[n][n])
{
	// Array to store constructed MST
	int parent[n];
	int minimumtime = 0;
	// Key values used to pick minimum weight edge in cut
	int key[n];
	// To represent set of vertices included in MST
	int mstSet[n];

	// Initialize all keys as INFINITE
	for (int i = 0; i < n; i++){
		key[i] = INT_MAX;
		mstSet[i] = 0;}

	key[0] = 0;
	parent[0] = -1; 

	for (int count = 0; count < n - 1; count++) {
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(n,key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = 1;
		for (int v = 0; v < n; v++)
			if (connections[u][v].time && mstSet[v] == 0 && connections[u][v].time < key[v])
				parent[v] = u, key[v] = connections[u][v].time;
	}

	for (int i = 1; i < n; i++){
		minimumtime += connections[i][parent[i]].time;
		edges[i].first = parent[i];
		edges[i].second = i;}
		for (int i = 1; i <n; i++){
		printf("%d \t %d\n", edges[i].first, edges[i].second);
		}
printf("%d", minimumtime);


	return minimumtime;
}
int q9(int n, pair_t edges[n-1], connection_t connections[n][n]){
	primMST(n, edges, connections);
}
// driver program to test above function
int main()
{
            // Q9
        connection_t q9_t1_connections[4][4] = {
            {{0, 0}, {1, 2}, {2, 6}, {INT_MAX, INT_MAX}},
            {{1, 2}, {0, 0}, {3, 5}, {4, 1}},
            {{2, 6}, {3, 5}, {0, 0}, {5, 7}},
            {{INT_MAX, INT_MAX}, {4, 1}, {5, 7}, {0, 0}}};

        int n = 4;

        pair_t edges[3] = {{-1, -1}, {-1, -1}, {-1, -1}};
        int result = q9(n, edges, q9_t1_connections);

    
	

	return 0;
}

