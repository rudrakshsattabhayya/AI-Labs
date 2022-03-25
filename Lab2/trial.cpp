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

bool goalTest(vector<string> currentState){
    if(currentState.size()==goalState.size()){
        for(int i=0; i<currentState.size(); i++){
            if(currentState[i]!=goalState[i])
            return false;
        }
        return true;
    }else return false;
    
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

vector<struct Node> moveGen(struct Node currentNode){//Add parentindexnum to each node
    vector<string> currentState = currentNode.currentState;
    vector<string> parentState = currentNode.parentState;

    visitedVector.push_back(currentNode);//Adding current Node into closed list

    struct Node temp = currentNode;
    string tempString;
    vector<struct Node> moveGenStates;
    
    for(int i=0;i<currentState.size();i++){
        for(int j=0;j<currentState.size();j++){
            if(i!=j){
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
    moveGenStates = filterdVector(moveGenStates);
    return moveGenStates;
}

void bestFirstSearch(struct Node initialStateNode){
    struct Node currentNode;
    vector<struct Node> moveGenStates;
    priority_queue<struct Node, vector<struct Node>, CompareHeuristicValue> priorityQueue;

    priorityQueue.push(initialStateNode);
    while(priorityQueue.size()!=0){
        currentNode = priorityQueue.top();
        priorityQueue.pop();
         if(!goalTest(currentNode)){
           moveGenStates = moveGen(currentNode);//remember to add filter movegen states func
            for(int i=0;i<moveGenStates.size();i++){
                priorityQueue.push(moveGenStates[i]);
            }
        }else{
            
        }
    }
}
vector<int> hillClimb(){
    struct Node currentNode;
    vector<struct Node> moveGenStates;
    priority_queue<struct Node, vector<struct Node>, CompareHeuristicValue> priorityQueue;

    priorityQueue.push(initialStateNode);
    while(priorityQueue.size()!=0){
        currentNode = priorityQueue.top();
        priorityQueue.pop();
         if(!goalTest(currentNode.currentState)){
           moveGenStates = moveGen(currentNode);
           int maxHeuristicValue = INT_MIN;
           int indexOfMaxHeuristicValue = -1;
            for(int i=0;i<moveGenStates.size();i++){
                if(maxHeuristicValue<moveGenStates.heuristicValue)
                indexOfMaxHeuristicValue = i;
            }
            priorityQueue.push(moveGenStates[indexOfMaxHeuristicValue]);
        }else{
            visitedVector.push_back(currentNode);
            return trackBack(currentNode);
        }
    }
}

int main(){
   
    string boxStack;
   cout<<"Enter initial State stacks: "<<endl;
    for(int i=0;i<3;i++){
        cin>>boxStack;
        initialStateNode.currentState.push_back(boxStack);
    }
    cout<<"Enter Goal State stacks: "<<endl;
    for(int i=0;i<3;i++){
        cin>>boxStack;
        goalStateNode.currentState.push_back(boxStack);
    }
//also add heuristic value in next line

    //////////////////////////////////////////////////////////
    

}