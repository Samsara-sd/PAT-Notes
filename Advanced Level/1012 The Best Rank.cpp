// 题干的描述比较绕, 是说在某个学生的四种成绩对应了四个分别的排名, 得到其中最高的排名, 以及这个最高的排名是哪一科
// 优先级为 A > C > M > E, 按这个顺序分别根据相应成绩排序, 如果出现了更高的排名就更新排名与对应的科目
// 对于较多数据考虑使用unordered_map建立索引, 提高查询速度, 需要增加某学号是否已经建立过索引的判断
// 由于并列排名的情况, 需要向前搜索到该成绩的最高排名( 测试点 2 )
// 另一个小问题: sort使用的排序函数不能带等号, 可能触发coredump( 测试点 3, 4 )
//     描述可详见  https://blog.csdn.net/jiange_zh/article/details/78240806

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct person
{
    string id;
    int C;
    int M;
    int E;
    int A;
    int bestrank;
    char bestranktype;
    person(string ID, int c, int m, int e):id(ID), C(c), M(m), E(e) 
    {
        A = int( ( C + M + E ) / 3 + 0.5 );
    }
};

struct ranklist
{
    vector<person> personlist;
    unordered_map<string, pair<int, char>> personmap;  // 学号 -> 最高排名 的索引
    static bool sortbyC(const person& p1, const person& p2) // 四个排序函数不带等号
    {
        return p1.C > p2.C;
    }
    static bool sortbyM(const person& p1, const person& p2)
    {
        return p1.M > p2.M;
    }
    static bool sortbyE(const person& p1, const person& p2)
    {
        return p1.E > p2.E;
    }
    static bool sortbyA(const person& p1, const person& p2)
    {
        return p1.A > p2.A;
    }
    void createmap()  // 建立索引
    {
        int len = personlist.size();
        for (int iter = 0; iter < len; ++iter)
        {
            personmap.insert(make_pair(personlist[iter].id, make_pair(personlist[iter].bestrank, personlist[iter].bestranktype)));
        }
    }
    void getbestrank()  //得到最高排名
    {
        int len = personlist.size();
        sort(personlist.begin(), personlist.end(), sortbyA);
        for (int iter = 0; iter < len; ++iter)
        {
            int maxrank = iter;
            while( maxrank >= 1 && personlist[maxrank].A == personlist[maxrank - 1].A )
            {
                maxrank--;
            }
            personlist[iter].bestrank = maxrank + 1;
            personlist[iter].bestranktype = 'A';
        }
        sort(personlist.begin(), personlist.end(), sortbyC);
        for (int iter = 0; iter < len; ++iter)
        {
            int maxrank = iter;
            while( maxrank >= 1 && personlist[maxrank].C == personlist[maxrank - 1].C )
            {
                maxrank--;
            }
            if( personlist[iter].bestrank > maxrank + 1 )
            {
                personlist[iter].bestrank = maxrank + 1;
                personlist[iter].bestranktype = 'C';
            }
        }
        sort(personlist.begin(), personlist.end(), sortbyM);
        for (int iter = 0; iter < len; ++iter)
        {
            int maxrank = iter;
            while( maxrank >= 1 && personlist[maxrank].M == personlist[maxrank - 1].M )
            {
                maxrank--;
            }
            if( personlist[iter].bestrank > maxrank + 1 )
            {
                personlist[iter].bestrank = maxrank + 1;
                personlist[iter].bestranktype = 'M';
            }
        }
        sort(personlist.begin(), personlist.end(), sortbyE);
        for (int iter = 0; iter < len; ++iter)
        {
            int maxrank = iter;
            while( maxrank >= 1 && personlist[maxrank].E == personlist[maxrank - 1].E )
            {
                maxrank--;
            }
            if( personlist[iter].bestrank > maxrank + 1 )
            {
                personlist[iter].bestrank = maxrank + 1;
                personlist[iter].bestranktype = 'E';
            }
        }
        createmap();
    }
};

int main(int argc, const char* argv[])
{
    ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    ranklist list;
    for (int iter = 0; iter < N; ++iter)
    {
        string id;
        int C, M, E;
        cin >> id >> C >> M >> E;
        list.personlist.emplace_back(person(id, C, M, E));
    }
    list.getbestrank();
    for (int iter = 0; iter < M; ++iter)
    {
        string id;
        cin >> id;
        if( 0 != list.personmap.count(id) )  // 判断该学号是否被输入过
        {
            cout << list.personmap[id].first << " " << list.personmap[id].second << endl;
        }
        else
        {
            cout << "N/A" << endl;
        }
    }

    return 0;
}