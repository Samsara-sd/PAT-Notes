// cyll 课上学来的最快 ( O(N) ) 的 on-line algorithm

#include <iostream>
#include <array>

using namespace std;

int main(int argc, const char* argv[])
{
	int len;
	cin >> len;
	array<int, 10001> arr;
	for (int iter = 1; iter <= len; ++iter)
	{
		cin >> arr[iter];
	}
	int MaxSum = 0, TempSum = 0;
	int start = arr[1], end = arr[len];
	int temp_start = start;
	for (int iter = 1; iter <= len; ++iter)
	{
		TempSum += arr[iter];
		if (TempSum >= MaxSum)
		{
      // 如该样例: -1 0 0 -1 输出的应为 0 0 0
      // 全负会定义 Sum 为0, 如果出现新的子段和0, 则应当更新, 因为此时不是全负(有点绕) 
			if( TempSum > MaxSum || TempSum == 0 )
			MaxSum = TempSum;
			start = temp_start;
			end = arr[iter];
		}

		if (TempSum < 0)
		{
			TempSum = 0;
			temp_start = arr[iter + 1];
		}
	}

	cout << MaxSum << " " << start << " " << end;
	return 0;
}
