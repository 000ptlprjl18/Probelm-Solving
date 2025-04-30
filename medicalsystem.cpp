#include <iostream>
using namespace std;

class MedicalRecord {
public:
    int patientID;
    string patientName;
    string medicalHistory;
    string treatmentPlan;

    MedicalRecord() {
        patientID = -1; // -1 represents empty, -2 will represent deleted
    }
};

class MedicalHash {
    MedicalRecord* table;
    int tableSize;
    int count;

    int hashFunction(int key) {
        return key % tableSize;
    }

    void resizeTable() {
        int oldSize = tableSize;
        tableSize *= 2;
        MedicalRecord* oldTable = table;
        table = new MedicalRecord[tableSize];
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i].patientID != -1 && oldTable[i].patientID != -2) {
                addRecordWithoutPrompt(oldTable[i]);
            }
        }

        delete[] oldTable;
        cout << "Hash table resized to " << tableSize << ".\n";
    }

    void addRecordWithoutPrompt(MedicalRecord record) {
        int index = hashFunction(record.patientID);

        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i * i) % tableSize;
            if (table[probe].patientID == -1 || table[probe].patientID == -2) {
                table[probe] = record;
                count++;
                return;
            }
        }
    }

public:
    MedicalHash() {
        tableSize = 3;
        count = 0;
        table = new MedicalRecord[tableSize];
    }

    void addRecord() {
        if (count == tableSize) {
            resizeTable();
        }

        MedicalRecord record;
        cout << "Enter Patient ID: ";
        cin >> record.patientID;
        cout << "Enter Patient Name: ";
        cin >> record.patientName;
        cout << "Enter Medical History: ";
        cin >> record.medicalHistory;
        cout << "Enter Treatment Plan: ";
        cin >> record.treatmentPlan;

        int index = hashFunction(record.patientID);
        bool inserted = false;

        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i * i) % tableSize;
            if (table[probe].patientID == -1 || table[probe].patientID == -2) {
                table[probe] = record;
                count++;
                if (i == 0)
                    cout << "Record added at index " << probe << ".\n";
                else
                    cout << "Collision! Record added at index " << probe << " using quadratic probing.\n";
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            cout << "Unexpected error. Could not insert.\n";
        }
    }

    void searchRecord() {
        int patientID;
        cout << "Enter Patient ID to search: ";
        cin >> patientID;

        int index = hashFunction(patientID);
        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i * i) % tableSize;
            if (table[probe].patientID == patientID) {
                cout << "\nRecord found at index " << probe << ":\n";
                cout << "Patient ID: " << table[probe].patientID << endl;
                cout << "Name: " << table[probe].patientName << endl;
                cout << "Medical History: " << table[probe].medicalHistory << endl;
                cout << "Treatment Plan: " << table[probe].treatmentPlan << endl;
                return;
            }
            if (table[probe].patientID == -1) break;
        }

        cout << "Record not found.\n";
    }

    void displayRecords() {
        cout << "\n--- Hash Table (Medical Records) ---\n";
        for (int i = 0; i < tableSize; i++) {
            if (table[i].patientID == -1) {
                cout << "Index " << i << ": [Empty]\n";
            } else if (table[i].patientID == -2) {
                cout << "Index " << i << ": [Deleted]\n";
            } else {
                cout << "Index " << i << ": Patient ID: " << table[i].patientID
                     << ", Name: " << table[i].patientName
                     << ", History: " << table[i].medicalHistory
                     << ", Treatment: " << table[i].treatmentPlan << endl;
            }
        }
    }

    void deleteRecord() {
        int patientID;
        cout << "Enter Patient ID to delete: ";
        cin >> patientID;

        int index = hashFunction(patientID);
        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i * i) % tableSize;
            if (table[probe].patientID == patientID) {
                table[probe].patientID = -2; // mark as deleted
                table[probe].patientName = "";
                table[probe].medicalHistory = "";
                table[probe].treatmentPlan = "";
                count--;
                cout << "Record with Patient ID " << patientID << " deleted.\n";
                return;
            }
            if (table[probe].patientID == -1) break;
        }

        cout << "Record not found.\n";
    }

    void updateRecord() {
        int patientID;
        cout << "Enter Patient ID to update: ";
        cin >> patientID;

        int index = hashFunction(patientID);
        for (int i = 0; i < tableSize; i++) {
            int probe = (index + i * i) % tableSize;
            if (table[probe].patientID == patientID) {
                cout << "Record found. Enter new details:\n";
                cout << "Enter New Patient Name: ";
                cin >> table[probe].patientName;
                cout << "Enter New Medical History: ";
                cin >> table[probe].medicalHistory;
                cout << "Enter New Treatment Plan: ";
                cin >> table[probe].treatmentPlan;
                cout << "Record updated successfully.\n";
                return;
            }
            if (table[probe].patientID == -1) break;
        }

        cout << "Record not found.\n";
    }
};

int main() {
    MedicalHash mh;
    int choice;

    while (true) {
        cout << "\n1. Add Record\n2. Search Record\n3. Display Records\n4. Delete Record\n5. Update Record\n6. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: mh.addRecord(); break;
            case 2: mh.searchRecord(); break;
            case 3: mh.displayRecords(); break;
            case 4: mh.deleteRecord(); break;
            case 5: mh.updateRecord(); break;
            case 6: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}
