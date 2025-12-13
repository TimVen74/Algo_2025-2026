#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 1e5 + 10;
const int cLG = 20;
const int cINF = 1e9 + 7;

int a[cN];
int lg[cN];
std::pair<int, int> spt[cN][cLG];

std::pair<int, int> Get(int l, int r) {
  if (l > r) {
    return {cINF, cINF};
  }
  int j = lg[r - l + 1];
  return min(spt[l][j], spt[r - (1 << j) + 1][j]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  lg[1] = 0;
  for (int i = 2; i < cN; ++i) {
    lg[i] = lg[i / 2] + 1;
  }
  int n;
  int q;
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    spt[i][0] = {a[i], i};
  }
  std::vector<int> cur;
  for (int j = 1; j < cLG; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
      std::pair<int, int> p1 = spt[i][j - 1];
      std::pair<int, int> p2 = spt[i + (1 << (j - 1))][j - 1];
      spt[i][j] = min(p1, p2);
    }
  }
  for (int q1 = 0; q1 < q; ++q1) {
    int l;
    int r;
    std::cin >> l >> r;
    std::pair<int, int> mn = Get(l, r);
    std::pair<int, int> p1 = Get(l, mn.second - 1);
    std::pair<int, int> p2 = Get(mn.second + 1, r);
    std::cout << min(p1, p2).first << '\n';
  }
  return 0;
}
