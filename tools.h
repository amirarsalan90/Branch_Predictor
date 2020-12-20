//
// Created by arajabi on 11/6/20.
//

#ifndef PREDICTION_TOOLS_H
#define PREDICTION_TOOLS_H


#include <string>
#include <map>


class nsmith {
public:
    int counter;
    int num_bits;
    int prediction;
    int misprediction;
    nsmith(int number_of_bits);
    void predict(char actual);
    int return_mispredictions();
    int return_counter();
};


const char* hexcharacter_to_bincharacter(char mychar);
std::string hexstring_to_binstring(const std::string& hex);
int convertBinaryToDecimal(long long int n);

std::string calc_xor(std::string x, std::string y, int n);


int return_decimal_from_binary(std::string binary);


/*
class nsmith {
public:
    int misprediction;
    std::map<std::string, int> history;
    int num_bits;
    nsmith(int number_of_bits);
    void insert_data(std::string tag, char actual);
    void print_data(std::string tag);
    void print_misprediction();

};*/



#endif //PREDICTION_TOOLS_H

