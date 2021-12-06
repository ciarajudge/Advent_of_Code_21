//
//  day6.cpp
//  
//
//  Created by Ciara Judge on 06/12/2021.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include <boost>

//using namespace boost::multiprecision;
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


void multiplier(vector<int> &invec) {
    int extras = 0;
    for (int i = 0 ; i<invec.size(); i++){
        invec[i] = invec[i]-1;
        if (invec[i]==-1){
            invec[i]=6;
            extras++;
        }
    }
    for (int i = 0; i<extras;i++){
        invec.push_back(8);
    }
}

void adjuster(vector<long int> &invec) {
    long int turnover = invec[0];
    for (int i = 0 ; i<invec.size()-1; i++){
        invec[i] = invec[i+1];
    }
    invec[invec.size()-1] = turnover;
    invec[6] = invec[6] +turnover;
}



int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day6input.txt");
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
    /*
    for (int i = 0; i<256; i++){
        std::cout<<i<<"\n";
        multiplier(input);
    }
    
    std::cout<<"Day 256: "<<input.size()<<"\n";
    */
    
//    alternate approach
    vector<long int> numatcurrent;
    for (int i=0;i<9;i++){
        long int count = 0;
        for (int j=0;j<input.size();j++){
            if(input[j]==i){
                count++;
            }
        }
        numatcurrent.push_back(count);
    }
//    printvec(numatcurrent);
    
    for (int i = 0; i<256; i++){
        adjuster(numatcurrent);
    }
//    printvec(numatcurrent);
    long int sum=0;
    for (int i=0; i<numatcurrent.size();i++){
        sum = sum + numatcurrent[i];
    }
    
    std::cout<<sum<<"\n";
    
}
