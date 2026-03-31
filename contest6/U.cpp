#include <algorithm>
#include <iostream>

const int cN = 25;

int n;
long long g[cN * 2];
int dp[1 << cN];
long long msk_all[1 << cN];

void Solve() {
  std::cin >> n;
  n = std::max(0, n);
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    std::reverse(s.begin(), s.end());
    for (char x : s) {
      g[i] *= 2;
      g[i] += (x - '0');
    }
    g[i] |= (1LL << i);
  }

  int sz1 = std::max(0, n / 2);
  int sz2 = std::max(0, n - sz1);
  int fh = (1 << sz1) - 1;

  msk_all[0] = (1LL << n) - 1;
  for (int mask = 0; mask < (1 << sz1); ++mask) {
    if (mask != 0) {
      int i = __builtin_ctz(mask);
      msk_all[mask] = msk_all[mask ^ (1 << i)] & g[i];
    }
    if ((msk_all[mask] & mask) == mask) {
      dp[mask] = 1;
    }
  }
  for (int i = 0; i < sz1; ++i) {
    for (int mask = 0; mask < (1 << sz1); ++mask) {
      if ((mask & (1 << i)) != 0) {
        dp[mask] += dp[mask ^ (1 << i)];
      }
    }
  }

  long long ans = 0;
  for (int mask = 0; mask < (1 << sz2); ++mask) {
    if (mask != 0) {
      int i = __builtin_ctz(mask);
      msk_all[mask] = msk_all[mask ^ (1 << i)] & g[i + sz1];
    }
    if ((msk_all[mask] & ((1LL * mask) << sz1)) == ((1LL * mask) << sz1)) {
      ans += dp[msk_all[mask] & fh];
    }
  }

  std::cout << ans << '\n';
}

signed main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  auto start = clock();
#endif
  Solve();
#ifdef LOCAL
  auto end = clock();
  std::cerr << "TIME: " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
#endif
}
