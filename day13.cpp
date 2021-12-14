//
//  day13.cpp
//  
//
//  Created by Ciara Judge on 14/12/2021.
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


vector<vector<string> > makecanvas(vector<int> xs, vector<int> ys) {
    vector<vector<string> > canvas;
    auto xmax = *max_element(std::begin(xs), std::end(xs));
    auto ymax = *max_element(std::begin(ys), std::end(ys));
    std::cout<<xmax<<" "<<ymax<<"\n";
    
    
    for (int i = 0; i<=ymax; i++) {
        vector<string> tempvec;
        for (int j = 0; j<=xmax; j++) {
            tempvec.push_back(".");
        }
        canvas.push_back(tempvec);
    }

    
    for (int i=0; i< xs.size();i++){
        canvas[ys[i]][xs[i]] = "#";
    }
    
    return canvas;
}


void fold(vector<vector<string> > &canvas, string foldinst) {
    string axis = splitstring(foldinst,"=")[0];
    int foldpoint = stringtoint(splitstring(foldinst,"=")[1]);
    vector<vector<string> > newcanvas;
    
    if (axis == "y") {
        for (int i=0; i< foldpoint; i++){
            newcanvas.push_back(canvas[i]);
        }
        for (int i= foldpoint+1; i<canvas.size(); i++){
            int newi = foldpoint - (i-foldpoint);
            for (int j = 0; j <canvas[i].size(); j++) {
                if (canvas[i][j] == "#"){
                    newcanvas[newi][j]= "#";
                }
            }
        }
        
        
    }
    
    if (axis == "x") {
        for (int i=0; i< canvas.size(); i++){
            vector<string> tempvec;
            for (int j = 0; j <canvas[i].size();j++) {
                if (j < foldpoint){
                    tempvec.push_back(canvas[i][j]);
                }
                else if (j == foldpoint){
                    continue;
                }
                else {
                    if (canvas[i][j] =="#"){
                        tempvec[foldpoint - (j-foldpoint)] = "#";
                    }
                }
            }
            newcanvas.push_back(tempvec);
        }
    }
    
    
    
    canvas = newcanvas;
    
    
    
    
}


int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day13input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
    vector<int> x;
    vector<int> y;
    vector<string> instructions;
    bool coords = true;
    for (string line:lines){
        if (line == ""){
            coords = false;
            continue;
        }
        if (coords == true) {
            x.push_back(stringtoint(splitstring(line, ",")[0]));
            y.push_back(stringtoint(splitstring(line, ",")[1]));
        }
        else {
            remove(line, "fold along ");
            instructions.push_back(line);
        }
    }
    
    printvec(x);
    printvec(y);
    printvec(instructions);
    
    vector<vector<string> > canvas = makecanvas(x,y);
    
    printmatrix(canvas);
    for (int i=0;i<instructions.size();i++){
        std::cout<<instructions[i]<<"\n";
        fold(canvas, instructions[i]);

    }
    
    printmatrix(canvas);
    
    int count = 0;
    for (int i = 0; i < canvas.size(); i++){
        for (int j = 0; j < canvas[i].size(); j++) {
            if (canvas[i][j] == "#"){
                count++;
            }
        }
    }
    std::cout<<"Number Visible: "<<count<<"\n";
    
    
    
}
