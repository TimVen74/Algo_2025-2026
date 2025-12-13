#include <iostream>
#include <random>
#include <vector>

const int cMod = 1e7 + 4321;
const int cK1 = 123;
const int cK2 = 45;
std::mt19937 rnd(time(NULL));

void Srt(std::vector<int>& a) {
  if ((int)a.size() == 1) {
    return;
  }
  if ((int)a.size() == 2) {
    if (a[1] < a[0]) {
      std::swap(a[0], a[1]);
    }
    return;
  }
  std::vector<int> b;
  std::vector<int> c;
  for (int i = 0; i < (int)a.size() / 2; ++i) {
    b.push_back(a[i]);
  }
  for (int i = (int)a.size() / 2; i < (int)a.size(); ++i) {
    c.push_back(a[i]);
  }
  Srt(b);
  Srt(c);
  a.clear();
  int i = 0;
  int j = 0;
  while (i < (int)b.size() || j < (int)c.size()) {
    if (i != (int)b.size() && (j == (int)c.size() || b[i] <= c[j])) {
      a.push_back(b[i++]);
    } else {
      a.push_back(c[j++]);
    }
  }
}

int Stupidmedian(std::vector<int>& a) {
  Srt(a);
  return a[(int)a.size() / 2];
}

int Findkth(std::vector<int>& val, int k) {
  int mid = val[rnd() % (int)val.size()];

  std::vector<int> v1;
  std::vector<int> v2;
  int cnt = 0;
  for (int i = 0; i < (int)val.size(); ++i) {
    if (val[i] < mid) {
      v1.push_back(val[i]);
    } else if (val[i] == mid) {
      ++cnt;
    } else {
      v2.push_back(val[i]);
    }
  }
  if ((int)v1.size() >= k) {
    return Findkth(v1, k);
  }
  if ((int)v1.size() + cnt >= k) {
    return mid;
  }
  return Findkth(v2, k - (int)v1.size() - cnt);
}

int main() {
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int n;
  int k;
  std::cin >> n >> k;
  std::vector<int> a(n);
  std::cin >> a[0] >> a[1];
  for (int i = 2; i < n; ++i) {
    a[i] = (a[i - 1] * cK1 + a[i - 2] * cK2) % cMod;
  }
  std::cout << Findkth(a, k);
  return 0;
}
