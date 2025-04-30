#include <iostream>
#include <stack>
using namespace std;

class BT {
public:
    int data;
    BT *left, *right;

    BT(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to create the tree (Root Node)
BT* CreateTree() {
    int val;
    cout << "Enter root node value: ";
    cin >> val;
    return new BT(val);
}

// Function to insert nodes in the tree
BT* Insert(BT* root, int val) {
    if (root == NULL) 
        return new BT(val);

    char ch;
    cout << "\nInsert left (l) or right (r) of " << root->data << ": ";
    cin >> ch;

    if (ch == 'l' || ch == 'L')
        root->left = Insert(root->left, val);
    else
        root->right = Insert(root->right, val);

    return root;
}

// Preorder Traversal (Root → Left → Right)
void PreOrder(BT* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

// Inorder Traversal (Left → Root → Right)
void InOrder(BT* root) {
    if (root == NULL) return;
    InOrder(root->left);
    cout << root->data << " ";
    InOrder(root->right);
}

// Postorder Traversal (Left → Right → Root)
void PostOrder(BT* root) {
    if (root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->data << " ";
}

// Function to count total nodes in the tree
int CountNodes(BT* root) {
    if (root == NULL) return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

// Function to display all leaf nodes
void DisplayLeafNodes(BT* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        cout << root->data << " ";
        return;
    }
    DisplayLeafNodes(root->left);
    DisplayLeafNodes(root->right);
}

// Function to calculate the height of the tree
int Height(BT* root) {
    if (root == NULL) return 0;
    return 1 + max(Height(root->left), Height(root->right));
}

// Function to find and print ancestors of a given node
bool FindAncestors(BT* root, int target) {
    if (root == NULL) return false;
    if (root->data == target) return true;

    if (FindAncestors(root->left, target) || FindAncestors(root->right, target)) {
        cout << root->data << " ";
        return true;
    }
    return false;
}

// Iterative Preorder Traversal (Using Stack)
void IterativePreOrder(BT* root) {
    if (root == NULL) return;

    stack<BT*> s;
    s.push(root);

    while (!s.empty()) {
        BT* temp = s.top();
        s.pop();
        cout << temp->data << " ";

        if (temp->right) s.push(temp->right);
        if (temp->left) s.push(temp->left);
    }
}

// Iterative Inorder Traversal (Using Stack)
void IterativeInOrder(BT* root) {
    stack<BT*> s;
    BT* curr = root;

    while (curr != NULL || !s.empty()) {
        while (curr != NULL) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

// Iterative Postorder Traversal (Using Two Stacks)
void IterativePostOrder(BT* root) {
    if (root == NULL) return;

    stack<BT*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        BT* temp = s1.top();
        s1.pop();
        s2.push(temp);

        if (temp->left) s1.push(temp->left);
        if (temp->right) s1.push(temp->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// Main Function
int main() {
    BT *root = NULL;
    int choice, val, target;

    do {
        cout << "\n1. Create Tree\n2. Insert Node\n3. Preorder Display\n4. Inorder Display\n5. Postorder Display";
        cout << "\n6. Count Total Nodes\n7. Display Leaf Nodes\n8. Height of Tree\n9. Find Ancestors";
        cout << "\n10. Iterative Preorder\n11. Iterative Inorder\n12. Iterative Postorder";
        cout << "\n13. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (root == NULL)
                root = CreateTree();
            else
                cout << "\nRoot already exists!";
            break;

        case 2:
            if (root == NULL)
                cout << "\nCreate root first!";
            else {
                cout << "\nEnter node value: ";
                cin >> val;
                Insert(root, val);
            }
            break;

        case 3:
            cout << "\nPreorder Traversal: ";
            PreOrder(root);
            cout << endl;
            break;

        case 4:
            cout << "\nInorder Traversal: ";
            InOrder(root);
            cout << endl; 
            break;

        case 5:
            cout << "\nPostorder Traversal: ";
            PostOrder(root);
            cout << endl;
            break;

        case 6:
            cout << "\nTotal Nodes: " << CountNodes(root) << endl;
            break;

        case 7:
            cout << "\nLeaf Nodes: ";
            DisplayLeafNodes(root);
            cout << endl;
            break;

        case 8:
            cout << "\nHeight of Tree: " << Height(root) << endl;
            break;

        case 9:
            cout << "\nEnter node value to find ancestors: ";
            cin >> target;
            cout << "Ancestors: ";
            if (!FindAncestors(root, target))
                cout << "No ancestors found!";
            cout << endl;
            break;

        case 10:
            cout << "\nIterative Preorder Traversal: ";
            IterativePreOrder(root);
            cout << endl;
            break;

        case 11:
            cout << "\nIterative Inorder Traversal: ";
            IterativeInOrder(root);
            cout << endl;
            break;

        case 12:
            cout << "\nIterative Postorder Traversal: ";
            IterativePostOrder(root);
            cout << endl;
            break;

        case 13:
            cout << "\nExiting program!";
            break;

        default:
            cout << "\nInvalid choice!";
        }
    } while (choice != 13);

    return 0;
}
