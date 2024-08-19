#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void compressFile(const string &inputFileName, const string &outputFileName) {
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName, ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Failed to open the input or output file!" << endl;
        return;
    }

    char currentChar, previousChar = '\0';
    int count = 0;

    while (inputFile.get(currentChar)) {
        if (currentChar == previousChar) {
            ++count;
        } else {
            if (count > 0) {
                outputFile << count << previousChar;
            }
            previousChar = currentChar;
            count = 1;
        }
    }

    if (count > 0) {
        outputFile << count << previousChar;
    }

    inputFile.close();
    outputFile.close();
}

void decompressFile(const string &inputFileName, const string &outputFileName) {
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName, ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Failed to open the input or output file!" << endl;
        return;
    }

    int count;
    char character;

    while (inputFile >> count >> character) {
        outputFile.write(string(count, character).c_str(), count);
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    cout << "File Compressor and Decompressor by Anwaar-ur-Rehman" << endl;

    string inputFileName, outputFileName;
    char operationChoice;

    cout << "Choose operation - Compress (c) or Decompress (d): ";
    cin >> operationChoice;

    cout << "Enter the input file name: ";
    cin >> inputFileName;

    cout << "Enter the output file name: ";
    cin >> outputFileName;

    switch (operationChoice) {
        case 'c':
            compressFile(inputFileName, outputFileName);
            cout << "Compression completed successfully!" << endl;
            break;
        case 'd':
            decompressFile(inputFileName, outputFileName);
            cout << "Decompression completed successfully!" << endl;
            break;
        default:
            cerr << "Invalid choice! Please select 'c' to compress or 'd' to decompress." << endl;
            break;
    }

    return 0;
}
