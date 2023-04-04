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
			int i, value;
			cin >> i >> value;
			--i;
			v[i] = value;
		}
	}
}