#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <climits>
#include <iomanip>
using namespace std;

vector<vector<double>> cityToCityCost;
vector<vector<double>> pheremones;
struct Parent {
    vector<int> tour;
    double cost;
};
queue<struct Parent> bestTopTen;
queue<struct Parent> temp;
time_t startTime;
time_t finishTime;

int readFromInput(){
    ifstream fileObj;
    string fileName;
    string line;
    cout<<"Write name for input file: ";
    cin>>fileName;
    startTime = time(NULL);
    fileObj.open(fileName);

    if(!fileObj){
        cerr<<"File open error"<<endl;
        return -1;
    }else{
        getline(fileObj,line);
        getline(fileObj,line);
        int t=stoi(line);
        int n = t;
        while(t--){
            getline(fileObj,line);
        }
        t=n;
        string dist;
        int oldindex,newindex;
        while(t--){
            oldindex=0;
            newindex=0;
            getline(fileObj,line);

            vector<double> temp;
            for(int i=0;i<n;i++){
            newindex = line.find(" ",oldindex);
            double x = stod(line.substr(oldindex,newindex-oldindex));
            temp.push_back(x);
            oldindex=newindex+1;
            }
            cityToCityCost.push_back(temp);   
        }
        fileObj.close();
        return n;
    }
}

double costOfTour(vector<int> currentTour){
    double cost=0;
    for(int i=0;i<currentTour.size()-1;i++){
        cost+=cityToCityCost[currentTour[i]][currentTour[i+1]];
    }
    cost+=cityToCityCost[currentTour[currentTour.size()-1]][currentTour[0]];
    return cost;
}

void updateTopTen(vector<int> currentTour, double cost){
    struct Parent node;
    node.tour = currentTour;
    node.cost = cost;

    if(bestTopTen.size()==0) bestTopTen.push(node);

        if(node.cost<=bestTopTen.back().cost && node.tour!=bestTopTen.back().tour){
           if(bestTopTen.size()<10){
               bestTopTen.push(node);
           }else{
               bestTopTen.push(node);
               bestTopTen.pop(); 
           }

            finishTime = time(NULL) - startTime;
           cout<<"Next Best Tour: "<<endl;
           for(auto x: currentTour)
           cout<<x<<" ";
           cout<<endl<<"Tour Length: "<<cost<<endl;
           cout<<"Time taken: "<<finishTime<<endl<<endl;
        }

}



//Genetic Algo funcs

int bestAvailHeurCity(int fromCity, vector<int> map){
    double minCost = INT_MAX;
    int toCity;
    for(int i=0;i<map.size();i++){
        if(cityToCityCost[fromCity][i] < minCost && i!=fromCity && map[i]==0){
            minCost = cityToCityCost[fromCity][i];
            toCity = i;
        }
    }

    return toCity;
}

vector<int> heuristicCrossover(vector<int> parent1, vector<int> parent2){
    vector <int> child;
    vector <int> visitedMap(parent1.size(),0);
    int temp=0;
    srand((unsigned int)time(NULL));
    for(int i=0;i<10;i++){
        temp+=rand()%parent1.size();
    }

    child.push_back(temp%parent1.size());
    visitedMap[child[0]] = 1;
    double toParent1city, toParent2city;

    for(int i=0;i<parent1.size()-1;i++){
        if(visitedMap[parent1[child[i]]]!=1)
            toParent1city = cityToCityCost[child[i]][parent1[child[i]]];
        else
            toParent1city = -1;

        if(visitedMap[parent2[child[i]]]!=1)
             toParent2city = cityToCityCost[child[i]][parent2[child[i]]];
        else
            toParent2city = -1;

        if(toParent2city==-1&&toParent1city==-1) child.push_back(bestAvailHeurCity(child[i], visitedMap));
        else if(toParent1city==-1) child.push_back(parent2[child[i]]);
        else if(toParent2city==-1) child.push_back(parent1[child[i]]);
        else if(toParent1city>toParent2city) child.push_back(parent2[child[i]]);
        else child.push_back(parent1[child[i]]);

        visitedMap[child[i+1]] = 1;
    }

    return child;
}

vector <int> toAdjacencyRep(vector <int> tour){
    vector <int> adjRepOfTour(tour.size(),-1);

    for(int i=0;i<tour.size();i++){
        if(i!=tour.size()-1)
        adjRepOfTour[tour[i]]=tour[i+1];
        else 
        adjRepOfTour[tour[i]]=tour[0];
    }

    return adjRepOfTour;
}

vector <int> backToPathRep(vector <int> tour){
    vector <int> pathRepOfTour;
    int i=tour.size(), temp=0;

    while(i--){
        pathRepOfTour.push_back(tour[temp]);
        temp=tour[temp];
    }

    return pathRepOfTour;
}


void geneticAlgorithm(){
    int size = bestTopTen.size();
    double totalCost = 0;
    double totalValue =0;
    double tempp;
    int x = 0,freq=0;
    if(size<=1) return;

    vector<struct Parent> top5ParentList;
    vector<struct Parent> bottom5ParentList;
    vector<struct Parent> totalParentList;
    vector<int> tour1;
    vector<int> tour2;
    struct Parent node;
    bool didWeFind = false;

    temp = bestTopTen;

    srand(unsigned(time(NULL)));
        int t = 10;
         while(t--){
             finishTime = time(NULL) - startTime;
             size = temp.size();
    
             while(temp.size()>0){
                node = temp.front();
         
                if(temp.size()>=size/2){
                    tour1 = node.tour;
                    random_shuffle(tour1.begin(), tour1.end());
                    node.tour = tour1;
                    bottom5ParentList.push_back(node);
                }else{
                     if(rand()%2==0){
                     tour1 = node.tour;
                     random_shuffle(tour1.begin(), tour1.end());
                     node.tour = tour1;
                     }
                     top5ParentList.push_back(node);
                }
                if(temp.size()>0) temp.pop();
             }

                 random_shuffle(top5ParentList.begin(),top5ParentList.end());
                 random_shuffle(bottom5ParentList.begin(),bottom5ParentList.end());
                 totalParentList = top5ParentList;
                 totalParentList.insert(totalParentList.end(),bottom5ParentList.begin(),bottom5ParentList.end());
                 random_shuffle(totalParentList.begin(),totalParentList.end());

                 for(int i=0;i<totalParentList.size()-1;i++){
                     tour1 = heuristicCrossover(totalParentList[i].tour,totalParentList[i+1].tour);
                     tempp = costOfTour(tour1);
                     updateTopTen(tour1,tempp);
                     node.tour = tour1;
                     node.cost = tempp;
                     temp.push(node);

                     if(tempp<bestTopTen.back().cost){
                         didWeFind = true;
                     }
                 }  
             }

             if(!didWeFind){
                 cout<<"Genetic Algo was not able to find better tour compared to Ant colony opt."<<endl;
             }

}

int nextStepOfAnt(vector<int> currentTour, int numOfCities, double alpha, double beta){
    vector<int>allowedCities(numOfCities,1);
    double prob;
    int currentCity = currentTour[currentTour.size()-1];
    for(int i=0;i<currentTour.size();i++) {allowedCities[currentTour[i]]=0;}
    struct cityProbs {
        int city;
        double probability;
    };
    struct cityProbs temp;
    struct cityProbs bestProbCity;
    bestProbCity.city = -1;
    bestProbCity.probability=0;
    //Denominator
    double denominator=0;
    for(int j=0;j<allowedCities.size();j++) {
        if(allowedCities[j]==1){
            denominator+=pow(pheremones[currentCity][j],alpha)*pow(1/cityToCityCost[currentCity][j],beta);
        }
    }


    //Numerator
    vector<struct cityProbs> allowedProbs;

    for(int i=0;i<allowedCities.size();i++) {
        if(allowedCities[i]==1){
            prob = pow(pheremones[currentCity][i],alpha)*pow(1/cityToCityCost[currentCity][i],beta);
            prob = prob/denominator;
            temp.city = i;
            temp.probability = prob;
            if(prob>bestProbCity.probability){
                bestProbCity = temp;
            }
            allowedProbs.push_back(temp);
        }
    }

    return bestProbCity.city;

}



void updatePheremones(vector<int> currentTour, double cost, double q, double rho){
    for(int i=0;i<currentTour.size()-1;i++){
         pheremones[currentTour[i]][currentTour[i + 1]] *= rho;
         pheremones[currentTour[i]][currentTour[i + 1]] += q / cost;
         pheremones[currentTour[i + 1]][currentTour[i]] *= rho;
         pheremones[currentTour[i + 1]][currentTour[i]] += q / cost;
    }
    return;
}

vector<int> ant(int maxIteration, int numOfCities, double alpha, double beta, double q, double rho){
    
    vector<int> bestTour(numOfCities,0);
    double bestCost=INT_MAX;
    bool bestTourFound = false;

    while(finishTime<200&&maxIteration!=0){

        finishTime=time(NULL)-startTime;
        maxIteration--;
        vector<int> currentTour;
        double cost = INT_MAX;

        currentTour.push_back((rand()%numOfCities));
        while(currentTour.size()!=numOfCities){
            currentTour.push_back(nextStepOfAnt(currentTour, numOfCities, alpha, beta));
        }
    
        cost = costOfTour(currentTour);
        updateTopTen(currentTour,cost);//For Applying GA in further steps

        if(cost<bestCost){
            bestCost=cost;
            bestTour = currentTour;
        }

        updatePheremones(currentTour,cost,q,rho);
    }
    return bestTour;
}

int main(){
    finishTime =0;

    const double alpha=4.0,beta=3.0,rho=0.1,q=100;
    const int numOfCities = readFromInput();
    
    if(numOfCities!=-1){
            vector<vector<double>> tempPheremones( numOfCities , vector<double> (numOfCities, pow(numOfCities,-2)));
            pheremones=tempPheremones;
            vector<int> bestTour;
            bestTour = ant(INT_MAX,numOfCities,alpha,beta,q,rho);
            cout<<"Starting Genetic Algorithm:"<<endl;
            geneticAlgorithm();
    }
}