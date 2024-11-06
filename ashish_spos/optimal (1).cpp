#include <iostream>
using namespace std;

// Function to find the optimal page to replace
int findOptimal(int pages[], int frames[], int frameSize, int currentIndex, int numPages)
{
    int farthest = currentIndex; // Track farthest reference
    int pageIndex = -1;          // Index of page to be replaced

    // Loop through each frame to find which page is used farthest in the future
    for (int i = 0; i < frameSize; i++)
    {
        int j;
        // Check how far in the future the current page in frames[i] will be used
        for (j = currentIndex; j < numPages; j++)
        {
            if (frames[i] == pages[j])
            {
                // If the page in frame is found in future references
                if (j > farthest)
                {
                    farthest = j;  // Update the farthest usage
                    pageIndex = i; // Update page index to replace
                }
                break;
            }
        }
        // If the page in frame is never referenced again, replace it immediately
        if (j == numPages)
            return i;
    }

    // Return index of page to replace (either the farthest found or first frame if none found)
    // return pageIndex == -1 ? 0 : pageIndex;

    if (pageIndex == -1)
        return 0;
    else
        return pageIndex;
}

// Function implementing the Optimal Page Replacement algorithm
void optimalPageReplacement(int pages[], int numPages, int frameSize)
{
    int frames[frameSize]; // Array to store pages in frames
    int pageFaults = 0;    // Counter for page faults
    int count = 0;         // Counter for filled frames

    // Initialize all frames to -1 to indicate they are empty
    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    // Process each page in the reference string
    for (int i = 0; i < numPages; i++)
    {
        bool isPageInFrame = false;

        // Step 1: Check if the page is already in any frame (page hit)
        for (int j = 0; j < frameSize; j++)
        {
            if (frames[j] == pages[i])
            {
                isPageInFrame = true; // Page is already in frame, no page fault
                break;
            }
        }

        // Step 2: If page is not in a frame (page miss), it's a page fault
        if (!isPageInFrame)
        {
            // If there’s space in the frame, place the page in the next empty slot
            if (count < frameSize)
            {
                frames[count++] = pages[i]; // Place the page in the frame
            }
            else
            {
                // No empty frame available, replace the optimal page
                int optimalIndex = findOptimal(pages, frames, frameSize, i + 1, numPages);
                frames[optimalIndex] = pages[i]; // Replace page at optimal index
            }
            pageFaults++; // Increment page fault count
        }

        // Display the frame contents after each page request
        cout << "Frames: ";
        for (int j = 0; j < frameSize; j++)
        {
            if (frames[j] != -1)
                cout << frames[j] << " ";
            else
                cout << "- ";
        }
        cout << endl; // Newline after displaying frames
    }

    // Display total page faults after processing all pages
    cout << "Total Page Faults: " << pageFaults << endl;
}

int main()
{
    int numPages, frameSize;

    cout << "Enter number of pages: ";
    cin >> numPages; // Input the number of pages

    int pages[numPages];
    cout << "Enter the page references:\n";
    for (int i = 0; i < numPages; i++)
    {
        cin >> pages[i]; // Input each page in the reference string
    }

    cout << "Enter the number of frames: ";
    cin >> frameSize; // Input the number of frames available

    // Run the Optimal Page Replacement algorithm
    optimalPageReplacement(pages, numPages, frameSize);

    return 0;
}

