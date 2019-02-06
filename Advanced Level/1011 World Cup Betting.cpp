// 按照题目中的公式算

#include <iostream>
#include <iomanip> // fixed & setprecision()

using namespace std;

struct game
{
	double W;
	double T;
	double L;
	double M;
	char max;
	void get()
	{
		max = (W > T ? (W > L ? 'W' : 'L') : (T > L ? 'T' : 'L'));
		M = (W > T ? (W > L ? W : L) : (T > L ? T : L));
	}
};

int main(void)
{
	game games[3];

	for (int iter = 0; iter < 3; ++iter)
	{
		cin >> games[iter].W >> games[iter].T >> games[iter].L;
		games[iter].get();
		cout << games[iter].max << " ";
	}

	cout << fixed << setprecision(2) << (games[0].M * games[1].M * games[2].M * 0.65 - 1) * 2;

	return 0;
}