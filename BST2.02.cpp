#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    int id;
    string name;
    float salary;
    Employee* left;
    Employee* right;

    Employee(int empID, string empName, float empSalary) {
        id = empID;
        name = empName;
        salary = empSalary;
        left = right = NULL;
    }
};

// Insert Employee (Sorted by ID)
Employee* insert(Employee* root, int id, string name, float salary) {
    if (root == NULL) {
        return new Employee(id, name, salary);
    }
    if (id < root->id) {
        root->left = insert(root->left, id, name, salary);
    } else {
        root->right = insert(root->right, id, name, salary);
    }
    return root;
}

// Search Employee by ID
Employee* search(Employee* root, int id) {
    if (root == NULL || root->id == id) {
        return root;
    }
    if (id < root->id) {
        return search(root->left, id);
    }
    return search(root->right, id);
}

// Find Minimum Employee by ID
Employee* findMin(Employee* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Find Maximum Employee by ID
Employee* findMax(Employee* root) {
    while (root->right != NULL)
        root = root->right;
    return root;
}

// Delete 
Employee* deleteEmployee(Employee* root, int id) {
    if (root == NULL) return root;

    if (id < root->id) {
        root->left = deleteEmployee(root->left, id);
        cout<<"Id deleted successfully!";
    } else if (id > root->id) {
        root->right = deleteEmployee(root->right, id);
        cout<<"Id deleted successfully!";
    } else {
        // Node with one or no child
        if (root->left == NULL) {
            Employee* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Employee* temp = root->left;
            delete root;
            return temp;
        }
        // Node with two children
        Employee* temp = findMin(root->right);
        root->id = temp->id;
        root->name = temp->name;
        root->salary = temp->salary;
        root->right = deleteEmployee(root->right, temp->id);
    }
    return root;
}

// Update 
Employee* updateEmployee(Employee* root, int id, string newName) {
    Employee* emp = search(root, id);
    if (emp != NULL) {
        emp->name = newName;
    }
    return root;
}

// Inorder Traversal (Sorted Order of Employees)
void inorder(Employee* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "ID: " << root->id << ", Name: " << root->name << ", Salary: " << root->salary << endl;
        inorder(root->right);
    }
}

// Preorder Traversal
void preorder(Employee* root) {
    if (root != NULL) {
        cout << "ID: " << root->id << ", Name: " << root->name << ", Salary: " << root->salary << endl;
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(Employee* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << "ID: " << root->id << ", Name: " << root->name << ", Salary: " << root->salary << endl;
    }
}




// Main Function
int main() {
    Employee* root = NULL;
    int choice, id;
    string name;
    float salary;

    do {
        cout << "\n1. Insert Employee\n2. Search Employee\n3. Delete Employee\n4. Update Employee Name\n5. Inorder Traversal";
        cout << "\n6. Preorder Traversal\n7. Postorder Traversal\n8. Find Min Employee\n9. Find Max Employee";
        cout << "\n10. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID, Name, Salary: ";
                cin >> id;
                cin.ignore();
                getline(cin, name);
                cin >> salary;
                root = insert(root, id, name, salary);
                break;

            case 2:
                cout << "Enter Employee ID to search: ";
                cin >> id;
                if (search(root, id)) cout << "Employee found!\n";
                else cout << "Employee not found!\n";
                break;

            case 3:
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                root = deleteEmployee(root, id);
                break;

            case 4:
                cout << "Enter Employee ID and new Name: ";
                cin >> id;
                cin.ignore();
                getline(cin, name);
                root = updateEmployee(root, id, name);
                break;

            case 5:
                inorder(root);
                break;

            case 6:
                preorder(root);
                break;

            case 7:
                postorder(root);
                break;

            case 8:
                cout << "Minimum Employee ID: " << findMin(root)->id << endl;
                break;

            case 9:
                cout << "Maximum Employee ID: " << findMax(root)->id << endl;
                break;

           
        }
    } while (choice != 10);

    return 0;
}