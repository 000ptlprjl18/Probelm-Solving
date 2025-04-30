#include <iostream>

using namespace std;

class gr {
    string city[10]; 
    int adj[10][10]; 
    int v;           

public:
    void accept();
    void dijkstra();
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
        for (int j = i + 1; j < v; j++) {
            cout << "Enter the distance from " << city[i] << " to " << city[j] << ": ";
            cin >> adj[i][j];
            adj[j][i] = adj[i][j]; // making it Bidirectional
        }
    }
}

void gr::dijkstra() {
    int src;
    cout << "Enter the source city index (0 to " << v - 1 << "): ";
    cin >> src;
    
    int dist[10]; 
    bool visited[10] = {false}; 
    
    for (int i = 0; i < v; i++) {
        dist[i] = 999;
    }
    dist[src] = 0;

    for (int count = 0; count < v - 1; count++) {
        int minDist = 999, u = -1;
        
        for (int i = 0; i < v; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        visited[u] = true;

        for (int j = 0; j < v; j++) {
            if (!visited[j] && adj[u][j] && dist[u] != 999 && dist[u] + adj[u][j] < dist[j]) {
                dist[j] = dist[u] + adj[u][j];
            }
        }
    }

    cout << "\nShortest distances from " << city[src] << ":\n";
    for (int i = 0; i < v; i++) {
        cout << city[src] << " -> " << city[i] << " : " << dist[i] << endl;
    }
}

int main() {
    gr g;
    int ch;
    while (true) {
        cout << "\n1. Accept\n2. Dijkstra's Algorithm\n3. Exit\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                g.accept();
                break;
            case 2:
                g.dijkstra();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }
    }
    return 0;
}