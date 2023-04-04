#include <iostream>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

#define int long long 

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

signed main(signed argc, char** argv) {
	assert(argc == 3);
	int sizev = stoi(argv[1]);
	int cntq = stoi(argv[2]);
	cout << sizev << '\n';
	for (int i = 0; i < sizev; ++i) {
		int value = rnd() % (int)4e9 + (int)2e9;
		cout << value << ' ';
	}
	cout << '\n' << cntq << '\n';
	for (int i = 0; i < cntq; ++i) {
		int x = rnd() % 2;
		if (x) {
			int l = rnd() % sizev + 1;
			int r = rnd() % sizev + 1;
			if (l > r) swap(l, r);
			cout << "? " << l << ' ' << r << '\n';
		} else {
			int l = rnd() % sizev + 1;
			int r = rnd() % sizev + 1;
			if (l > r) swap(l, r);
			int value = rnd() % (int)4e9 + (int)2e9;
			cout << "! " << l << ' ' << r << ' ' << value << '\n'; 
		}
	}
}