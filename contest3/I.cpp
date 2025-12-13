#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 1e5 + 10;

int a[cN];
std::vector<int> tree[cN * 4];

void Build(int tind, int l, int r) {
  if (r - l == 1) {
    tree[tind] = {a[l]};
  } else {
    int m = (r + l) >> 1;
    Build(tind * 2 + 1, l, m);
    Build(tind * 2 + 2, m, r);
    tree[tind].resize(r - l);
    std::merge(tree[tind * 2 + 1].begin(), tree[tind * 2 + 1].end(),
               tree[tind * 2 + 2].begin(), tree[tind * 2 + 2].end(),
               tree[tind].begin());
  }
}

int Get(int tind, int l, int r, int ql, int qr, std::pair<int, int> p) {
  if (ql >= r || l >= qr) {
    return 0;
  }
  if (ql <= l && r <= qr) {
    int x = p.first;
    int y = p.second;
    return (int)(upper_bound(tree[tind].begin(), tree[tind].end(), y) -
                 lower_bound(tree[tind].begin(), tree[tind].end(), x));
  }
  int m = (r + l) >> 1;
  return Get(tind * 2 + 1, l, m, ql, qr, p) +
         Get(tind * 2 + 2, m, r, ql, qr, p);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int n;
  int q;
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  Build(0, 1, n + 1);
  for (int q1 = 0; q1 < q; ++q1) {
    int l;
    int r;
    int x;
    int y;
    std::cin >> l >> r >> x >> y;
    std::cout << Get(0, 1, n + 1, l, r + 1, {x, y}) << '\n';
  }
  return 0;
}
