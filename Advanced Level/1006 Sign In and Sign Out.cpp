//简单的找序列中最大值和最小值

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main(void)
{
    int sign_num;
    scanf("%d", &sign_num);
    string sign_in, sign_out;
    int h1 = 0, m1 = 0, s1 = 0, h2 = 23, m2 = 59, s2 = 59;
    string tname;
    int th1, tm1, ts1, th2, tm2, ts2;

    for (int iter = 1; iter <= sign_num; ++iter)
    {
        cin >> tname;
        scanf("%d:%d:%d %d:%d:%d", &th1, &tm1, &ts1, &th2, &tm2, &ts2);
        if( th1 < h1 || ( th1 == h1 && tm1 < m1 ) || ( th1 == h1 && tm1 == m1 && ts1 < s1 ) )
        {
            sign_in = tname;
            h1 = th1;
            m1 = tm1;
            s1 = ts1;
        }

        if( th2 > h2 || ( th2 == h2 && tm2 > m2 ) || ( th2 == h2 && tm2 == m2 && ts2 > s2 ) )
        {
            sign_out = tname;
            h2 = th2;
            m2 = tm2;
            s2 = ts2;
        }
    }

    cout << sign_in << " " << sign_out;
    return 0;
}