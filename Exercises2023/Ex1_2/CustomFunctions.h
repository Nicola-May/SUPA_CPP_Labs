// CustomFunctions.h

#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>  // Include for std::cout and std::endl
#include <ostream>   // Include for std::endl

// Function to read data from the file and store it in a vector
std::vector<std::pair<double, double>> readDataFromFile(const std::string& filename);

// Function to calculate the magnitude of each data point
std::vector<double> calculateMagnitudes(const std::vector<std::pair<double, double>>& data);

// Function to fit a straight line (y = mx + c) using the least squares method
std::string fitStraightLine(const std::vector<std::pair<double, double>>& data, const std::vector<std::pair<double, double>>& errors);

// Function to calculate chi-squared
std::string findChiSquared(const std::vector<std::pair<double, double>>& data, const std::vector<double>& magnitudes,
                           const std::vector<std::pair<double, double>>& errors);

// Function to print data and magnitudes up to a specified number of lines
void printDataAndMagnitudes(const std::vector<std::pair<double, double>>& data,
const std::vector<double>& magnitudes, int n);

// Function to calculate x^y for each data point with y rounded to the nearest whole number
std::vector<double> calculatePower(const std::vector<std::pair<double, double>>& data);

// Generic print function for vectors
template <typename T>
inline void printVector(const std::vector<T>& vec, int n = -1) {
    if (n > vec.size() || n == -1) {
        n = vec.size();
    }

    for (int i = 0; i < n; ++i) {
        std::cout << vec[i] << std::endl;
    }
}

#endif // CUSTOM_FUNCTIONS_H