#include <iostream>
#include <vector>

using namespace std;

#define int long long

signed main() {
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
			int ans = 0;
			for (int i = l; i <= r; ++i) ans += v[i];
			cout << ans << '\n';
		} else if (x == '!') {
			int l, r, value;
			cin >> l >> r >> value;
			--l, --r;
			for (int i = l; i <= r; ++i) v[i] += value;
		}
	}

}