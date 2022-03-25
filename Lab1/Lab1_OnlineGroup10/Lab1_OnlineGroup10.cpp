#include <bits/stdc++.h>
using namespace std;
#define ll long long

char temp = 'p';
int statesExplored = 1;
int pathLength = 0;
int check = 0;
pair<int, int> o;

void DFS(vector<vector<char>> a, pair<int, int> u, map<pair<int, int>, pair<int, int>> &parentstored, map<pair<int, int>, int> &visited, int m, int n);
void moveGen2(int start, int end, int x, int y, map<pair<int, int>, int> &visited, map<pair<int, int>, pair<int, int>> &parentstored, vector<vector<char>> &a, int m, int n);

void DFID(int check, int count, vector<vector<char>> a, pair<int, int> u, map<pair<int, int>, pair<int, int>> &parentstored, map<pair<int, int>, int> &visited, int m, int n);
void moveGen3(int check, int count, int start, int end, int x, int y, map<pair<int, int>, int> &visited, map<pair<int, int>, pair<int, int>> &parentstored, vector<vector<char>> &a, int m, int n);

bool goalState(int x, int y, vector<vector<char>> &a)
{
    if (a[x][y] == '*')
    {
        temp = 'u';
        o = {x, y};
        return true;
    }
    return false;
}

void moveGen1(int start, int end, int x, int y, map<pair<int, int>, int> &visited, map<pair<int, int>, pair<int, int>> &parentstored, vector<vector<char>> &a, int m, int n, queue<pair<int, int>> &q)
{
    if (temp == 'p' && x >= 0 && x <= m - 1 && y >= 0 && y <= n - 1 && (visited[{x, y}] == 0) && a[x][y] != '+' && a[x][y] != '|' && a[x][y] != '-')
    {

        statesExplored++;
        parentstored[{x, y}] = {start, end};
        q.push({x, y});
        visited[{x, y}] = 1;

        if (goalState(x, y, a))
        {
            return;
        }
    }
}
int main()
{
    vector<string> maze;
    int searchAlgo;
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("input.txt");
    string tempString;
    getline(inputFile, tempString);
    searchAlgo = stoi(tempString);
    while (getline(inputFile, tempString))
    {

        maze.push_back(tempString);
    }
    int m = maze.size();
    int n = maze[0].size();
    vector<vector<char>> a(m);
    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < maze[0].size(); j++)
        {
            if (j < maze[i].size())
            {
                a[i].push_back(maze[i][j]);
            }
            else
            {
                a[i].push_back(' ');
            }
        }
    }
    map<pair<int, int>, pair<int, int>> parentstored;
    map<pair<int, int>, int> visited;

    if (searchAlgo == 0)
    {
        queue<pair<int, int>> q;
        q.push({0, 0});
        while (!q.empty())
        {
            pair<int, int> u = q.front();
            q.pop();
            if (visited[{u.first, u.second}] == 0)
            {
                visited[{u.first, u.second}] = 1;
            }
            moveGen1(u.first, u.second, u.first + 1, u.second, visited, parentstored, a, m, n, q);
            moveGen1(u.first, u.second, u.first - 1, u.second, visited, parentstored, a, m, n, q);
            moveGen1(u.first, u.second, u.first, u.second + 1, visited, parentstored, a, m, n, q);
            moveGen1(u.first, u.second, u.first, u.second - 1, visited, parentstored, a, m, n, q);

            if (temp != 'p')
                break;
        }
    }
    else if (searchAlgo == 1)
    {
        DFS(a, {0, 0}, parentstored, visited, m, n);
    }
    else if (searchAlgo == 2)
    {
        int cnt = 1;
        while (cnt != m * n && temp == 'p')
        {
            int temp = statesExplored;
            DFID(check, cnt, a, {0, 0}, parentstored, visited, m, n);
            statesExplored++;

            cnt++;

            visited.clear();
            check = 0;
        }
    }
    int x = o.first;
    int y = o.second;

    while (x != 0 || y != 0)
    {
        a[x][y] = '0';
        pathLength++;
        pair<int, int> t1 = parentstored[{x, y}];
        x = t1.first;
        y = t1.second;
    }
    a[x][y] = '0';
    pathLength++;

    cout << statesExplored << endl;
    cout << pathLength << endl;
    // cout << m << " " << n << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j];
        }
        cout << endl;
    }

    return 0;
}
void DFS(vector<vector<char>> a, pair<int, int> u, map<pair<int, int>, pair<int, int>> &parentstored, map<pair<int, int>, int> &visited, int m, int n)
{

    if (visited[{u.first, u.second}] == 0)
    {
        visited[{u.first, u.second}] = 1;
    }
    moveGen2(u.first, u.second, u.first + 1, u.second, visited, parentstored, a, m, n);
    moveGen2(u.first, u.second, u.first - 1, u.second, visited, parentstored, a, m, n);
    moveGen2(u.first, u.second, u.first, u.second + 1, visited, parentstored, a, m, n);
    moveGen2(u.first, u.second, u.first, u.second - 1, visited, parentstored, a, m, n);
    if (temp != 'p')
        return;
}

void moveGen2(int start, int end, int x, int y, map<pair<int, int>, int> &visited, map<pair<int, int>, pair<int, int>> &parentstored, vector<vector<char>> &a, int m, int n)
{
    if (temp == 'p' && x >= 0 && x <= m - 1 && y >= 0 && y <= n - 1 && (visited[{x, y}] == 0) && a[x][y] != '+' && a[x][y] != '|' && a[x][y] != '-')
    {

        statesExplored++;
        parentstored[{x, y}] = {start, end};

        visited[{x, y}] = 1;
        if (goalState(x, y, a))
        {
            return;
        }
        DFS(a, {x, y}, parentstored, visited, m, n);
    }

    else
    {
        return;
    }
}
void DFID(int check, int cnt, vector<vector<char>> a, pair<int, int> u, map<pair<int, int>, pair<int, int>> &parentstored, map<pair<int, int>, int> &visited, int m, int n)
{

    if (visited[{u.first, u.second}] == 0)
    {
        visited[{u.first, u.second}] = 1;
    }
    moveGen3(check, cnt, u.first, u.second, u.first + 1, u.second, visited, parentstored, a, m, n);

    moveGen3(check, cnt, u.first, u.second, u.first - 1, u.second, visited, parentstored, a, m, n);

    moveGen3(check, cnt, u.first, u.second, u.first, u.second + 1, visited, parentstored, a, m, n);

    moveGen3(check, cnt, u.first, u.second, u.first, u.second - 1, visited, parentstored, a, m, n);

    if (temp != 'p')
        return;
}

void moveGen3(int check, int cnt, int start, int end, int x, int y, map<pair<int, int>, int> &visited, map<pair<int, int>, pair<int, int>> &parentstored, vector<vector<char>> &a, int m, int n)
{
    if (temp == 'p' && x >= 0 && x <= m - 1 && y >= 0 && y <= n - 1 && (visited[{x, y}] == 0) && a[x][y] != '+' && a[x][y] != '|' && a[x][y] != '-')
    {
        if (check >= cnt)
        {
            return;
        }
        statesExplored++;
        parentstored[{x, y}] = {start, end};

        visited[{x, y}] = 1;
        if (goalState(x, y, a))
        {
            return;
        }
        DFID(check + 1, cnt, a, {x, y}, parentstored, visited, m, n);
        visited[{x, y}] = 0;
    }

    else
    {
        return;
    }
}
