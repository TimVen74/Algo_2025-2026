#include <iostream>

const int cN = 1010;
const int cK = 21;
const int cINF = 1e9 + 7;

std::string u;
std::string v;
int k;
int dp[cK][cN][cN];

void Upd(int& x, int y) { x = std::min(x, y); }

void Solve() {
  std::cin >> u >> v >> k;
  int n = (int)u.size();
  int m = (int)v.size();
  u = ' ' + u;
  v = ' ' + v;
  for (int x = 0; x <= k; ++x) {
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= m; ++j) {
        dp[x][i][j] = cINF;
      }
    }
    dp[x][0][0] = 0;
  }
  for (int x = 0; x <= k; ++x) {
    for (int i = 1; i <= std::min(n, x); ++i) {
      dp[x][i][0] = 0;
    }
    for (int j = 1; j <= std::min(m, x); ++j) {
      dp[x][0][j] = 0;
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (x > 0) {
          Upd(dp[x][i][j], dp[x - 1][i - 1][j]);
          Upd(dp[x][i][j], dp[x - 1][i][j - 1]);
          Upd(dp[x][i][j], dp[x - 1][i - 1][j - 1]);
        }
        Upd(dp[x][i][j], dp[x][i - 1][j - 1] + static_cast<int>(u[i] != v[j]));
      }
    }
  }
  int ans = cINF;
  for (int i = 0; i <= k; ++i) {
    ans = std::min(ans, dp[i][n][m]);
  }
  std::cout << (ans == cINF ? -1 : ans) << '\n';
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
