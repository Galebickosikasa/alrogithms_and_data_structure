#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <memory>

using namespace std;

#define int long long 

#ifdef LOCAL 
	#define dbg(x) cerr << #x << " : " << x << endl;
#else
	#define dbg(x) 228;
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

class Tree {
public:
	Tree(int x) {
		value = x;
		sz = 1;
		left = right = nullptr;
		priority = rnd();
	}

	shared_ptr<Tree> left;
	shared_ptr<Tree> right;
	int priority;
	int sz;
	int value;
};

typedef shared_ptr<Tree> T;

T render(T root) {
	root->sz = 1;
	if (root->left) root->sz += root->left->sz;
	if (root->right) root->sz += root->right->sz;
	return root;
}

int get_sz(T root) {
	if (!root) return 0;
	return root->sz;
}

int get_index(T root) {
	if (!root) return 0;
	return get_sz(root->left) + 1;
}

T make_tree(int value) {
	return make_shared<Tree>(value);
}

T merge(T a, T b) {
	if (!a) return b;
	if (!b) return a;
	if (a->priority > b->priority) {
		a->right = merge(a->right, b);
		return render(a);
	} else {
		b->left = merge(a, b->left);
		return render(b);
	}
}

pair<T, T> split(T root, int x) {
	pair<T, T> ptt{nullptr, nullptr};
	if (!root) return ptt;
	if (get_index(root) <= x) {
		ptt = split(root->right, x - get_index(root));
		root->right = ptt.first;
		ptt.first = root;
	} else {
		ptt = split(root->left, x);
		root->left = ptt.second;
		ptt.second = root;
	}
	render(root);
	return ptt;
}

T add(T root, T new_t) {
	return merge(root, new_t);
}

T add(T root, int x) {
	T new_t = make_tree(x);
	return add(root, new_t);
}

T find(T root, int i) {
	if (!root) return root;
	if (get_index(root) == i) return root;
	if (get_index(root) < i) return find(root->right, i - get_index(root));
	return find(root->left, i);
}

T erase(T root, int i) {
	if (!root) return root;
	if (get_index(root) == i) return merge(root->left, root->right);
	if (get_index(root) < i) root->right = erase(root->right, i - get_index(root));
	else root->left = erase(root->left, i);
	return render(root);
}

pair<int, int> split(int x) {
	if (x % 2) return {x / 2, x / 2 + 1};
	return {x / 2, x / 2};
}

signed main() {
	int n, p;
	cin >> n >> p;
	T root = nullptr;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		ans += x * x;
		root = add(root, x);
	}
	cout << ans << '\n';
	int q;
	cin >> q;
	while (q--) {
		int e, v;
		cin >> e >> v;
		if (e == 1) {
			T t = find(root, v);
			int value = t->value;
			ans -= value * value;
			auto ptt = split(root, v);
			T l, r;
			l = r = nullptr;
			if (get_sz(ptt.second)) r = find(ptt.second, 1);
			if (get_sz(ptt.first) > 1) l = find(ptt.first, v - 1);
			ptt.first = erase(ptt.first, v);
			if (l && r) {
				ans -= l->value * l->value;
				ans -= r->value * r->value;
				auto p = split(value);
				l->value += p.first;
				r->value += p.second;
				ans += l->value * l->value + r->value * r->value;
			} else if (l) {
				ans -= l->value * l->value;
				l->value += value;
				ans += l->value * l->value;
			}
			else {
				ans -= r->value * r->value;
				r->value += value;
				ans += r->value * r->value;
			}
			root = merge(ptt.first, ptt.second);
		} else {
			T t = find(root, v);
			auto p = split(t->value);
			ans -= t->value * t->value;
			ans += p.first * p.first + p.second * p.second;
			auto ptt = split(root, v);
			ptt.first = erase(ptt.first, v);
			ptt.first = add(ptt.first, p.first);
			ptt.first = add(ptt.first, p.second);
			root = merge(ptt.first, ptt.second);
		}
		cout << ans << '\n';
	}

}