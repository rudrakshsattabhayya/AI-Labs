#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct Node {
    vector<string> parentState;
    vector<string> currentState;
    int heuristicValue;
    int parentIndexInVisitedVector;
};

vector<struct Node> visitedVector;
struct Node initialStateNode;
struct Node goalStateNode;

struct CompareHeuristicValue {
    bool operator()(Node const& p1, Node const& p2)
    {
        return p1.heuristicValue < p2.heuristicValue;
    }
};

int heuristicFunc1(vector<string> currentState){
    int heuristicValue=0;
    vector<string> goalState=goalStateNode.currentState;
    for(int i=0;i<currentState.size();i++){
        for(int j=0;j<min(currentState[i].size(),goalState[i].size());j++){
            if(currentState[i].at(j)==goalState[i].at(j)){
                heuristicValue++;
            }else{heuristicValue--;}
        }
        if(goalState[i].size()<currentState[i].size())
        heuristicValue= heuristicValue- (currentState[i].size()-goalState[i].size());
    }

    return heuristicValue;
}

int heuristicFunc2(vector<string> currentState){
    int heuristicValue=0;
    vector<string> goalState=goalStateNode.currentState;
    for(int i=0;i<currentState.size();i++){
        for(int j=0;j<min(currentState[i].size(),goalState[i].size());j++){
            if(currentState[i].at(j)==goalState[i].at(j)){
                heuristicValue++;
        }
    }
    }

    return heuristicValue;
}

int heuristicFunc3(vector<string> currentState){
    int heuristicValue=0;
    vector<string> goalState=goalStateNode.currentState;
    for(int i=0,j;i<currentState.size();i++){
        for(j=0;j<min(currentState[i].size(),goalState[i].size());j++){
            if(currentState[i].at(j)==goalState[i].at(j)){
                heuristicValue+=j+1;
            }else{heuristicValue-=(j+1);}
        }
        if(goalState[i].size()<currentState[i].size()){
            int sum = 0;
            for(int k=goalState[i].size()+1;k<=currentState[i].size();k++)
            sum+=k;
           heuristicValue= heuristicValue - sum;
        }
        
    }

    return heuristicValue;
}

bool goalTest(vector<string> currentState){
    // vector<string> goalState = goalStateNode.currentState;
    // if(currentState.size()==goalState.size()){
    //     for(int i=0; i<currentState.size(); i++){
    //         if(currentState[i]!=goalState[i])
    //         return false;
    //     }
    //     return true;
    // }else return false;
    
    int hv = heuristicFunc1(currentState);
    cout<<"hv value: "<<hv<<endl;
    if(hv==6) return true;
    
    return false;
    
}

vector<struct Node> filterNeighboringStates(vector<struct Node> x){
    vector<struct Node> filterdVector;
    for(int i=0;i<x.size();i++){
        bool isOk = true;
        for(int j=0;j<visitedVector.size();j++){
            if(visitedVector[j].currentState==x[i].currentState){
                isOk = false;
                break;
            }
        }
        if(isOk){filterdVector.push_back(x[i]);}
    }

    return filterdVector;
}

vector<int> trackBack(struct Node finalNode){
    int x=-2;
    struct Node currentNode = finalNode;
    vector<int> indexNums;
    indexNums.push_back(visitedVector.size()-1);
    while(x!=-1){
        x = currentNode.parentIndexInVisitedVector;
        if(x!=-1){
        indexNums.push_back(x);
        currentNode = visitedVector[x];
        }
    }
    return indexNums;
}


vector<struct Node> moveGen(struct Node currentNode){//Add parentindexnum to each node
    vector<string> currentState = currentNode.currentState;
    vector<string> parentState = currentNode.parentState;

    visitedVector.push_back(currentNode);//Adding current Node into closed list

    struct Node temp = currentNode;
    string tempString;
    vector<struct Node> moveGenStates;
    
    for(int i=0;i<currentState.size();i++){
        for(int j=0;j<currentState.size();j++){
            if(i!=j && currentNode.currentState[i].size()){
                tempString = currentState[j]+currentState[i][currentState[i].size()-1];

                temp.currentState[i].erase(currentState[i].size()-1);
                temp.currentState[j] = tempString;
                temp.parentState = parentState;
                temp.parentIndexInVisitedVector = visitedVector.size()-1;// For easement of backtracking
                moveGenStates.push_back(temp);
                temp = currentNode;
            }
        }
    }
    moveGenStates = filterNeighboringStates(moveGenStates);
    for(int i=0;i<moveGenStates.size();i++)
    moveGenStates[i].heuristicValue = heuristicFunc1(moveGenStates[i].currentState);
    return moveGenStates;
}

vector<int> bestFirstSearch(struct Node initialStateNode){
    cout<<"called bfs"<<endl;
    struct Node currentNode;
    vector<struct Node> moveGenStates;
    priority_queue<struct Node, vector<struct Node>, CompareHeuristicValue> priorityQueue;

    priorityQueue.push(initialStateNode);
    while(!priorityQueue.empty()){
        currentNode = priorityQueue.top();
        // cout<<currentNode.heuristicValue<<endl;
        // for(int i=0;i<3;i++){
        //     cout<<currentNode.currentState[i]<<" ";
        // }
        // cout<<endl;
        visitedVector.push_back(currentNode);
        priorityQueue.pop();
         if(!goalTest(currentNode.currentState)){
           moveGenStates = moveGen(currentNode);
            for(int i=0;i<moveGenStates.size();i++){
                priorityQueue.push(moveGenStates[i]);
            }
        }else{
            cout<<"reach goal state";
            return trackBack(currentNode);
        }
    }
    
    return {};
}


int main(){
   
    initialStateNode.currentState.push_back("ebf");
    initialStateNode.currentState.push_back("da");
    initialStateNode.currentState.push_back("c");

    goalStateNode.currentState.push_back("adb");
    goalStateNode.currentState.push_back("efc");
    goalStateNode.currentState.push_back("");
    
    initialStateNode.heuristicValue = heuristicFunc1(initialStateNode.currentState);
    vector<int> x = bestFirstSearch(initialStateNode);
//also add heuristic value in next line

    //////////////////////////////////////////////////////////
    

}