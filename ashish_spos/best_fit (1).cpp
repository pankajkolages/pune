#include <iostream>
using namespace std;

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    // Initialize all allocations to -1 (meaning unallocated)
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    // Place each process in the best fitting block
    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block was found, allocate it
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    // Display the result
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

int main()
{
    int m, n;

    cout << "Enter the number of memory blocks: ";
    cin >> m;
    int blockSize[m];
    cout << "Enter the size of each block:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> blockSize[i];
    }

    cout << "Enter the number of processes: ";
    cin >> n;
    int processSize[n];
    cout << "Enter the size of each process:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> processSize[i];
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}
