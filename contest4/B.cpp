#include <iostream>

const int cN = 1e6 + 10;
const int cINF = 1e9 + 7;

struct Node {
  int key;
  int lft;
  int rgh;
  int par;
  int sz;

  Node(int x = 0) : key(x), lft(-1), rgh(-1), par(-1), sz(1) {}
};

Node data[cN];
int root = -1;
int tmr = 0;

int Sz(int x) {
  if (x == -1) {
    return 0;
  }
  return data[x].sz;
}

void Pull(int x) {
  if (x == -1) {
    return;
  }
  data[x].sz = Sz(data[x].lft) + Sz(data[x].rgh) + 1;
}

void Rotate(int x) {
  int p = data[x].par;
  if (p == -1) {
    return;
  }
  int ded = data[p].par;
  if (data[p].lft == x) {
    int b = data[x].rgh;
    data[x].rgh = p;
    data[p].lft = b;
    if (b != -1) {
      data[b].par = p;
    }
  } else {
    int b = data[x].lft;
    data[x].lft = p;
    data[p].rgh = b;
    if (b != -1) {
      data[b].par = p;
    }
  }
  data[x].par = ded;
  data[p].par = x;
  if (ded != -1) {
    if (data[ded].lft == p) {
      data[ded].lft = x;
    } else {
      data[ded].rgh = x;
    }
  } else {
    root = x;
  }
  Pull(p);
  Pull(x);
  if (ded != -1) {
    Pull(ded);
  }
}

void Splay(int x) {
  while (data[x].par != -1) {
    int p = data[x].par;
    int ded = data[p].par;
    if (ded == -1) {
      Rotate(x);
    } else if ((data[p].lft == x && data[ded].lft == p) ||
               (data[p].rgh == x && data[ded].rgh == p)) {
      Rotate(p);
      Rotate(x);
    } else {
      Rotate(x);
      Rotate(x);
    }
  }
}

int Find(int key) {
  int cur = root;
  int lst = -1;
  while (cur != -1) {
    lst = cur;
    if (key < data[cur].key) {
      cur = data[cur].lft;
    } else if (key > data[cur].key) {
      cur = data[cur].rgh;
    } else {
      return cur;
    }
  }
  return lst;
}

std::pair<int, int> Split(int key) {
  if (root == -1) {
    return {-1, -1};
  }
  int cur = Find(key);
  Splay(cur);
  if (data[cur].key < key) {
    int r = data[cur].rgh;
    if (r != -1) {
      data[r].par = -1;
    }
    data[cur].rgh = -1;
    Pull(cur);
    return {cur, r};
  }
  int l = data[cur].lft;
  if (l != -1) {
    data[l].par = -1;
  }
  data[cur].lft = -1;
  Pull(cur);
  return {l, cur};
}

int Merge(int r1, int r2) {
  if (r1 == -1) {
    return r2;
  }
  if (r2 == -1) {
    return r1;
  }
  int cur = r1;
  while (data[cur].rgh != -1) {
    cur = data[cur].rgh;
  }
  Splay(cur);
  data[cur].rgh = r2;
  data[r2].par = cur;
  Pull(cur);
  return cur;
}

int Kth(int k) {
  int x = root;
  if (x == -1 || k < 0 || k >= data[x].sz) {
    return -1;
  }

  while (x != -1) {
    if (k < Sz(data[x].lft)) {
      x = data[x].lft;
    } else if (k == Sz(data[x].lft)) {
      Splay(x);
      return x;
    } else {
      k -= Sz(data[x].lft) + 1;
      x = data[x].rgh;
    }
  }
  return -1;
}

bool Exists(int key) {
  if (root == -1) {
    return false;
  }

  int node = Find(key);
  Splay(node);

  return data[node].key == key;
}

void Insert(int key) {
  if (Exists(key)) {
    return;
  }
  auto [p1, p2] = Split(key);
  data[tmr] = Node(key);
  int nw = tmr++;
  data[nw].lft = p1;
  data[nw].rgh = p2;

  if (p1 != -1) {
    data[p1].par = nw;
  }
  if (p2 != -1) {
    data[p2].par = nw;
  }
  Pull(nw);
  root = nw;
}

void Delete(int key) {
  if (!Exists(key)) {
    return;
  }
  int p1 = data[root].lft;
  int p2 = data[root].rgh;
  if (p1 != -1) {
    data[p1].par = -1;
  }
  if (p2 != -1) {
    data[p2].par = -1;
  }
  root = Merge(p1, p2);
}

int Next(int key) {
  if (root == -1) {
    return cINF;
  }
  int cur = Find(key);
  Splay(cur);
  if (data[cur].key > key) {
    return data[cur].key;
  }
  if (data[cur].rgh == -1) {
    return cINF;
  }
  cur = data[cur].rgh;
  while (data[cur].lft != -1) {
    cur = data[cur].lft;
  }
  return data[cur].key;
}

int Prev(int key) {
  if (root == -1) {
    return cINF;
  }
  int cur = Find(key);
  Splay(cur);
  if (data[cur].key < key) {
    return data[cur].key;
  }
  if (data[cur].lft == -1) {
    return cINF;
  }
  cur = data[cur].lft;
  while (data[cur].rgh != -1) {
    cur = data[cur].rgh;
  }
  return data[cur].key;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#ifdef LOCAL
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::string type;
  int x;
  while (std::cin >> type >> x) {
    if (type == "insert") {
      Insert(x);
    } else if (type == "delete") {
      Delete(x);
    } else if (type == "exists") {
      if (Exists(x)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (type == "next") {
      int ans = Next(x);
      if (ans == cINF) {
        std::cout << "none\n";
      } else {
        std::cout << ans << '\n';
      }
    } else if (type == "prev") {
      int ans = Prev(x);
      if (ans == cINF) {
        std::cout << "none\n";
      } else {
        std::cout << ans << '\n';
      }
    } else {
      int ans = Kth(x);
      if (ans == -1) {
        std::cout << "none\n";
      } else {
        std::cout << data[ans].key << '\n';
      }
    }
  }
  return 0;
}
