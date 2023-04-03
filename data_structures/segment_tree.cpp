#include <iostream>
#include <vector>

using namespace std;

#define sz(v) static_cast<int>(v.size())

const int inf = 2e9;

class Tree {
public:
	Tree(const vector<int>& v) {
		sz = 0;
		while ((1 << sz) <= sz(v)) ++sz;
		++sz;
		sz = (1 << sz);
		capacity = (sz >> 1);
		t = vector<int>(sz, -inf);
		for (int i = 0; i < sz(v); ++i) t[i + capacity] = v[i];
		for (int i = capacity - 1; i > 0; --i) t[i] = max(t[i * 2], t[i * 2 + 1]);
	}

	int get(int l, int r) {
		return get(1, 0, capacity - 1, l, r);
	}

	void set(int i, int value) {
		i += capacity;
		t[i] = value;
		i >>= 1;
		while (i) {
			t[i] = max(t[i * 2], t[i * 2 + 1]);
			i >>= 1;
		}
	}

private:
	vector<int> t;
	int sz, capacity;

	int get(int cur, int left, int right, int l, int r) {
		if (right < l || left > r) return -inf;
		if (l <= left && r >= right) return t[cur];
		return max(get(cur * 2, left, (left + right) / 2, l, r), get(cur * 2 + 1, (left + right) / 2 + 1, right, l, r));
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (auto& x: v) cin >> x;
	Tree t(v);
	int q;
	cin >> q;
	while (q--) {
		char x;
		cin >> x;
		if (x == '?') {
			int l, r;
			cin >> l >> r;
			--l, --r;
			cout << t.get(l, r) << '\n';
		} else if (x == '!') {
			int i, value;
			cin >> i >> value;
			--i;
			t.set(i, value);
		}
	}
}