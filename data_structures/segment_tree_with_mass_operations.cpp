#include <iostream>
#include <vector>

using namespace std;

#define sz(v) static_cast<int>(v.size())
#define int long long

class Tree {
public:
	Tree(const vector<int>& v) {
		sz = 0;
		while ((1 << sz) <= sz(v)) ++sz;
		++sz;
		sz = (1 << sz);
		capacity = (sz >> 1);
		t = vector<int>(sz);
		assign = vector<int>(sz);
		for (int i = 0; i < sz(v); ++i) t[i + capacity] = v[i];
		for (int i = capacity - 1; i > 0; --i) t[i] = t[i * 2] + t[i * 2 + 1];
	}

	int get(int l, int r) {
		return get(1, 0, capacity - 1, l, r);
	}

	void add(int l, int r, int value) {
		add(1, 0, capacity - 1, l, r, value);
	}

private:
	vector<int> t, assign;
	int sz, capacity;

	int get(int cur, int left, int right, int l, int r) {
		if (left > r || right < l) return 0;
		if (l <= left && r >= right) return t[cur] + assign[cur];
		push(cur);
		int ans = get(cur * 2, left, (left + right) / 2, l, r) + 
					get(cur * 2 + 1, (left + right) / 2 + 1, right, l, r);
		render(cur);
		return ans;
	}

	void add(int cur, int left, int right, int l, int r, int value) {
		if (left > r || right < l) return;
		if (l <= left && r >= right) {
			assign[cur] += value;
			return;
		} 
		push(cur);
		add(cur * 2, left, (left + right) / 2, l, r, value);
		add(cur * 2 + 1, (left + right) / 2 + 1, right, l, r, value);
		render(cur);
	}

	void push(int cur) {
		if (cur * 2 >= sz || !assign[cur]) return;
		assign[cur * 2] += assign[cur];
		assign[cur * 2 + 1] += assign[cur];
		assign[cur] = 0;
	}

	void render(int cur) {
		t[cur] = t[cur * 2] + assign[cur * 2] + t[cur * 2 + 1] + assign[cur * 2 + 1];
	}
};

signed main() {
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
			int l, r, value;
			cin >> l >> r >> value;
			--l, --r;
			t.add(l, r, value);
		}
	}

}