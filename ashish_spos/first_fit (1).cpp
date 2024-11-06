#include <iostream>
using namespace std;

// Function to perform the first-fit memory allocation
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n]; // Array to keep track of which block each process is allocated to

    // Initialize all allocations to -1 (meaning unallocated)
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    // Iterate through each process to find a suitable memory block
    for (int i = 0; i < n; i++)
    { // Loop through each process
        for (int j = 0; j < m; j++)
        { // Loop through each memory block
            // Check if the current block can accommodate the process
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;              // Allocate the block to the process
                blockSize[j] -= processSize[i]; // Reduce the size of the block
                break;                          // Exit loop as process is allocated
            }
        }
    }

    // Display the allocation results
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)       // Check if process was allocated
            cout << allocation[i] + 1; // Output block number (1-based index)
        else
            cout << "Not Allocated"; // Indicate if no block was found
        cout << endl;
    }
}

int main()
{
    int m, n;

    // Get the number of memory blocks from the user
    cout << "Enter the number of memory blocks: ";
    cin >> m;
    int blockSize[m]; // Array to store the size of each memory block

    // Get the size of each memory block from the user
    cout << "Enter the size of each block:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> blockSize[i];
    }

    // Get the number of processes from the user
    cout << "Enter the number of processes: ";
    cin >> n;
    int processSize[n]; // Array to store the size of each process

    // Get the size of each process from the user
    cout << "Enter the size of each process:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> processSize[i];
    }

    // Call the firstFit function to allocate processes to memory blocks
    firstFit(blockSize, m, processSize, n);

    return 0;
}
