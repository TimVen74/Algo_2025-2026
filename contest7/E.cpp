#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 2e4 + 10;

std::vector<std::pair<int, int>> g[cN];
std::vector<int> ans;
int tin[cN];
int tout[cN];
int fup[cN];
int tmr = 0;

void Dfs(int v, int pred) {
  tin[v] = tmr++;
  fup[v] = tin[v];
  for (auto [to, id] : g[v]) {
    if (id == pred) {
      continue;
    }
    if (tin[to] == -1) {
      Dfs(to, id);
      fup[v] = std::min(fup[v], fup[to]);
      if (fup[to] > tin[v]) {
        ans.push_back(id);
      }
    } else {
      fup[v] = std::min(fup[v], tin[to]);
    }
  }
  tout[v] = tmr++;
}

void Solve() {
  int n;
  int m;
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int x;
    int y;
    std::cin >> x >> y;
    g[x].push_back({y, i});
    g[y].push_back({x, i});
  }
  std::fill(tin + 1, tin + n + 1, -1);
  for (int i = 1; i <= n; ++i) {
    if (tin[i] == -1) {
      Dfs(i, -1);
    }
  }
  std::sort(ans.begin(), ans.end());
  std::cout << (int)ans.size() << '\n';
  for (int x : ans) {
    std::cout << x << ' ';
  }
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
