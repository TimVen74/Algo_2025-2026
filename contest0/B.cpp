#include <cmath>
#include <iostream>
#include <vector>

const int cOut = 12;

int main() {
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::cout.precision(cOut);
  std::cout << std::fixed;
  int n;
  std::cin >> n;
  std::vector<long double> a(n + 1);
  std::vector<long double> pref(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    pref[i] = pref[i - 1] + log2(a[i]);
  }
  int q;
  std::cin >> q;
  for (int i = 1; i <= q; ++i) {
    int l;
    int r;
    std::cin >> l >> r;
    ++l;
    ++r;
    std::cout << pow(2, (pref[r] - pref[l - 1]) / (r - l + 1)) << '\n';
  }
  return 0;
}
