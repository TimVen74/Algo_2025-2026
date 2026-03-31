#include <iostream>
#include <vector>

void Solve() {
  int n;
  std::cin >> n;
  if (n == 1) {
    std::cout << 1;
    return;
  }
  long long ans = 0;
  for (int cnt = 1; cnt * (cnt + 1) / 2 <= n; ++cnt) {
    std::vector<std::vector<long long>> dp(cnt,
                                           std::vector<long long>(n + 1, 0));
    dp[0][0] = 1;
    for (int mn = 2; cnt * mn + cnt * (cnt - 1) / 2 <= n; ++mn) {
      int m = n - cnt * mn;
      for (int sm = n; sm >= mn - 1; --sm) {
        for (int c = 1; c < cnt; ++c) {
          dp[c][sm] += dp[c - 1][sm - (mn - 1)];
        }
      }
      ans += dp[cnt - 1][m];
    }
  }
  std::cout << ans << '\n';
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
