#include <deque>
#include <iostream>
#include <vector>

const int cN = 510;
const int cM = 2e4 + 10;
const long long cINF = 1e18 + 7;
const int cLOG = 30;

int state[cN];
long long d[cN];
std::vector<std::pair<int, int>> g[cN];
int ptr[cN];
long long c[cM];
long long f[cM];
int n;
int m;
int s;
int t;
int tmr = 0;
long long delta;

bool Bfs() {
  std::fill(d + 1, d + n + 1, cINF);
  d[s] = 0;
  std::deque<int> q;
  q.push_back(s);
  while (!q.empty()) {
    int v = q.front();
    q.pop_front();
    for (auto [to, id] : g[v]) {
      if (c[id] - f[id] >= delta) {
        if (d[to] > d[v] + 1) {
          d[to] = d[v] + 1;
          q.push_back(to);
        }
      }
    }
  }
  return d[t] != cINF;
}

long long FindFlow(int v, long long flow) {
  if (v == t) {
    return flow;
  }
  while (ptr[v] < (int)g[v].size()) {
    auto [to, id] = g[v][ptr[v]];
    if (c[id] - f[id] >= delta && d[v] + 1 == d[to]) {
      long long x = FindFlow(to, std::min(flow, c[id] - f[id]));
      if (x == 0) {
        ++ptr[v];
      } else {
        f[id] += x;
        f[id ^ 1] -= x;
        return x;
      }
    } else {
      ++ptr[v];
    }
  }
  return 0;
}

long long MaxFlow() {
  long long ans = 0;
  delta = (1 << cLOG);
  while (delta >= 1) {
    while (Bfs()) {
      std::fill(ptr + 1, ptr + n + 1, 0);
      while (true) {
        long long x = FindFlow(s, cINF);
        if (x == 0) {
          break;
        }
        ans += x;
        if (ans >= cINF) {
          return cINF;
        }
      }
    }
    delta >>= 1;
  }
  return ans;
}

void AddEdge(int v, int u, long long cap) {
  int id = tmr;
  int rev_id = tmr + 1;
  c[id] = cap;
  g[v].emplace_back(u, id);
  g[u].emplace_back(v, rev_id);
  tmr += 2;
}

void Solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int v;
    int u;
    int w;
    std::cin >> v >> u >> w;
    AddEdge(v, u, w);
  }
  s = 1;
  t = n;
  std::cout << MaxFlow() << '\n';
  for (int i = 0; i < 2 * m; i += 2) {
    std::cout << f[i] << '\n';
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
