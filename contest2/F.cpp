#include <algorithm>
#include <deque>
#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int ttt;
  std::cin >> ttt;
  std::deque<int> q;
  std::deque<int> q_min;
  for (int j = 0; j < ttt; ++j) {
    std::string t;
    std::cin >> t;
    if (t == "enqueue") {
      int x;
      std::cin >> x;
      q.push_back(x);
      while (!q_min.empty() && x < q_min.back()) {
        q_min.pop_back();
      }
      q_min.push_back(x);
      std::cout << "ok\n";
    } else if (t == "dequeue") {
      if (q.empty()) {
        std::cout << "error\n";
      } else {
        int x = q.front();
        q.pop_front();
        if (x == q_min.front()) {
          q_min.pop_front();
        }
        std::cout << x << '\n';
      }
    } else if (t == "front") {
      if (q.empty()) {
        std::cout << "error\n";
      } else {
        std::cout << q.front() << '\n';
      }
    } else if (t == "size") {
      std::cout << q.size() << '\n';
    } else if (t == "clear") {
      q.clear();
      q_min.clear();
      std::cout << "ok\n";
    } else {
      if (q_min.empty()) {
        std::cout << "error\n";
      } else {
        std::cout << q_min.front() << '\n';
      }
    }
  }
  return 0;
}
