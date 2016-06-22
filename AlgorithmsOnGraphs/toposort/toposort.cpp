#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using std::vector;
using std::pair;

void previsit( int v, std::unordered_map< int, std::pair< int, int > > &order,
               int &c )
{
  ++c;
  auto &p = order[ v ];
  p.first = c;
}

void postvisit( int v, std::unordered_map< int, std::pair< int, int > > &order,
                int &c )
{
  ++c;
  auto &p = order[ v ];
  p.second = c;
}

void explore( const vector< vector< int > > &adj, vector< bool > &visited,
              int v, std::unordered_map< int, std::pair< int, int > > &order,
              int &c )
{
  visited[ v ] = true;
  const auto &es = adj[ v ];
  previsit( v, order, c );
  for ( const auto &w : es )
  {

    if ( !visited[ w ] )
    {
      explore( adj, visited, w, order, c );
    }
  }

  postvisit( v, order, c );
}

std::vector< std::pair< int, int > > dfs_v1( vector< vector< int > > &adj )
{
  // write your code here
  std::vector< bool > visited( adj.size(), false );
  std::unordered_map< int, std::pair< int, int > > order;
  for ( int i = 0; i < adj.size(); ++i )
  {
    order[ i ] = std::make_pair( 0, 0 );
  }

  int c = 0;

  for ( int v = 0; v < adj.size(); ++v )
  {
    if ( !visited[ v ] )
    {
      explore( adj, visited, v, order, c );
    }
  }

  std::vector< std::pair< int, int > > ooo( adj.size(),
                                            std::make_pair( 0, 0 ) );
  for ( const auto &kv : order )
  {
    int i = kv.first;
    int p = kv.second.second;

    ooo[ i ] = std::make_pair( i, p );
  }

  std::sort( ooo.begin(), ooo.end(), []( const std::pair< int, int > &l,
                                         const std::pair< int, int > &r ) {
    return l.second >= r.second;
  } );

  return ooo;
}

void dfs( vector< vector< int > > &adj, vector< int > &used,
          vector< int > &order, int x )
{
  // write your code here
}

vector< int > toposort( vector< vector< int > > adj )
{
  vector< int > used( adj.size(), 0 );
  vector< int > order;
  // write your code here
  return order;
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector< vector< int > > adj( n, vector< int >() );
  for ( size_t i = 0; i < m; i++ )
  {
    int x, y;
    std::cin >> x >> y;
    adj[ x - 1 ].push_back( y - 1 );
  }
  vector< std::pair< int, int > > order = dfs_v1( adj );
  for ( size_t i = 0; i < order.size(); i++ )
  {
    std::cout << order[ i ].first + 1 << " ";
  }

  return 0;
}
