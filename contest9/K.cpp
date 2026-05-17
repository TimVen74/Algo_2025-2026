#include <iostream>
#include <set>
#include <vector>

const int cN = 110;
const int cM = 2010;
const long long cINF = 1e18 + 7;

std::vector<std::pair<int, int>> g[cN];
std::pair<int, int> pred[cN];
long long potential[cN];
long long cost[cM];
long long c[cM];
long long d[cM];
int n;
int m;
int s;
int t;
int tmr = 0;

void AddEdge(int v, int u, long long cap, long long cst) {
  int id = tmr;
  int rev_id = tmr + 1;
  g[v].emplace_back(u, id);
  g[u].emplace_back(v, rev_id);
  c[id] = cap;
  cost[id] = cst;
  c[rev_id] = 0;
  cost[rev_id] = -cst;
  tmr += 2;
}

bool Dijkstra() {
  std::fill(d, d + n + 1, cINF);
  std::fill(pred, pred + n + 1, std::make_pair(-1, -1));
  std::set<std::pair<long long, int>> q;
  d[s] = 0;
  q.insert({0, s});
  while (!q.empty()) {
    auto [dv, v] = *q.begin();
    q.erase(q.begin());
    if (dv != d[v]) {
      continue;
    }
    for (auto [to, id] : g[v]) {
      if (c[id] <= 0) {
        continue;
      }
      if (d[to] > d[v] + cost[id] + potential[v] - potential[to]) {
        d[to] = d[v] + cost[id] + potential[v] - potential[to];
        pred[to] = {v, id};
        q.insert({d[to], to});
      }
    }
  }
  return d[t] != cINF;
}

std::pair<long long, long long> MinCostMaxFlow() {
  long long ans_flow = 0;
  long long ans_cost = 0;
  std::fill(potential, potential + n + 1, 0);
  while (Dijkstra()) {
    for (int i = 1; i <= n; ++i) {
      if (d[i] < cINF) {
        potential[i] += d[i];
      }
    }
    long long mn = cINF;
    for (int v = t; v != s; v = pred[v].first) {
      mn = std::min(mn, c[pred[v].second]);
    }
    for (int v = t; v != s; v = pred[v].first) {
      int id = pred[v].second;
      c[id] -= mn;
      c[id ^ 1] += mn;
      ans_cost += mn * cost[id];
    }
    ans_flow += mn;
  }
  return {ans_flow, ans_cost};
}

void Solve() {
  std::cin >> n >> m;

  for (int i = 1; i <= m; ++i) {
    int v;
    int u;
    long long cap;
    long long w;
    std::cin >> v >> u >> cap >> w;
    AddEdge(v, u, cap, w);
  }
  s = 1;
  t = n;
  auto [ans_flow, ans_cost] = MinCostMaxFlow();
  std::cout << ans_cost << '\n';
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
