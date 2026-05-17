#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 1e5 + 10;

int rt[cN];
int sz[cN];
int Root(int x) {
  if (rt[x] != x) {
    rt[x] = Root(rt[x]);
  }
  return rt[x];
}
bool Merge(int v, int u) {
  int r1 = Root(v);
  int r2 = Root(u);
  if (r1 == r2) {
    return false;
  }
  if (sz[r1] > sz[r2]) {
    rt[r2] = r1;
    sz[r1] += sz[r2];
  } else {
    rt[r1] = r2;
    sz[r2] += sz[r1];
  }
  return true;
}

int n;
int m;
std::vector<std::tuple<int, int, int>> edg;

void Solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int x;
    int y;
    int w;
    std::cin >> x >> y >> w;
    edg.push_back({w, x, y});
  }
  std::sort(edg.begin(), edg.end());
  for (int i = 1; i <= n; ++i) {
    rt[i] = i;
    sz[i] = 1;
  }
  long long ans = 0;
  for (auto [w, v, u] : edg) {
    if (Merge(v, u)) {
      ans += w;
    }
  }
  std::cout << ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  Solve();
  return 0;
}
