#include <iostream>
#include <utility>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;


typedef struct Point{
    int x;
    int y;
}Point;
// input the maze,return the 2D vector maze
vector<vector<char>> InputMap()
{
    int m,n;
    vector<vector<char>> map;
    cout<<"input col and row:"<<endl;
    cin>>m>>n;

    for(int i=0;i<m;i++)
    {
        vector<char> temp;
        for(int j=0;j<n;j++)
        {
            char t;
            cin>>t;
            temp.push_back(t);
        }
        map.push_back(temp);
    }
    return map;
}
// print the maze
void PrintMap(vector<vector<char>> map)
{
    cout<<"Output:"<<endl;
    unsigned m,n;
    m=map.size();
    n=map[0].size();
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<map[i][j]<<' ';
        }
        cout<<endl;
    }
}

//according to path,drawing the path of the maze
vector<vector<char>> GetMapPath(vector<vector<char>> map,const stack<Point>& path)
{
    unsigned n;
    n=path.size();
    stack<Point> p = path;
    vector<vector<char>> path_map =std::move(map);
    for (int i = 0; i < n; ++i) {
        Point cur = p.top();
        path_map[cur.x][cur.y] = '+';
        p.pop();
    }
    return path_map;
}

//check if finished visiting,if yes return ture,not return false
bool AllSearch(vector<vector<int>> visit)
{
    unsigned m,n;
    m = visit.size();
    n = visit[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if(visit[i][j]!=1)
                return false;
        }
    }
    return true;
}

//find all the paths
void DFS(Point start,Point end,Point &current,stack<Point> path,vector<vector<char>> map,vector<vector<int>> &visit,int deep=0)
{
    path.push(current);
    visit[current.x][current.y] = 1;
    //output the path
    if (end.x==current.x&&end.y==current.y) {
        cout << "deep:" << deep<<endl;
        PrintMap(GetMapPath(map,path));
    }
    //return
    if(AllSearch(visit))
        return;

    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    string directions[]={"right","left","down","up"};
    for (int i = 0; i < 4; i++) {
        int nx = current.x + dx[i], ny = current.y + dy[i];
        if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size() && map[nx][ny] != '*' && visit[nx][ny] != 1) {
            cout << directions[i] << endl;
            Point next = {nx, ny};
            DFS(start, end, next, path, map, visit, deep + 1);
        }
    }
    visit[current.x][current.y] = 0;
    if (!path.empty()) path.pop();
}

int main()
{
    vector<vector<char>> map = InputMap();
    unsigned m=map.size();
    unsigned n=map[0].size();
    Point start;
    Point end;
    cout<<"Input Start:"<<endl;
    cin>>start.x>>start.y;
    cout<<"Input End"<<endl;
    cin>>end.x>>end.y;
    vector<vector<int>> visit(m, vector<int>(n, 0));
    stack<Point> path;
    DFS(start,end,start,path,map,visit);
}
