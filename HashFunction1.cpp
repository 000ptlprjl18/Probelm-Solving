#include <iostream>
using namespace std;

class Node {
public:
    int id;
    string name, album, artist;

    Node() {
        id = -1; // -1 represents empty, -2 will represent deleted
    }
};

class MusicHash {
    Node* table;
    int tableSize;
    int count;

    int hashFunction(int key) {
        return key % tableSize;
    }

    void resizeTable() {
        int oldSize = tableSize;
        tableSize *= 2;
        Node* oldTable = table;
        table = new Node[tableSize];
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i].id != -1 && oldTable[i].id != -2) {
                insertWithoutPrompt(oldTable[i]);
            }
        }

        delete[] oldTable;
        cout << "Hash table resized to " << tableSize << ".\n";
    }

    void insertWithoutPrompt(Node track) {
        int index = hashFunction(track.id);

        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i) % tableSize;
            if (table[probe].id == -1 || table[probe].id == -2) {
                table[probe] = track;
                count++;
                return;
            }
        }
    }

public:
    MusicHash() {
        tableSize = 3;
        count = 0;
        table = new Node[tableSize];
    }

    void addTrack() {
        if (count == tableSize) {
            resizeTable();
        }

        Node track;
        cout << "Enter Track ID: ";
        cin >> track.id;
        cout << "Enter Track Name: ";
        cin >> track.name;
        cout << "Enter Album Name: ";
        cin >> track.album;
        cout << "Enter Artist Name: ";
        cin >> track.artist;

        int index = hashFunction(track.id);
        bool inserted = false;

        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i) % tableSize;
            if (table[probe].id == -1 || table[probe].id == -2) {
                table[probe] = track;
                count++;
                if (i == 0)
                    cout << "Track added at index " << probe << ".\n";
                else
                    cout << "Collision! Track added at index " << probe << " using linear probing.\n";
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            cout << "Unexpected error. Could not insert.\n";
        }
    }

    void searchTrack() {
        int id;
        cout << "Enter Track ID to search: ";
        cin >> id;

        int index = hashFunction(id);
        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i) % tableSize;
            if (table[probe].id == id) {
                cout << "\nTrack found at index " << probe << ":\n";
                cout << "Track ID: " << table[probe].id << endl;
                cout << "Track Name: " << table[probe].name << endl;
                cout << "Album Name: " << table[probe].album << endl;
                cout << "Artist: " << table[probe].artist << endl;
                return;
            }
            if (table[probe].id == -1) break;
        }

        cout << "Track not found.\n";
    }

    void displayTracks() {
        cout << "\n--- Hash Table Contents ---\n";
        for (int i = 0; i < tableSize; i++) {
            if (table[i].id == -1) {
                cout << "Index " << i << ": [Empty]\n";
            } else if (table[i].id == -2) {
                cout << "Index " << i << ": [Deleted]\n";
            } else {
                cout << "Index " << i << ": Track ID: " << table[i].id
                     << ", Name: " << table[i].name
                     << ", Album: " << table[i].album
                     << ", Artist: " << table[i].artist << endl;
            }
        }
    }

    void deleteTrack() {
        int id;
        cout << "Enter Track ID to delete: ";
        cin >> id;

        int index = hashFunction(id);
        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i) % tableSize;
            if (table[probe].id == id) {
                table[probe].id = -2; // mark as deleted
                table[probe].name = "";
                table[probe].album = "";
                table[probe].artist = "";
                count--;
                cout << "Track with ID " << id << " deleted.\n";
                return;
            }
            if (table[probe].id == -1) break;
        }

        cout << "Track not found.\n";
    }

    void updateTrack() {
        int id;
        cout << "Enter Track ID to update: ";
        cin >> id;

        int index = hashFunction(id);
        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i) % tableSize;
            if (table[probe].id == id) {
                cout << "Track found. Enter new details:\n";
                cout << "Enter New Track Name: ";
                cin >> table[probe].name;
                cout << "Enter New Album Name: ";
                cin >> table[probe].album;
                cout << "Enter New Artist Name: ";
                cin >> table[probe].artist;
                cout << "Track updated successfully.\n";
                return;
            }
            if (table[probe].id == -1) break;
        }

        cout << "Track not found.\n";
    }
};

int main() {
    MusicHash mh;
    int choice;

    while (true) {
        cout << "\n1. Add Track\n2. Search Track\n3. Display Tracks\n4. Delete Track\n5. Update Track\n6. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: mh.addTrack(); break;
            case 2: mh.searchTrack(); break;
            case 3: mh.displayTracks(); break;
            case 4: mh.deleteTrack(); break;
            case 5: mh.updateTrack(); break;
            case 6: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}
