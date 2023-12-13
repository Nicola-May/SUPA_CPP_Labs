 // Nicola Agnew 
 // Nicola.agnew@strath.ac.uk
 
 // g++ main_function.cpp FiniteFunctions.cxx -o main_function -lboost_iostreams
 // ./main_function

 // I have had to edit the FiniteFunctions plotting functions as the original version
 // does not display the plots. Now in saves plot as .png in outputs folder 

 // I am having issue with creating mulpiple plots as once. My current (non- optimal) method is to 
 // comment out the plots that I am not evaluating at the time and recomplile for each plot seperately. 
 // This means you wont see all the results by just running this code. There is a plot 
 // for the defualt function + data, normal + data, lorentz + data, neg crystal ball +
 // data and function+pseudo random generated data.


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include "FiniteFunctions.h"
#include "gnuplot-iostream.h"

int main() {
    // Open the file
    std::ifstream inputFile("MysteryData01200.txt");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1; // Return an error code
    }

    // Read the values from the file and store them in a vector
    std::vector<double> MysteryValues;
    double value;
    while (inputFile >> value) {
        MysteryValues.push_back(value);
    }
    
    // Lets the user know that saving variables was sucessful
    std::cout << "File MysteryData01200.txt saved to vector MysteryValues !" << std::endl;

    // Close the file
    inputFile.close();

    // Create an instance of FiniteFunction (Does NOT fit data)
    //FiniteFunction function{};
    //function.plotFunction();
    //function.plotData(MysteryValues, 100, true);

    // Create and test NormalDistribution (Does fit data)
    NormalDistribution normalDist(-1, 2); // mean , standard deviation 
    normalDist.plotFunction();
    normalDist.plotData(MysteryValues, 100, true);

    // Create and test CauchyLorentzDistribution (Does NOT fit data)
    CauchyLorentzDistribution cauchyDist(-1, 2); // x0 , gamma
    //cauchyDist.plotFunction();
    //cauchyDist.plotData(MysteryValues, 100, true);

    // create and test NegativeCrystalBallDistribution (does fit data) 
    NegativeCrystalBallDistribution crystalBallDist(2, 2, -1, 2); // alpha , n , x_bar , sigma 
    //crystalBallDist.plotFunction();
    //crystalBallDist.plotData(MysteryValues, 100, true);

// PART 2: Metropolis algorithm 

// Create an new instance of NormalDistribution (1)
NormalDistribution normalDist_2(-1, 2); 

// Generate x_i
// Random number generator initialization
std::random_device rd;
std::mt19937 eng(rd());
// Uniform distribution in range [-5, 5]
std::uniform_real_distribution<> distr(-5.0, 5.0);

// Generate initial x_i from a uniform distribution
double x_i = distr(eng);

// no of samples to be accepted
int iterations = 10000;
// vector to store accepted values
std::vector<double> acceptedSamples;

for (int i = 0; i < iterations; ++i) {

    // Generate y from normal distribution (2)
    double y = normalDist_2.generateRandom(x_i, 1.0); 

    // Evaluate f(x_i)
    double f_x_i = normalDist_2.callFunction(x_i);
    // Evaluate f(y)
    double f_y = normalDist_2.callFunction(y);

    // Evaluate aceptance ratio A (3)
    double A = std::min(f_y / f_x_i, 1.0);
 
    // generating random number T (4)
    std::uniform_real_distribution<> distT(0.0, 1.0);  // Uniform distribution between 0 and 1
    double T = distT(eng);  // Generate a random number T

if (T < A) {
    x_i = y; // accept y ad update x_i (5)
    acceptedSamples.push_back(y); // save the accepted sample
}
}

// plot normal distribution function 
//normalDist_2.plotFunction();
// plot pseudo random data 
//normalDist_2.plotData(acceptedSamples, 100, true);

    // End the main function 
    return 0;
}