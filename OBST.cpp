#include<iostream>
using namespace std;

class Obst {
public:
    int key[10];
    int success_prob[10];
    int unsuccess_prob[10];
    int w[10][10];
    int c[10][10];
    int r[10][10];
    int k;

    Obst() {
        k = 0;
    }

    void getKey() {
        cout << "Enter number of keys: ";
        cin >> k;
        for (int i = 1; i <= k; i++) {
            cout << "Enter key " << i << ": ";
            cin >> key[i];
            cout << "Enter successful probability of key " << key[i] << ": ";
            cin >> success_prob[i];
        }
        for (int i = 0; i <= k; i++) {
            cout << "Enter unsuccessful probability for index " << i << ": ";
            cin >> unsuccess_prob[i];
        }
    }

    void computeObst() {
        int n = k + 1;

        // Initialization of w[i][i], c[i][i], and r[i][i]
        for (int i = 0; i < n; i++) {
            w[i][i] = unsuccess_prob[i];
            c[i][i] = 0;
            r[i][i] = 0;

            cout << "[i=" << i << ", j=" << i << "] ";
            cout << "w[" << i << "][" << i << "] = " << w[i][i] << "\t";
            cout << "r[" << i << "][" << i << "] = " << r[i][i] << "\t";
            cout << "c[" << i << "][" << i << "] = " << c[i][i] << "\n";
        }

        // OBST calculation using dynamic programming
        for (int length = 1; length < n; length++) {
            for (int i = 0; i < n - length; i++) {
                int j = i + length;
                w[i][j] = w[i][j - 1] + success_prob[j] + unsuccess_prob[j];

                int minCost = 999;
                int minRoot = -1;

                for (int k = i + 1; k <= j; k++) {
                    int tempCost = c[i][k - 1] + c[k][j];
                    if (tempCost < minCost) {
                        minCost = tempCost;
                        minRoot = k;
                    }
                }

                c[i][j] = minCost + w[i][j];
                r[i][j] = minRoot;

                cout << "[i=" << i << ", j=" << j << "] ";
                cout << "w[" << i << "][" << j << "] = " << w[i][j] << "\t";
                cout << "r[" << i << "][" << j << "] = " << r[i][j] << "\t";
                cout << "c[" << i << "][" << j << "] = " << c[i][j] << "\n";
            }
        }

        cout << "\nMinimum cost of OBST: " << c[0][k] << endl;
    }
};

int main() {
    Obst o;
    o.getKey();
    o.computeObst();
    return 0;
}
