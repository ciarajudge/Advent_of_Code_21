//
//  day4.cpp
//  
//
//  Created by Ciara Judge on 04/12/2021.
//

#include "day4.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



using namespace std;

void updatecards(int number, vector<vector<int> > &cards) {
    for (int i = 0; i < cards.size() ; i++){
        for (int j = 0; j<cards[i].size() ; j++){
            if (cards[i][j] == number) {
                cards[i][j] = 101;
            }
        }
    }
}

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(" ");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

vector<int> checkwinner(vector<vector<int> > cards){
    vector<vector<int> > winningcombos = {{0,1,2,3,4}, {5,6,7,8,9}, {10,11,12,13,14}, {15,16,17,18,19}, {20,21,22,23,24}, {1,6,11,16,21}, {2,7,12,17,22}, {3,8,13,18,23}, {4,9,14,19,24}, {0,5,10,15,20}};
    
    vector<int> winners;
    for (int i = 0; i<cards.size(); i++) {
        vector<int> currentcard = cards[i];
        for (int x=0;x<currentcard.size();x++){
            currentcard[x] = currentcard[x];
        }

        for (int j = 0; j<winningcombos.size(); j++) {
            vector<int> currentcombo = winningcombos[j];
            int crossedoff = 0;
            /*
            std::cout<<"Current combo: "<<j<<"\n";
            */
            for (int k=0; k<currentcombo.size(); k++) {
//                std::cout<<currentcombo[k]<<" ";
//                std::cout<<currentcard[currentcombo[k]]<<" ";
                if (currentcard[currentcombo[k]] == 101){
                    crossedoff++;
                }
            }
//            std::cout<<"\n";
            if (crossedoff == 5){
                winners.push_back(i);
            }
        }
    }
    winners.erase( unique( winners.begin(), winners.end() ), winners.end() );
    return winners;
}


int main(){
//    Parsing all the lines into a vector
    std::ifstream infile;
    string line;
    infile.open("/Users/ciarajudge/Desktop/Advent_of_Code_21/day4input.txt");
    vector<string> lines;
    while (getline(infile,line)){
        lines.push_back(line);
    }
    int value;
    string firstline = lines[0];
    std::cout<<firstline<<"\n";
    stringstream ss(firstline);
    vector<string> bingonumberscopy;
    vector<int> bingonumbers;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        bingonumberscopy.push_back( substr );
    }
    for (int i=0; i<bingonumberscopy.size(); i++){
        stringstream ss;
        
        ss << bingonumberscopy[i];
        ss >> value;
        bingonumbers.push_back(value);
    }
    
//  Next going to sort the bingo cards into little vectors
    vector<vector<int> > bingocards;
    for (int i = 2; i <lines.size(); i+=6) {
        vector<string> tempcopy;
        for (int j = 0; j<5; j++){
            string l = lines[i+j];
            stringstream ss(l);
            while( ss.good() ) {
                string substr;
                getline( ss, substr, ' ' );
                tempcopy.push_back( trim(substr) );
            }
        }
        vector<int> temp;
        for (int x = 0;x<tempcopy.size(); x++) {
            stringstream ss(trim(tempcopy[x]));
            ss >> value;
//int value = std::stoi(trim(tempcopy[x]));
            std::cout<<value<<" ";
            temp.push_back(value);
        }
        temp.erase( unique( temp.begin(), temp.end() ), temp.end() );
        std::cout<<"\n";
        bingocards.push_back(temp);
     }
    
    for(int i=0; i<bingocards.size();i++){
        for(int j=0; j<bingocards[i].size();j++){
            std::cout<<bingocards[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    
    
    vector<vector<int> > bingocardscopy = bingocards;
//    Create a while loop to call the new bingo number, update all the cards, and check for a winner
    bool win = false;
    int inc = 0;
    while (win == false){
        if (inc == bingonumbers.size()){
            win = true;
        }
        std::cout<<bingonumbers[inc]<<" was drawn\n";
        
        updatecards(bingonumbers[inc], bingocards);
        
        for (int i = 0; i < bingocards.size() ; i++){
            for (int j = 0; j<bingocards[i].size() ; j++){
                    bingocards[i][j] = bingocards[i][j];
            }
        }
        /*
        for(int i=0; i<bingocards.size();i++){
            for(int j=0; j<bingocards[i].size();j++){
                std::cout<<bingocards[i][j]<<"";
            }
            std::cout<<"\n";
        }*/
        
        vector<int> checkingwin = checkwinner(bingocards);
        
        
        if (checkingwin.size() > 0){
            win = true;
            for (int i =0;i<checkingwin.size();i++){
                std::cout<<"\nTurn: "<<inc<<"\n";
                std::cout<<"Winner: "<<checkingwin[i]<<"\n";
                int sum = 0;
                for (int j=0; j<bingocards[checkingwin[i]].size(); j++){
                    std::cout<<bingocards[checkingwin[i]][j]<<" ";
                    if (bingocards[checkingwin[i]][j] != 101){
                        sum+=bingocards[checkingwin[i]][j];
                    }
                }
                std::cout<<"Sum of remaining: "<<sum<<"\n";
                int temp =  bingonumbers[inc];
                std::cout<<"Score: "<<temp*sum<<"\n";
            }
        }
        
        inc++;
    }
    
    
    
    std::cout<<"##### PART 2 - I'm losing my will to live #####\n";
    bool allwin = false;
    inc = 0;
    vector<int> oldcheckingwin;
    vector<int> newcheckingwin;
    while (allwin == false){
        if (inc == bingonumbers.size()) {
            allwin = true;
        }
        std::cout<<bingonumbers[inc]<<" was drawn\n";
        
        updatecards(bingonumbers[inc], bingocardscopy);
        
        newcheckingwin = checkwinner(bingocardscopy);
        
        if (newcheckingwin.size() >0) {
            int newitem = 0;
            for (int i =0;i<newcheckingwin.size();i++){
                if (std::count(oldcheckingwin.begin(), oldcheckingwin.end(), newcheckingwin[i])) {
                        int placeholder = 0;
                    }
                else {
                    newitem = newcheckingwin[i];
                }
            }
                std::cout<<"\nTurn: "<<inc<<"\n";
                std::cout<<"New winner: "<<newitem<<"\n";
                int sum = 0;
                for (int j=0; j<bingocardscopy[newitem].size(); j++){
                    std::cout<<bingocardscopy[newitem][j]<<" ";
                    if (bingocardscopy[newitem][j] != 101){
                        sum+=bingocardscopy[newitem][j];
                    }
                }
                std::cout<<"Sum of remaining: "<<sum<<"\n";
                int temp =  bingonumbers[inc];
                std::cout<<"Score: "<<temp*sum<<"\n";
            
        }
        
        oldcheckingwin = newcheckingwin;
        
        
        if (newcheckingwin.size() == bingocardscopy.size()){
            allwin = true;
        }
        inc++;
    }
    
    for (int i=0;i<newcheckingwin.size();i++) {
        std::cout<<newcheckingwin[i]<<"\n";
    }
}

