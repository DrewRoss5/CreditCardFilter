#include <iostream>
#include <fstream>
#include "cardFunctions.h"
#include "luhn.h"

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
        // read the card number and save the result
        digits.clear();
        int parsed = parse_num(digits, tmp);
        // write the card number to the file if it's valid.
        if (parsed == 0 && valid_card_len(digits) && luhn_valid(digits))
            out << tmp << '\n';
    }
    in.close();
    out.close();
    std::cout << "Your file has been filtered" << std::endl;
}
