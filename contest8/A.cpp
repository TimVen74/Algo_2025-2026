#include <iostream>
#include <set>
#include <vector>

const int cN = 2e5 + 10;
const int cINF = 2009000999;

int n;
int m;
std::vector<std::pair<int, int>> g[cN];
int d[cN];

void Solve() {
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    g[i].clear();
    d[i] = cINF;
  }
  for (int i = 1; i <= m; ++i) {
    int v;
    int u;
    int w;
    std::cin >> v >> u >> w;
    g[v].push_back({u, w});
    g[u].push_back({v, w});
  }
  int st;
  std::cin >> st;
  d[st] = 0;
  std::multiset<std::pair<int, int>> q;
  q.insert({0, st});
  while (!q.empty()) {
    auto [dv, v] = *q.begin();
    q.erase(q.begin());
    for (auto [to, w] : g[v]) {
      if (d[to] > d[v] + w) {
        q.erase({d[to], to});
        d[to] = d[v] + w;
        q.insert({d[to], to});
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::cout << d[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int ttt;
  std::cin >> ttt;
  for (int t = 0; t < ttt; ++t) {
    Solve();
  }
  return 0;
}
