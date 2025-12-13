#include <iostream>

const int cN = 3e5 + 10;
const int cMOD = 1e9;

struct Node {
  int key;
  int h;
  int lft;
  int rgh;

  Node() : key(0), h(0), lft(-1), rgh(-1) {}

  Node(int k) : key(k), h(1), lft(-1), rgh(-1) {}
};

Node dat[cN];
int tmr = 1;

struct AVLTree {
  int root;

  static int H(int node) {
    if (node == -1) {
      return 0;
    }
    return dat[node].h;
  }

  static void Pull(int node) {
    if (node != -1) {
      dat[node].h = 1 + std::max(H(dat[node].lft), H(dat[node].rgh));
    }
  }

  static int BalDiff(int node) {
    if (node == -1) {
      return 0;
    }
    return H(dat[node].lft) - H(dat[node].rgh);
  }

  static int RotateRight(int y) {
    int x = dat[y].lft;
    int z = dat[x].rgh;
    dat[x].rgh = y;
    dat[y].lft = z;
    Pull(y);
    Pull(x);
    return x;
  }

  static int RotateLeft(int x) {
    int y = dat[x].rgh;
    int z = dat[y].lft;
    dat[y].lft = x;
    dat[x].rgh = z;
    Pull(x);
    Pull(y);
    return y;
  }

  static int Recalc(int node) {
    if (node == -1) {
      return node;
    }
    Pull(node);
    int bf = BalDiff(node);
    if (bf > 1) {
      if (BalDiff(dat[node].lft) < 0) {
        dat[node].lft = RotateLeft(dat[node].lft);
      }
      return RotateRight(node);
    }
    if (bf < -1) {
      if (BalDiff(dat[node].rgh) > 0) {
        dat[node].rgh = RotateRight(dat[node].rgh);
      }
      return RotateLeft(node);
    }
    return node;
  }

  int Insert(int node, int key) {
    if (node == -1) {
      dat[tmr] = Node(key);
      return tmr++;
    }

    if (key < dat[node].key) {
      dat[node].lft = Insert(dat[node].lft, key);
    } else if (key > dat[node].key) {
      dat[node].rgh = Insert(dat[node].rgh, key);
    } else {
      return node;
    }
    return Recalc(node);
  }

  AVLTree() : root(-1) {}

  void Insert(int key) { root = Insert(root, key); }

  int LowerBound(int x) const {
    int current = root;
    int result = -1;
    while (current != -1) {
      if (dat[current].key >= x) {
        result = dat[current].key;
        current = dat[current].lft;
      } else {
        current = dat[current].rgh;
      }
    }
    return result;
  }
};

void Solve() {
  AVLTree tree;
  int q;
  std::cin >> q;
  bool f = false;
  int lst = 0;
  for (int q1 = 0; q1 < q; ++q1) {
    char t;
    int x;
    std::cin >> t >> x;
    if (t == '+') {
      if (!f) {
        tree.Insert(x);
      } else {
        tree.Insert((x + lst) % cMOD);
      }
      f = false;
    } else {
      f = true;
      lst = tree.LowerBound(x);
      std::cout << lst << '\n';
    }
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
