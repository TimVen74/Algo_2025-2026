#include <iostream>
#include <vector>

const int cN = 260;

int mt[cN];
std::vector<int> g[cN];
int usd[cN];
int tmr = 1;

bool TryK(int v) {
  if (usd[v] == tmr) {
    return false;
  }
  usd[v] = tmr;
  for (int to : g[v]) {
    if (mt[to] == -1 || TryK(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

void Solve() {
  int n;
  int k;
  std::cin >> n >> k;
  std::fill(mt + 1, mt + k + 1, -1);

  for (int i = 1; i <= n; ++i) {
    int x;
    std::cin >> x;
    while (x != 0) {
      g[i].push_back(x);
      std::cin >> x;
    }
  }

  for (int i = 1; i <= n; ++i) {
    TryK(i);
    ++tmr;
  }

  std::vector<std::pair<int, int>> ans;
  for (int i = 1; i <= k; ++i) {
    if (mt[i] != -1) {
      ans.push_back({mt[i], i});
    }
  }
  std::cout << (int)ans.size() << '\n';
  for (auto [x, y] : ans) {
    std::cout << x << ' ' << y << '\n';
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
