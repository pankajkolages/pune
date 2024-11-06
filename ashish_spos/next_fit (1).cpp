// #include <iostream>
// using namespace std;

// void nextFit(int blockSize[], int m, int processSize[], int n)
// {
//     int allocation[n]; // Array to store block index for each process
//     int lastIndex = 0; // Keeps track of the last allocated index

//     // Step 1: Initialize all allocations to -1 (meaning unallocated)
//     for (int i = 0; i < n; i++)
//     {
//         allocation[i] = -1;
//     }

//     // Step 2: Place each process in the next fitting block
//     for (int i = 0; i < n; i++)
//     {
//         int count = 0; // This variable ensures we do not loop infinitely

//         // Step 3: Try to allocate the process starting from lastIndex
//         while (count < m)
//         { // Check each block once to prevent infinite looping
//             // Step 4: If the block at lastIndex fits, allocate it to the process
//             if (blockSize[lastIndex] >= processSize[i])
//             {
//                 allocation[i] = lastIndex;              // Allocate current block to the process
//                 blockSize[lastIndex] -= processSize[i]; // Reduce block size by the process size
//                 break;                                  // Move to the next process after allocation
//             }

//             // Step 5: Move to the next block, and wrap around if necessary
//             lastIndex = (lastIndex + 1) % m; // Move to the next block
//             count++;                         // Increment count to track iterations
//         }
//     }

//     // Step 6: Display the result of the allocation
//     cout << "Process No.\tProcess Size\tBlock No.\n";
//     for (int i = 0; i < n; i++)
//     {
//         cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
//         if (allocation[i] != -1)
//             cout << allocation[i] + 1; // Output allocated block number (1-based index)
//         else
//             cout << "Not Allocated"; // Indicate if the process was not allocated
//         cout << endl;
//     }
// }

// int main() {
//     int m, n;

//     // Input for number of memory blocks and their sizes
//     cout << "Enter the number of memory blocks: ";
//     cin >> m;
//     int blockSize[m];
//     cout << "Enter the size of each block:\n";
//     for (int i = 0; i < m; i++) {
//         cin >> blockSize[i];
//     }

//     // Input for number of processes and their sizes
//     cout << "Enter the number of processes: ";
//     cin >> n;
//     int processSize[n];
//     cout << "Enter the size of each process:\n";
//     for (int i = 0; i < n; i++) {
//         cin >> processSize[i];
//     }

//     // Perform next fit allocation
//     nextFit(blockSize, m, processSize, n);

//     return 0;
// }

#include <iostream>
using namespace std;

void nextFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int lastIndex = 0;

    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int count = 0;
        while (count < m)
        {
            if (blockSize[lastIndex] >= processSize[i])
            {
                allocation[i] = lastIndex;
                blockSize[lastIndex] -= processSize[i];
                break;
            }
            lastIndex = (lastIndex + 1) % m;
            count++;
        }
    }
    cout << "process no\tprocess size\tblock no\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
        {
            cout << allocation[i] + 1;
        }
        else
        {
            cout << "not allocated";
        }
        cout << endl;
    }
}

int main()
{
    int m, n;

    // Input for number of memory blocks and their sizes
    cout << "Enter the number of memory blocks: ";
    cin >> m;
    int blockSize[m];
    cout << "Enter the size of each block:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> blockSize[i];
    }

    // Input for number of processes and their sizes
    cout << "Enter the number of processes: ";
    cin >> n;
    int processSize[n];
    cout << "Enter the size of each process:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> processSize[i];
    }

    // Perform next fit allocation
    nextFit(blockSize, m, processSize, n);

    return 0;
}
