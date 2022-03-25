#include <bits/stdc++.h>
using namespace std;
#define ll long long

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

    while(getline(inputFile, tempString))
    {
        maze.push_back(tempString);
    }  
int nOSt=0;
int length=0;   
    int m=maze.size();
    int n=maze[0].size();
    char a[m][n];
      for(int i=0;i<m;i++){
          for(int j=0;j<maze[i].size();j++){
              a[i][j]=maze[i][j];
          }
      }

         vector<int> visited1(m,0);
          vector<int> visited2(n,0);
          int upx;
          int upy;
          int leftx;
          int lefty;
          int rightx;
          int righty;
          int downx;
          int downy;
          
      queue<pair<int,int>> q;
        char temp='p';
      map<pair<int,int>,pair<int,int>> mp;
       map<pair<int,int>,int> mp2;
     q.push({0,0});
    
       while(!q.empty()){
          
          pair<int,int> u=q.front();
          q.pop();
      if(mp2[{u.first,u.second}]==0){
          
        mp2[{u.first,u.second}]=1;
          }
          upx=u.first-1;
          upy=u.second;
          leftx=u.first;
          lefty=u.second-1;
          rightx=u.first;
          righty=u.second+1;
          downx=u.first+1;
          downy=u.second;
        
        // cout<<"main points "<<u.first<<","<<u.second<<endl;
        // cout<<leftx<<","<<lefty<<endl;
        // cout<<rightx<<","<<righty<<endl;
        // cout<<upx<<","<<upy<<endl;
        // cout<<downx<<","<<downy<<endl;
        //  printQueue(q);
        // cout<<endl;
        
if(upx>=0&&upx<=m-1&&upy>=0&&upy<=n-1&&(mp2[{upx,upy}]==0)&&a[upx][upy]!='+'&&a[upx][upy]!='|'&&a[upx][upy]!='-'){
           //   cout<<"hi1"<<endl;
           nOSt++;
              mp[{upx,upy}]={u.first,u.second};
                 q.push({upx,upy});
                 mp2[{upx,upy}]=1;
           
              if(a[upx][upy]=='*'){
                  temp='u';
              break;
               
          }
          }
if(leftx>=0&&leftx<=m-1&&lefty>=0&&lefty<=n-1&&(mp2[{leftx,lefty}]==0)&&a[leftx][lefty]!='+'&&a[leftx][lefty]!='|'&&a[leftx][lefty]!='-'){
 //   cout<<"hi2"<<endl;
  nOSt++;
                  mp[{leftx,lefty}]={u.first,u.second};
                    q.push({leftx,lefty});
            mp2[{leftx,lefty}]=1;
          if(a[leftx][lefty]=='*'){
                                  temp='l';
              break;
          }
          }
if(downx>=0&&downx<=m-1&&downy>=0&&downy<=n-1&&(mp2[{downx,downy}]==0)&&a[downx][downy]!='+'&&a[downx][downy]!='|'&&a[downx][downy]!='-'){
            //    cout<<"hi3"<<endl;
             nOSt++;
                mp[{downx,downy}]={u.first,u.second};
                    q.push({downx,downy});
             mp2[{downx,downy}]=1;
            if(a[downx][downy]=='*'){
                temp='d';
              break;
          }
          }
if(rightx>=0&&rightx<=m-1&&righty>=0&&righty<=n-1&&(mp2[{rightx,righty}]==0)&&a[rightx][righty]!='+'&&a[rightx][righty]!='|'&&a[rightx][righty]!='-')
{
   
     nOSt++;
                 mp[{rightx,righty}]={u.first,u.second};
                  q.push({rightx,righty});
mp2[{rightx,righty}]=1;
            if(a[rightx][righty]=='*'){
                                  temp='r';
              break;
          }
          }
          
          
          
          

          
          
          
      }
      
      
  //    cout<<temp<<endl;
      if(temp=='u'){
          int x=upx;
          int y=upy;
         
          while(x!=0||y!=0){
              a[x][y]='0';
              length++;
                pair<int,int> t1=mp[{x,y}];
              x=t1.first;
              y=t1.second;
          }a[x][y]='0';
           length++;
      }else if(temp=='d'){
          int x=downx;
          int y=downy;
          
          while(x!=0||y!=0){
              a[x][y]='0';
                length++;
              pair<int,int> t1=mp[{x,y}];
              x=t1.first;
              y=t1.second;
          }a[x][y]='0';
           length++;
      }else if(temp=='l'){
          int x=leftx;
          int y=lefty;
           
          while(x!=0||y!=0){
              a[x][y]='0';
                length++;
              pair<int,int> t1=mp[{x,y}];
              x=t1.first;
              y=t1.second;
          }a[x][y]='0';
           length++;
      }else if(temp=='r'){
          int x=rightx;
          int y=righty;
         
          while(x!=0||y!=0){
              a[x][y]='0';
                length++;
               pair<int,int> t1=mp[{x,y}];
              x=t1.first;
              y=t1.second;
          }
          a[x][y]='0';
           length++;
      }
      
      
      cout<<nOSt<<endl;
      cout<<length<<endl;
      for(int i=0;i<m;i++){
          for(int j=0;j<n;j++){
              cout<<a[i][j];
          }cout<<endl;
      }
      
  return 0;
}
               
          
          
     
