#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders
{
  int n;
  vector< int > key;
  vector< int > left;
  vector< int > right;

public:
  void read()
  {
    cin >> n;
    key.resize( n );
    left.resize( n );
    right.resize( n );
    for ( int i = 0; i < n; i++ )
    {
      cin >> key[ i ] >> left[ i ] >> right[ i ];
    }
  }

  struct Node
  {
    int key;
    int left;
    int right;
  };

  void inorder_traverse( std::vector< int > &result, int nodeIdx )
  {
    if ( nodeIdx == -1 )
      return;

    int k = key[ nodeIdx ];
    int l = left[ nodeIdx ];
    int r = right[ nodeIdx ];

    inorder_traverse( result, l );
    result.push_back( k );
    inorder_traverse( result, r );
  }

  vector< int > in_order()
  {
    if ( key.empty() )
      return std::vector< int >();

    vector< int > result;
    inorder_traverse( result, 0 );
    return result;
  }

  void preorder_traverse( std::vector< int > &result, int nodeIdx )
  {
    if ( nodeIdx == -1 )
      return;

    result.push_back( key[ nodeIdx ] );
    preorder_traverse( result, left[ nodeIdx ] );
    preorder_traverse( result, right[ nodeIdx ] );
  }

  vector< int > pre_order()
  {
    if ( key.empty() )
      return std::vector< int >();

    vector< int > result;
    preorder_traverse( result, 0 );
    return result;
  }

  void postorder_traverse( std::vector< int > &result, int nodeIdx )
  {
    if ( nodeIdx == -1 )
      return;

    postorder_traverse( result, left[ nodeIdx ] );
    postorder_traverse( result, right[ nodeIdx ] );

    result.push_back( key[ nodeIdx ] );
  }
  vector< int > post_order()
  {
    if (key.empty())
      return std::vector< int >();

    vector< int > result;
    postorder_traverse( result, 0 );
    return result;
  }
};

void print( vector< int > a )
{
  for ( size_t i = 0; i < a.size(); i++ )
  {
    if ( i > 0 )
    {
      cout << ' ';
    }
    cout << a[ i ];
  }
  cout << '\n';
}

int main()
{
  ios_base::sync_with_stdio( 0 );
  TreeOrders t;
  t.read();
  print( t.in_order() );
  print( t.pre_order() );
  print( t.post_order() );
  return 0;
}
