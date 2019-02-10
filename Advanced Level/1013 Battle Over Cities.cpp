// 无向图，查找/计数连通分量用 BFS / DFS 均可，本代码用的是BFS
// 大数据输入 一定要 ios::sync_with_stdio(false); 
//                 cin.tie(0) 也有一定效果

#include <iostream>
#include <vector>

using namespace std;

class Graph
{
public:
	int CityNum;
	int RoadNum;
	int LoseCityNum;
	vector<vector<int>> HighwayNetwork;
	vector<int> LoseCity;
	Graph(int num1, int num2, int num3) : CityNum(num1), RoadNum(num2), LoseCityNum(num3),
		HighwayNetwork(vector<vector<int>>(num1 + 1)), LoseCity(vector<int>(num3))
	{
		for (auto &iter : HighwayNetwork)
		{
			iter = vector<int>(num1 + 1);
			for (auto &jter : iter)
			{
				jter = 0;
			}
		}
	}
	Graph(const Graph& g) : CityNum(g.CityNum), RoadNum(g.RoadNum), HighwayNetwork(vector<vector<int>>(g.CityNum + 1))
	{
		HighwayNetwork.assign(g.HighwayNetwork.begin(), g.HighwayNetwork.end());
		LoseCity.assign(g.LoseCity.begin(), g.LoseCity.end());
	}
	void input_network()
	{
		int temp_s, temp_v;
		for (auto iter = 0; iter < RoadNum; ++iter)
		{
			cin >> temp_s >> temp_v;
			HighwayNetwork[temp_s][temp_v] = HighwayNetwork[temp_v][temp_s] = 1;
		}
		for (auto iter = 0; iter < LoseCityNum; ++iter)
		{
			cin >> LoseCity[iter];
		}
		return;
	}
};

class Solution
{
public:
	static void __init__(vector<bool>& cityseq, int LoseCity)
	{
		for (auto a : cityseq)
		{
			a = false;
		}
		cityseq[LoseCity] = true;
		return;
	}
	static int findnextcity(const vector<bool>& cityseq) // 寻找下一个搜索起点
	{
		int ans = 0, len = cityseq.size();
		for (auto iter = 1; iter < len; ++iter)
		{
			if (cityseq[iter] == false)
			{
				ans = iter;
				break;
			}
		}
		return ans;
	}

	static void solution(const Graph& g)
	{
		for (auto ster = 0; ster < g.LoseCityNum; ++ster)
		{
			Graph tg(g); //构建交通网络的拷贝，从而不影响其他情况
			for (auto iter = 1; iter <= g.CityNum; ++iter) // 清空隔绝城市到其他城市的道路
			{
				tg.HighwayNetwork[iter][tg.LoseCity[ster]] = tg.HighwayNetwork[tg.LoseCity[ster]][iter] = 0;
			}
			vector<bool> cityseq(g.CityNum + 1);
			__init__(cityseq, tg.LoseCity[ster]);
			int amount = 0, thiscity = findnextcity(cityseq);
			while (thiscity != 0)  // 广度优先搜索，计数连通分量的个数
			{
				vector<int> citycomponent;
				citycomponent.emplace_back(thiscity);
				cityseq[citycomponent[0]] = true; // 入队的元素记为已访问
				while (citycomponent.size() != 0)
				{
					for (auto iter = 1; iter <= tg.CityNum; ++iter)
					{
						if (cityseq[iter] == false && tg.HighwayNetwork[citycomponent[0]][iter] != 0)
						{
							citycomponent.emplace_back(iter);
							cityseq[iter] = true; // 入队的元素记为已访问
						}
					}
					citycomponent.erase(citycomponent.begin()); // 删除头元素，以进行下一轮BFS
				}
				++amount;
				thiscity = findnextcity(cityseq); // 寻找下一个搜索起点
			}
			cout << amount - 1 << endl; // 道路数最小值为 联通分量个数 - 1
		}
		return;
	}
};

int main(int argc, const char* argv[])
{
	ios::sync_with_stdio(false); // 解除 输入输出流 与 stdio 的绑定，执行后不要混用 scanf / printf
	cin.tie(0); // 解除 cin 与 cout 的绑定

	int CityNum, RoadNum, LoseCityNum;
	cin >> CityNum >> RoadNum >> LoseCityNum;
	Graph g = Graph(CityNum, RoadNum, LoseCityNum); // 构建图对象
	g.input_network();

	Solution::solution(g); // algorithm

	return 0;
}