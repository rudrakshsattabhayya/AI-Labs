#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;
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
#define debug(x...)               \
	cerr << "[" << #x << "] = ["; \
	_print(x)
#else
#define debug(x...)
#endif
#define ll long long
#include <time.h>

vector<string> initialState(3);
vector<string> finalState(3);
map<vector<string>, bool> opened;
map<vector<string>, bool> closed;
map<vector<string>, vector<string>> mp2;
int statesExplored = 0;
int pathLength = 0;
bool pathFound = false;
bool goalState(vector<string> check)
{
	for (int i = 0; i < finalState.size(); i++)
	{
		if (finalState[i].size() != check[i].size())
		{
			return false;
		}
		else
		{
			for (int j = 0; j < finalState[i].size(); j++)
			{
				if (check[i][j] != finalState[i][j])
				{
					return false;
				}
			}
		}
	}
	return true;
}
int heuristic2(vector<string> current)
{
	int cnt = 0;
	for (int i = 0; i < current.size(); i++)
	{
		int j = 0;
		while (j < current[i].size() && j < finalState[i].size())
		{
			if (finalState[i][j] != current[i][j])
			{
				int y = 0;
				for (int k = 0; k < current[i].size(); k++)
				{
					if (finalState[i][j] == current[i][k])
					{
						y++;
						cnt += 1;
						break;
					}
				}
				if (y == 0)
				{
					cnt += 2;
				}
			}
			j++;
		}
		cnt += (int)abs((long)current[i].size() - (long)finalState[i].size());
	}
	return cnt;
}
int heuristic3(vector<string> current)
{
	int cnt = 0;
	for (int i = 0; i < current.size(); i++)
	{
		int j = 0;
		while (j < current[i].size() && j < finalState[i].size())
		{
			if (finalState[i][j] != current[i][j])
			{
				cnt++;
			}
			j++;
		}
		cnt += (int)abs((long)current[i].size() - (long)finalState[i].size());
	}
	return cnt;
}
int heuristic1(vector<string> current)
{
	int cnt = 0;
	for (int i = 0; i < current.size(); i++)
	{
		int j = 0;
		while (j < current[i].size() && j < finalState[i].size())
		{
			if (finalState[i][j] != current[i][j])
			{
				break;
			}
			j++;
		}

		for (int k = j; k < min(current[i].size(), finalState[i].size()); k++)
		{
			cnt++;
		}
		if (current[i].size() > finalState[i].size())
		{
			cnt += (int)abs((long)current[i].size() - (long)finalState[i].size());
		}
	}
	return cnt;
}
vector<vector<string>> moveGenStates(vector<string> current)
{
	vector<vector<string>> ans;
	int i = 0;

	if (current[i].size() != 0)
	{
		string temp1 = current[i + 1];
		string temp2 = current[i + 2];
		temp1 += current[i][current[i].size() - 1];
		temp2 += current[i][current[i].size() - 1];
		vector<string> temp;

		temp.push_back(current[i].substr(0, current[i].size() - 1));
		temp.push_back(temp1);
		temp.push_back(current[i + 2]);
		ans.push_back(temp);
		temp.clear();
		temp.push_back(current[i].substr(0, current[i].size() - 1));
		temp.push_back(current[i + 1]);
		temp.push_back(temp2);
		ans.push_back(temp);
		temp.clear();
	}
	if (current[i + 1].size() != 0)
	{
		string temp1 = current[i];
		string temp2 = current[i + 2];
		temp1 += current[i + 1][current[i + 1].size() - 1];
		temp2 += current[i + 1][current[i + 1].size() - 1];
		vector<string> temp;

		temp.push_back(temp1);
		temp.push_back(current[i + 1].substr(0, current[i + 1].size() - 1));
		temp.push_back(current[i + 2]);
		ans.push_back(temp);
		temp.clear();

		temp.push_back(current[i]);
		temp.push_back(current[i + 1].substr(0, current[i + 1].size() - 1));
		temp.push_back(temp2);
		ans.push_back(temp);
		temp.clear();
	}
	if (current[i + 2].size() != 0)
	{
		string temp1 = current[i];
		string temp2 = current[i + 1];
		temp1 += current[i + 2][current[i + 2].size() - 1];
		temp2 += current[i + 2][current[i + 2].size() - 1];
		vector<string> temp;
		temp.push_back(temp1);
		temp.push_back(current[i + 1]);
		temp.push_back(current[i + 2].substr(0, current[i + 2].size() - 1));
		ans.push_back(temp);
		temp.clear();

		temp.push_back(current[i]);
		temp.push_back(temp2);
		temp.push_back(current[i + 2].substr(0, current[i + 2].size() - 1));
		ans.push_back(temp);
		temp.clear();
	}

	return ans;
}
void BestFirstSearch(vector<string> current, int (*heuristic)(vector<string> currentState))
{
	priority_queue<pair<int, vector<string>>> open;
	open.push({0, current});
	opened[current] = true;
	while (!open.empty())
	{

		pair<int, vector<string>> check = open.top();
		open.pop();

		statesExplored++;
		//	debug(check.second);
		opened[check.second] = false;
		closed[check.second] = true;

		if (!goalState(check.second))
		{
			vector<vector<string>> states = moveGenStates(check.second);

			for (int i = 0; i < states.size(); i++)
			{
				if (opened[states[i]] || closed[states[i]])
					continue;
				int val = -1 * heuristic(states[i]);

				open.push({val, states[i]});
				mp2[states[i]] = check.second;
				opened[states[i]] = true;
			}
		}
		else
		{
			vector<string> t = check.second;
			while (t != initialState)
			{
				//debug(t);
				pathLength++;

				t = mp2[t];
			}

			break;
		}
	}
}

void HillClimbing(vector<string> current, int (*heuristic)(vector<string> currentState))
{
	priority_queue<pair<int, vector<string>>> open;
	open.push({0, current});
	opened[current] = true;
	while (!open.empty())
	{

		pair<int, vector<string>> check = open.top();

		open.pop();
		statesExplored++;
		opened[check.second] = false;
		closed[check.second] = true;

		if (!goalState(check.second))
		{
			vector<vector<string>> states = moveGenStates(check.second);
			int minVal = INT_MAX;
			vector<string> minNode;
			for (int i = 0; i < states.size(); i++)
			{

				if (opened[states[i]] || closed[states[i]])
					continue;

				int val = heuristic(states[i]);
				if (val <= minVal)
				{
					minVal = val;
					minNode = states[i];
				}
			}
			if (minNode.size() == 0)
			{
				return;
			}
			else
			{
				if (minVal > heuristic(check.second))
				{
					return;
				}
				else
				{
					open.push({-1 * minVal, minNode});
					opened[minNode] = true;
				}
			}
		}

		else
		{
			pathFound = true;
			break;
		}
	}
}

int main()
{
	ifstream inputFile;
	ofstream outputFile;

	inputFile.open("input.txt");

	string wasteString;

	//ignore first line of input file
	getline(inputFile, wasteString);

	//get initial state
	for (int i = 0; i < 3; i++)
	{
		getline(inputFile, initialState[i]);
	}

	//ignore 4th line of input file
	getline(inputFile, wasteString);

	//get goal state
	for (int i = 0; i < 3; i++)
	{
		getline(inputFile, finalState[i]);
	}

	inputFile.close();
	ofstream outfile("output.txt");
	auto start = high_resolution_clock::now();
	BestFirstSearch(initialState, &heuristic1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	outfile << "BEST FIRST SEARCH FOR HEURISTIC 1" << endl;
	outfile << "StateExplored " << statesExplored << endl;
	outfile << "pathLength " << pathLength << endl;
	outfile << "Time taken by function: "
			<< duration.count() << " microseconds" << endl;
	outfile << endl;

	opened.clear();
	closed.clear();
	mp2.clear();
	statesExplored = 0;
	pathLength = 0;
	pathFound = false;
	auto start1 = high_resolution_clock::now();
	BestFirstSearch(initialState, &heuristic2);
	auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	outfile << "BEST FIRST SEARCH FOR HEURISTIC 2" << endl;
	outfile << "StateExplored " << statesExplored << endl;
	outfile << "pathLength " << pathLength << endl;
	outfile << "Time taken by function: "
			<< duration1.count() << " microseconds" << endl;
	outfile << endl;

	opened.clear();
	closed.clear();
	mp2.clear();
	statesExplored = 0;
	pathLength = 0;
	pathFound = false;
	auto start2 = high_resolution_clock::now();
	BestFirstSearch(initialState, &heuristic3);
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	outfile << "BEST FIRST SEARCH FOR HEURISTIC 3" << endl;
	outfile << "StateExplored " << statesExplored << endl;
	outfile << "pathLength " << pathLength << endl;
	outfile << "Time taken by function: "
			<< duration2.count() << " microseconds" << endl;
	outfile << endl;

	opened.clear();
	closed.clear();
	mp2.clear();
	statesExplored = 0;
	pathLength = 0;
	pathFound = false;
	auto start3 = high_resolution_clock::now();
	HillClimbing(initialState, &heuristic1);
	auto stop3 = high_resolution_clock::now();
	auto duration3 = duration_cast<microseconds>(stop3 - start3);
	outfile << "HILL CLIMBING FOR HEURISTIC 1" << endl;
	outfile << "StateExplored " << statesExplored << endl;
	outfile << "pathFound " << pathFound << endl;
	outfile << "Time taken by function: "
			<< duration3.count() << " microseconds" << endl;
	outfile << endl;

	opened.clear();
	closed.clear();
	mp2.clear();
	statesExplored = 0;
	pathLength = 0;
	pathFound = false;
	auto start4 = high_resolution_clock::now();
	HillClimbing(initialState, &heuristic2);
	auto stop4 = high_resolution_clock::now();
	auto duration4 = duration_cast<microseconds>(stop4 - start4);
	outfile << "HILL CLIMBING FOR HEURISTIC 2" << endl;
	outfile << "StateExplored " << statesExplored << endl;
	outfile << "pathFound " << pathFound << endl;
	outfile << "Time taken by function: "
			<< duration4.count() << " microseconds" << endl;
	outfile << endl;

	opened.clear();
	closed.clear();
	mp2.clear();
	statesExplored = 0;
	pathLength = 0;
	pathFound = false;
	auto start5 = high_resolution_clock::now();
	HillClimbing(initialState, &heuristic3);
	auto stop5 = high_resolution_clock::now();
	auto duration5 = duration_cast<microseconds>(stop5 - start5);
	outfile << "HILL CLIMBING FOR HEURISTIC 3" << endl;
	outfile << "StateExplored " << statesExplored << endl;
	outfile << "pathFound " << pathFound << endl;
	outfile << "Time taken by function: "
			<< duration5.count() << " microseconds" << endl;
	outfile << endl;
	outfile.close();
	return 0;
}
