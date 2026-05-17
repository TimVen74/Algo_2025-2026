#include <deque>
#include <iostream>
#include <vector>

const int cN = 110;
const int cM = 1610;
const long long cINF = 1e18 + 7;

std::pair<int, int> edg[cM];
long long c[cM];
long long f[cM];
std::vector<std::pair<int, int>> g[cN];
std::pair<int, int> p[cN];
int n;
int m;
std::vector<int> min_cut;

long long Flow() {
  for (int i = 1; i <= n; ++i) {
    g[i].clear();
    p[i] = {-1, -1};
  }
  for (int i = 0; i < 4 * m; ++i) {
    if (c[i] - f[i] > 0) {
      g[edg[i].first].emplace_back(edg[i].second, i);
    }
  }

  std::deque<int> q;
  q.push_back(1);
  p[1] = {1, 0};
  while (!q.empty()) {
    int v = q.front();
    q.pop_front();
    for (auto [to, id] : g[v]) {
      if (p[to] == std::make_pair(-1, -1)) {
        p[to] = {v, id};
        q.push_back(to);
      }
    }
  }
  if (p[n] == std::make_pair(-1, -1)) {
    for (int i = 0; i < 4 * m; i += 4) {
      auto [v, u] = edg[i];
      if ((p[v] == std::make_pair(-1, -1)) !=
          (p[u] == std::make_pair(-1, -1))) {
        min_cut.push_back(i / 4 + 1);
      }
    }
    return 0;
  }
  int cur = n;
  long long mn = cINF;
  while (cur != 1) {
    int id = p[cur].second;
    mn = std::min(mn, c[id] - f[id]);
    cur = p[cur].first;
  }
  cur = n;
  while (cur != 1) {
    int id = p[cur].second;
    int rev_id = id ^ 1;
    f[id] += mn;
    f[rev_id] -= mn;
    cur = p[cur].first;
  }
  return mn;
}

void Solve() {
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int id = 4 * i;
    int rev_id = 4 * i + 1;
    int v;
    int u;
    std::cin >> v >> u >> c[id];
    edg[id] = {v, u};
    edg[rev_id] = {u, v};

    id = 4 * i + 2;
    rev_id = 4 * i + 3;
    c[id] = c[id - 2];
    edg[id] = {u, v};
    edg[rev_id] = {v, u};
  }
  long long ans = 0;
  while (true) {
    long long x = Flow();
    if (x == 0) {
      break;
    }
    ans += x;
  }

  std::cout << (int)min_cut.size() << ' ' << ans << '\n';
  for (int x : min_cut) {
    std::cout << x << ' ';
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
