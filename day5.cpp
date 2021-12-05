//
//  day5.cpp
//  
//
//  Created by Ciara Judge on 05/12/2021.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include "head.hpp"

using namespace std;

vector<string> splitstring(std::string str, std::string delimiter){
    int len = delimiter.size();
    vector<string> outvec;
    std::size_t found = str.find(delimiter);
    if (found!=std::string::npos){
        outvec.push_back(str.substr(0, found));
        outvec.push_back(str.substr(found+len, str.size()-(found+len)));
    }
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

void iterthruinput(std::string line, vector<int> &x1, vector<int> &y1, vector<int> &x2, vector<int> &y2) {
//    vector<string> v1;
    vector<string> v1 = splitstring(line, " -> ");
    vector<string> v2 = splitstring(v1[0], ",");
    vector<string> v3 = splitstring(v1[1], ",");
    int value = stringtoint(v2[0]);
    int value2 = stringtoint(v2[1]);
    int value3 = stringtoint(v3[0]);
    int value4 = stringtoint(v3[1]);
    x1.push_back(value);
    y1.push_back(value2);
    x2.push_back(value3);
    y2.push_back(value4);
    
}

vector<vector<int> > createfield(int xmax, int ymax) {
    vector<vector<int> > field;
    for (int i=0; i<ymax+1; i++){
        vector<int> placeholder;
        for (int j=0;j<xmax+1;j++){
            placeholder.push_back(0);
        }
        field.push_back(placeholder);
    }
    return field;
}

void printfield(vector<vector<int> > field){
    for (int i=0 ; i<field.size(); i++){
        printvec(field[i]);
    }
}

void addtomaphorizvert(vector<vector<int> > &field, int x1, int y1, int x2, int y2) {
//    check if horizontal or vertical
    if (x1 == x2 || y1 == y2) {
        if (x1 == x2){
            int x = x1;
            vector<int> ys = {y1,y2};
            auto ymax = *max_element(std::begin(ys), std::end(ys));
            auto ymin = *min_element(std::begin(ys), std::end(ys));
            for (int y=ymin; y<ymax+1; y++) {
                field[y][x]++;
            }
        }
        else if (y1 == y2){
            int y = y1;
            vector<int> xs = {x1,x2};
            auto xmax = *max_element(std::begin(xs), std::end(xs));
            auto xmin = *min_element(std::begin(xs), std::end(xs));
            for (int x=xmin; x<xmax+1; x++) {
                field[y][x]++;
            }
        }
    }
}

void addtomap(vector<vector<int> > &field, int x1, int y1, int x2, int y2) {
    if (x1 == x2){
        int x = x1;
        vector<int> ys = {y1,y2};
        auto ymax = *max_element(std::begin(ys), std::end(ys));
        auto ymin = *min_element(std::begin(ys), std::end(ys));
        for (int y=ymin; y<ymax+1; y++) {
            field[y][x]++;
        }
    }
    else if (y1 == y2){
        int y = y1;
        vector<int> xs = {x1,x2};
        auto xmax = *max_element(std::begin(xs), std::end(xs));
        auto xmin = *min_element(std::begin(xs), std::end(xs));
        for (int x=xmin; x<xmax+1; x++) {
            field[y][x]++;
        }
    }
    else {
        int yinc;
        int xinc;
        int numpoints;
        if (y2 > y1){
            yinc = 1;
        }
        else {yinc = -1;}
        if (x2 >x1){
            xinc = 1;
            numpoints = x2-x1;
        }
        else {xinc = -1;
            numpoints = x1-x2;
        }
        
        for (int i=0;i<numpoints+1;i++){
            field[y1+(yinc*i)][x1+(xinc*i)]++;
        }
        
    }
}

int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day5input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
//    Iterate through lines to make vectors
    vector<int> x1;
    vector<int> y1;
    vector<int> x2;
    vector<int> y2;
    for (int i=0; i < lines.size(); i++){
        iterthruinput(lines[i], x1, y1, x2, y2);
    }
    
    printvec(x1);
    printvec(y1);
    printvec(x2);
    printvec(y2);
    
//    Lay out playing field
    auto x1max = *max_element(std::begin(x1), std::end(x1));
    auto x2max = *max_element(std::begin(x2), std::end(x2));
    auto y1max = *max_element(std::begin(y1), std::end(y1));
    auto y2max = *max_element(std::begin(y2), std::end(y2));
    vector<int> xmaxs = {x1max, x2max};
    vector<int> ymaxs = {y1max, y2max};
    auto xmax = *max_element(std::begin(xmaxs), std::end(xmaxs));
    auto ymax = *max_element(std::begin(ymaxs), std::end(ymaxs));
    
    std::cout<<xmax<<" "<<ymax<<"\n";
    
    vector<vector<int> > playingfield = createfield(xmax, ymax);
    
    printfield(playingfield);
    
//    Add vents to map
    for (int i=0;i<x1.size();i++){
        std::cout<<x1[i]<<y1[i]<<x2[i]<<y2[i]<<"\n";
        addtomaphorizvert(playingfield, x1[i], y1[i], x2[i], y2[i]);
    }
    
    printfield(playingfield);
    
    
//    Count how many points > 2
    int count = 0;
    for (int i=0; i < playingfield.size(); i++){
        for (int j=0; j < playingfield[i].size(); j++){
            if(playingfield[i][j] >1){
                count++;
            }
        }
    }
    std::cout<<count<<"\n";
    
    
    
//    PART 2
    vector<vector<int> > playingfield2 = createfield(xmax, ymax);
//    Add vents to map
      for (int i=0;i<x1.size();i++){
          std::cout<<x1[i]<<y1[i]<<x2[i]<<y2[i]<<"\n";
          addtomap(playingfield2, x1[i], y1[i], x2[i], y2[i]);
      }
      
      printfield(playingfield2);
      
      
  //    Count how many points > 2
      count = 0;
      for (int i=0; i < playingfield.size(); i++){
          for (int j=0; j < playingfield2[i].size(); j++){
              if(playingfield2[i][j] >1){
                  count++;
              }
          }
      }
      std::cout<<count<<"\n";
    
}

