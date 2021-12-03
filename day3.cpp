//
//  day3.cpp
//  
//
//  Created by Ciara Judge on 03/12/2021.
//


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void part2(std::vector<std::string> &vec, int ind, std::string variable ){
    int onecount=0;
    int zerocount=0;
    std::vector<int> oneindices;
    std::vector<int> zeroindices;
    std::string current;
    char spotlighttemp;
    for (int i = 0; i < vec.size(); i++){
//        std::cout<<vec[i]<<"\n";
        current = vec[i];
        spotlighttemp = current[ind];
        int spotlight = spotlighttemp - '0';
        if (spotlight == 0){
            zeroindices.push_back(i);
            zerocount++;
        }
        else if (spotlight == 1){
            oneindices.push_back(i);
            onecount++;
        }
        else {
            std::cout<<"Error\n";
        }
    }
    std::vector<int> indices;
//    std::cout<<onecount<<"\n";
//    std::cout<<zerocount<<"\n";
    if (onecount>=zerocount && variable == "oxygen"){
        indices = oneindices;
    }
    else if (onecount<zerocount && variable == "oxygen"){
        indices = zeroindices;
    }
    else if (onecount>=zerocount && variable == "co2"){
        indices = zeroindices;
    }
    else if (onecount<zerocount && variable == "co2"){
        indices = oneindices;
    }
    else {
        std::cout<<"Error\n";
    }
    
    std::vector<std::string> tempvec;
    for (int i=0 ; i<indices.size() ; i++){
        tempvec.push_back(vec[indices[i]]);
    }
    
    vec = tempvec;

}




int main() {
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day3input.txt");
    

    std::cout<<"##### PART 1 #####\n";
    std::vector<int> biginput;
    int numlines=0;
    int perline;
    std::vector<std::string> part2vec;
    if (infile.is_open()){
        std::cout<<"File Open\n";
        while (getline(infile,line)){
            numlines++;
            part2vec.push_back(line);
            for (int i=0 ; i<line.size() ; i++){
                perline = line.size();
                int value;
                int value2;
                char a = line[i];
                stringstream ss;
                ss << a;
                ss >> value;
                biginput.push_back(value);
            }
        }
    }
    else {
        std::cout<<"Unable to open";
    }
    int numzero;
    int numone;
    int num;
    std::cout<<"Checkpoint\n";
    for (int i=0 ; i<perline ; i++){
        std::vector<int> vec;
        numzero = 0;
        numone = 0;
        for (int j=0 ; j<numlines ; j++){
            num = biginput[i + (j*perline)];
            if (num == 0){
                numzero++;
            }
            else if (num == 1){
                numone++;
            }
            else{
                std::cout<<"Error\n";
            }
        }
        if (numzero>numone){
            std::cout<<0;
        }
        else {
            std::cout<<1;
        }
        std::cout<<"\n";
    }
    
    std::vector<std::string> copy = part2vec;
    
    std::cout<<"\n##### PART 2 #####\n";
    int x = 0;
    while (part2vec.size()>1){
        part2(part2vec, x, "oxygen");
        x++;
    }
    std::cout<<part2vec.size()<<"\n";
    std::cout<<part2vec[0]<<"\n";
    
    x = 0;
    while (copy.size()>1){
        part2(copy, x, "co2");
        x++;
    }
    std::cout<<copy.size()<<"\n";
    std::cout<<copy[0]<<"\n";
    
    
    
}



