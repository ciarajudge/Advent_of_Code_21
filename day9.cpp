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

string concatvector(vector<string> invec) {
    string output = invec[0];
    for (int i=1;i<invec.size();i++ ){
        output = output+" "+invec[i];
    }
    return output;
}

int checksurroundings(vector<vector<int> > invec, int i, int j){
    bool islowest = true;
    int risk = 0;
    vector<int> neighbours;
    
//  Top and bottom neighbours
    if (i-1 >= 0) {
        neighbours.push_back(invec[i-1][j]);
    }
    if (i+1 <= invec.size()-1) {
        neighbours.push_back(invec[i+1][j]);
    }
//    Side to side neighbours
    if (j-1 >= 0) {
        neighbours.push_back(invec[i][j-1]);
    }
    if (j+1 <= invec[i].size()-1) {
        neighbours.push_back(invec[i][j+1]);
    }
    
//    std::cout<<"Neighbours of "<<invec[i][j]<<":";
//    printvec(neighbours);
    
    for (int neighbour:neighbours){
        if (neighbour <= invec[i][j]){
            islowest = false;
        }
    }
    
    
    if (islowest){
        risk = invec[i][j]+1;
    }
    
    return risk;
}

void coordsoflowestpoints(vector<vector<int> > invec, int i, int j, vector<vector<int> > &coordvector){
    bool islowest = true;
    int risk = 0;
    vector<int> neighbours;
    
//  Top and bottom neighbours
    if (i-1 >= 0) {
        neighbours.push_back(invec[i-1][j]);
    }
    if (i+1 <= invec.size()-1) {
        neighbours.push_back(invec[i+1][j]);
    }
//    Side to side neighbours
    if (j-1 >= 0) {
        neighbours.push_back(invec[i][j-1]);
    }
    if (j+1 <= invec[i].size()-1) {
        neighbours.push_back(invec[i][j+1]);
    }
    
//    std::cout<<"Neighbours of "<<invec[i][j]<<":";
//    printvec(neighbours);
    
    for (int neighbour:neighbours){
        if (neighbour <= invec[i][j]){
            islowest = false;
        }
    }
    
    
    if (islowest){
        coordvector.push_back({i,j});
    }
    
}

vector<int> sortascending(vector<int> str){
    int len = str.size();
        for(int i=0; i<len; i++)
        {
            for(int j=0; j<(len-1); j++)
            {
                if(str[j]>str[j+1])
                {
                    int ch = str[j];
                    str[j] = str[j+1];
                    str[j+1] = ch;
                }
            }
        }
    return str;
}

vector<vector<int> > mapadjuster(vector<vector<int> > invec){
    for (int i=0;i<invec.size();i++){
        for (int j=0;j<invec[i].size();j++){
            if (invec[i][j] != 9){
                invec[i][j] =0;
            }
        }
    }
    
    return invec;

}

bool window(vector<vector<int> > invec, vector<vector<int> > &coordlist, vector<int> coords) {
    int midi = coords[0];
    int midj = coords[1];
    bool edge = true;
    
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
    
    vector<int> is = {midi, mini, midi, maxi, midi};
    vector<int> js = {midj, midj, maxj, midj, minj};
//    std::cout<<midi<<","<<midj<<"\n";
    for (int x=0;x<is.size();x++){
        int i = is[x];
        int j = js[x];
            vector<int> tempvec = {i,j};
            if (invec[i][j] != 9) {
                bool alreadypresent = false;
                for (vector<int> v:coordlist){
                    if (v == tempvec){
                        alreadypresent = true;
                    }
                }
                if (alreadypresent==false){
                    coordlist.push_back(tempvec);
                    edge = false;
                }
            }

    }
    
    return edge;
    
}



int getbasinsize(vector<vector<int> > invec, vector<int> lowcoords) {
    bool basin = true;
    int area=0;
    vector<vector<int> > basincoords = {lowcoords};
    while (basin) {
        basin = false;
        for (int c=0;c<basincoords.size(); c++){
            vector<int> coords = basincoords[c];
            if(window(invec, basincoords, coords) == false ){
                basin = true;
            }
        }
    }
    for(vector<int> v:basincoords){
        area++;
        printvec(v);
    }

    return area;
}





int main() {
//    Read in file to vector of lines
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day9input.txt");
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
        printvec(intvec);
        intlines.push_back(intvec);
    }
    
    int sum = 0;
    for (int i=0;i<intlines.size();i++) {
        for (int j=0; j<intlines[i].size();j++){
            sum += checksurroundings(intlines, i, j);
        }
    }
    
    std::cout<<"Answer: "<<sum<<"\n";
    
//    Get coords of lowest points, it might help idk
    vector<vector<int> > coords;
    for (int i=0;i<intlines.size();i++) {
        for (int j=0; j<intlines[i].size();j++){
            coordsoflowestpoints(intlines, i, j, coords);
        }
    }

    
    vector<vector<int> > newmap = mapadjuster(intlines);
    for (vector<int> line:newmap){
        printvec(line);
    }
    
    vector<int> basinsizes;
    for (int i=0;i<coords.size();i++){
        printvec(coords[i]);
        basinsizes.push_back(getbasinsize(newmap, coords[i]));
    }
    
    printvec(basinsizes);
    
    vector<int> sorted = sortascending(basinsizes);
    
    printvec(sorted);
    int ans = sorted[sorted.size()-1]*sorted[sorted.size()-2]*sorted[sorted.size()-3];
    std::cout<<"Answer: "<<ans<<"\n";
}

