//
//  day11.cpp
//  
//
//  Created by Ciara Judge on 12/12/2021.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <map>

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
void printvec(vector<string> vec){
    for (int i=0;i<vec.size();i++){
        std::cout<<vec[i]<<" ";
    }
    std::cout<<"\n";
}
void printvec(vector<long int> vec){
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

int stringtoint(char str){
    int value;
    stringstream ss;
    ss << str;
    ss >> value;
    return value;
}

vector<long int> sortascending(vector<long int> str){
    int len = str.size();
        for(int i=0; i<len; i++)
        {
            for(int j=0; j<(len-1); j++)
            {
                if(str[j]>str[j+1])
                {
                    long int ch = str[j];
                    str[j] = str[j+1];
                    str[j+1] = ch;
                }
            }
        }
    return str;
}

string concatvector(vector<string> invec) {
    string output = invec[0];
    for (int i=1;i<invec.size();i++ ){
        output = output+invec[i];
    }
    return output;
}

bool remove(string &str, string delimiter) {
    string strcopy = str;
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
    
    str = concatvector(outvec);
    if (str == strcopy) {
        return false;
    }
    else {
        return true;
    }

}

void popadjuster(vector<vector<int> > &invec){
    for (int i=0;i<invec.size();i++){
        for (int j=0;j<invec[i].size();j++){
            invec[i][j]++;
        }
    }
}

void window(vector<vector<int> > &invec, vector<int> coords) {
    int midi = coords[0];
    int midj = coords[1];
    
    int mini = midi-1;
    int maxi = midi+1;
    int minj = midj-1;
    int maxj = midj+1;
    
    if (mini < 0 ){
        mini = 0;
    }
    if (minj < 0 ){
        minj = 0;
    }
    if (maxi > invec.size()-1 ){
        maxi = invec.size()-1;
    }
    if (maxj > invec[0].size()-1 ){
        maxj = invec[0].size()-1;
    }
    
    for (int i=mini;i<=maxi;i++){
        for (int j=minj;j<=maxj;j++){
            if (invec[i][j] != 0){
                invec[i][j] =  invec[i][j] +1;
            }
        }
    }
    invec[midi][midj] = 0;
}

void part1(vector<vector<int> > &invec, int &flashes) {
    popadjuster(invec);
    bool finished = false;
    while (finished == false) {
        int count = 0;
        for (int i=0;i<invec.size();i++){
            for (int j=0;j<invec[i].size();j++){
                if (invec[i][j] >= 10) {
                    count++;
                    flashes++;
                    window(invec, {i,j});
                }
            }
        }
        if (count == 0){
            finished = true;
        }
    }
    
}












int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day11input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
    vector<vector<int> > intlines;
    for (string line:lines){
        vector<int> intvec;
        for (int i=0;i<line.size();i++){
            intvec.push_back(stringtoint(line[i]));
        }
        intlines.push_back(intvec);
    }
    
    for (vector<int> line:intlines){
        printvec(line);
    }
    std::cout<<"\n";
    std::cout<<"\n";
    
    vector<vector<int> > intlinescopy = intlines;
    
    int flashes = 0;
    
    for (int i=0 ; i<100; i++){
        part1(intlines, flashes);
    }
    
    
    for (vector<int> line:intlines){
        printvec(line);
    }
    std::cout<<"Number of flashes: "<<flashes<<"\n";

    
//    Part 2
    int count = 0;
    bool sync = false;
    while (sync == false) {
        part1(intlinescopy, flashes);
        sync = true;
        for (int i=0;i<intlinescopy.size();i++){
            for (int j=0;j<intlinescopy[i].size();j++){
                if (intlinescopy[i][j] != 0) {
                    sync = false;
                    goto endloop;
                }
            }
        }
        
        endloop:
        count++;
    }
    
    for (vector<int> line:intlines){
        printvec(line);
    }
    
    std::cout<<"First point of synchronicity: "<<count<<"\n";
    
}

