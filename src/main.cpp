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

// reads digits from a string and pushes them into a referenced vector
int parse_num(std::vector<int>& digits, std::string number_str){
    int digit;
    for (char i : number_str){
        // skip dashses and spaces
        if (i != ' ' && i != '-'){
            digit = get_digit(i);
            if (digit != -1)
                digits.push_back(digit);
            else
                return -1;
        }
    }
    return 0;
}

// returns true if a card has the correct number of digits for it's starting digit, otherwise returns false
bool valid_card_len(std::vector<int>& digits){
    enum CARD_TYPES {AMEX=3, VISA, MASTER, DISCOVER}; // the four major credit card types with their starting numbers.
    int card_len;  // the number of a digits a card should have, depends on the card type
    // determine the number of characters a card should should have, based on it's first digit
    switch (digits[0]){
    case AMEX:
        card_len = 15;
        break;
    case VISA: case MASTER: case DISCOVER:
        card_len = 16;
        break;
    default:
        return false;
    }
    // return if the card has the correct number of digits
    return digits.size() == card_len;
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

