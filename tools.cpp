//
// Created by arajabi on 11/6/20.
//

#include "tools.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

nsmith::nsmith(int number_of_bits){
    counter = 0;
    num_bits = number_of_bits;
    misprediction = 0;
    if (num_bits == 1){
        prediction = 1;
    } else if (num_bits == 2) {
        prediction = 2;
    } else if (num_bits == 3) {
        prediction = 4;
    } else if (num_bits == 4) {
        prediction = 8;
    }
}



int nsmith::return_mispredictions() {
    return misprediction;
}

int nsmith::return_counter() {
    return prediction;
}


void nsmith::predict(char actual){

    if (num_bits == 1) {
        if (actual == 't'){
            if (prediction == 1){

            } else if (prediction == 0){
                misprediction += 1;
                prediction += 1;
            }
        } else if (actual == 'n'){
            if (prediction == 0){

            } else if (prediction == 1){
                misprediction += 1;
                prediction -= 1;
            }
        }
    }


    if (num_bits == 2) {
        if (prediction !=0 && prediction !=3){
            if (actual == 't'){
                if (prediction >= 2){
                    prediction += 1;
                } else if (prediction < 2){
                    misprediction += 1;
                    prediction += 1;
                }
            } else if (actual == 'n'){
                if (prediction >= 2){
                    misprediction += 1;
                    prediction -= 1;
                } else if (prediction < 2){
                    prediction -= 1;
                }
            }
        } else if (prediction == 0) {
            if (actual == 't'){
                misprediction += 1;
                prediction += 1;
            } else if (actual == 'n'){

            }
        } else if (prediction == 3){
            if (actual == 't'){

            }else if (actual == 'n'){
                misprediction += 1;
                prediction -= 1;
            }
        }
    }


    if (num_bits == 3) {
        if (prediction !=0 && prediction !=7){
            if (actual == 't'){
                if (prediction >= 4){
                    prediction += 1;
                } else if (prediction < 4){
                    misprediction += 1;
                    prediction += 1;
                }
            } else if (actual == 'n'){
                if (prediction >= 4){
                    misprediction += 1;
                    prediction -= 1;
                } else if (prediction < 4){
                    prediction -= 1;
                }
            }
        } else if (prediction == 0) {
            if (actual == 't'){
                misprediction += 1;
                prediction += 1;
            } else if (actual == 'n'){

            }
        } else if (prediction == 7){
            if (actual == 't'){

            }else if (actual == 'n'){
                misprediction += 1;
                prediction -= 1;
            }
        }
    }


    if (num_bits == 4) {
        if (prediction !=0 && prediction !=15){
            if (actual == 't'){
                if (prediction >= 8){
                    prediction += 1;
                } else if (prediction < 8){
                    misprediction += 1;
                    prediction += 1;
                }
            } else if (actual == 'n'){
                if (prediction >= 8){
                    misprediction += 1;
                    prediction -= 1;
                } else if (prediction < 8){
                    prediction -= 1;
                }
            }
        } else if (prediction == 0) {
            if (actual == 't'){
                misprediction += 1;
                prediction += 1;
            } else if (actual == 'n'){

            }
        } else if (prediction == 15){
            if (actual == 't'){

            }else if (actual == 'n'){
                misprediction += 1;
                prediction -= 1;
            }
        }
    }
    counter += 1;
}








////////////////////////////////////////////
/*
nsmith::nsmith(int number_of_bits){
    num_bits = number_of_bits;
    misprediction = 0;
}

void nsmith::insert_data(string tag, char actual) {
    if (num_bits == 1) {
        if (history.find(tag) == history.end()){
            history.insert(pair<string, int>(tag, 1));
            if (actual == 't'){

            } else if (actual == 'n'){
                misprediction += 1;
            }
        } else {
            if (history[tag] == 1) {
                if (actual == 't'){

                } else if (actual == 'n'){
                    history[tag] -= 1;
                    misprediction += 1;
                }
            } else if (history[tag] == 0){
                if (actual == 't'){
                    history[tag] += 1;
                    misprediction += 1;
                } else if (actual == 'n'){

                }
            }

        }
    }

    if (num_bits == 2) {
        if (history.find(tag) == history.end()){
            history.insert(pair<string, int>(tag, 2));
        } else {
            if ((history[tag] != 0) && (history[tag] != 3)) {
                if (actual == 't'){
                    if (history[tag] >= 2){
                        history[tag] += 1;
                    } else if (history[tag] < 2){
                        misprediction += 1;
                        history[tag] += 1;
                    }
                } else if(actual == 'n'){
                    if (history[tag] >= 2){
                        misprediction += 1;
                        history[tag] -= 1;
                    } else if(history[tag] < 2){
                        history[tag] -= 1;
                    }
                }
            } else if(history[tag] == 0){
                if (actual == 't'){
                    misprediction += 1;
                    history[tag] += 1;
                } else if(actual == 'n'){

                }
            } else if(history[tag] == 3){
                if (actual == 't'){

                } else if(actual == 'n'){
                    misprediction += 1;
                    history[tag] -= 1;
                }
            }
        }
    }

}

void nsmith::print_data(std::string tag) {
    cout << history[tag] << "\n";
}

void nsmith::print_misprediction() {
    cout << misprediction <<"\n";
}
*/
////////////////////////////////////////////////

const char* hexcharacter_to_bincharacter(char mychar) {
    switch(toupper(mychar))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

string hexstring_to_binstring(const string &hex) {
    string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
        bin += hexcharacter_to_bincharacter(hex[i]);
    return bin;
}

int convertBinaryToDecimal(long long int n) {

    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

string calc_xor(string x, string y, int n){
    string result = "";

    // Loop to iterate over the
    // Binary Strings
    for (int i = 0; i < n; i++)
    {
        // If the Character matches
        if (x[i] == y[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}


int return_decimal_from_binary(string binary){
    char *ptr;
    long ret;
    ret = strtol(binary.c_str(), &ptr, 2);
    int set = (int)ret;
    return set;
}


