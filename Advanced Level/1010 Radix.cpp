// 为了便于比较，将两个数字都转化为十进制
// 坑点略多:
// 1: 数字最高到'z' 不代表最高进制就是35, 而是已知进制的数的十进制值 + 1
// 2: 数据溢出, 故需要用 long long 型
// 3: 当进制过高时, 利用for循环寻找进制可能会超时, 故需要用二分查找
//    ( 当溢出时转换得到的是负数, 故当得到负数时应特殊判断, 此时应当更改的是右边界 )

#include <iostream>
#include <string>

using namespace std;

long long intpow(int num, int exponent) // 计算整数幂
{
	if (num == 0 && exponent == 0)
	{
		return 0;
	}

	long long ans = 1;
	for (int iter = 1; iter <= exponent; ++iter)
	{
		ans *= num;
	}
	return ans;
}

int getint(char ch) // 字符转为整数
{
	if ('0' <= ch && '9' >= ch)
	{
		return int(ch - '0');
	}
	else
	{
		return int(ch - 'a' + 10);
	}
}

int getminradix(const string& num) // 判断某个数据的最小进制
{
	int max = 0;
	unsigned int len = num.length();
	for (int iter = 0; iter < len; iter++)
	{
		int temp = getint(num[iter]);
		max = (max >= temp ? max : temp);
	}
	return max + 1;
}

long long convert_x_to_radix(const string& num, long long radix) // 将某个 radix 进制数转化为 十进制数
{
	long long ans = 0;
	unsigned int len = num.length();
	for (int iter = 0; iter < len; ++iter)
	{
		ans += getint(num[iter]) * intpow(radix, len - iter - 1);
	}
	return ans;
}

int main(int argc, const char* argv[])
{
	string num1, num2;
	long long tag, radix;
	cin >> num1 >> num2 >> tag >> radix;

	long long sum = (tag == 1 ? convert_x_to_radix(num1, radix) : convert_x_to_radix(num2, radix));
	string num = (tag == 1 ? num2 : num1);
	long long minradix = getminradix(num);

        long long left = minradix, right = sum + 1;
    
        while ( left <= right )
	{
        	long long mid = ( right + left ) / 2;
        	long long tempsum = convert_x_to_radix(num, mid);
		if (sum == tempsum)
		{
			cout << mid;
			return 0;
		}
        	else if( sum < tempsum || tempsum < 0 ) // 溢出判断
        	{
            		right = mid - 1;
        	}
        	else
        	{
            		left = mid + 1;
        	}
	}

	cout << "Impossible";
	return 0;
}
