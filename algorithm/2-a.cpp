
#include <iostream>
#include <cstring>
using namespace std;
int a[1001];

int Max(int n)
{
	int max = a[0];
	int sum = a[0];
	for (int i = 1; i < n; i++){
		if (a[i] > max){
			sum += a[i];
			max = a[i];
		}
	}
	
	return sum;
}

int main()
{
	int t;
	cin >> t;
	while (t != 0){
		memset(a, 0, sizeof(a));
		for (int i = 0; i < t; i++){
			cin >> a[i];
		}
		int res = Max(t);

		cout << res << endl;

		cin >> t;
	}

	return 0;
}
