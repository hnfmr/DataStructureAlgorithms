#include <iostream>
#include <unordered_map>>
#include <vector>

using std::vector;
using std::unordered_map;

void relax( int u, int v, vector< int > &prev, unordered_map< int, int > &dist,
            const vector< vector< int > > &cost )
{
  int new_w = dist[ u ] + cost[ u ][ v ];
  if ( dist[ v ] > new_w )
  {
    dist[ v ] = new_w;
    prev[ v ] = u;
  }
}

int negative_cycle( vector< vector< int > > &adj,
                    vector< vector< int > > &cost )
{
  // write your code here

  std::unordered_map< int, long long > dist;
  std::vector< long long > prev(adj.size(), -1);
  for (size_t i = 0; i < adj.size(); ++i)
  {
    dist[i] = std::numeric_limits<int>::max();
  }

  dist[ 0 ] = 0;

  for (int i = 0; i < adj.size() - 1; ++i) {

  }
  return 0;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector< vector< int > > adj( n, vector< int >() );
  vector< vector< int > > cost( n, vector< int >( n, -1 ) );
  for ( int i = 0; i < m; i++ )
  {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[ x - 1 ].push_back( y - 1 );
    cost[ x - 1 ][ y - 1 ] = w;
  }
  std::cout << negative_cycle( adj, cost );
}
