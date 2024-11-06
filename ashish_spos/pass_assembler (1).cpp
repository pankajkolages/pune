#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

// Data structures
map<string, int> symbolTable;    // Symbol table to hold labels and their addresses
vector<string> intermediateCode; // Intermediate code to hold instructions

// Pass I: Create the symbol table and intermediate code
void passI(const string &filename)
{
    ifstream inputFile(filename);
    string line;
    int address = 0; // Starting address

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string label, instruction;
        iss >> label; // Read the label (if exists)

        // Check if the first word is a label
        if (label.back() == ':')
        {
            label.pop_back();             // Remove the ':' from the label
            symbolTable[label] = address; // Add label to symbol table
        }
        else
        {
            instruction = label; // If no label, it's the instruction
            address++;           // Increment address for each instruction
        }

        // Store the instruction in intermediate code
        intermediateCode.push_back(instruction);
    }

    inputFile.close();
}

// Pass II: Generate the machine code using the symbol table and intermediate code
void passII()
{
    cout << "Generated Machine Code:\n";
    for (const auto &instruction : intermediateCode)
    {
        if (instruction.empty())
            continue; // Skip empty lines
        // Check for symbol usage in the instruction
        if (symbolTable.find(instruction) != symbolTable.end())
        {
            cout << "LOAD " << instruction << " -> " << symbolTable[instruction] << endl;
        }
        else
        {
            cout << instruction << endl; // Direct instruction
        }
    }
}

int main()
{
    string filename;

    cout << "Enter the name of the input file (with .asm extension): ";
    cin >> filename;

    // First pass to create symbol table and intermediate code
    passI(filename);

    // Display the symbol table
    cout << "Symbol Table:\n";
    for (const auto &entry : symbolTable)
    {
        cout << entry.first << " : " << entry.second << endl;
    }

    // Second pass to generate machine code
    passII();

    return 0;
}

// #include <iostream>
// #include <fstream>
// #include <map>
// #include <vector>
// #include <sstream>

// using namespace std;

// // Data structures
// map<string, int> symbolTable;    // Symbol table to hold labels and their addresses
// vector<string> intermediateCode; // Intermediate code to hold instructions

// // Pass I: Create the symbol table and intermediate code
// void passI(const string &filename)
// {
//     ifstream inputFile(filename);
//     string line;
//     int address = 0; // Starting address

//     while (getline(inputFile, line))
//     {
//         istringstream iss(line);
//         string label, instruction;
//         iss >> label; // Read the label (if exists)

//         // Check if the first word is a label
//         if (label.back() == ':')
//         {
//             label.pop_back();             // Remove the ':' from the label
//             symbolTable[label] = address; // Add label to symbol table
//         }
//         else
//         {
//             instruction = label; // If no label, it's the instruction
//             address++;           // Increment address for each instruction
//         }

//         // Store the instruction in intermediate code
//         intermediateCode.push_back(instruction);
//     }

//     inputFile.close();
// }

// // Pass II: Generate the machine code using the symbol table and intermediate code
// void passII()
// {
//     cout << "Generated Machine Code:\n";
//     for (const auto &instruction : intermediateCode)
//     {
//         if (instruction.empty())
//             continue; // Skip empty lines
//         // Check for symbol usage in the instruction
//         if (symbolTable.find(instruction) != symbolTable.end())
//         {
//             cout << "LOAD " << instruction << " -> " << symbolTable[instruction] << endl;
//         }
//         else
//         {
//             cout << instruction << endl; // Direct instruction
//         }
//     }
// }

// int main()
// {
//     string filename;

//     cout << "Enter the name of the input file (with .asm extension): ";
//     cin >> filename;

//     // First pass to create symbol table and intermediate code
//     passI(filename);

//     // Display the symbol table
//     cout << "Symbol Table:\n";
//     for (const auto &entry : symbolTable)
//     {
//         cout << entry.first << " : " << entry.second << endl;
//     }

//     // Second pass to generate machine code
//     passII();

//     return 0;
// }

// // START:
// // LOAD A
// // ADD B
// // STORE RESULT
// // END
