#include <iostream>
#include <vector>

using namespace std;

#define int long long
#define sz(v) static_cast<int>(v.size())

class Fenwick {
public:
	Fenwick(int sz) {
		t = vector<int>(sz + 1);
	}

	Fenwick(const vector<int>& v) : Fenwick(v.size()) {
		for (int i = 0; i < sz(v); ++i) add(i, v[i]);
	}

	void add(int i, int value) {
		++i;
		for (; i < sz(t); i += i & -i) t[i] += value;
	}

	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
	
private:
	vector<int> t;

	int get(int i) {
		++i;
		int ans = 0;
		for (; i > 0; i -= i & -i) ans += t[i];
		return ans;
	}
};

signed main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (auto& x: v) cin >> x;
	Fenwick f(v);
	int q;
	cin >> q;
	while (q--) {
		char x;
		cin >> x;
		if (x == '?') {
			int l, r;
			cin >> l >> r;
			--l, --r;
			cout << f.get(l, r) << '\n';
		} else if (x == '!') {
			int i, value;
			cin >> i >> value;
			--i;
			f.add(i, value);
		}
	}

}