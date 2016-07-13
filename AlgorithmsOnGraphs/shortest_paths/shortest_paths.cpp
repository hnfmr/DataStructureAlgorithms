#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <functional>
#include <set>

using std::vector;
using std::unordered_map;
using std::priority_queue;
using std::queue;
using std::pair;

struct Node
{
  Node() : isinf( true ), val( 0 ) {}
  explicit Node( int val ) : isinf( false ), val( val ) {}
  bool isinf;
  int val;
};

Node operator+( const Node &n, int c )
{
  if ( n.isinf )
    return Node();

  return Node( n.val + c );
}

bool operator>( const Node &l, const Node &r )
{
  if ( !l.isinf && !r.isinf )
    return l.val > r.val;
  else if ( l.isinf )
    return true;
  else
    return false;
}

bool try_relax( int u, int v, const vector< int > &,
                const unordered_map< int, Node > &dist,
                const vector< vector< int > > &cost )
{
  auto new_w = dist.at( u ) + cost[ u ][ v ];
  if ( dist.at( v ) > new_w )
  {
    return true;
  }
  return false;
}

void relax( int u, int v, vector< int> &prev,
            unordered_map< int, Node > &dist,
            const vector< vector< int > > &cost )
{
  auto new_w = dist[ u ] + cost[ u ][ v ];
  if ( dist[ v ] > new_w )
  {
    dist[ v ] = new_w;
    prev[ v ] = u;
  }
}

std::tuple< bool, unordered_map< int, Node >, vector< int > >
bellman_ford( vector< vector< int > > &adj, vector< vector< int > > &cost,
                int s )
{
  std::unordered_map< int, Node > dist;
  std::vector< int > prev( adj.size(), -1 );
  for ( size_t i = 0; i < adj.size(); ++i )
  {
    dist[ i ] = Node();
  }

  dist[ s ] = Node( 0 );

  int V = adj.size();
  for ( int i = 0; i < V - 1; ++i )
  {
    for ( size_t j = 0; j < adj.size(); ++j )
    {
      int u = j;
      const auto &es = adj[ u ];
      for ( int v : es )
      {
        relax( u, v, prev, dist, cost );
      }
    }
  }

  for ( size_t j = 0; j < adj.size(); ++j )
  {
    int u = j;
    const auto &es = adj[ u ];
    for ( int v : es )
    {
      if ( try_relax( u, v, prev, dist, cost ) )
        return std::make_tuple( true, dist, prev );
    }
  }
  return std::make_tuple( false, dist, prev);
}

std::tuple< unordered_map< int, Node >, vector< int > >
dijkstra( const vector< vector< int > > &adj,
              const vector< vector< int > > &cost, int s )
{
  std::unordered_map< int, Node > dist;
  std::vector< int > prev( adj.size(), -1 );
  for ( size_t i = 0; i < adj.size(); ++i )
  {
    dist[ i ] =  Node();
  }

  dist[ s ] = Node(0);

  auto cmp = [&dist]( int left, int right ) {
    return dist[ left ] > dist[ right ];
  };

  std::priority_queue< int, std::vector< int >, decltype( cmp ) > h( cmp );

  for ( size_t i = 0; i < adj.size(); ++i )
  {
    h.push( i );
  }

  while ( !h.empty() )
  {
    int u = h.top();
    h.pop();

    const auto &edges = adj[ u ];
    for ( auto v : edges )
    {
      int w = cost[ u ][ v ];
      if ( dist[ v ] > ( dist[ u ] + w ) )
      {
        dist[ v ] = dist[ u ] + w;
        prev[ v ] = u;
        h.push( v );
      }
    }
  }

  return std::make_tuple( dist, prev );
}

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
  std::vector< bool > visited( adj.size(), false );

  explore( adj, visited, x );

  if ( visited[ y ] )
    return 1;

  return 0;
}

void shortest_paths( vector< vector< int > > &adj,
                     vector< vector< int > > &cost, int s,
                     vector< long long > &distance, vector< int > &reachable,
                     vector< int > &shortest )
{
  // write your code here
  bool negCycle = false;
  unordered_map< int, Node > dist;
  vector<int> prev;
  std::tie( negCycle, dist, prev) = bellman_ford( adj, cost, s );

  auto get_dist0 = [&cost]( const vector< int > &prev, int u,
                         int v ) -> long long {
      int tmp = v;
      long long sum = 0;
      while ( tmp != u )
      {
        if ( tmp == -1 || prev[ tmp ] == -1 )
          return -1;
        int w = cost[ prev[ tmp ] ][ tmp ];
        if ( w == -1 )
          return -1;
        sum += w;
        tmp = prev[ tmp ];
      }
      return sum;
    };

  unordered_map< int, Node > dist0;
  vector< int > prev0;

  std::set<int> cycles;
  if ( !negCycle )
  {
    std::tie( dist0, prev0 ) = dijkstra( adj, cost, s );
  }
  else
  {
    std::set< int > cycles;
    int startPoint = -1;
    for ( size_t j = 0; j < adj.size(); ++j )
    {
      int u = j;
      const auto &es = adj[ u ];
      for ( int v : es )
      {
        if ( try_relax( u, v, prev, dist, cost ) ) {
          startPoint = u;
          break;
        }
      }
    }

    cycles.insert( startPoint );

    int q = prev[ startPoint ];
    cycles.insert( q );

    while ( startPoint != q )
    {
      q = prev[ q ];
      cycles.insert( q );
    }
  }

  std::vector< bool > visited( adj.size(), false );

  explore( adj, visited, s );

  for ( size_t i = 0; i < adj.size(); ++i )
  {
    if ( i == s )
    {
      reachable[ i ] = 1;
      distance[ i ] = 0;
      continue;
    }

    int r = visited[ i ];
    reachable[ i ] = r;

    if ( r == 1 )
    {
      if ( negCycle )
      {
        // two cases
        // case 1: if u is not in the cycle path
        //if ( reach( adj, negV, i ) == 0 )
        if ( cycles.find( i ) == cycles.end() )
        {
          distance[ i ] = get_dist0( prev, s, i );
        }
        else {
          shortest[ i ] = 0;
        }
        //
        // case 2: if u is in inside 
      }
      else
      {
        distance[ i ] = get_dist0( prev0, s, i );
      }
    }
  }
}

int main()
{
  int n, m, s;
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
  std::cin >> s;
  s--;
  vector< long long > distance( n, std::numeric_limits< long long >::max() );
  vector< int > reachable( n, 0 );
  vector< int > shortest( n, 1 );
  shortest_paths( adj, cost, s, distance, reachable, shortest );
  for ( int i = 0; i < n; i++ )
  {
    if ( !reachable[ i ] )
    {
      std::cout << "*\n";
    }
    else if ( !shortest[ i ] )
    {
      std::cout << "-\n";
    }
    else
    {
      std::cout << distance[ i ] << "\n";
    }
  }

  return 0;
}
