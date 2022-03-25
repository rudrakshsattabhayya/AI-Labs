#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Maze {
    vector<string> mazeStrings;
};

struct Coordinate {
    int x = -1,y = -1;
};


struct Node {
   struct Coordinate currentState, parentState;
};

//Global vector for storing all mazes
vector<struct Maze> mazes;

 vector<struct Node> MoveGen(
     struct Node currentNode, 
     vector<vector<struct Coordinate>> currentMazeParentLayout,
     vector<string> currentMazeStringLayout
 ){
     struct Coordinate down = {1,0}, up = {-1,0}, left = {0,-1}, right = {0,1};
     vector<struct Node> moveGenStates;// Going to set in opposite priorty
     
     return moveGenStates;
 }



int main(){

    struct Maze x;

    string inputLine = "";
    ifstream inputFile("input.txt");

      while(getline(inputFile, inputLine)){
          if(!inputLine.find("Input")){
              mazes.push_back(x);
          }else{
              mazes[mazes.size()-1].mazeStrings.push_back(inputLine);
          }
      }
    inputFile.close();

   
    for(int i=0;i<=0;i++){
        int rowSize = mazes[i].mazeStrings[0].size();
        int colSize = mazes[i].mazeStrings.size();
        vector<vector<struct Coordinate>> currentMazeLayout( colSize , vector<struct Coordinate> (rowSize)); // To store parent nodes
        struct Node ex = {{1;0;}; 
                            {0;0;};};
        MoveGen(ex, currentMazeLayout, mazes[0].mazeStrings);
    }

}