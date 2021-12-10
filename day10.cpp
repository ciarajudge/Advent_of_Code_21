//
//  day9.cpp
//  
//
//  Created by Ciara Judge on 09/12/2021.
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

string reducetoillegal(string instring) {
    bool finished = false;
    while (finished == false){
        vector<bool> status;
        status.push_back(remove(instring, "()"));
        status.push_back(remove(instring, "[]"));
        status.push_back(remove(instring, "{}"));
        status.push_back(remove(instring, "<>"));

        finished = true;
        for (bool b:status){
            if (b){
                finished = false;
            }
        }
    }
    return(instring);
}

int getscore(string str){
    string reduced = reducetoillegal(str);
    bool incomplete = true;
    string candidates =")]}>";
    for (int j=0;j<candidates.size();j++){
        for (int i=0;i<reduced.size(); i++){
            if (reduced[i] == candidates[j]){
                incomplete = false;
            }
        }
    }
    if (incomplete == true){
        return 0;
    }
    else {
        remove(reduced, "(");
        remove(reduced, "{");
        remove(reduced, "[");
        remove(reduced, "<");
        auto first = reduced[0];
        if (first == candidates[0]) {
            return 3;
        }
        else if (first == candidates[1]){
            return 57;
        }
        else if (first == candidates[2]){
            return 1197;
        }
        else {
            return 25137;
        }
    }
}


long int part2(string str){
    string reduced = reducetoillegal(str);
    std::cout<<reduced<<"\n";
    map<char, int> dict;
    dict['('] = 1;
    dict['['] = 2;
    dict['{'] = 3;
    dict['<'] = 4;
    long int current = 0;
    
    for (int i = reduced.size()-1 ; i>-1;i--){
        std::cout<<i<<"\n";
        current = current*5;
        current = current+dict[reduced[i]];
    }
    
    return current;
    
}


int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day10input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
    
    int sum = 0;
    for (string line:lines){
        std::cout<<reducetoillegal(line)<<"\n";
        sum += getscore(line);
    }
    
    std::cout<<"Part 1 Answer: "<<sum<<"\n";
    
    vector<string> incompletes;
    for (string line:lines){
        if (getscore(line)==0){
            incompletes.push_back(line);
        }
    }
    
    vector<long int> part2scores;
    for (string line:incompletes){
        part2scores.push_back(part2(line));
    }
    printvec(part2scores);
    vector<long int> sorted = sortascending(part2scores);
    printvec(sorted);
    long int answer = sorted[(sorted.size()/2)+0.5];
    std::cout<<"Part 2 Answer: "<<answer<<"\n";
    
}

