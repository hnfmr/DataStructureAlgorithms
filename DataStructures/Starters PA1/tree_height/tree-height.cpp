#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

class Node
{
public:
  Node( int v )
    : val( v )
    , children()
  {
  }

  Node( const Node &n )
    : val( n.val )
    , children( n.children )
  {
  }

  void add_child( int v ) { children.push_back( v ); }

  int size() const { return children.size(); }

  int val;
  std::vector< int > children;
};

class TreeHeight
{
  int n;
  std::vector< int > parent;
  std::map< int, Node * > ns;
  Node *node;

public:
  ~TreeHeight()
  {
    for ( const auto &n : ns )
    {
      delete n.second;
    }
  }

  void read()
  {
    std::cin >> n;
    parent.resize( n );
    for ( int i = 0; i < n; i++ )
      std::cin >> parent[ i ];
  }

  int compute_height()
  {
    construct_tree();
    return max_depth( node );
  }

private:
  int max_depth( Node *n )
  {
    if ( n == nullptr )
      return 0;

    if ( n->size() == 0 )
      return 1;

    int m = 0;
    for ( int i = 0; i < n->size(); ++i )
    {
      int d = max_depth( ns[ n->children[ i ] ] );
      if ( d > m )
        m = d;
    }
    return m + 1;
  }

  void construct_tree()
  {
    for ( int i = 0; i < n; ++i )
    {
      ns[ i ] = new Node( i );
    }

    for ( int i = 0; i < n; ++i )
    {
      int p = parent[ i ];

      if ( p != -1 )
      {
        ns[ p ]->add_child( i );
      }
      else
      {
        node = ns[ i ];
      }
    }
  }
};

int main()
{
  std::ios_base::sync_with_stdio( 0 );
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;

  return 0;
}
