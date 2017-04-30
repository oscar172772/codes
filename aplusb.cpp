#include <iostream>
#include <cmath>
using namespace std;

typedef long long s64;

int main() {
	int a, b;
	cin >> a >> b;
	int best = rand(), cur = abs(best - (a + b));
	double T = 1e9;
	double tmp0 = 1e9;
	while (T > 1e-9)
	{
		tmp0 *= 0.99999;
		int x = cur + max(1, int(rand() * tmp0)) * (rand() >> 5 & 1 ? 1 : -1);
		int delta = abs(x - (a + b)) - cur;
		if (delta < 0 || (double)rand() / RAND_MAX < exp(-delta / T))
		{
			cur += delta;
			best = x;
		}
		T *= 0.99999;
	}
    //    if (best=a+b);
	cout << best << endl;
	system("pause");
	return 0;
}
