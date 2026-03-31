#include <deque>
#include <iostream>
#include <vector>

const int cN = 1e6 + 10;
const int cINF = 1e9 + 7;

int n;
std::vector<std::pair<int, int>> g[cN];
int lvl[cN];
int cnt[2];
int mn[2];
long long sm[2];
int val[cN];
bool usd[cN];

bool Check(int x) {
  std::vector<bool> was(n + 1, false);
  for (int i = 1; i <= n; ++i) {
    int cur = val[i] + (lvl[i] == 0 ? x : -x);
    if (cur > n || cur < 1 || was[cur]) {
      return false;
    }
    was[cur] = true;
  }
  for (int v = 1; v <= n; ++v) {
    for (auto [to, s] : g[v]) {
      int cur1 = val[v] + (lvl[v] == 0 ? x : -x);
      int cur2 = val[to] + (lvl[to] == 0 ? x : -x);
      if (cur1 + cur2 != s) {
        return false;
      }
    }
  }
  return true;
}

void Solve() {
  int m;
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int v;
    int u;
    int s;
    std::cin >> v >> u >> s;
    g[v].push_back({u, s});
    g[u].push_back({v, s});
  }
  mn[0] = mn[1] = cINF;
  std::deque<int> q;
  q.push_back(1);
  usd[1] = true;
  while (!q.empty()) {
    int v = q.front();
    q.pop_front();
    sm[lvl[v]] += val[v];
    cnt[lvl[v]]++;
    mn[lvl[v]] = std::min(mn[lvl[v]], val[v]);
    for (auto [to, s] : g[v]) {
      if (!usd[to]) {
        usd[to] = true;
        lvl[to] = lvl[v] ^ 1;
        val[to] = s - val[v];
        q.push_back(to);
      }
    }
  }

  long long sm_all = 1LL * n * (n + 1) / 2;
  int ans = 0;

  if (cnt[1] == cnt[0]) {
    if (Check(1 - mn[0])) {
      ans = 1 - mn[0];
    } else {
      ans = mn[1] - 1;
    }
  } else {
    ans = (sm_all - sm[0] - sm[1]) / (cnt[0] - cnt[1]);
  }
  for (int i = 1; i <= n; ++i) {
    int cur = val[i] + ans;
    if (lvl[i] == 1) {
      cur -= 2 * ans;
    }
    std::cout << cur << ' ';
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
