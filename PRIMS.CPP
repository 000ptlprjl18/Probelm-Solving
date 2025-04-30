#include <iostream>
using namespace std;

class gr {
    string city[10]; 
    int adj[10][10]; 
    int v;           

public:
    void accept();
    void sp();
};

void gr::accept() {
    cout << "Enter the number of cities: ";
    cin >> v;

    cout << "Enter the city names:\n";
    for (int i = 0; i < v; i++) {
        cin >> city[i];
    }

    // Initialize adjacency matrix with 0 (no connection)
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            adj[i][j] = 0;
        }
    }

    cout << "Enter adjacency matrix (enter 0 for no connection):\n";
    for (int i = 0; i < v; i++) {
        for (int j = i+1; j < v; j++) { // j = i + 1 to avoid calculating distance with itself
            cout << "Enter the distance from " << city[i] << " to " << city[j] << ": ";
            cin >> adj[i][j];
            adj[j][i] = adj[i][j]; // making it Bidirectional
        }
    }
}

void gr::sp()
 {
    int key[10];//array to store minimum edge weigth
    int parent[10];
    bool visited[10];//marking the node which are already marked up in MST
    int total_weight = 0;

    for (int i = 0; i < v; i++) 
    {
        visited[i] = false;
        key[i] = 999; 
        parent[i] = -1; 
    }

    key[0] = 0; 

    for (int count = 0; count < v - 1; count++) {
        int min = 999, u = -1;// u is keeping the record of index of variable with least value

        for (int i = 0; i < v; i++) 
        {
            if (!visited[i] && key[i] < min) 
            {
                min = key[i];//updating min value
                u = i;//  making u as a next vertex to be visisted
            }
        }

        visited[u] = true;

        for (int j = 0; j < v; j++) {
            if (adj[u][j] && !visited[j] && adj[u][j] < key[j]) {
                parent[j] = u;
                key[j] = adj[u][j];
            }
        }
    }

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (int i = 1; i < v; i++) {
        cout << city[parent[i]] << " - " << city[i] << " : " << key[i] << endl;
        total_weight += key[i];
    }

    cout << "Total MST weight: " << total_weight << endl;
}

int main() {
    gr g;
    int ch;
    while (true) {
        cout << "\n1. Accept\n2. Spanning tree\n3. Exit\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                g.accept();
                break;
            case 2:
                g.sp();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}