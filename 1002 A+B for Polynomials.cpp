/*
思路: 将多项式所有项置入一个vector, 按指数大小排列各项, 再合并相邻项。注意去除合并后可能的零项。
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> // std::sort

using namespace std;

struct item 
{
    int exponent;
    double ratio;
    item(int e, double r): exponent(e), ratio(r) {}
};

bool compare (const item& i1, const item& i2)
{
    return i1.exponent >= i2.exponent;
}

int main(int argc, const char* argv[])
{
    vector<item> polynomial;
    int N, temp_exponent;
    double temp_ratio;
    
    cin >> N;
    for (int iter = 0; iter < N; iter++)
    {
        cin >> temp_exponent >> temp_ratio;
        polynomial.emplace_back(item(temp_exponent, temp_ratio));
    }
    cin >> N;
    for (int iter = 0; iter < N; iter++)
    {
        cin >> temp_exponent >> temp_ratio;
        polynomial.emplace_back(item(temp_exponent, temp_ratio));
    }

    sort(polynomial.begin(), polynomial.end(), compare);

    int iter = 0;
    // 可能是两个零多项式相加, polynomial.size() 为 size_t ( unsigned ) 型, 减1变为整数, 造成越界超时, 故要先判断是否为0 
    while ( polynomial.size() != 0 && iter < polynomial.size() - 1)
    {
        while ( iter + 1 < polynomial.size() && polynomial[iter].exponent == polynomial[iter + 1].exponent )
        {
            polynomial[iter].ratio += polynomial[iter + 1].ratio;
            polynomial.erase(polynomial.begin() + iter + 1);
        }
        if( polynomial[iter].ratio == 0 )
        {
            polynomial.erase(polynomial.begin() + iter);
        }
        else
        {
            iter++;
        }
    }

    int len = polynomial.size();
    // 题目要求保留一位小数
    cout << fixed << setprecision(1) << len;

    for (int jter = 0; jter < len; jter++)
    {
        cout << " " << polynomial[jter].exponent << " " << polynomial[jter].ratio;
    }

    cout << endl;

    return 0;
}