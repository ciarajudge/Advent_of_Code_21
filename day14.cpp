//
//  day14.cpp
//  
//
//  Created by Ciara Judge on 15/12/2021.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <map>
#include <algorithm>

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

void printmatrix(vector<vector<string> > inmat){
    std::cout<<"\n";
    for (int i= 0; i<inmat.size(); i++) {
        printvec(inmat[i]);
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

void unique(vector<string> &vec){
  std::sort(vec.begin(), vec.end());
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
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


void editstring(string &instring, map<string, string> dict){
    string newstring;
    for (int i=0; i<instring.size()-1; i++){
        string str;
        string a;
        string b;
        a = instring[i];
        b = instring[i+1];
        str = a+b;
        newstring = newstring + dict[str];
    }
    string end;
    end = instring[instring.size()-1];
    newstring = newstring + end;
    instring = newstring;
}

vector<int> counter(string instring, vector<string> letters){
    vector<int> sizes;
    for (int l=0; l<letters.size(); l++){
        string letter = letters[l];
        int count = 0;
        for (int c=0; c<instring.size(); c++){
            string cand;
            cand = instring[c];
            if (cand == letter) {
                count++;
            }
        }
        sizes.push_back(count);
        std::cout<<letter<<" count: "<<count<<"\n";
    }
    return sizes;
}

void editdict(map<string, long int> &stringdict, map<string, string> staticdict, vector<string> alldimers, map<string, long int> templatedict){
    for (int i=0; i<alldimers.size(); i++){
        string dimer = alldimers[i];
        string newseq = staticdict[dimer];
        string a1;
        string a2;
        a1 = newseq[0];
        a2 = newseq[1];
        string a = a1+a2;
        string b1;
        string b2;
        b1 = newseq[1];
        b2 = dimer[1];
        string b = b1 + b2;
        templatedict[a] = templatedict[a] + stringdict[dimer];
        templatedict[b] = templatedict[b] + stringdict[dimer];
    }
    stringdict = templatedict;
}

vector<long int> complexcounter(map<string, long int> stringdict, vector<string> letters, string finalletter){
    vector<long int> sizes;
    for (int l=0; l<letters.size(); l++){
        string letter = letters[l];
        long int count = 0;
        if (letter == finalletter){
            count++;
        }
        for(std::map<string,long int>::iterator it = stringdict.begin(); it != stringdict.end(); ++it) {
            auto key =  it->first;
            string monomer;
            monomer = key[0];
            if (monomer == letter){
                count = count + it->second;
            }
        }
        sizes.push_back(count);
        std::cout<<letter<<" count: "<<count<<"\n";
    }
    return sizes;
}

int main() {
//    Read in file to vector of lines
    ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day14input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
    string inputstring;
    map<string, string> dict;
    vector<string> allletters;
    bool first = true;
    for (string line:lines){
        if (line == ""){
            first = false;
            continue;
        }
        if (first == true) {
            inputstring = line;
            for (int i=0;i<line.size();i++){
                string t;
                t = inputstring[i];
                allletters.push_back(t);
            }
        }
        else {
            vector<string> splitted = splitstring(line, " -> ");
            string dimer = splitted[0];
            dict[dimer] = dimer[0]+splitted[1];
            string t;
            t = splitted[1];
            allletters.push_back(t);
        }
    }
    unique(allletters);
    printvec(allletters);
    string finalletter;
    finalletter = inputstring[inputstring.size()-1];
    
//  Some stuff for part 2 Start up the master dictionary of all dimers
    map<string, long int> masterdict;
    vector<string> alldimers;
    for (int i=0;i<allletters.size();i++){
        for(int j=0;j<allletters.size();j++){
            masterdict[allletters[i]+allletters[j]] = 0;
            alldimers.push_back(allletters[i]+allletters[j]);
        }
    }
    map<string, long int> masterdicttemplate = masterdict;
    string inputstringcopy = inputstring;
    for (int i=0; i<inputstring.size()-1; i++){
        string str;
        string a;
        string b;
        a = inputstring[i];
        b = inputstring[i+1];
        str = a+b;
        masterdict[str] = masterdict[str]+1;
    }

    
    //Part 1
    std::cout<<inputstring<<"\n";
    for (int i = 0; i<10;i++){
        editstring(inputstring, dict);
    }
    
    vector<int> counts = counter(inputstring, allletters);
    auto min = *min_element(std::begin(counts), std::end(counts));
    auto max = *max_element(std::begin(counts), std::end(counts));
    int answer = max - min;
    
    std::cout<<"Part 1 answer: "<<answer<<"\n";
    
     //Part 2
    printvec(alldimers);
    for(std::map<string,long int>::iterator it = masterdict.begin(); it != masterdict.end(); ++it) {
      std::cout << "Key: " << it->first <<"\n";
      std::cout << "Value: " << it->second << "\n";
    }
    std::cout<<"\n";
    for (int i = 0; i<40;i++){
        editdict(masterdict, dict, alldimers, masterdicttemplate);
    }
    
    for(std::map<string,long int>::iterator it = masterdict.begin(); it != masterdict.end(); ++it) {
      std::cout << "Key: " << it->first <<"\n";
      std::cout << "Value: " << it->second << "\n";
    }
    vector<long int> part2counts = complexcounter(masterdict, allletters, finalletter);
    auto min2 = *min_element(std::begin(part2counts), std::end(part2counts));
    auto max2 = *max_element(std::begin(part2counts), std::end(part2counts));
    long int part2answer = max2 - min2;
    
    std::cout<<"Part 2 answer: "<<part2answer<<"\n";
}

