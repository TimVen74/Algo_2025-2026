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
  int q;
  std::cin >> q;
  std::deque<int> head;
  std::deque<int> tail;
  for (int j = 0; j < q; ++j) {
    char t;
    std::cin >> t;
    if (t == '+') {
      int x;
      std::cin >> x;
      tail.push_back(x);
      while (tail.size() > head.size()) {
        head.push_back(tail.front());
        tail.pop_front();
      }
    } else if (t == '*') {
      int x;
      std::cin >> x;
      head.push_back(x);
      while (head.size() > tail.size() + 1) {
        tail.push_front(head.back());
        head.pop_back();
      }
    } else {
      std::cout << head.front() << '\n';
      head.pop_front();
      while (tail.size() > head.size()) {
        head.push_back(tail.front());
        tail.pop_front();
      }
    }
  }
  return 0;
}
