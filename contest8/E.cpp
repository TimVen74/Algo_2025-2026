#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 110;
const int cBAD = 1e5;

int n;
int d[cN];
int p[cN];
std::vector<std::tuple<int, int, int>> edg;

void Solve() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int x;
      std::cin >> x;
      if (x != cBAD) {
        edg.emplace_back(i, j, x);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    d[i] = 0;
    p[i] = -1;
  }
  bool neg = false;
  int st = -1;
  for (int i = 0; i < n; ++i) {
    neg = false;
    for (auto [v, u, w] : edg) {
      if (d[u] > d[v] + w) {
        d[u] = d[v] + w;
        p[u] = v;
        st = u;
        neg = true;
      }
    }
  }
  if (!neg) {
    std::cout << "NO";
  } else {
    std::cout << "YES\n";
    for (int i = 0; i < n; ++i) {
      st = p[st];
    }
    std::vector<int> ans(1, st);
    st = p[st];
    while (st != ans[0]) {
      ans.push_back(st);
      st = p[st];
    }
    std::reverse(ans.begin(), ans.end());
    ans.push_back(ans[0]);
    std::cout << (int)ans.size() << '\n';
    for (int x : ans) {
      std::cout << x << ' ';
    }
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
