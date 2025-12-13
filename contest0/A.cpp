#include <iostream>

const int cN = 1e5 + 10;
const int cInf = 1e9 + 7;

int a[cN];
int pref[cN];
int suf[cN];

int main() {
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  pref[0] = cInf, suf[n + 1] = cInf;
  for (int i = 1; i <= n; ++i) {
    pref[i] = std::min(pref[i - 1], a[i]);
  }
  for (int i = n; i >= 1; --i) {
    suf[i] = std::min(suf[i + 1], a[i]);
  }
  int q;
  std::cin >> q;
  for (int i = 1; i <= q; ++i) {
    int l;
    int r;
    std::cin >> l >> r;
    std::cout << std::min(pref[l], suf[r]) << '\n';
  }
  return 0;
}
