#include <iostream>
#include <string>
#include <vector>

struct Heap {
  std::vector<long long> vals;
  std::vector<int> id;
  std::vector<int> rev_id;
  int sz = 0;
  int ids = 0;

  void Change(int i, int j) {
    std::swap(id[i], id[j]);
    std::swap(vals[i], vals[j]);
    rev_id[id[i]] = i;
    rev_id[id[j]] = j;
  }

  void Sdown(int i) {
    while (2 * i + 1 < sz) {
      int lft = 2 * i + 1;
      int rgh = 2 * i + 2;
      int cur = lft;
      if (rgh < sz && vals[rgh] < vals[lft]) {
        cur = rgh;
      }
      if (vals[i] > vals[cur]) {
        Change(i, cur);
        i = cur;
      } else {
        break;
      }
    }
  }

  void Sup(int i) {
    while (i != 0 && vals[i] < vals[(i - 1) / 2]) {
      Change(i, (i - 1) / 2);
      i = (i - 1) / 2;
    }
  }

  void Insert(long long x) {
    ++sz;
    ++ids;
    id.push_back(ids - 1);
    rev_id.push_back(sz - 1);
    vals.push_back(x);
    Sup(sz - 1);
  }

  void Extract() {
    Change(0, sz - 1);
    --sz;
    vals.pop_back();
    id.pop_back();
    Sdown(0);
  }

  long long Mn() { return vals[0]; }

  void DecKey(int x, int delt) {
    vals[rev_id[x]] -= delt;
    Sup(rev_id[x]);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int q;
  std::cin >> q;
  std::vector<int> cnt(q + 1, 0);
  Heap h;
  for (int q1 = 1; q1 <= q; ++q1) {
    std::string t;
    std::cin >> t;
    cnt[q1] = cnt[q1 - 1];
    if (t == "insert") {
      int x;
      std::cin >> x;
      h.Insert(x);
      ++cnt[q1];
    } else if (t == "getMin") {
      std::cout << h.Mn() << '\n';
    } else if (t == "extractMin") {
      h.Extract();
    } else {
      int i;
      int delt;
      std::cin >> i >> delt;
      h.DecKey(cnt[i - 1], delt);
    }
  }
  return 0;
}
