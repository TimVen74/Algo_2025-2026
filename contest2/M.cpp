#include <iostream>

const int cN = 1e6 + 10;
const int cK = 1e3 + 10;
const int cDEG = 21;
const int cINF = 1e9 + 7;

int rev_ind[cN];
int by_deg[cDEG];
int tmr = 0;

struct Node {
  int val = 0;
  int ind = 0;
  int parent = -1;
  int child = -1;
  int sibling = -1;
  int deg = 0;

  Node() {
    val = ind = deg = 0;
    parent = child = sibling = -1;
  }

  Node(int x, int i, int td) {
    val = x;
    ind = i;
    rev_ind[i] = td;
    parent = child = sibling = -1;
    deg = 1;
  }
};

Node data[cN];

void Change(int i, int j) {
  std::swap(data[i].val, data[j].val);
  std::swap(data[i].ind, data[j].ind);
  rev_ind[data[i].ind] = i;
  rev_ind[data[j].ind] = j;
}

void Up(int i) {
  while (i != -1 && data[i].parent != -1) {
    int j = data[i].parent;
    if (data[i].val < data[j].val ||
        (data[i].val == data[j].val && data[i].ind < data[j].ind)) {
      Change(i, j);
      i = j;
    } else {
      break;
    }
  }
}

void Down(int i) {
  while (i != -1 && data[i].child != -1) {
    int j = data[i].child;
    int x = data[j].sibling;

    while (x != -1) {
      if (data[x].val < data[j].val ||
          (data[x].val == data[j].val && data[x].ind < data[j].ind)) {
        j = x;
      }
      x = data[x].sibling;
    }

    if (data[i].val > data[j].val ||
        (data[i].val == data[j].val && data[i].ind > data[j].ind)) {
      Change(i, j);
      i = j;
    } else {
      break;
    }
  }
}

void SetVal(int i, int x) {
  int idx = rev_ind[i];
  int old_val = data[idx].val;
  data[idx].val = x;

  if (x < old_val) {
    Up(idx);
  } else if (x > old_val) {
    Down(idx);
  }
}

struct BinHeap {
  int head = -1;

  int Min() const {
    int min_val = cINF;
    int x = head;
    while (x != -1) {
      min_val = std::min(min_val, data[x].val);
      x = data[x].sibling;
    }
    return min_val;
  }

  void Recalc() {
    std::fill(by_deg, by_deg + cDEG, -1);
    int cur = head;

    while (cur != -1) {
      int next = data[cur].sibling;
      data[cur].sibling = -1;

      int deg = data[cur].deg;
      while (by_deg[deg] != -1) {
        int ot = by_deg[deg];
        by_deg[deg] = -1;

        if (data[cur].val > data[ot].val ||
            (data[cur].val == data[ot].val && data[cur].ind > data[ot].ind)) {
          std::swap(cur, ot);
        }

        data[ot].sibling = data[cur].child;
        data[ot].parent = cur;
        data[cur].child = ot;
        data[cur].deg++;
        deg++;
      }
      by_deg[deg] = cur;
      cur = next;
    }

    head = -1;
    for (int i = cDEG - 1; i >= 0; --i) {
      if (by_deg[i] != -1) {
        data[by_deg[i]].sibling = head;
        head = by_deg[i];
      }
    }
  }

  void Insert(int x, int i) {
    data[tmr] = Node(x, i, tmr);
    data[tmr].sibling = head;
    head = tmr;
    ++tmr;
    Recalc();
  }
};

BinHeap Merge(BinHeap h1, BinHeap h2) {
  if (h1.head == -1) {
    return h2;
  }
  if (h2.head == -1) {
    return h1;
  }
  BinHeap ans;
  int x1 = h1.head;
  int x2 = h2.head;
  if (data[x1].deg < data[x2].deg) {
    ans.head = x1;
    x1 = data[x1].sibling;
  } else {
    ans.head = x2;
    x2 = data[x2].sibling;
  }
  int x = ans.head;
  while (x1 != -1 && x2 != -1) {
    if (data[x1].deg < data[x2].deg) {
      data[x].sibling = x1;
      x = x1;
      x1 = data[x1].sibling;
    } else {
      data[x].sibling = x2;
      x = x2;
      x2 = data[x2].sibling;
    }
  }
  while (x1 != -1) {
    data[x].sibling = x1;
    x = x1;
    x1 = data[x1].sibling;
  }
  while (x2 != -1) {
    data[x].sibling = x2;
    x = x2;
    x2 = data[x2].sibling;
  }
  ans.Recalc();
  return ans;
}

void DeleteMin(BinHeap& a) {
  int mnp = -1;
  int mn_i = a.head;
  int prev = -1;
  int current = a.head;

  while (current != -1) {
    if (data[current].val < data[mn_i].val ||
        (data[current].val == data[mn_i].val &&
         data[current].ind < data[mn_i].ind)) {
      mn_i = current;
      mnp = prev;
    }
    prev = current;
    current = data[current].sibling;
  }

  if (mnp == -1) {
    a.head = data[mn_i].sibling;
  } else {
    data[mnp].sibling = data[mn_i].sibling;
  }

  int child_head = -1;
  int child = data[mn_i].child;
  while (child != -1) {
    int next_child = data[child].sibling;
    data[child].sibling = child_head;
    data[child].parent = -1;
    child_head = child;
    child = next_child;
  }

  BinHeap child_heap;
  child_heap.head = child_head;
  BinHeap main_heap;
  main_heap.head = a.head;
  BinHeap new_heap = Merge(main_heap, child_heap);
  a.head = new_heap.head;
  rev_ind[data[mn_i].ind] = -1;
}

BinHeap heaps[cK];

signed main() {
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::fill(rev_ind, rev_ind + cN, -1);
  int n;
  int q;
  std::cin >> n >> q;
  int a;
  int b;
  int i;
  int x;
  int id = 1;
  for (int q1 = 0; q1 < q; ++q1) {
    int t;
    std::cin >> t;
    if (t == 0) {
      std::cin >> a >> x;
      heaps[a].Insert(x, id++);
    } else if (t == 1) {
      std::cin >> a >> b;
      heaps[b] = Merge(heaps[a], heaps[b]);
      heaps[a].head = -1;
    } else if (t == 2) {
      std::cin >> i;
      SetVal(i, cINF);
    } else if (t == 3) {
      std::cin >> i >> x;
      SetVal(i, x);
    } else if (t == 4) {
      std::cin >> a;
      std::cout << heaps[a].Min() << '\n';
    } else if (t == 5) {
      std::cin >> a;
      DeleteMin(heaps[a]);
    }
  }
  return 0;
}
