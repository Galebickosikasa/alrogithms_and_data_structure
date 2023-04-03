#include <iostream>
#include <vector>

using namespace std;

const int inf = 2e9;

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (auto& x: v) cin >> x;
	int q;
	cin >> q;
	while (q--) {
		char x;
		cin >> x;
		if (x == '?') {
			int l, r;
			cin >> l >> r;
			--l, --r;
			int mx = -inf;
			for (int i = l; i <= r; ++i) mx = max(mx, v[i]);
			cout << mx << '\n';
		} else if (x == '!') {
			int i, value;
			cin >> i >> value;
			--i;
			v[i] = value;
		}
	}
}