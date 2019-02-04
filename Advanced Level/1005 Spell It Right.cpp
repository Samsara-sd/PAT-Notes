//std::string 与 int 转换
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    string number;
    cin >> number;
    int len = number.length();
    int sum = 0;
    
    for (int iter = 0; iter < len; ++iter)  //Compute the sum
    {
        sum += int(number[iter] - '0');
    }

    number = to_string(sum);
    len = number.length();

    for (int iter = 0; iter < len; ++iter)
    {
        switch( number[iter] )
        {
            case '0':
            {
                cout << "zero";
                break;
            }
            case '1':
            {
                cout << "one";
                break;
            }
            case '2':
            {
                cout << "two";
                break;
            }
            case '3':
            {
                cout << "three";
                break;
            }
            case '4':
            {
                cout << "four";
                break;
            }
            case '5':
            {
                cout << "five";
                break;
            }
            case '6':
            {
                cout << "six";
                break;
            }
            case '7':
            {
                cout << "seven";
                break;
            }
            case '8':
            {
                cout << "eight";
                break;
            }
            case '9':
            {
                cout << "nine";
                break;
            }
        }

        cout << ( iter == len - 1 ? "" : " " ) ;
    }

    return 0;
}