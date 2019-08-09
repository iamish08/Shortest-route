/*** C Program to calculate shortest route and distance between two cities
 ** @date Nov 1, 2017
 **
 **/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define MAX 22

int z;                                                  // declaring a global variable
void relax(int);                                        // declaring fuctions
int graphCall(int, int);
int updater(int, int);
void pathPrinter(int, int);
int dist[22];                                           //array storing the shortest path from source to every node
bool visited[22];                                        //array for checking if every node is visited or not
int throughCity[22];
int main()
{
    int source, destination;
    char city[22][22]={"Srinagar","Chandigarh","Delhi","Jaipur","Agra","Kanpur","Gorakhpur","Patna","Guwahati","Ahmedabad","Bhopal","Ranchi","Kolkata",
    "Mumbai","Nagpur","Hyderabad","goa","Bangalore","Chennai","Mysuru","Coimbatore","Kanyakumari"};
    int i;
    printf("citites are:\n");
    for(i=0;i<22;i++)
    {
        printf("City code-%d %s\t",i+1,city[i]);
    }
    for(i = 0; i < MAX; i++){
            if(i % 5 ==0)
                printf("\n");
    }

    printf("Enter your starting city\n");
    scanf("%d", &source);                               //source city
    source--;
    printf("Enter the destination\n");                  //destination
    destination--;
    scanf("%d", &destination);
    destination--;
    printf("The shortest route between source and destination is %d km\n\n", updater(source, destination));
    printf("\n");
    /*for(int i=0;i<MAX;i++) {
        printf("%d \t %d\n",i+1,throughCity[i]+1);
    }*/
    pathPrinter(source, destination);
    return 0;

}
int graphCall(int x, int y){                            //returns the distance between two cities
    int distance;
    int graph[22][22] =  {{ 10000 ,563   ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  563   ,10000 ,245   ,10000, 10000, 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,245   ,10000 ,282   ,233  , 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,282   ,10000 ,238  , 10000, 10000, 10000 ,10000, 655  , 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,233   ,238   ,10000, 277  , 10000, 10000 ,10000, 10000, 553, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,277  , 10000, 364  , 10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 364  , 10000, 264   ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 264  , 10000 ,938  , 10000, 10000, 318  , 580  , 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 938   ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,655   ,10000, 10000, 10000, 10000 ,10000, 10000, 583  , 10000, 10000, 524  , 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,553  , 10000, 10000, 10000 ,10000, 583  , 10000, 10000, 10000, 776  , 351  , 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
		                 {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 318   ,10000, 10000, 10000, 10000, 373  , 10000, 833  , 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 580   ,10000, 10000, 10000, 373  , 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 524  , 776  , 10000, 10000, 10000, 10000, 707  , 584  , 980  , 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 10000, 351  , 833  , 10000, 10000, 10000, 501  , 10000, 10000, 10000, 10000, 10000, 10000 },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 707  , 501  , 10000, 10000, 569  , 628  , 10000, 10000, 10000 },
		                 {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 584  , 10000, 10000, 10000, 558  , 10000, 10000, 10000, 10000 },
		                 {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 980  , 10000, 569  , 558  , 10000, 327  , 144  , 313  , 10000 },
		                 {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 628  , 10000, 327  , 10000, 10000, 510  , 10000 },
		                 {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 144  , 10000, 10000, 10000, 10000 },
		                 {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 313  , 510  , 10000, 10000, 436   },
                         {  10000 ,10000 ,10000 ,10000 ,10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 436  , 10000 }};
    //storing a graph using adjecency matrix
    distance = graph[x][y];
    return(distance);
}

void relax(int u){                                                  // find the shortest path in each call
    int i;
    /*printf("Called for %d\n\n",u+1);*/
    for(i = 0; i < MAX; i++){
        if(graphCall(u, i) != 10000){
            if(dist[i] > dist[u] + graphCall(u, i)) {
                dist[i] = dist[u] + graphCall(u, i);
                throughCity[i] = u;
                /*printf("Changed %d for\t %d\n", i+1, u+1);*/
            }
        }
    }

}
void pathPrinter(int source, int destination){                    //fuction to print the shortest path
    int i, j = 0, k;
    i = destination;
    printf("%d --<\t",i+1);
    while(i != source){

        printf("%d --<< ",throughCity[i]+1);
        if(i == throughCity[i]){
            break;
        }
        i = throughCity[i];
        j++;
    }

}



int updater(int source, int destination) {                           //sets the no. of calls to relax
    int i, j, min;
    z = 0;

    for(i = 0; i< MAX; i++) {                                        //initializing  the dist array
        dist[i]= 10000;
    }
    dist[source]= 0;
                                                                     //initializing the visited array
    for(i = 0; i < MAX; i++) {
       visited[i] = false;
    }

   while(z < MAX) {
        min = 10000;
        for(i = 0; i < MAX; i++) {
            if(dist[i] < min && visited[i] == false) {               //extracting minimum value from array which is not yet called by relax
                min = dist[i];
                j = i;
            }
        }

        relax(j);
        visited[j] = true;

        z++;
    }

    return (dist[destination]);                                     //returning the required distance
}
