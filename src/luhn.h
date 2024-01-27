#include <vector>

bool luhn_valid(std::vector<int>& digits){
    int card_size = digits.size();
    // double every other digit starting from the second rightmost
    for (int i = card_size - 2; i >= 0; i -= 2){
        digits[i] *= 2;
        if(digits[i] >= 10)
            digits[i] -= 9;
    }
    // sum all digits
    int sum = 0;
    for (int i = 0; i < card_size; i++)
        sum += digits[i];
    // return if the number is divisible by 10
    return sum % 10 == 0;

}