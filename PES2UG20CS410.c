#include<stdlib.h>
#include<limits.h>
#include "header.h"
#include<stdio.h>
// ANY STATIC FUNCTIONS ARE UP HERE
//Used in Q7
//This function is used to find the length pf the string passed as an argurement. It returns the total count of characters in a string.
static int string_length(const char s[]){
	int counter=0,i=0;
	while(s[i]!='\0'){
		counter++;
		i++;
	}
	return counter;
}
//Used in Q7
//creates a shift table for the pattern specified
static void shifttable(const char p[], int t[]) {
	int i,j,m,pattern;
	m=string_length(p);
	for (i=0;i<256;i++)
	  t[i]=m;
	for (j=0;j<m-1;j++){
	  pattern = p[j];
	  t[pattern]=m-1-j;
	  }

	  
}

//implementation of horsepool's algorithm
static int horsepool(const char src[],const char p[], int t[]) {
	int i,k,m,n,source;
	n=string_length(src);
	m=string_length(p);
	i=m-1;
	while(i<n) {
		k=0;
		while((k<m)&&(p[m-1-k]==src[i-k]))
		   k++;
		if(k==m)
		   return(1); 
		else{
		   source = src[i];
		   i+=t[source];
		   }
	}
	return 0;
}
//used in ques1
//appends an element in the queue
static void append(int *queue, int v, int *pqr) {
    ++(*pqr);
    queue[*pqr] = v;
}
//used in ques1
//delete an element from the queue
static int delete(int *queue, int *pqr) {
    int res = queue[0];

    for (int i = 0; i < *pqr; ++i) {
        queue[i] = queue[i + 1];
    }
    --(*pqr);
    return res;
}
//used in ques3
//check the visited array if we can reach from src to dest and back to src
static void helperq3(int n ,const connection_t connections[n][n], int *visited , int src) 
{
    visited[src] = 1;
    for (int i = 0; i < n; ++i) {
        if (connections[src][i].distance!=0 && connections[src][i].distance != INT_MAX && visited[i] == 0) {
            helperq3(n,connections,visited,i);
        }
    }
}
//used in ques1
//BFS traversal to traverse the array with every vertex as the source 
static int bfs_cycle(int n, const connection_t connections[n][n]) {
    int *visited, *queue, qr = -1;

    visited = (int *) calloc(n, sizeof(int));
    queue = (int *) calloc(n, sizeof(int));

    for (int start = 0; start < n; ++start) {

        for (int i = 0; i < n; ++i) {
            visited[i] = 0;
        }

        append(queue, start, &qr);
        visited[start] = 1;

        int vertex;

        while (qr != -1) {

            vertex = delete(queue, &qr);

            for (int i = 0; i < n; ++i) {
            int cond = connections[vertex][i].distance;
                if (cond !=INT_MAX && !visited[i]) {
                    visited[i] = 1;
                    append(queue, i, &qr);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                free(visited);
                free(queue);
                return 0;
            }
        }
    }
    free(visited);
    free(queue);
    return 1;
}
//used for ques10
//we use floyd algorithm to creratest the shortest time matrix and then get the required values
static void floydWarshall (int n, const connection_t connections[n][n], int dist[n][n])
{
	int i, j, k;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			dist[i][j] = connections[i][j].time;
			}
			}
		for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				if(dist[i][j]==INT_MAX){
					dist[i][j]=9999999;
				}		
			}
		}

	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];

				
			}
		}
	}
}
//used for ques2
//use dfs traversal to get the maximum fligths reqd to move from src to dest
static void q2_dfs (int x ,  int dest , int vis[] , int n , const connection_t graph[n][n] ,int num , int *ans)
{
    vis[x] = 1;
    if (x == dest)
    {        
        int max = 0;
        for (int i  = 0 ; i < n ; i++)
        {
            if (vis[i] == 1)
            {
                max++;
            }
        }
        if (max <= num+1)
        {
            *ans = 1;
        }
    }
    for(int i = x ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if (graph[i][j].distance != INT_MAX && vis[j]!= 1)
            {
               q2_dfs(j , dest, vis , n , graph , num , ans);
            }
        }
    }
}
//used for ques4
//used to swap two elements using a temporary variable
static void swap(airport_t *x, airport_t *y)
{
    airport_t temp = *x;
    *x = *y;
    *y = temp;
}
//used for q4
//helper function for quicksort
static int partition(airport_t airport_list[], int start, int end,int (*predicate_func)(const airport_t *, const airport_t *))
{
    int pIndex = start;
    airport_t pivot = airport_list[end];
    int i;
    for(i = start; i < end; i++)
    {
        if(predicate_func(&airport_list[i] , &pivot))
        {
            swap(&airport_list[i], &airport_list[pIndex]);
            pIndex++;
        }
    }
    swap(&airport_list[end], &airport_list[pIndex]);
    return pIndex;
}
//used for ques4
//used the quicksort algorithm to sort the array given according to the predicate func with average case time efficiency nlogn
static void quickSort(airport_t arr[], int start, int end,int (*predicate_func)(const airport_t *, const airport_t *) )
{
    if(start < end)
    {
        int pIndex = partition(arr, start, end,predicate_func);
        quickSort(arr, start, pIndex-1,predicate_func);
        quickSort(arr, pIndex+1, end,predicate_func);
    }
}
//used for ques5
//gives the length of string until characters are matched in two different strings
static int len(airport_t airport1,airport_t airport2)
{
    int i=0;
    while(airport1.airport_name[i]!='\0' && airport2.airport_name[i]!='\0' && airport1.airport_name[i] == airport2.airport_name[i])
    {
        i++;
    }
    return i;
}
//used for ques8
//helper function for ques8 where we return the occurences of n in the selected array
static int q8helper(int n,int select[n])
{
    int i,count=0;
    for(i=0;i<n;i++)
    {
        if(select[i]==1)
            count++;
    }
    return count;
}
//used for ques8
static void ques8(int n, int trip_order[n - 1], int temp[n-1],const connection_t connections[n][n], int select[n],int *totalcost,int src, int src_temp, int index,int *min)
{
    int i;
    int value;
    select[src] = 1;
    

    for(i=0;i<n;i++)
    {
        if(q8helper(n,select) == n-1)
        {
            int temp_value = connections[src][src_temp].distance;
            if(temp_value != INT_MAX)
            {
                temp[index] = src;
                *totalcost += temp_value;
                
                if(*totalcost <= *min)
                {
                    *min = *totalcost;
                    for(int j=0;j<n-1;j++){
                            trip_order[j] = temp[j];
                    }
                    
                        
                }                
            }
            else
                temp_value = 0;

            *totalcost-= temp_value;
            i = n;

        }

        else if(connections[src][i].distance !=0 && connections[src][i].distance != INT_MAX && select[i]==0) 
        {
            value = connections[src][i].distance;
            temp[index++] = src;    
            *totalcost+=value;     
            ques8(n,trip_order,temp,connections,select, totalcost,i,src_temp, index, min);
            *totalcost -= value;
            index--;
        }
        
    }
      
    select[src] = 0;
    
}
// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n])
{
   int ans;
   if(n>=1 && n<=1000){
   ans = bfs_cycle(n, connections);
   return ans;
   }
   else{
   return 0;
   }
   
    
}

int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])
{
	if((n>=1 && n<=1000)&&(k>=1 && k<=n))
	{
		int visited[1000];
	    	int source_val = src->num_id;
	    	int dest_val = dest->num_id;
	    	int ans = 0;
	    	for(int i = 0 ; i < n ; i++)
		    {
			visited[i] = 0;
		    }
		q2_dfs(source_val, dest_val, visited, n, connections, k, &ans);
		if(ans == 1)
		    {
			return 1;
		    }
		else
		    {
			return 0;
		    }
	 }
         return 0;
}

int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    if(n>=1 && n<=1000){
    int visited[n];
    int i;
    for(i=0;i<n;i++)
        visited[i] = 0;

    helperq3(n,connections,visited, src->num_id);
    
    return visited[src->num_id];
    }
    return -1;
}
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
	if(n>=1 && n<=1000000){
		quickSort(airport_list,0,n-1,predicate_func);
		}
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    if(n>=1 && n<=100000){
    int maximum = 0;
    int x;
    for(int i=0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            x = len(airports[i],airports[j]);
            if(maximum < x)
            {
                maximum = x;
                ans.first = airports[i].num_id;
                ans.second = airports[j].num_id;
            }
        }
    }
    }
return ans;    
}
//use Binary search to satisfy the given condition so that the time complexity is lower than that of brute force approach
int q6(int n, int amount, const int entry_fee[n])
{
	int start = 0;
	if(n>=1 && n<1000000){
		int end = n-1;
		int mid;
		while(start<=end)
		{
			mid = start+(end-start)/2;
			if(entry_fee[mid]==amount){
				return mid+1;
			}
			else if(entry_fee[mid]<amount){
				start = mid+1;
			}
			else{
				end = mid-1;
			}
		}
		return start;	
	}
	return -1;
}

//create a shifttable and then use it in Horsepool's algorithm to find if a string contains the pattern 
void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
	int len_pat = string_length(pat);
	if((n>=1 && n<=1000)&&(len_pat>=1 && len_pat<=100000)){
	const char *src;
	int t[256];
	shifttable(pat,t);
	for(int i=0;i<n;i++){
		int len_text = string_length(airports[i].airport_name);
		if(len_text>=1 && len_text<=100000){
		src = airports[i].airport_name;
		shifttable(pat,t);
		contains[i] = horsepool(src,pat,t);
		}
		}

	}
}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    if(n>=1 && n<=7){
	    int select[n];
	    int lowest = INT_MAX, min = INT_MAX,i,j,index=0,totalcost=0;
	    int temp[n-1];

	    for(i=0;i<n;i++)
	    {
		for(j=0;j<n;j++)
		    select[j] = 0;

		ques8(n,trip_order,temp,connections,select,&totalcost,i,i,index,&min);

		if(min < lowest)
		    lowest = min;
	    
		totalcost = 0;
	    }  
	    if(min == INT_MAX)
	    {
		lowest = -1;
		for(i=0;i<n-1;i++)
		    trip_order[i] = -1;
	    }
	    

	    return lowest;
	    }
	return 0;
}
//for this question, we implement Prim's Algorithm to find the minimum spanning tree for the given graph. This returns all the connections reqd so that every vertex is in the graph with minimum time possible
int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{

    if (n>=1 && n<=1000){
    int a, b, u, v, i, j, ne = 1,count=0;
	int visited[1000] = {0}, min, mincost = 0, cost[n+1][n+1];
    for(i=0;i<=n;i++)
    	for(j=0;j<=n;j++)
    		cost[i][j]=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if (connections[i][j].time == INT_MAX)
                cost[i+1][j+1] = 999;
            else
                cost[i+1][j+1] = connections[i][j].time;
            
        }
    }
	visited[1] = 1;
	while (ne < n)
	{
		for (i = 1, min = 999; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (cost[i][j] < min)
					if (visited[i] != 0)
					{
						min = cost[i][j];
						a = u = i;
						b = v = j;
					}
		if (visited[u] == 0 || visited[v] == 0)
		{
			edges[count].first=a-1;
            edges[count].second=b-1;
            count++;
            ne++;
			mincost += min;
			visited[b] = 1;
		}
		cost[a][b] = cost[b][a] = 999;
	}
    return mincost;
}
return -1;
}

//use floyd's algorithm to determine the shortest time matrix
void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
	if((n>=1 && n<1000) && (k>=1 && k<=n)){
        int distance[n][n];
        int destination;
        int source = src[0].num_id;
        floydWarshall(n, connections, distance);
        for(int i=0; i<k; i++){
        	destination = destinations[i];
        	//printf("\n%d\n", destination);
             	costs[i] = distance[source][destination];
        
        }
        }
}

// END
