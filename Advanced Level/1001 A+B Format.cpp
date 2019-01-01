/*
基础题，需要注意的有几个细节:
1. 数字转字符串，为方便判断长度只转数字部分，不转可能的负号
2. 判断是否应添加逗号 1000000 应为 1,000,000 而非 100,000,0
*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[])
{
    int a, b;
    cin >> a >> b;
    int c = a + b;

    cout << (c < 0 ? "-" : "");
    string num = to_string(c < 0 ? -c : c);

    int flag = num.length() % 3;

    for (int iter = 1; iter <= num.length(); iter++)
    {
        cout << num[iter - 1];
        if( iter % 3 == flag && iter != num.length())
        {
            cout << ",";
        }
    }

    cout << endl;

    return 0;
}