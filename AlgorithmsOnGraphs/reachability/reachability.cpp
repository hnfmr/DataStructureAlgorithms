#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore( const vector< vector< int > > &adj, vector< bool > &visited,
              int v )
{
  visited[ v ] = true;
  const auto &es = adj[ v ];

  for ( const auto &w : es )
  {

    if ( !visited[ w ] )
    {
      explore( adj, visited, w );
    }
  }
}
int reach( vector< vector< int > > &adj, int x, int y )
{
  // write your code here
  std::vector< bool > visited( adj.size(), false );

  explore( adj, visited, x );

  if ( visited[ y ] )
    return 1;

  return 0;
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
    adj[ y - 1 ].push_back( x - 1 );
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach( adj, x - 1, y - 1 );
}
