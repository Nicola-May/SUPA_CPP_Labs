// Nicola Agnew
// Nicola.agnew@strath.ac.uk

// To compile use command g++ AnalyseData.cpp CustomFunctions.cpp -o AnalyseData
// To run use command ./AnalyseData

// Didnt have time to impliment steps (11) and (12)

#include <iostream>
#include "CustomFunctions.h"

int main() {
    // Get the input data file
    std::string filename = "input2D_float.txt";
    // Get errors from file
    std::string filename_errors = "error2D_float.txt";

    // Read data from the file
    std::vector<std::pair<double, double>> data = readDataFromFile(filename);
    // Read errors from file
    std::vector<std::pair<double, double>> errors = readDataFromFile(filename_errors);

    // Calculate magnitudes
    std::vector<double> magnitudes = calculateMagnitudes(data);

    // Ask the user which function to use
    std::cout << "Choose a function: \n";
    std::cout << "1. Print data\n";
    std::cout << "2. Calculate magnitudes\n";
    std::cout << "3. Fit straight line and calculate chi-squared\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // If printing, ask for the number of lines to print
        int linesToPrint;
        std::cout << "Enter the number of lines to print: ";
        std::cin >> linesToPrint;

        // Print the first n lines of the data and magnitudes
        printDataAndMagnitudes(data, magnitudes, linesToPrint);
    } else if (choice == 2) {
        // Print magnitudes
        std::cout << "Magnitudes:\n";
        printVector(magnitudes);
    } else if (choice == 3) {
        // Fit a straight line using least squares and calculate chi-squared
        std::string result = fitStraightLine(data, errors);

        // Print the line function and chi-squared to the terminal
        std::cout << "Fitted Line Function and Chi-squared:\n" << result << std::endl;
    } else {
        std::cerr << "Invalid choice. Exiting program.\n";
        return 1;
    }

    // Print the total number of lines read from the file
    std::cout << data.size() << " lines read from file" << std::endl;

    
    // Calculate x^y for each data point
    std::vector<double> poweredValues = calculatePower(data);

    return 0;
}
