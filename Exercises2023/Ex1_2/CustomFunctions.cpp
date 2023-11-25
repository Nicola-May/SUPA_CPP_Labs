#include "CustomFunctions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>




// Function to read data from a file and store it in a vector of pairs
std::vector<std::pair<double, double>> readDataFromFile(const std::string& filename) {
    std::ifstream myInput(filename); // Open a file stream for reading

// Check if the file stream is successfully opened
    if (myInput.fail()) {
        std::cerr << "Could not open file" << std::endl; // Print an error message if the file can't be opened
        exit(1); // Exit the prgram with an error code
    } else {
        std::cout << "File opened successfully!" << std::endl; // print a success message if the file is opened
    }

    std::string header;
    getline(myInput, header); // Read and ignore the header line

    double x, y;
    std::vector<std::pair<double, double>> data; // Vector to store pairs of data (x, y)

// Loop to read pairs of doubles from the file separated by commas and store them in the vector
    while (myInput >> x >> std::ws && myInput.peek() == ',' && myInput.ignore() >> y) {
        data.push_back(std::make_pair(x, y));
    }

    myInput.close(); // Close the file stream

    return data; // Return the vector contianing the data
}






// Function to calculate magnitudes from a vector of pairs x nd y
std::vector<double> calculateMagnitudes(const std::vector<std::pair<double, double>>& data) {
    std::vector<double> magnitudes;

// Loop through each pair in input vector and calculate magnitude
    for (const auto& point : data) {
        double magnitude = sqrt(point.first * point.first + point.second * point.second);
        magnitudes.push_back(magnitude); // Add each magnitude to the vector
    }

    return magnitudes; // Return the vector containing calculated magnitudes
}




// Function to print data and magnitudes up to a specified number of lines
void printDataAndMagnitudes(const std::vector<std::pair<double, double>>& data,
                             const std::vector<double>& magnitudes, int n) {
// Check if the requested number of lines to print is larger than the total number of data points
    if (n > data.size()) {
        std::cerr << "Warning: Requested number of lines to print (" << n
                  << ") is larger than the total number of data points. Printing the first 5 lines." << std::endl;
        n = std::min(5, static_cast<int>(data.size())); // Set n to the minimum of 5 and the total number of data points
    }

    std::cout << "Read values from the vector:" << std::endl;

// Loop to print the values of x, y, and magnitude for each line up to the specified limit (n)
    for (int i = 0; i < n; ++i) {
        std::cout << "x = " << data[i].first << ", y = " << data[i].second << std::endl;
    }
}



//function for chi sqaured and fitline 
std::string fitStraightLine(const std::vector<std::pair<double, double>>& data,
                            const std::vector<std::pair<double, double>>& errors) {
    size_t n = data.size();

    // Calculate the sums needed for the least squares method
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sumX += data[i].first;
        sumY += data[i].second;
        sumXY += data[i].first * data[i].second;
        sumX2 += data[i].first * data[i].first;
    }

    // Calculate the coefficients (m and c) for the least squares line
    double p = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double q = (sumX2 * sumY - sumXY * sumX) / (n * sumX2 - sumX * sumX);

    // Calculate chi-squared
    double chiSquared = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double residual = data[i].second - (p * data[i].first + q);
        chiSquared += std::pow(residual / errors[i].second, 2);
    }

    // Calculate degrees of freedom
    size_t ndf = n - 2;

    // Create the string representation of the line function and chi-squared result
    std::stringstream result;
    result << "y = " << std::fixed << std::setprecision(2) << p << "x + " << q << "\n"
           << "Chi-squared: " << chiSquared << "\nNDF: " << ndf << "\nReduced Chi-squared: " << chiSquared / ndf;

    // Save the results to a new file
    std::ofstream outputFile("fitResults.txt");
    if (outputFile.is_open()) {
        outputFile << result.str();
        outputFile.close();
        std::cout << "Fit results saved to fitResults.txt" << std::endl;
    } else {
        std::cerr << "Error: Unable to open fitResults.txt for writing." << std::endl;
    }

    return result.str();
}


// Function to calculate x^y for each data point with y rounded to the nearest whole number
std::vector<double> calculatePower(const std::vector<std::pair<double, double>>& data) {
    std::vector<double> result;

    for (const auto& point : data) {
        // Round y to the nearest whole number
        int exponent = static_cast<int>(std::round(point.second));

        // Initialize result to 1.0 for the power operation
        double poweredValue = 1.0;

        // Handle the case when exponent is positive
        for (int i = 0; i < exponent; ++i) {
            poweredValue *= point.first;
        }

        // Handle the case when exponent is negative
        for (int i = 0; i > exponent; --i) {
            poweredValue /= point.first;
        }

        // Add the result to the vector
        result.push_back(poweredValue);

        // Print the result to the terminal
        std::cout << "x^y for (" << point.first << ", " << point.second << "): " << poweredValue << std::endl;
    }

    return result;
}


// Calculate chi sqaured function
// std::string findChiSqaured(const std::vector<std::pair<double, double>>& errors)


// Generic print function for vectors
//template <typename T>
//void printVector(const std::vector<T>& vec, int n) {
//    if (n > vec.size() || n == -1) {
 //       n = vec.size();
 //   }

  //  for (int i = 0; i < n; ++i) {
    //    std::cout << vec[i] << std::endl;
   // }
//}

// Overload for printing pairs
template <typename T, typename U>
void printVector(const std::vector<std::pair<T, U>>& vec, int n) {
    if (n > vec.size() || n == -1) {
        n = vec.size();
    }

    for (int i = 0; i < n; ++i) {
        std::cout << "(" << vec[i].first << ", " << vec[i].second << ")" << std::endl;
    }
}

// Overload for printing strings
void printVector(const std::vector<std::string>& vec, int n) {
    if (n > vec.size() || n == -1) {
        n = vec.size();
    }

    for (int i = 0; i < n; ++i) {
        std::cout << vec[i] << std::endl;
    }
}