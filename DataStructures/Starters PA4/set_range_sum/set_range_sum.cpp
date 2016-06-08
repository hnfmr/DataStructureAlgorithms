#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex
{
  int key;
  // Sum of all the keys in the subtree - remember to update
  // it after each operation that changes the tree.
  long long sum;
  Vertex *left;
  Vertex *right;
  Vertex *parent;

  Vertex( int key, long long sum, Vertex *left, Vertex *right, Vertex *parent )
    : key( key )
    , sum( sum )
    , left( left )
    , right( right )
    , parent( parent )
  {
  }
};

void update( Vertex *v )
{
  if ( v == NULL )
    return;
  v->sum = v->key + ( v->left != NULL ? v->left->sum : 0ll ) +
           ( v->right != NULL ? v->right->sum : 0ll );
  if ( v->left != NULL )
  {
    v->left->parent = v;
  }
  if ( v->right != NULL )
  {
    v->right->parent = v;
  }
}

void small_rotation( Vertex *v )
{
  Vertex *parent = v->parent;
  if ( parent == NULL )
  {
    return;
  }
  Vertex *grandparent = v->parent->parent;
  if ( parent->left == v )
  {
    Vertex *m = v->right;
    v->right = parent;
    parent->left = m;
  }
  else
  {
    Vertex *m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update( parent );
  update( v );
  v->parent = grandparent;
  if ( grandparent != NULL )
  {
    if ( grandparent->left == parent )
    {
      grandparent->left = v;
    }
    else
    {
      grandparent->right = v;
    }
  }
}

void big_rotation( Vertex *v )
{
  if ( v->parent->left == v && v->parent->parent->left == v->parent )
  {
    // Zig-zig
    small_rotation( v->parent );
    small_rotation( v );
  }
  else if ( v->parent->right == v && v->parent->parent->right == v->parent )
  {
    // Zig-zig
    small_rotation( v->parent );
    small_rotation( v );
  }
  else
  {
    // Zig-zag
    small_rotation( v );
    small_rotation( v );
  }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay( Vertex *&root, Vertex *v )
{
  if ( v == NULL )
    return;
  while ( v->parent != NULL )
  {
    if ( v->parent->parent == NULL )
    {
      small_rotation( v );
      break;
    }
    big_rotation( v );
  }
  root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex *find( Vertex *&root, int key )
{
  Vertex *v = root;
  Vertex *last = root;
  Vertex *next = NULL;
  while ( v != NULL )
  {
    if ( v->key >= key && ( next == NULL || v->key < next->key ) )
    {
      next = v;
    }
    last = v;
    if ( v->key == key )
    {
      break;
    }
    if ( v->key < key )
    {
      v = v->right;
    }
    else
    {
      v = v->left;
    }
  }
  splay( root, last );
  return next;
}

void split( Vertex *root, int key, Vertex *&left, Vertex *&right )
{
  right = find( root, key );
  splay( root, right );
  if ( right == NULL )
  {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if ( left != NULL )
  {
    left->parent = NULL;
  }
  update( left );
  update( right );
}

Vertex *merge( Vertex *left, Vertex *right )
{
  if ( left == NULL )
    return right;
  if ( right == NULL )
    return left;
  Vertex *min_right = right;
  while ( min_right->left != NULL )
  {
    min_right = min_right->left;
  }
  splay( right, min_right );
  right->left = left;
  update( right );
  return right;
}

// Code that uses splay tree to solve the problem

Vertex *root = NULL;

void insert( int x )
{
  Vertex *left = NULL;
  Vertex *right = NULL;
  Vertex *new_vertex = NULL;
  split( root, x, left, right );
  if ( right == NULL || right->key != x )
  {
    new_vertex = new Vertex( x, x, NULL, NULL, NULL );
  }
  root = merge( merge( left, new_vertex ), right );
}

bool find( int x )
{
  // Implement find yourself
  Vertex *v = find( root, x );
  splay( root, v );

  if ( v == nullptr || v->key != x )
    return false;

  if ( v->key == x )
  {
    return true;
  }
  return false;
}

void erase( int x )
{
  // Implement erase yourself

  Vertex *v = find( root, x );
  splay( root, v );

  if ( v == nullptr || v->key != x )
    return;

  if ( v && v->key == x )
  {
    root = merge( root->left, root->right );
    if ( root )
      root->parent = nullptr;
  }
}

long long sum( int from, int to )
{
  Vertex *left = NULL;
  Vertex *middle = NULL;
  Vertex *right = NULL;
  split( root, from, left, middle );
  split( middle, to + 1, middle, right );
  long long ans = 0;
  update( left );
  update( right );
  update( middle );
  if ( middle != nullptr )
    ans = middle->sum;

  root = merge( merge( left, middle ), right );
  return ans;
}

const int MODULO = 1000000001;

struct Operation {
  char code; // + - ? s
  int x; // for +, -, ?
  int l; // for s l r
  int r;
};

int main()
{
  std::stringstream ss;

  int n;
  std::cin >> n;

  std::vector<Operation> ops;

  for (int i = 0; i < n; ++i) {
    Operation op;
    char code;
    std::cin >> code;
    switch (code) {
      case 's':
        {
          int l, r;
          std::cin >> l;
          std::cin >> r;
          op = {code, -1, l, r};
        }
        break;
      case '+':
        {
          int x;
          std::cin >> x;
          op = {code, x, -1, -1};
        }
        break;
      case '-':
        {
          int x;
          std::cin >> x;
          op = {code, x, -1, -1};
        }
        break;
      case '?':
        {
          int x;
          std::cin >> x;
          op = {code, x, -1, -1};
        }
        break;
      default: break;
    }
    ops.push_back(op);
  }

  int last_sum_result = 0;
  for ( int i = 0; i < n; i++ )
  {
    auto op = ops[ i ];
    switch ( op.code )
    {
    case '+':
    {
      insert( ( op.x + last_sum_result ) % MODULO );
    }
    break;
    case '-':
    {
      erase( ( op.x + last_sum_result ) % MODULO );
    }
    break;
    case '?':
    {
      if ( find( ( op.x + last_sum_result ) % MODULO ) )
        ss << "Found\n";
      else
        ss << "Not found\n";
    }
    break;
    case 's':
    {
      long long res = sum( ( op.l + last_sum_result ) % MODULO,
                           ( op.r + last_sum_result ) % MODULO );
      ss << res << "\n";
      last_sum_result = int( res % MODULO );
    }
    }
  }

  std::cout << ss.str();
#if 0
  std::string splay1 = ss.str();

  ss = std::stringstream();

  // reference answer
  last_sum_result = 0;
  std::set<int> s;
  for ( int i = 0; i < n; i++ )
  {
    auto op = ops[ i ];
    switch ( op.code )
    {
    case '+':
    {
      s.insert( ( op.x + last_sum_result ) % MODULO );
    }
    break;
    case '-':
    {
      s.erase( ( op.x + last_sum_result ) % MODULO );
    }
    break;
    case '?':
    {
      if ( s.find( ( op.x + last_sum_result ) % MODULO ) != s.end() )
        ss << "Found\n";
      else
        ss << "Not found\n";
    }
    break;
    case 's':
    {
      long long res = 0;
      for (auto it = s.begin(); it != s.end(); ++it) {
        if ( *it >= ( ( op.l + last_sum_result ) % MODULO ) &&
             *it <= ( ( op.r + last_sum_result ) % MODULO ) )
          res += *it;
      }
      ss << res << "\n";
      last_sum_result = int( res % MODULO );
    }
    }
  }

  std::string splay2 = ss.str();

  std::cout << "SPLAY1\n"
    << splay1 << "\n";
  std::cout << "SPLAY2\n"
    << splay2 << "\n";

  if (splay1 != splay2) {
    std::cerr << "######################################## DIFF\n";
  }

#endif
  return 0;
}
