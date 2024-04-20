#include <iostream>
using namespace std;

class KeyProbabilityPair
{
public:
    double key;
    double probability;

    KeyProbabilityPair() : key(0), probability(0) {}
};

class OBST
{
private:
    double **root_cost;
    int **root;
    KeyProbabilityPair *keyProbPairs;
    int n;
    const double INF = 1e9;

public:
    OBST(int size) : n(size)
    {
        root_cost = new double *[n];
        root = new int *[n];
        keyProbPairs = new KeyProbabilityPair[n];
        for (int i = 0; i < n; ++i)
        {
            root_cost[i] = new double[n];
            root[i] = new int[n];
            for (int j = 0; j < n; ++j)
            {
                root_cost[i][j] = 0;
                root[i][j] = 0;
            }
        }
    }

    ~OBST()
    {
        for (int i = 0; i < n; ++i)
        {
            delete[] root_cost[i];
            delete[] root[i];
        }
        delete[] root_cost;
        delete[] root;
        delete[] keyProbPairs;
    }

    void input_keys_and_probabilities()
    {
        cout << "Enter the keys and their probabilities:\n";
        for (int i = 0; i < n; ++i)
        {
            cout << "Key " << i + 1 << ": ";
            cin >> keyProbPairs[i].key;
            cout << "Probability " << i + 1 << ": ";
            cin >> keyProbPairs[i].probability;
        }
    }

    double sum(const KeyProbabilityPair *keyProbPairs, int start, int end)
    {
        double sum = 0;
        for (int k = start; k <= end; ++k)
        {
            sum += keyProbPairs[k].probability;
        }
        return sum;
    }

    void printRootCostMatrix(double **root_cost, int n)
    {
        cout << "Root Cost Matrix:" << endl;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << root_cost[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void printRootMatrix(int **root, int n)
    {
        cout << "Root Matrix:" << endl;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << root[i][j] << "\t";
            }
            cout << endl;
        }
    }

    double optimal_cost()
    {

        for (int i = 0; i < n; ++i)
        {
            root_cost[i][i] = keyProbPairs[i].probability;
            root[i][i] = i;
        }

        for (int l = 2; l <= n; ++l)
        {
            for (int i = 0; i <= n - l; ++i)
            {
                int j = i + l - 1;
                root_cost[i][j] = INF;
                double sum_p = sum(keyProbPairs, i, j);

                for (int k = i; k <= j; ++k)
                {
                    double cost = sum_p + (k > i ? root_cost[i][k - 1] : 0) + (k < j ? root_cost[k + 1][j] : 0);
                    if (cost < root_cost[i][j])
                    {
                        root_cost[i][j] = cost;
                        root[i][j] = k;
                    }
                }
            }
        }

        printRootCostMatrix(root_cost, n);
        printRootMatrix(root, n);

        return root_cost[0][n - 1];
    }
};

int main()
{
    int size;
    cout << "Enter the number of keys: ";
    cin >> size;

    OBST obst(size);

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Input keys and probabilities\n";
        cout << "2. Calculate optimal cost\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            obst.input_keys_and_probabilities();
            break;
        }
        case 2:
        {
            double cost = obst.optimal_cost();
            cout << "Optimal cost: " << cost << endl;
            break;
        }
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 3);

    return 0;
}
