#include <iostream>
#include <vector>

void MergeSort(std::vector<std::pair<int, int>>& a) {
  if ((int)a.size() == 1) {
    return;
  }
  std::vector<std::pair<int, int>> b;
  std::vector<std::pair<int, int>> c;
  for (int i = 0; i < (int)a.size() / 2; ++i) {
    b.push_back(a[i]);
  }
  for (int i = (int)a.size() / 2; i < (int)a.size(); ++i) {
    c.push_back(a[i]);
  }
  MergeSort(b);
  MergeSort(c);
  a.clear();
  int i = 0;
  int j = 0;
  while (i < (int)b.size() || j < (int)c.size()) {
    if (i != (int)b.size() && (j == (int)c.size() || b[i] < c[j])) {
      a.push_back(b[i++]);
    } else {
      a.push_back(c[j++]);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i].first >> a[i].second;
  }
  MergeSort(a);
  std::vector<std::pair<int, int>> ans;
  int l = a[0].first;
  int r = a[0].second;
  for (int i = 1; i < n; ++i) {
    if (a[i].first <= r) {
      r = std::max(r, a[i].second);
    } else {
      ans.push_back({l, r});
      l = a[i].first;
      r = a[i].second;
    }
  }
  ans.push_back({l, r});
  std::cout << (int)ans.size() << '\n';
  for (int i = 0; i < (int)ans.size(); ++i) {
    std::cout << ans[i].first << ' ' << ans[i].second << '\n';
  }
  return 0;
}
