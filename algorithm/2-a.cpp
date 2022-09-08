#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int a[1001], b[1001];

int Max(int n)
{
	int ans = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < i; j++){
			if (a[j] < a[i] && (a[i] + b[j] > b[i])){ 
				b[i] = a[i] + b[j]; // 只有比前面大的数才能加到值里
		
			}
		}
		ans = max(ans, b[i]);
	}
	
	return ans;
}

int main()
{
	int t;
	while (cin >> t && t != 0){
		memset(a, 0, sizeof(a));
		for (int i = 0; i < t; i++){
			cin >> a[i];
			b[i] = a[i];
		}
		int res = Max(t);

		cout << res << endl;
	}

	return 0;
}
