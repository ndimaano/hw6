#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0,0,0,0,0}; // create an array to store each converted part of the string
				size_t a[6] = {0,0,0,0,0,0}; // create an array to store each the things that needed to be added up from the string
				std::string j = k; // set a new string for editing
				int counter = 0; // create a counter to see how many characters we have already done 
				while(!j.empty()) { // while j isn't empty
					if(j.length() < 6) { // check if it is less than 6
					// if it is less than 6 you can just convert the characters
							for(size_t i = 0; i < 6;i++) {
									if(i > 5-j.length()) {
											a[i]=j[i-(5-j.length())];
									}
									else if(i <= (5-j.length())) {
											a[i]=0;
									}
							}
					}
					// if it is not less than 6 then you have to convert the 6 characters at the end
					// of the string
					for(size_t i =0; i<6;i++) {
						a[5-i]=letterDigitToNumber(j[j.length()-1-i]);
					}
					for(size_t i =0; i<6;i++) {
						if(j.empty()) {
							break;
						}
						j.pop_back();
					}
					// after you convert the characters you have to place it into the w array which is the actual converted number before using random numbers
					w[4-counter] = static_cast<unsigned long long>(((((a[0]*36+a[1])*36+a[2])*36+a[3])*36+a[4])*36+a[5]);
					for(size_t i = 0; i < 5; i++) {
						a[i]=0;
					}
					counter++;
				}
				// return the fully converted number
				return static_cast<unsigned long long>(rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4]);
				
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        size_t digit = letter; // turn the char into ascii
        if(digit > 47 && digit < 58) { // if the character is a number
            digit = digit -'0' + 26;
        }
        else if (digit > 64 && digit < 91) { // if the character is a captial letter
            digit = digit - 'A';
        }
        else if (digit > 96 && digit < 123) { // if the character is a lower case letter
            digit = digit - 'a';
        }
				return digit;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
