#include <algorithm>
#include <iostream>
#include <vector>

const int cINF = 2147483647;

std::vector<int> Nvp(std::vector<int>& a) {
  int n = (int)a.size();
  std::vector<int> dst(n + 1, cINF);
  std::vector<int> pos(n + 1);
  std::vector<int> prev(n + 1);
  int length = 0;
  pos[0] = -1;
  dst[0] = -cINF;
  for (int i = 0; i < n; ++i) {
    int j = (int)(upper_bound(dst.begin(), dst.end(), a[i]) - dst.begin());
    if (dst[j - 1] < a[i] && a[i] < dst[j]) {
      dst[j] = a[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      length = std::max(length, j);
    }
  }
  std::vector<int> ans;
  int dsu = pos[length];
  while (dsu != -1) {
    ans.push_back(dsu);
    dsu = prev[dsu];
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

void Solve() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    a[i] *= -1;
  }
  std::vector<int> ans = Nvp(a);
  std::cout << (int)ans.size() << '\n';
  for (int x : ans) {
    std::cout << x + 1 << ' ';
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
