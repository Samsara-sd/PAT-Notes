// 审清题没坑点
#include <iostream>
using namespace std;

int main(void)
{
    int num, templevel;
    cin >> num;
    int thislevel = 0;
    int time = 0;
    for(int iter = 1; iter <= num; ++iter)
    {
        cin >> templevel;
        if(templevel > thislevel)
        {
            time += 6 * (templevel - thislevel);
        }
        else
        {
            time += 4 * (thislevel - templevel);
        }
        time += 5;
        thislevel = templevel;
    }
    cout << time;
    return 0;
}