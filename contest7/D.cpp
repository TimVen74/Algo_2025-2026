#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 5e5 + 10;

int n;
int m;
std::vector<int> g[cN];
std::vector<int> rg[cN];
bool usd[cN];
int ans[cN];
int col = 1;
std::vector<int> top_sort;

void Dfs(int v) {
  usd[v] = true;
  for (int to : g[v]) {
    if (!usd[to]) {
      Dfs(to);
    }
  }
  top_sort.push_back(v);
}

void Color(int v) {
  ans[v] = col;
  for (int to : rg[v]) {
    if (ans[to] == -1) {
      Color(to);
    }
  }
}

std::vector<int> gc[cN];
std::vector<int> top_sort_c;
bool usdc[cN];
int idc[cN];

void Dfs2(int c) {
  usdc[c] = true;
  for (int to : gc[c]) {
    if (!usdc[to]) {
      Dfs2(to);
    }
  }
  top_sort_c.push_back(c);
}

void Solve() {
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> edg;
  for (int i = 1; i <= m; ++i) {
    int x;
    int y;
    std::cin >> x >> y;
    edg.push_back({x, y});
    g[x].push_back(y);
    rg[y].push_back(x);
  }

  for (int i = 1; i <= n; ++i) {
    if (!usd[i]) {
      Dfs(i);
    }
  }

  std::fill(ans + 1, ans + n + 1, -1);
  std::reverse(top_sort.begin(), top_sort.end());

  for (int x : top_sort) {
    if (ans[x] == -1) {
      Color(x);
      ++col;
    }
  }
  --col;

  for (auto [x, y] : edg) {
    if (ans[x] != ans[y]) {
      gc[ans[x]].push_back(ans[y]);
    }
  }

  for (int i = 1; i <= col; ++i) {
    if (!usdc[i]) {
      Dfs2(i);
    }
  }
  std::reverse(top_sort_c.begin(), top_sort_c.end());
  for (int i = 0; i < (int)top_sort_c.size(); ++i) {
    idc[top_sort_c[i]] = i + 1;
  }

  std::cout << col << '\n';
  for (int i = 1; i <= n; ++i) {
    std::cout << idc[ans[i]] << ' ';
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
