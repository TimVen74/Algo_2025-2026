#include <iostream>
#include <vector>

const int cN = 256;
const int cByte = 8;

void LsdSort(std::vector<unsigned long long>& a) {
  unsigned long long mask = (1 << cByte) - 1;
  int cnt[cN];
  std::vector<unsigned long long> b(a.size());
  for (int byte = 0; byte < cByte; ++byte) {
    for (int i = 0; i < cN; ++i) {
      cnt[i] = 0;
    }
    for (int i = 0; i < (int)a.size(); ++i) {
      ++cnt[(a[i] >> (byte * cByte)) & mask];
    }
    int tmp = 0;
    for (int i = 0; i < cN; ++i) {
      int cur = cnt[i];
      cnt[i] = tmp;
      tmp += cur;
    }
    for (int i = 0; i < (int)a.size(); ++i) {
      b[cnt[(a[i] >> (byte * cByte)) & mask]++] = a[i];
    }
    a.swap(b);
  }
}

int main() {
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int n;
  std::cin >> n;
  std::vector<unsigned long long> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  LsdSort(a);
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << ' ';
  }
  return 0;
}
