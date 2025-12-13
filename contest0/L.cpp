#include <iostream>
#include <string>

const int cN = 2e5 + 10;

int n;
int m;
std::string s;
std::string t;
int a[cN];
int id[cN];

bool Check(int tm) {
  int j = 1;
  for (int i = 1; i <= n; ++i) {
    if (j == m + 1) {
      break;
    }
    if (id[i] > tm && s[i] == t[j]) {
      ++j;
    }
  }
  return j == m + 1;
}

int main() {
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::cin >> s >> t;
  n = (int)s.size();
  m = (int)t.size();
  s = ' ' + s;
  t = ' ' + t;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    id[a[i]] = i;
  }

  int l = -1;
  int r = n;
  while (r - l > 1) {
    int mid = (r + l) / 2;
    if (Check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  std::cout << l << '\n';
  return 0;
}
