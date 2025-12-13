#include <iostream>

const int cN = 1e6 + 10;

int n;
int q;
int x;
int a[cN];
int b[cN];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> b[i];
  }
  std::cin >> q;
  for (int i = 1; i <= q; ++i) {
    std::cin >> x;
    int l = 1;
    int r = n + 1;
    while (r - l > 1) {
      int m = (r + l) >> 1;
      if (a[m] + x >= b[m]) {
        r = m;
      } else {
        l = m;
      }
    }
    if (r == n + 1 || b[l] <= a[r] + x) {
      std::cout << l << '\n';
    } else {
      std::cout << r << '\n';
    }
  }
  return 0;
}
