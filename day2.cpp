//
//  day2.cpp
//  
//
//  Created by Ciara Judge on 02/12/2021.
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
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day2input.txt");
    int horpoz = 0;
    int depth = 0;
    std::cout<<"##### PART 1 #####\n";
    std::string delimiter = " ";
    if (infile.is_open()){
        std::cout<<"File Open\n";
        while (getline(infile,line)){
            int value;
            std::string mvttype = line.substr(0, line.find(delimiter));
            std::string strvalue = line.substr(line.find(delimiter)+1, line.size());
            stringstream ss;
            ss << strvalue;
            ss >> value;
            std::cout<<value<<"\n";
            std::cout<<mvttype<<"\n";
            if (mvttype == "forward"){
                horpoz = horpoz + value;
            }
            else if (mvttype == "down"){
                depth = depth + value;
            }
            else {
                depth = depth - value;
            }
        }
    }
    else {
        std::cout<<"Unable to open";
    }
    std::cout<<horpoz<<"\n";
    std::cout<<depth<<"\n";
    std::cout<<horpoz*depth<<"\n";
    
    infile.close();
    std::cout<<"##### PART 2 #####";
    horpoz = 0;
    depth = 0;
    int aim = 0;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day2input.txt");
    if (infile.is_open()){
        while (getline(infile,line)){
            int value;
            std::string mvttype = line.substr(0, line.find(delimiter));
            std::string strvalue = line.substr(line.find(delimiter)+1, line.size());
            stringstream ss;
            ss << strvalue;
            ss >> value;
            if (mvttype == "forward"){
                horpoz = horpoz + value;
                depth = depth + (aim*value);
            }
            else if (mvttype == "down"){
                aim = aim + value;
            }
            else {
                aim = aim - value;
            }
            std::cout<<horpoz<<"\n";
            std::cout<<depth<<"\n";
            std::cout<<aim<<"\n";
        }
    }
    else {
        std::cout<<"Unable to open";
    }
    std::cout<<horpoz<<"\n";
    std::cout<<depth<<"\n";
    std::cout<<horpoz*depth<<"\n";
    
    
}






