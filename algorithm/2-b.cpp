#include<iostream>
using namespace std;

typedef long long ll;

ll m ,n;

int main(){
	cin >> n >> m;
	cout << (m + 1) * (1 << n);
	return 0;
}

