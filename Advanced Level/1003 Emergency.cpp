/*
思路: 单源最短路径问题, Dijkstra 算法

要求数出最短路径的条数, 同时数出可以募集的最多队伍数
使用一个 pre 向量, 存储经由哪个点, 到达此点
如果找到了比已有路更短的路, 由于最短距离优先, pre存储新路, 道路数量更改
如果找到了和已有路等距的路, pre存储可募集到队伍更多的路, 道路数量合并(相加)

被卡了一会的一个点(审题问题): 这个图是个无向图。
*/

#include <iostream>
#include <vector>

using namespace std;

const int infinity = 200000000; // 表示不连通

int find_nearest_city(int city_num, const vector<int>& dist, const vector<bool>& sure) // 找下一个单源最短距离点
{
    int ans = -1;
    int temp_min = infinity;
    for (int iter = 0; iter < city_num; iter++)
    {
        if( !sure[iter] && dist[iter] < temp_min )
        {
            ans = iter;
            temp_min = dist[iter];
        }
    }
    return ans;
}

void Dijkstra(int city_num, int source, int destination, vector<vector<int>>& graph, vector<int>& team_num, vector<int>& dist, vector<int>& count, vector<bool>& sure, vector<int>& pre)
{
    dist[source] = 0;
    count[source] = 1;

    int this_city = find_nearest_city(city_num, dist, sure);
    while( this_city != -1 )
    {
        sure[this_city] = true;
        if( pre[this_city] != -1 )
        {
            team_num[this_city] += team_num[pre[this_city]]; // 更新救援队数量, 为其pre点的队数加该点已有的队数
        }
        for (int iter = 0; iter < city_num; iter++)
        {
            if( !sure[iter] && graph[this_city][iter] != infinity )
            {
                if( dist[this_city] + graph[this_city][iter] < dist[iter] ) // 找到了更短的路, 更新距离以及路径数, 其pre点也要变化
                {
                    pre[iter] = this_city;
                    dist[iter] = dist[this_city] + graph[this_city][iter];
                    count[iter] = count[this_city];
                }
                else if( dist[this_city] + graph[this_city][iter] == dist[iter] ) // 找到了等距的路, 判断是否要改pre点
                {
                    pre[iter] = ( team_num[pre[iter]] > team_num[this_city] ? pre[iter] : this_city );
                    count[iter] += count[this_city];
                }
            }
        }

        this_city = find_nearest_city(city_num, dist, sure);
    }

    return;
}

int main(int argc, const char* argv[])
{
    vector<int> team_num, dist, count, pre;
    vector<bool> sure;
    vector<vector<int>> graph;
    int city_num, road_num, source, destination;
    cin >> city_num >> road_num >> source >> destination;
    
    for (int iter = 1; iter <= city_num; iter++) // 各vector的初始化
    {
        vector<int> temp_row;
        for (int jter = 1; jter <= city_num; jter++)
        {
            temp_row.emplace_back(infinity);
        }
        graph.emplace_back(temp_row);
        dist.emplace_back(infinity);
        count.emplace_back(0);
        sure.emplace_back(false);
        pre.emplace_back(-1);

        int temp_num;
        cin >> temp_num;
        team_num.emplace_back(temp_num);
    }

    for (int iter = 1; iter <= road_num; iter++) // 图的初始化
    {
        int temp_s, temp_e, temp_l;
        cin >> temp_s >> temp_e >> temp_l;
        graph[temp_s][temp_e] = graph[temp_e][temp_s] = temp_l;
    }

    Dijkstra(city_num, source, destination, graph, team_num, dist, count, sure, pre);

    cout << count[destination] << " " << team_num[destination] << endl;

    return 0;
}
