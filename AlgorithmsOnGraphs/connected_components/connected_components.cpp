#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore( const vector< vector< int > > &adj, vector< bool > &visited,
              std::vector< int > &ccnum, int v, int cc )
{
  visited[ v ] = true;
  ccnum[ v ] = cc;
  const auto &es = adj[ v ];
  for ( const auto &w : es )
  {
    if ( !visited[ w ] )
    {
      explore( adj, visited, ccnum, w, cc );
    }
  }
}

int number_of_components( vector< vector< int > > &adj )
{
  int res = 0;
  // write your code here
  std::vector< bool > visited( adj.size(), false );
  std::vector< int > ccnum( adj.size(), 0 );
  int cc = 1;

  for ( int v = 0; v < adj.size(); ++v )
  {
    if ( !visited[ v ] )
    {
      explore( adj, visited, ccnum, v, cc );
      ++cc;
    }
  }

  std::sort( ccnum.begin(), ccnum.end() );
  res = std::unique( ccnum.begin(), ccnum.end() ) - ccnum.begin();
  return res;
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
  std::cout << number_of_components( adj );
}
