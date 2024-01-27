#include <iostream>
#include <fstream>
#include <string>
#include "luhn.h"

// returns a character as an int or -1 if the char isn't an integer
int get_digit(char digit){
    try{
        return std::stoi(&digit);
    }
    catch (...){
        return -1;
    }
}
int main(int argc, char** argv){
    if (argc != 3){
        std::cerr << "Error: This program accepts exactly two arguments." << std::endl;
        return -1;
    }
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    // validate input file path
    if (!in.good()){
        std::cerr << "Invalid Input File!" << std::endl;
        return -1;
    }
    std::string tmp;
    std::vector<int> digits;
    int digit;
    // check if each card number is valid, and write it to the output file if so
    while(std::getline(in, tmp)){
        // create a vector representing the digits in the card
        digits.clear();
        for (char i : tmp){
            digit = get_digit(i);
            // skip invalid numbers
            if (digit != -1)
                digits.push_back(digit);
        }
        // check if the card number is valid, and write it to the output file if so
        if (luhn_valid(digits))
            out << tmp << "\n";
    }
    in.close();
    out.close();
    std::cout << "Your file has been filtered" << std::endl;
}

