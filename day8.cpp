//
//  day8.cpp
//  
//
//  Created by Ciara Judge on 08/12/2021.
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

int stringtoint(std::string str){
    int value;
    stringstream ss;
    ss << str;
    ss >> value;
    return value;
}

string concatvector(vector<string> invec) {
    string output = invec[0];
    for (int i=1;i<invec.size();i++ ){
        output = output+" "+invec[i];
    }
    return output;
}

vector<string> guessdigit(std::string instring){
    vector<string> splitted = splitstring(instring, " ");
    vector<string> newguess;
    for (string word:splitted) {
        switch (word.length()){
            case 7:
                word = "8";
                break;
            case 4:
                word = "4";
                break;
            case 2:
                word = "1";
                break;
            case 3:
                word = "7";
                break;
            default:
                word = word;
        }
        newguess.push_back(word);
    }
    return newguess;
}

string outlier(string big, string small){ //Use if you know there will only be one outlier
    string out = "x";
    for (int i = 0; i<small.size();i++){
        bool found = false;
        for (int j = 0; j<big.size(); j++){
            if (big[j] == small[i]){
                found = true;
            }
        }
        if (found == false) {
            out = small[i];
        }
    }
    return out;
}

string alphabetical(string str){
    int len = str.size();
        for(int i=0; i<len; i++)
        {
            for(int j=0; j<(len-1); j++)
            {
                if(str[j]>str[j+1])
                {
                    char ch = str[j];
                    str[j] = str[j+1];
                    str[j+1] = ch;
                }
            }
        }
    return str;
}

int guessdigit2(std::string instring, std::string outstring){
    map<string, int> dict;
    map<int, string> dictcopy;
    map<string, string> match;
    vector<string> splitted = splitstring(instring, " ");
    vector<string> outvec = splitstring(outstring, " ");
    vector<string> newguess;
    vector<string> fives;
    vector<string> sixes;
    for (string word:splitted) {
        switch (word.length()){
            case 7:
                dict[alphabetical(word)] = 8;
                dictcopy[8] = word;
                break;
            case 4:
                dict[alphabetical(word)] = 4;
                dictcopy[4] = word;
                break;
            case 2:
                dict[alphabetical(word)] = 1;
                dictcopy[1] = word;
                break;
            case 3:
                dict[alphabetical(word)] = 7;
                dictcopy[7] = word;
                break;
            case 5:
                fives.push_back(alphabetical(word));
                break;
            case 6:
                sixes.push_back(alphabetical(word));
                break;
            default:
                std::cout<<"somethings gone wrong\n";
        }
    }
    string confirmedletters = "";
//    We can find g now as it's in 8 and not the others
    match[outlier(dictcopy[1]+dictcopy[4]+dictcopy[7], dictcopy[8])] = "g";
    confirmedletters = confirmedletters+outlier(dictcopy[1]+dictcopy[4]+dictcopy[7], dictcopy[8]);
//    Same with a
    match[outlier(dictcopy[7], dictcopy[1])] = "a";
    confirmedletters = confirmedletters+outlier(dictcopy[7], dictcopy[1]);
//  We can also find 6, as the only member of 'sixes' that will not have all numbers in common with 1
    for (string member:sixes){
        string guess = outlier(member, dictcopy[1]);
        if (guess != "x"){
            dictcopy[6] = member;
            dict[member] = 6;
            match[guess] = "c";
            confirmedletters = confirmedletters+guess;
            match[outlier(guess+outlier(dictcopy[7], dictcopy[1]), dictcopy[7])]="f";
            confirmedletters = confirmedletters+outlier(guess+outlier(dictcopy[7], dictcopy[1]), dictcopy[7]);
            auto itr = std::find(sixes.begin(), sixes.end(), member);
            sixes.erase(itr);
            break;
        }
    }
//    Now find 0 and 9
    for (string member:sixes){
        string guess = outlier(member, dictcopy[4]);
        if (guess != "x"){
            dictcopy[0] = member;
            dict[member] = 0;
            match[guess] = "d";
            confirmedletters = confirmedletters+guess;
            auto itr = std::find(sixes.begin(), sixes.end(), member);
            sixes.erase(itr);
            break;
        }
    }
    dictcopy[9] = sixes[0];
    dict[sixes[0]] = 9;
    match[outlier(dictcopy[8], dictcopy[9])] = "e";
    confirmedletters = confirmedletters+outlier(dictcopy[8], dictcopy[9]);
    
    
    for (string member:fives){
        string guess = outlier(dictcopy[6], member);
        if (guess == "x"){
            dictcopy[5] = member;
            dict[member] = 5;
            match[guess] = "b";
            confirmedletters = confirmedletters+guess;
            auto itr = std::find(fives.begin(), fives.end(), member);
            fives.erase(itr);
            break;
        }
    }
    
    for (string member:fives){
        string guess = outlier(dictcopy[9]+dictcopy[5], member);
        if (guess != "x"){
            dictcopy[2] = member;
            dict[member] = 2;
            auto itr = std::find(fives.begin(), fives.end(), member);
            fives.erase(itr);
            break;
        }
    }
    dictcopy[3] = fives[0];
    dict[fives[0]] = 3;
    
    
    int sum = 0;
    int mult = 1000;
    for (string word:outvec){
        sum = sum + (mult*dict[alphabetical(word)]);
        mult = mult/10;
    }

    return sum;
}


int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day8input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
    vector<string> outputs;
    vector<string> inputs;
    for (string line:lines){
        inputs.push_back(splitstring(line, " | ")[0]);
        outputs.push_back(splitstring(line, " | ")[1]);
    }

    
    int count = 0;
    for (string line: outputs){
        vector<string> guesses = guessdigit(line);
        printvec(guesses);
        for (string digit: guesses){
//            I can only describe this approach as ham fisted
            if (digit == "1"){
                count++;
            }
            else if (digit == "4"){
                count++;
            }
            else if (digit == "7") {
                count++;
            }
            else if (digit == "8" ){
                count++;
            }
        }
    }
    
    std::cout<<count<<"\n";
    
    int sum = 0;
    for (int i = 0; i<inputs.size(); i++){
        int out = guessdigit2(inputs[i], outputs[i]);
        std::cout<<out<<"\n";
        sum += out;
    }
    std::cout<<"Total: "<<sum<<"\n";
}
