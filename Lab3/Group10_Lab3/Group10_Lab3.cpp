#include <bits/stdc++.h>
using namespace std;
#define ll long long
ofstream outfileFile;
ofstream outfile("output.txt");
/*******************DEBUG TEMPLATE*************************/
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x)                  \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif
/*******************DEBUG TEMPLATE*************************/
string finalState = "";
int stateExplored = 0;

bool done = true;
string genInitialState(int n)
{
    string initialState = "";

    for (int i = 0; i < n; i++)
    {
        //Generating random 1 and 0's
        initialState += to_string(rand() % 2);
    }
    return initialState;
}
int clauseValue(string literals, map<char, int> &mp)
{

    int ans = 0;
    //Taking OR of the elements inside the clauses
    for (int i = 0; i < literals.size(); i++)
    {
        ans = ans | mp[literals[i]];
    }

    return ans;
}
int heuristic(string current, vector<string> &clauses)
{
    map<char, int> mp;
    int asci_start = 97;
    int ASCI_START = 65;

    for (int i = 0; i < current.size(); i++)
    {

        mp[(char)asci_start] = (int)(current[i] - '0');
        mp[(char)ASCI_START] = !(int)(current[i] - '0');
        asci_start++;
        ASCI_START++;
    }

    int heuristicValue = 0;
    for (int i = 0; i < clauses.size(); i++)
    {
        //clauseValue gives the value of that clause
        heuristicValue = heuristicValue + clauseValue(clauses[i], mp);
    }

    return heuristicValue;
}
vector<string> genClauses(int n, int k, int numOfLiterals)
{
    vector<string> clauses(k);
    vector<char> alphabet;
    int asci_start = 97;

    for (int i = 0; i < n; i++)
    {
        alphabet.push_back((char)asci_start);
        asci_start++;
    }
    vector<char> temp1 = alphabet;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < numOfLiterals; j++)
        {
            //getting random index from the alphabet array
            int index = rand() % (alphabet.size());
            int negation = rand() % 2;
            //For getting negation of the literal
            if (negation == 0)
            {
                clauses[i].push_back(alphabet[index]);
            }
            else
            {
                clauses[i].push_back((char)alphabet[index] - 32);
            }
            //erasing that element to avoid repitition
            alphabet.erase(alphabet.begin() + index);
        }
        alphabet.clear();
        //getting all the values back for next clause
        for (int i1 = 0; i1 < n; i1++)
        {
            alphabet.push_back(temp1[i1]);
        }
    }
    //returning all  the clauses
    return clauses;
}

bool goalState(string ans, vector<string> clauses)
{
    //as my heuristic function gives number of clauses statisfied so my ggoalstate =size of clauses

    if (heuristic(ans, clauses) == clauses.size())
    {
        return true;
    }
    return false;
}

vector<string> moveGen(string current, int bits)
{

    //bits states how many positions to change
    vector<string> allNeighbours;
    vector<int> currstate;
    int n = current.size();

    for (int i = 0; i < n; i++)
    {
        int f = current[i] - '0';
        currstate.push_back(f);
    }
    vector<vector<int>> neighbours;

    vector<int> permut(n, 0);
    for (int i = 0; i < bits; i++)
    {
        permut[n - 1 - i] = 1;
    }

    vector<int> neighbour = currstate;
    for (int i = 0; i < n; i++)
    {
        if (permut[i] == 1)
        {
            neighbour[i] ^= 1;
        }
    }

    neighbours.push_back(neighbour);

    while (next_permutation(permut.begin(), permut.end()))
    {
        neighbour = currstate;
        for (int i = 0; i < n; i++)
        {
            if (permut[i] == 1)
            {
                neighbour[i] ^= 1;
            }
        }
        neighbours.push_back(neighbour);
    }

    for (int i = 0; i < neighbours.size(); i++)
    {
        string temp = "";
        for (int j = 0; j < neighbours[i].size(); j++)
        {
            temp += to_string(neighbours[i][j]);
        }
        allNeighbours.push_back(temp);
    }
    // all neighbours are pushed in allNeighbours vector and is returned
    return allNeighbours;
}

void BeamSearch(string current, int betaValue, vector<string> &clauses)
{

    map<string, bool> opened;
    map<string, bool> closed;

    priority_queue<pair<int, string>> open;
    priority_queue<pair<int, string>> open2;

    open.push({heuristic(current, clauses), current});
    opened[current] = true;

    while (!open.empty())
    {
        pair<int, string> check = open.top();
        open.pop();
        //removing from the opened list as it is pop out
        opened[check.second] = false;
        //putting in the closed list as the state is explored
        closed[check.second] = true;
        stateExplored++;
        //checking for goalstate
        if (goalState(check.second, clauses) && done)
        {
            finalState = check.second;
            done = false;
            return;
        }
        //getting all neighbours of the initialstate
        vector<string> neighbours = moveGen(check.second, 1);
        for (int i = 0; i < neighbours.size(); i++)
        {
            if (closed[neighbours[i]] == false && opened[neighbours[i]] == false)
            {
                open2.push({heuristic(neighbours[i], clauses), neighbours[i]});
            }
        }
        // checking if open is empty or not
        if (open.empty())
        {
            //adding best states upto  beamlength
            for (int i = 0; i < betaValue; i++)
            {
                if (open2.empty())
                    break;

                pair<int, string> preference = open2.top();
                open.push(preference);
                //putting in the opened list as we are pushing in the Open list
                opened[preference.second] = true;
                open2.pop();
            }
            //clearing the open2 queue
            open2 = priority_queue<pair<int, string>>();
        }
    }
}

void TabuSearch(string current, int tenure, vector<string> &clauses)
{
    map<string, bool> opened;
    map<string, bool> closed;

    priority_queue<pair<int, string>> open;
    open.push({heuristic(current, clauses), current});
    opened[current] = true;
    int k = clauses.size();
    //storing tabu tenure time in the vector
    vector<int> time(k, 0);
    //storing index of the changed index
    int index = -1;

    while (!open.empty())
    {
        pair<int, string> check = open.top();
        //removing from the opened list as it is pop out
        open.pop();
        opened[check.second] = false;
        closed[check.second] = true;
        stateExplored++;
        //checking for goalstate
        if (goalState(check.second, clauses) && done)
        {
            finalState = check.second;
            done = false;
            return;
        }
        //variable used storing the best heuistic value and state
        int minVal = -1;
        string state = "";
        // getting all the neighbours
        vector<string> neighbours = moveGen(check.second, 1);
        for (int i = 0; i < neighbours.size(); i++)
        {
            if (closed[neighbours[i]] == false && opened[neighbours[i]] == false)
            { //getting the state having highest heuristic value
                if (heuristic(neighbours[i], clauses) > minVal)
                {

                    for (int j = 0; j < neighbours[i].size(); j++)
                    {
                        if (neighbours[i][j] != check.second[j])
                        { //checking if tenure is over or not
                            if (time[j] == 0)
                            {
                                minVal = heuristic(neighbours[i], clauses);
                                state = neighbours[i];
                                index = j;
                            }
                        }
                    }
                }
            }
        }
        if (minVal != -1)
        {

            open.push({minVal, state});
            //putting in the opened list as we are pushing in the Open list
            opened[state] = true;
            // storing tenure time as the index will not be changed for that duration.
            time[index] = tenure + 1;
        }
        else
        {
            return;
        }
        //decreasing tenure time by one in one cycle
        for (int i = 0; i < k; i++)
        {
            if (time[i] != 0)
                time[i]--;
        }
    }
}

void VND(string current, vector<string> &clauses)
{
    map<string, bool> opened;
    map<string, bool> closed;
    priority_queue<pair<int, string>> open;
    open.push({heuristic(current, clauses), current});
    opened[current] = true;
    while (!open.empty())
    {
        pair<int, string> check = open.top();
        open.pop();
        //removing from the opened list as it is pop out
        opened[check.second] = false;
        //putting in the closed list as the state is explored
        closed[check.second] = true;
        stateExplored++;

        //checking for goalstate
        if (goalState(check.second, clauses) && done)
        {
            finalState = check.second;
            done = false;
            return;
        }
        //Created vaiables for storing best State
        int minVal = -1;
        string state = "";
        int k = 1;
        while (minVal == -1 && k < current.size())
        {
            //Getting all Neighbours
            vector<string> neighbours = moveGen(check.second, k);
            for (int i = 0; i < neighbours.size(); i++)
            {
                if (closed[neighbours[i]] == false && opened[neighbours[i]] == false)
                {
                    //Getting the best state having highest Heuristic Value
                    if (heuristic(neighbours[i], clauses) > minVal)
                    {
                        minVal = heuristic(neighbours[i], clauses);
                        state = neighbours[i];
                    }
                }
            }
            //Checking the heuristic Value with Parent
            if (minVal < heuristic(check.second, clauses))
            {
                minVal = -1;
            }
            k++;
        }
        //if there is dead end
        if (k == current.size())
        {
            return;
        }
        else
        {
            //if we get best state from Neighbours
            open.push({minVal, state});
            //putting in the opened list as we are pushing in the Open list
            opened[state] = true;
        }
    }
}
void BeamSearchResult(string initialState, int beamLength, vector<string> &clauses)
{
    //Calling BeamSearch Algorithm
    BeamSearch(initialState, beamLength, clauses);

    outfile << "StateExplored for BeamSearch Algorithm with beam length " << beamLength << "= " << stateExplored << endl;
    outfile << "finalState for BeamSearch Algorithm " << finalState << endl;
    stateExplored = 0;
    finalState = "";
    done = true;
    outfile << endl;
}
void TabuSearchResults(string initialState, int tabuTenure, vector<string> &clauses)
{
    //Calling TabuSearch Algorithm
    TabuSearch(initialState, tabuTenure, clauses);

    outfile << "StateExplored for TabuSearch Algorithm tenure " << tabuTenure << "= " << stateExplored << endl;
    outfile << "finalState for TabuSearch Algorithm " << finalState << endl;
    outfile << endl;

    stateExplored = 0;
    finalState = "";
    done = true;
    outfile << endl;
}
void VNDResult(string initialState, vector<string> &clauses)
{
    //Calling VNDResult Algorithm
    VND(initialState, clauses);
    outfile << "StateExplored for VND Algorithm= " << stateExplored << endl;
    outfile << "finalState for VND Algorithm " << finalState << endl;

    stateExplored = 0;
    finalState = "";
    done = true;
    outfile << endl;
}
int main()
{

    ifstream inputFile;

    inputFile.open("input.txt");
    srand((unsigned int)time(NULL));

    int n, k;
    //Taking inputs as number of variables and number of clauses.
    string temp = "";
    getline(inputFile, temp);
    stringstream geek(temp);
    geek >> n;
    temp = "";
    getline(inputFile, temp);
    stringstream geek2(temp);
    geek2 >> k;

    // Generating Initial State
    string initialState = genInitialState(n);

    // Generating Clauses
    vector<string> clauses = genClauses(n, k, 4);
    inputFile.close();

    outfile << "Initialstate= " << initialState << endl;

    outfile << "Clauses generated are:- " << endl;
    //Printing the clauses
    for (int i = 0; i < k; i++)
    {
        outfile << clauses[i] << " ";
    }
    outfile << endl;

    for (int i = 1; i <= 4; i++)
    {
        // Getting BeamSearch Results for Beamlength 1,2,3,4
        BeamSearchResult(initialState, i, clauses);
    }
    // Getting VNDResult
    VNDResult(initialState, clauses);

    for (int i = 1; i <= 4; i++)
    {
        // Getting TabuSearchResults Results for TabuTenure 1,2,3,4
        TabuSearchResults(initialState, i, clauses);
    }

    outfile.close();
    return 0;
}
