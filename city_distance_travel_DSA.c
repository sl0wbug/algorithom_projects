#include <stdio.h>      // Include standard input/output library for printf and scanf
#include <stdlib.h>     // Include standard library for general functions
#include <string.h>     // Include string library for string manipulation functions
#include <limits.h>     // Include limits library for integer limits



#define MAX_CITIES 100  // Define a constant for the maximum number of cities
#define INF INT_MAX     // Define a constant for infinity using the maximum integer value
#define COST_PER_KM 3   // Define the cost per kilometer



// Define a structure to represent a route between two cities
typedef struct
{
    char city1[50];    // Name of the first city
    char city2[50];    // Name of the second city
    int distance;      // Distance between the two cities
} Route;



// Function prototypes for the functions used in the program
void mergeSort(Route arr[], int left, int right); // Function to sort routes using merge sort
void merge(Route arr[], int left, int mid, int right); // Function to merge two sorted halves
int knapsack(int cities[], int cost[], int n, int amoung_of_budget); // Function for the knapsack problem
int nearestNeighborHeuristic(int n, int dist[MAX_CITIES][MAX_CITIES], int route[MAX_CITIES]); // TSP heuristic
int getCityIndex(char city[], char cities[MAX_CITIES][50], int n); // Function to get city index



// Merge Sort function to sort routes by distance
void mergeSort(Route arr[], int left, int right)
{
    if (left < right)    // Check if the left index is less than the right index
    {
        int mid = (left + right) / 2;  // Find the middle index
        mergeSort(arr, left, mid);      // Recursively sort the left half
        mergeSort(arr, mid + 1, right); // Recursively sort the right half
        merge(arr, left, mid, right);    // Merge the two halves
    }
}



// Merge function to combine two sorted halves of the array
void merge(Route arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;  // Number of elements in the left half
    int n2 = right - mid;     // Number of elements in the right half

    Route L[n1], R[n2];       // Temporary arrays for left and right halves
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];  // Copy data to the left temporary array
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[mid + 1 + i]; // Copy data to the right temporary array
    }

    int i = 0, j = 0, k = left; // Initialize indices for left, right, and merged arrays
    while (i < n1 && j < n2)    // While there are elements in both halves
    {
        if (L[i].distance < R[j].distance)   // Compare distances
        {
            arr[k] = L[i];  // If left element is smaller, add it to the merged array
            i++;
        }
        else
        {
            arr[k] = R[j];  // Otherwise, add the right element
            j++;
        }
        k++;  // Move to the next position in the merged array
    }

    while (i < n1)    // If there are remaining elements in the left array
    {
        arr[k] = L[i]; // Add them to the merged array
        i++;
        k++;
    }

    while (j < n2)    // If there are remaining elements in the right array
    {
        arr[k] = R[j]; // Add them to the merged array
        j++;
        k++;
    }
}



// Knapsack function to maximize the number of cities visited within a amoung_of_budget
int knapsack(int cities[], int cost[], int n, int amoung_of_budget)
{
    int dp[amoung_of_budget + 1]; // Create a DP array to store maximum cities for each amoung_of_budget
    memset(dp, 0, sizeof(dp)); // Initialize the DP array to 0

    for (int i = 0; i < n; i++)   // Loop through each city
    {
        for (int j = amoung_of_budget; j >= cost[i]; j--)   // Loop through amoung_of_budget from high to low
        {
            // Update the DP array to maximize the number of cities visited
            dp[j] = dp[j] > dp[j - cost[i]] + cities[i] ? dp[j] : dp[j - cost[i]] + cities[i];
        }
    }
    return dp[amoung_of_budget]; // Return the maximum number of cities that can be visited within the amoung_of_budget
}



// Nearest Neighbor Heuristic for TSP Approximation
int nearestNeighborHeuristic(int n, int dist[MAX_CITIES][MAX_CITIES], int route[MAX_CITIES])
{
    int visited[MAX_CITIES] = {0}; // Array to track visited cities
    visited[0] = 1;  // Start from the first city
    int totalDistance = 0, currentCity = 0, count = 1; // Initialize total distance and current city

    route[0] = currentCity; // Set the starting city in the route

    while (count < n)   // While not all cities have been visited
    {
        int nearestCity = -1, minDist = INF; // Initialize nearest city and minimum distance
        for (int i = 0; i < n; i++)   // Loop through all cities
        {
            if (!visited[i] && dist[currentCity][i] < minDist)   // If city is not visited and distance is less than minDist
            {
                minDist = dist[currentCity][i]; // Update minimum distance
                nearestCity = i; // Update nearest city
            }
        }
        route[count++] = nearestCity; // Add nearest city to the route
        visited[nearestCity] = 1; // Mark the nearest city as visited
        totalDistance += minDist; // Add distance to total distance
        currentCity = nearestCity; // Move to the nearest city
    }
    totalDistance += dist[currentCity][0]; // Return to the starting city
    return totalDistance; // Return the total distance of the route
}





// Get the index of the city in the cities array
int getCityIndex(char city[], char cities[MAX_CITIES][50], int n)
{
    for (int i = 0; i < n; i++)   // Loop through the cities
    {
        if (strcmp(cities[i], city) == 0)   // Compare city names
        {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if city is not found
}





int main()
{
    Route routes[MAX_CITIES * MAX_CITIES]; // Array to store routes
    char cities[MAX_CITIES][50]; // Array to store city names
    int n = 0; // Number of routes
    int dist[MAX_CITIES][MAX_CITIES] = {0}; // Distance matrix initialized to 0
    int route[MAX_CITIES]; // Array to store the route



    // User input for number of routes
    printf("Enter the number of routes: ");
    scanf("%d", &n); // Read the number of routes

    // Input for routes (city1, city2, distance)
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter route %d:\n", i + 1); // Prompt for route input
        printf("Enter city 1: ");
        scanf("%s", routes[i].city1); // Read the first city
        printf("Enter city 2: ");
        scanf("%s", routes[i].city2); // Read the second city
        printf("Enter distance (in km): ");
        scanf("%d", &routes[i].distance); // Read the distance
    }

    // Sorting routes by distance (cost)
    mergeSort(routes, 0, n - 1); // Sort the routes using merge sort
    printf("\nSorted Routes by Cost:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s-> %s : %d km\n", routes[i].city1, routes[i].city2, routes[i].distance); // Print sorted routes
    }

    // Set up the cities array for TSP and distance matrix
    int cityIndex = 0; // Initialize city index
    for (int i = 0; i < n; i++)   // Loop through each route
    {
        int index1 = getCityIndex(routes[i].city1, cities, cityIndex); // Get index of city1
        if (index1 == -1)   // If city1 is not found
        {
            strcpy(cities[cityIndex], routes[i].city1); // Add city1 to cities array
            index1 = cityIndex++; // Update index1 and increment cityIndex
        }

        int index2 = getCityIndex(routes[i].city2, cities, cityIndex); // Get index of city2
        if (index2 == -1)   // If city2 is not found
        {
            strcpy(cities[cityIndex], routes[i].city2); // Add city2 to cities array
            index2 = cityIndex++; // Update index2 and increment cityIndex
        }

        dist[index1][index2] = routes[i].distance;

        dist[index1][index2] = routes[i].distance; // Set the distance in the distance matrix for city1 to city2
        dist[index2][index1] = routes[i].distance; // Set the distance in the distance matrix for city2 to city1 (undirected graph)
    }

    // User input for starting city and amoung_of_budget
    char Starting_from[50], destinationCity[50]; // Arrays to hold the names of the starting and destination cities
    int amoung_of_budget; // Variable to hold the user's amoung_of_budget
    printf("\nEnter the starting city: ");
    scanf("%s", Starting_from); // Read the starting city from user input
    printf("Enter the destination city: ");
    scanf("%s", destinationCity); // Read the destination city from user input
    printf("Enter your amoung_of_budget: ");
    scanf("%d", &amoung_of_budget); // Read the amoung_of_budget from user input


    // Knapsack DP to maximize cities to visit within amoung_of_budget
    int Destination[MAX_CITIES]; // Array to hold the number of cities to visit (each city can be visited once)
    int cost[MAX_CITIES]; // Array to hold the cost of visiting each city
    for (int i = 0; i < cityIndex; i++)   // Loop through each city
    {
        Destination[i] = 1; // Each city has 1 possibility (can be visited)
        cost[i] = dist[getCityIndex(Starting_from, cities, cityIndex)][i] * COST_PER_KM; // Calculate the cost of visiting the city from the starting city
    }

    int maxCities = knapsack(Destination, cost, cityIndex, amoung_of_budget); // Call the knapsack function to find the maximum number of cities that can be visited within the amoung_of_budget
    printf("\nMaximum cities you can visit within your amoung_of_budget: %d\n", maxCities); // Print the maximum number of cities that can be visited



    // Find the shortest route using Nearest Neighbor Heuristic
    int totalDistance = nearestNeighborHeuristic(cityIndex, dist, route); // Call the nearest neighbor heuristic to find the total distance of the route
    printf("\nOptimized Travel Plan (Shortest Route Approximation):\n");
    printf("Route: ");
    for (int i = 0; i < cityIndex; i++)   // Loop through the route array
    {
        printf("%s", cities[route[i]]); // Print the city name at the current index in the route
        if (i != cityIndex - 1)   // If not the last city
        {
            printf(" -> "); // Print an arrow to indicate the route
        }
    }
    printf("\nTotal Distance: %d km\n", totalDistance); // Print the total distance of the route
    printf("Total Cost: %d Taka\n", totalDistance * COST_PER_KM); // Print the total cost of the trip based on distance



    // Check if the trip is within the amoung_of_budget
    if (totalDistance * COST_PER_KM <= amoung_of_budget)   // If the total cost is less than or equal to the amoung_of_budget
    {
        printf("Your trip is within the amoung_of_budget.\n"); // Inform the user that the trip is within amoung_of_budget
    }
    else
    {
        printf("Your trip exceeds the amoung_of_budget.\n"); // Inform the user that the trip exceeds the amoung_of_budget
    }



    return 0;
}
