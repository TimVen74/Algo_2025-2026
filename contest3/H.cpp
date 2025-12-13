#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 4e5 + 10;
const int cINF = 1e9 + 7;

std::pair<int, int> tree[cN * 4];
int d[cN * 4];
std::vector<int> szh;

void Push(int tind, int l, int r) {
  tree[tind].first += d[tind];
  if (r - l > 1) {
    d[tind * 2 + 1] += d[tind];
    d[tind * 2 + 2] += d[tind];
  }
  d[tind] = 0;
}

std::pair<int, int> Mrg(std::pair<int, int> p1, std::pair<int, int> p2) {
  std::pair<int, int> ans = p1;
  if (p2.first < ans.first) {
    ans = p2;
  } else if (p2.first == ans.first) {
    ans.second += p2.second;
  }
  return ans;
}

void Build(int tind, int l, int r) {
  if (r - l == 1) {
    tree[tind] = {0, szh[r] - szh[l]};
  } else {
    int m = (r + l) >> 1;
    Build(tind * 2 + 1, l, m);
    Build(tind * 2 + 2, m, r);
    tree[tind] = Mrg(tree[tind * 2 + 1], tree[tind * 2 + 2]);
  }
}

void Upd(int tind, int l, int r, int ql, int qr, int x) {
  Push(tind, l, r);
  if (ql >= r || l >= qr) {
    return;
  }
  if (ql <= l && r <= qr) {
    d[tind] += x;
    Push(tind, l, r);
    return;
  }
  int m = (r + l) >> 1;
  Upd(tind * 2 + 1, l, m, ql, qr, x);
  Upd(tind * 2 + 2, m, r, ql, qr, x);
  tree[tind] = Mrg(tree[tind * 2 + 1], tree[tind * 2 + 2]);
}

struct Zpr {
  int x;
  int y1;
  int y2;
  int t;

  Zpr(int a, int b, int c, int e) : x(a), y1(b), y2(c), t(e) {}

  bool operator<(const Zpr& z) const { return x < z.x; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int n;
  std::cin >> n;
  std::vector<Zpr> ev;
  for (int i = 1; i <= n; ++i) {
    int x1;
    int y1;
    int x2;
    int y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2 || y1 == y2) {
      continue;
    }
    szh.push_back(y1);
    szh.push_back(y2);
    ev.push_back(Zpr(x1, y1, y2, 1));
    ev.push_back(Zpr(x2, y1, y2, -1));
  }
  std::sort(szh.begin(), szh.end());
  szh.resize(unique(szh.begin(), szh.end()) - szh.begin());
  int sz = (int)szh.size();
  szh.push_back(cINF);
  Build(0, 0, sz);
  std::sort(ev.begin(), ev.end());
  long long ans = 0;
  int px = -1;
  for (Zpr z : ev) {
    z.y1 = (int)(lower_bound(szh.begin(), szh.end(), z.y1) - szh.begin());
    z.y2 = (int)(lower_bound(szh.begin(), szh.end(), z.y2) - szh.begin());
    ans += 1LL * (z.x - px) * (cINF - szh[0] - tree[0].second);
    px = z.x;
    Upd(0, 0, sz, z.y1, z.y2, z.t);
  }
  std::cout << ans;
  return 0;
}
