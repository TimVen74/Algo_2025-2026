#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 110;
const int cW = 1e4 + 10;

int n;
int m;
int a[cN];
int c[cN];
int dp[cN][cW];

void Solve() {
  std::cin >> n;
  std::cin >> m;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> c[i];
  }

  for (int i = 1; i < cW; ++i) {
    dp[0][i] = -1;
  }
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= m; ++w) {
      dp[i][w] = dp[i - 1][w];
    }
    for (int w = 0; w + a[i] <= m; ++w) {
      if (dp[i - 1][w] == -1) {
        continue;
      }
      dp[i][w + a[i]] = std::max(dp[i][w + a[i]], dp[i - 1][w] + c[i]);
    }
  }
  int res = 0;
  int cur = 0;
  for (int w = 0; w <= m; ++w) {
    if (dp[n][w] >= res) {
      res = dp[n][w];
      cur = w;
    }
  }
  std::vector<int> ans;
  int i = n;
  while (cur > 0) {
    if (dp[i - 1][cur] != dp[i][cur]) {
      ans.push_back(i);
      cur -= a[i];
    }
    --i;
  }
  reverse(ans.begin(), ans.end());
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
