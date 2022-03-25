#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<bitset>
#include<utility>
#include<stack>

struct Coordinate = {
    int x,y;
}

struct Node = {
   Coordinate currentState, parentState;
}

    <vector<vector<Coordinate>> parentStorageGrid;// yet to initialize
    
int DFS(int m, int n, Coordinate goalState){
    int numOfStatesExplored = 0;
    Node currentNode = {
        {0,0},
        {-1,-1}
    };
    vector<Node> temp;
    stack openNodes;
    
    while(openNodes.size())){
    if(GoalTest(currentNode.currentState,goalState)){
        tracePath(currentNode);// It will also include length of path
        break;
    }else{
        temp.clear();
        temp = MoveGen(currentNode);
        for(int i=0;i<temp.size();i++){//In movegen dont forget to set this priorty
            openNodes.push(temp[i]);// According to Priorty list top is most priorty
        }

        currentNode = openNodes.pop();
        numOfStatesExplored++;
    }
}
}