#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using std::vector;
using std::queue;
using std::priority_queue;
using std::pair;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  std::unordered_map< int, long long > dist;
  std::vector< long long > prev( adj.size(), -1 );
  for ( size_t i = 0; i < adj.size(); ++i )
  {
    dist[ i ] = std::numeric_limits<int>::max();
  }

  dist[ s ] = 0;

  auto cmp = [&dist]( int left, int right ) { return dist[ left ] > dist[ right ]; };
  std::priority_queue< int, std::vector< int >, decltype( cmp ) > h( cmp );

  for (size_t i = 0; i < adj.size(); ++i) {
    h.push( i );
  }

  while (!h.empty()) {
    int u = h.top();
    h.pop();

    const auto& edges = adj[u];
    for (auto v : edges) {
      int w = cost[u][v];
      if ( dist[ v ] == std::numeric_limits< int >::max() )
      {
        dist[ v ] = dist[ u ] + w;
        prev[ v ] = u;
        h.push( v );
      }
      else
      {
        if ( dist[ v ] > ( dist[ u ] + w ) )
        {
          dist[ v ] = dist[ u ] + w;
          prev[ v ] = u;
          h.push( v );
        }
      }
    }
  }

  int tmp = t;
  int sum = 0;
  while ( tmp != s )
  {
    if (tmp == -1 || prev[tmp] == -1) return -1;
    int w = cost[prev[tmp]][tmp];
    if (w == -1) return -1;
    sum += w;
    tmp = prev[ tmp ];
  }
  return sum;
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
    //cost[ x - 1 ].push_back( w );
    cost[x - 1][y - 1] = w;
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance( adj, cost, s, t );
  return 0;
}
