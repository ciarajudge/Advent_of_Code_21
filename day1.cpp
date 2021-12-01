//
//  day1.cpp
//  
//
//  Created by Ciara Judge on 01/12/2021.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/adventofcode_inputday1.txt");
    bool counting = false;
    int previous = 0;
    int current = 0;
    int tally = 0;
    std::vector<int> inputvec;
    std::cout<<"##### PART 1 #####\n";
    if (infile.is_open()){
        std::cout<<"File Open\n";
        while (getline(infile,line)){
            stringstream ss;
            ss << line;
            ss >> current;
            inputvec.push_back(current);
            if (counting == true){
                if (current > previous){
                    std::cout<<current<<">"<<previous<<"\n";
                    tally++;
                }
            }
            previous = current;
            counting = true;
        }
    }
    else {
        std::cout<<"Unable to open";
    }
    std::cout<<"Answer: "<<tally<<"\n";
    
    
    
    std::cout<<"##### PART 2 #####\n";
    int currentsum;
    int previoussum;
    counting = false;
    tally = 0;
    for (int i = 0;i<inputvec.size()-2;i++){
//        std::cout<<i<<"\n";
        currentsum = inputvec[i]+inputvec[i+1]+inputvec[i+2];
        if (counting == true){
            if (currentsum > previoussum){
                std::cout<<currentsum<<">"<<previoussum<<"\n";
                tally++;
            }
        }
        previoussum = currentsum;
        counting = true;
    }
    std::cout<<"Answer: "<<tally<<"\n";
    
    
}



