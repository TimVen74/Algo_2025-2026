#include <algorithm>
#include <iostream>
#include <vector>

struct Fenwick {
  std::vector<long long> val;

  Fenwick() = default;

  void Add(int x, int delta) {
    for (int i = x; i < (int)val.size(); i = i | (i + 1)) {
      val[i] += delta;
    }
  }

  long long Sum(int r) {
    long long ans = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
      ans += val[i];
    }
    return ans;
  }
};

const int cN = 1e5 + 10;
int x[cN];
int y[cN];
int w[cN];
std::vector<int> coords[cN];
Fenwick tree[cN];
std::vector<int> xs;

void Upd(int a, int b, int delta) {
  for (int j = a; j < (int)xs.size(); j = j | (j + 1)) {
    int k = (int)(lower_bound(coords[j].begin(), coords[j].end(), b) -
                  coords[j].begin());
    tree[j].Add(k, delta);
  }
}

long long Get(int a, int b) {
  long long ans = 0;
  for (int j = a; j >= 0; j = (j & (j + 1)) - 1) {
    int k = (int)(--upper_bound(coords[j].begin(), coords[j].end(), b) -
                  coords[j].begin());
    ans += tree[j].Sum(k);
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int n;
  std::cin >> n;

  for (int i = 1; i <= n; ++i) {
    std::cin >> x[i] >> y[i] >> w[i];
    xs.push_back(x[i]);
  }

  std::sort(xs.begin(), xs.end());
  xs.resize(unique(xs.begin(), xs.end()) - xs.begin());

  for (int i = 1; i <= n; ++i) {
    x[i] = (int)(lower_bound(xs.begin(), xs.end(), x[i]) - xs.begin());
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = x[i]; j < (int)xs.size(); j = j | (j + 1)) {
      coords[j].push_back(y[i]);
    }
  }

  for (int i = 0; i < (int)xs.size(); ++i) {
    sort(coords[i].begin(), coords[i].end());
    tree[i].val.resize(coords[i].size());
  }

  for (int i = 1; i <= n; ++i) {
    Upd(x[i], y[i], w[i]);
  }

  int q;
  std::cin >> q;
  for (int q1 = 0; q1 < q; ++q1) {
    std::string t;
    std::cin >> t;
    if (t[0] == 'c') {
      int i;
      int nw;
      std::cin >> i >> nw;
      Upd(x[i], y[i], nw - w[i]);
      w[i] = nw;
    } else {
      int a;
      int b;
      std::cin >> a >> b;
      a = (int)(--upper_bound(xs.begin(), xs.end(), a) - xs.begin());
      std::cout << Get(a, b) << '\n';
    }
  }
  return 0;
}
