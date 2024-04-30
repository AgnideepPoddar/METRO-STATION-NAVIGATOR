#include <iostream>
#include <string>
#include <limits> // for numeric_limits
#include <climits>
#include <iomanip> // for setw
#include <ctime>   // for time and localtime
using namespace std;

#define INF 999

// ANSI escape codes for text color
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

// Define the number of stations
const int NUM_STATIONS = 5;

// Array to store station names
string stations[NUM_STATIONS] = {"Central", "Park", "Market", "Square", "Station"};

// Function to find the minimum distance vertex
int mindistance(int distance[], bool stat[], int n)
{
    int minimum = INT_MAX, ind;

    for (int k = 0; k < n; k++)
    {
        if (!stat[k] && distance[k] <= minimum)
        {
            minimum = distance[k];
            ind = k;
        }
    }

    return ind;
}

// Function to perform Dijkstra's algorithm
void dijkstra(int graph[NUM_STATIONS][NUM_STATIONS], int source, int destination, int n)
{
    int distance[NUM_STATIONS];
    bool stat[NUM_STATIONS];

    for (int k = 0; k < n; k++)
    {
        distance[k] = INT_MAX;
        stat[k] = false;
    }

    distance[source] = 0;

    for (int k = 0; k < n - 1; k++)
    {
        int m = mindistance(distance, stat, n);
        stat[m] = true;

        for (int k = 0; k < n; k++)
        {
            if (!stat[k] && graph[m][k] && distance[m] != INT_MAX && distance[m] + graph[m][k] < distance[k])
                distance[k] = distance[m] + graph[m][k];
        }
    }

    cout << CYAN << "\nShortest Path from " << stations[source] << " to " << stations[destination] << "\n"
         << RESET;

    cout << GREEN << "Shortest Distance: " << distance[destination] << " stations\n"
         << RESET;

    cout << "Route: ";
    int current = destination;
    cout << stations[current];
    while (current != source)
    {
        for (int i = 0; i < n; ++i)
        {
            if (graph[i][current] > 0 && distance[current] == distance[i] + graph[i][current])
            {
                cout << " <- " << stations[i];
                current = i;
                break;
            }
        }
    }
    cout << endl;

    cout << "Alternative routes:\n";
    for (int i = 0; i < n; i++)
    {
        if (distance[i] != INT_MAX)
        {
            cout << "From " << stations[source] << " to " << stations[destination] << " via " << stations[i] << ": " << distance[i] << " stations\n";
        }
    }
}

// Function to generate a ticket for the journey
void generateTicket(int source, int destination)
{
    cout << "\n****************\n";
    cout << YELLOW << "*               TICKET                   *\n";
    cout << "**************\n";
    cout << GREEN << "* Source: " << setw(20) << left << stations[source] << "*\n";
    cout << BLUE << "* Destination: " << setw(15) << left << stations[destination] << "*\n";

    // Get current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << MAGENTA << "* Date & Time: " << setw(16) << left << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << 1900 + ltm->tm_year;
    cout << setw(4) << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "*\n";
    
    cout << "**************\n";
}

// Function to list available stations
void listStations()
{
    cout << CYAN << "\nAvailable Stations:\n"
         << RESET;
    for (int i = 0; i < NUM_STATIONS; ++i)
    {
        cout << MAGENTA << i + 1 << ". " << stations[i] << endl;
    }
}

int main()
{
    int graph[NUM_STATIONS][NUM_STATIONS];

    // Initialize the adjacency matrix
    cout << "Enter the adjacency matrix for the graph (enter 0 for no connection):\n";
    for (int i = 0; i < NUM_STATIONS; ++i)
    {
        for (int j = 0; j < NUM_STATIONS; ++j)
        {
            cout << "Is there a connection from station " << stations[i] << " to station " << stations[j] << "? (1 for Yes, 0 for No): ";
            cin >> graph[i][j];
        }
    }

    int choice;
    do
    {
        cout << "\nChoose an option:\n";
        cout << YELLOW << "1. Find Shortest Path between Stations\n";
        cout << BLUE << "2. List Available Stations\n";
        cout << MAGENTA << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string source, destination;
            bool validInput = false;
            int sourceIndex, destIndex;

            // Input validation for source station
            do
            {
                cout << "\nEnter source station: ";
                cin >> source;
                for (int i = 0; i < NUM_STATIONS; ++i)
                {
                    if (source == stations[i])
                    {
                        sourceIndex = i;
                        validInput = true;
                        break;
                    }
                }
                if (!validInput)
                {
                    cout << RED << "Invalid station name! Please enter a valid station.\n"
                         << RESET;
                }
            } while (!validInput);

            // Reset validInput flag for destination station
            validInput = false;

            // Input validation for destination station
            do
            {
                cout << "Enter destination station: ";
                cin >> destination;
                for (int i = 0; i < NUM_STATIONS; ++i)
                {
                    if (destination == stations[i])
                    {
                        destIndex = i;
                        validInput = true;
                        break;
                    }
                }
                if (!validInput)
                {
                    cout << RED << "Invalid station name! Please enter a valid station.\n"
                         << RESET;
                }
            } while (!validInput);

            dijkstra(graph, sourceIndex, destIndex, NUM_STATIONS);
            generateTicket(sourceIndex, destIndex);
            break;
        }
        case 2:
        {
            listStations();
            break;
        }
        case 3:
        {
            cout << "Exiting...\n";
            break;
        }
        default:
            cout << RED << "Invalid choice! Please try again.\n" << RESET;
        }
    } while (choice != 3);

    return 0;
}