#include <iostream>
#include <vector>

const long long cINF = 1e16 + 7;

struct HeapMn {
  std::vector<long long> vals;
  std::vector<int> id;
  std::vector<int> rev_id;
  int sz = 0;

  void Clear() {
    sz = 0;
    vals.clear();
    id.clear();
  }

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

  void Insert(long long x, int i) {
    ++sz;
    id.push_back(i);
    rev_id.push_back(sz - 1);
    vals.push_back(x);
    Sup(sz - 1);
  }

  std::pair<long long, int> Extract() {
    long long ans1 = vals[0];
    int ans2 = id[0];
    Change(0, sz - 1);
    --sz;
    vals.pop_back();
    id.pop_back();
    Sdown(0);
    return {ans1, ans2};
  }

  long long Mn() { return vals[0]; }

  void DelKey(int x) {
    vals[rev_id[x]] = -cINF;
    Sup(rev_id[x]);
    Extract();
  }
};

struct HeapMx {
  std::vector<long long> vals;
  std::vector<int> id;
  std::vector<int> rev_id;
  int sz = 0;

  void Clear() {
    sz = 0;
    vals.clear();
    id.clear();
  }

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
      if (rgh < sz && vals[rgh] > vals[lft]) {
        cur = rgh;
      }
      if (vals[i] < vals[cur]) {
        Change(i, cur);
        i = cur;
      } else {
        break;
      }
    }
  }

  void Sup(int i) {
    while (i != 0 && vals[i] > vals[(i - 1) / 2]) {
      Change(i, (i - 1) / 2);
      i = (i - 1) / 2;
    }
  }

  void Insert(long long x, int i) {
    ++sz;
    id.push_back(i);
    rev_id.push_back(sz - 1);
    vals.push_back(x);
    Sup(sz - 1);
  }

  std::pair<long long, int> Extract() {
    long long ans1 = vals[0];
    int ans2 = id[0];
    Change(0, sz - 1);
    --sz;
    vals.pop_back();
    id.pop_back();
    Sdown(0);
    return {ans1, ans2};
  }

  long long Mx() { return vals[0]; }

  void DelKey(int x) {
    vals[rev_id[x]] = cINF;
    Sup(rev_id[x]);
    Extract();
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
  int tmr = 0;
  HeapMn h_mn;
  HeapMx h_mx;
  for (int q1 = 0; q1 < q; ++q1) {
    int t;
    std::cin >> t;
    if (t == 0) {
      int x;
      std::cin >> x;
      h_mn.Insert(x, tmr);
      h_mx.Insert(x, tmr);
      ++tmr;
      std::cout << "ok\n";
    } else if (t == 1) {
      if (h_mn.sz == 0) {
        std::cout << "error\n";
      } else {
        auto [x, y] = h_mn.Extract();
        h_mx.DelKey(y);
        std::cout << x << '\n';
      }
    } else if (t == 2) {
      if (h_mn.sz == 0) {
        std::cout << "error\n";
      } else {
        std::cout << h_mn.Mn() << '\n';
      }
    } else if (t == 3) {
      if (h_mx.sz == 0) {
        std::cout << "error\n";
      } else {
        auto [x, y] = h_mx.Extract();
        h_mn.DelKey(y);
        std::cout << x << '\n';
      }
    } else if (t == 4) {
      if (h_mx.sz == 0) {
        std::cout << "error\n";
      } else {
        std::cout << h_mx.Mx() << '\n';
      }
    } else if (t == 5) {
      std::cout << h_mn.sz << '\n';
    } else {
      h_mn.Clear();
      h_mx.Clear();
      std::cout << "ok\n";
    }
  }
  return 0;
}
