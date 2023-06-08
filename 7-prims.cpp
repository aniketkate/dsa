#include <iostream>
using namespace std;

class tree
{
    int** a;
    int v, e;
    int* visited;

public:
    void input();
    void display();
    void minimum();
    ~tree(); // Destructor to deallocate memory
};

void tree::input()
{
    cout << "Enter the number of branches: ";
    cin >> v;

    // Validate the number of branches
    if (v <= 0)
    {
        cout << "Invalid number of branches. Exiting..." << endl;
        exit(1);
    }

    // Allocate memory for adjacency matrix
    a = new int*[v];
    for (int i = 0; i < v; i++)
        a[i] = new int[v];

    visited = new int[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = 0;
        for (int j = 0; j < v; j++)
        {
            a[i][j] = 999;
        }
    }

    cout << "\nEnter the number of connections: ";
    cin >> e;

    // Validate the number of connections
    if (e < 0 || e > v * (v - 1) / 2)
    {
        cout << "Invalid number of connections. Exiting..." << endl;
        exit(1);
    }

    for (int i = 0; i < e; i++)
    {
        int l, u, w;
        cout << "Enter the end branches of connection: " << endl;
        cin >> l >> u;
        cout << "Enter the phone company charges for this connection: ";
        cin >> w;

        // Validate the end branches
        if (l < 1 || l > v || u < 1 || u > v)
        {
            cout << "Invalid end branches. Exiting..." << endl;
            exit(1);
        }

        a[l - 1][u - 1] = a[u - 1][l - 1] = w;
    }
}

void tree::display()
{
    cout << "\nAdjacency matrix:\n";
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            cout << a[i][j] << "   ";
        }
        cout << endl;
    }
}

void tree::minimum()
{
    int p = 0, q = 0, total = 0, min;
    visited[0] = 1; // Start with vertex 0
    for (int count = 0; count < (v - 1); count++)
    {
        min = 999;
        for (int i = 0; i < v; i++)
        {
            if (visited[i] == 1)
            {
                for (int j = 0; j < v; j++)
                {
                    if (visited[j] != 1)
                    {
                        if (min > a[i][j])
                        {
                            min = a[i][j];
                            p = i;
                            q = j;
                        }
                    }
                }
            }
        }
        visited[p] = 1;
        visited[q] = 1;
        total = total + min;
        cout << "Minimum cost connection is " << (p + 1) << " -> " << (q + 1) << " with charge: " << min << endl;
    }
    cout << "The minimum total cost of connections of all branches is: " << total << endl;
}

tree::~tree()
{
    // Deallocate memory for adjacency matrix and visited array
    for (int i = 0; i < v; i++)
        delete[] a[i];
    delete[] a;
    delete[] visited;
}

int main()
{
    int ch;
    tree t;
    do
    {
        cout << "==========PRIM'S ALGORITHM=================" << endl;
        cout << "\n1. INPUT\n2. DISPLAY\n3. MINIMUM\n4. EXIT\n" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
            case 1:
                cout << "******INPUT YOUR VALUES******" << endl;
                t.input();
                break;

            case 2:
                cout << "******DISPLAY THE CONTENTS*******" << endl;
                t.display();
                break;

            case 3:
                cout << "********MINIMUM***********" << endl;
                t.minimum();
                break;

            case 4:
                cout << "Exiting the program..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (ch != 4);

    return 0;
}
