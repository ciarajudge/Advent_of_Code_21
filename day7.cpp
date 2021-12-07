//
//  day7.cpp
//  
//
//  Created by Ciara Judge on 07/12/2021.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

vector<string> splitstring(std::string str, std::string delimiter){
    int len = delimiter.size();
    int stringlen = str.size();
    vector<string> outvec;
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        outvec.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    outvec.push_back(str);
    return outvec;
}

void printvec(vector<int> vec){
    for (int i=0;i<vec.size();i++){
        std::cout<<vec[i]<<" ";
    }
    std::cout<<"\n";
}
void printvecs(vector<string> vec){
    for (int i=0;i<vec.size();i++){
        std::cout<<vec[i]<<" ";
    }
    std::cout<<"\n";
}

int stringtoint(std::string str){
    int value;
    stringstream ss;
    ss << str;
    ss >> value;
    return value;
}

int getfuel(vector<int> invec, int target){
    int sum = 0;
    for (int i=0; i<invec.size();i++){
        int dist = abs(invec[i] - target);
        sum += dist;
    }
    return sum;
}

int getfuel2(vector<int> invec, int target){
    int sum = 0;
    for (int i=0; i<invec.size();i++){
        int dist = abs(invec[i] - target);
        for (int j=1;j<dist+1;j++){
            sum += j;
        }
    }
    return sum;
}


int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day7input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
    line = lines[0];
    vector<string> stringinput = splitstring(line, ",");
    vector<int> input;
    for (int i =0 ; i<stringinput.size();i++){
        input.push_back(stringtoint(stringinput[i]));
    }
    printvec(input);
    
    auto inputmin = *min_element(std::begin(input), std::end(input));
    auto inputmax = *max_element(std::begin(input), std::end(input));
    int fuel = std::numeric_limits<int>::max();
    int newfuel;
    int besttarget;
    for (int i=inputmin;i<inputmax+1;i++){
        newfuel = getfuel(input, i);
        if (newfuel < fuel) {
            fuel = newfuel;
            besttarget = i;
        }
    }
    
    std::cout<<"Score: "<<fuel<<"\n";
    std::cout<<"Target: "<<besttarget<<"\n";
    
    
//    Part 2
    fuel = std::numeric_limits<int>::max();
    newfuel = fuel;
    besttarget = 0;
    for (int i=inputmin;i<inputmax+1;i++){
        newfuel = getfuel2(input, i);
        if (newfuel < fuel) {
            fuel = newfuel;
            besttarget = i;
        }
    }
    
    std::cout<<"Score: "<<fuel<<"\n";
    std::cout<<"Target: "<<besttarget<<"\n";
    
}
