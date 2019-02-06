//类似于多项式加法, 先把所有的项计算出来，之后相邻指数合并
//注意删除系数为零的项

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> // std::sort

using namespace std;

struct item
{
    double ratio;
    int exponent;
    item(double r, int e): ratio(r), exponent(e) {}
};

using polynomial = vector<item>;

polynomial getpolynomial(int len)
{
    polynomial ans;
    double r;
    int e;
    for (int iter = 0; iter < len; ++iter)
    {
        cin >> e >> r;
        ans.emplace_back(item(r, e));
    }
    return ans;
}

bool compare(const item& i1, const item& i2) // 用于sort
{
    return i1.exponent >= i2.exponent;
}

void printpoly(const polynomial& poly) // 输出运算结果
{
    unsigned int len = poly.size();
    cout << len << " " << fixed << setprecision(1); // 输出格式要求
    if(len != 0)
    {
        cout <<  poly[0].exponent << " " << poly[0].ratio;
        for (int iter = 1; iter < len; ++iter)
        {
            cout << " " << poly[iter].exponent << " " << poly[iter].ratio;
        }
    }

    return;
}

int main(int argc, const char* argv[])
{
    int len1, len2;
    cin >> len1;
    polynomial poly1 = getpolynomial(len1);
    cin >> len2;
    polynomial poly2 = getpolynomial(len2);

    polynomial product;
    for (int iter = 0; iter < len1; ++iter)
    {
        for (int jter = 0; jter < len2; ++jter)
        {
            product.emplace_back(item(poly1[iter].ratio * poly2[jter].ratio, poly1[iter].exponent + poly2[jter].exponent));
        }
    }
    sort(product.begin(), product.end(), compare);

    for (int iter = 0; iter < product.size(); iter++)
    {
        while( iter + 1 < product.size() && product[iter].exponent == product[iter + 1].exponent ) // 合并同指数项
        {
            product[iter].ratio += product[iter + 1].ratio;
            product.erase(product.begin() + iter + 1);
        }
        if( product[iter].ratio == 0 ) // 去除合并后的零项
        {
            product.erase(product.begin() + iter);
        }
    }

    printpoly(product);
    return 0;
}