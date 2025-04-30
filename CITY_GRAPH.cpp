#include <iostream>
#include <limits>

using namespace std;

class Node {
public:
    string city;
    int distance;
    Node* next;

    Node(string cityName, int travelDistance) {
        city = cityName;
        distance = travelDistance;
        next = NULL;
    }
};

class Graph {
private:
    int V;
    string cities[10];   // Array to store city names
    Node* adjlist[10];   // Adjacency list
    int matrix[10][10];  // Adjacency matrix

public:
    Graph(int vertices) {
        V = vertices;
        for (int i = 0; i < V; i++) {
            adjlist[i] = NULL; // Initialize adjacency list with NULL
            cities[i] = "";     // Initialize city names
            for (int j = 0; j < V; j++)
                matrix[i][j] = 0;  // Initialize adjacency matrix with 0
        }
    }

    void addCity(int index, string cityName) {
        if (index >= 0 && index < V) {
            cities[index] = cityName;
        }
    }

    int getCityIndex(string cityName) {
        for (int i = 0; i < V; i++) {
            if (cities[i] == cityName)
                return i;
        }
        return -1;  // City not found
    }

    void addEdgeList(string src, string dest, int distance) {
        int srcIndex = getCityIndex(src);
        int destIndex = getCityIndex(dest);

        if (srcIndex == -1 || destIndex == -1) {
            cout << "Invalid City Name! Ensure cities are entered correctly.\n";
            return;
        }

        Node* newNode = new Node(dest, distance);
        newNode->next = adjlist[srcIndex];
        adjlist[srcIndex] = newNode;

        newNode = new Node(src, distance);
        newNode->next = adjlist[destIndex];
        adjlist[destIndex] = newNode;
    }

    void addEdgeMatrix(string src, string dest, int distance) {
        int srcIndex = getCityIndex(src);
        int destIndex = getCityIndex(dest);

        if (srcIndex == -1 || destIndex == -1) {
            cout << "Invalid City Name! Ensure cities are entered correctly.\n";
            return;
        }

        matrix[srcIndex][destIndex] = distance;
        matrix[destIndex][srcIndex] = distance;
    }

    void displayList() {
        cout << "\nAdjacency List Representation:\n";
        for (int i = 0; i < V; i++) {
            if (cities[i] == "") continue; 
            cout << cities[i] << " -> ";
            Node* temp = adjlist[i];
            while (temp) {
                cout << "(" << temp->city << ", Distance: " << temp->distance << ") -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix Representation (Distance between cities):\n";
        cout << "    ";
        for (int i = 0; i < V; i++)
            cout << cities[i] << "\t";
        cout << "\n";

        for (int i = 0; i < V; i++) {
            cout << cities[i] << "\t";
            for (int j = 0; j < V; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }
};

int main() 
{
    int V, E, choice;
    cout << "Enter the number of cities: ";
    cin >> V;

    if (V > 10) {
        cout << "Maximum 10 cities are allowed!\n";
        return 0;
    }

    Graph gr(V);

    cout << "Enter city names:\n";
    for (int i = 0; i < V; i++) {
        string cityName;
        cin >> cityName;
        gr.addCity(i, cityName);
    }

    cout << "Enter the number of flight paths: ";
    cin >> E;

    if (E > V * (V - 1) / 2) {
        cout << "Too many flight paths! Exceeds possible connections.\n";
        return 0;
    }

    cout << "How do you like to see the Graph Representation?\n1. Adjacency Matrix\n2. Adjacency List\n";
    cin >> choice;

    cout << "Enter " << E << " flight details (City1 City2 Distance):\n";
    for (int i = 0; i < E; i++) {
        string src, dest;
        int distance;
        cin >> src >> dest >> distance;

        if (distance <= 0) {
            cout << "Invalid distance! Enter a positive value.\n";
            return 0;
        }

        if (choice == 1)
            gr.addEdgeMatrix(src, dest, distance);
        else if (choice == 2)
            gr.addEdgeList(src, dest, distance);
        else {
            cout << "Invalid Choice!\n";
            return 0;
        }
    }

    if (choice == 1)
        gr.displayMatrix();
    else
        gr.displayList();

    return 0;
}
