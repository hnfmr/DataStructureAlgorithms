#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

using std::vector;
using std::map;
using std::priority_queue;
using std::queue;
using std::pair;

struct Node
{
  Node() : isinf( true ), val( 0 ) {}
  explicit Node( long long val ) : isinf( false ), val( val ) {}
  bool isinf;
  long long val;
};

inline Node operator+( const Node &n, long long c )
{
  if ( n.isinf )
    return Node();

  return Node( n.val + c );
}

inline bool operator>( const Node &l, const Node &r )
{
  if ( !l.isinf && !r.isinf )
    return l.val > r.val;
  else if ( l.isinf && !r.isinf )
    return true;
  else if ( !l.isinf && r.isinf )
    return false;
  else
    return false;
}

inline bool relax( long long u, long long v, map< long long, Node > &dist, const vector< vector< long long > > &cost )
{
  auto new_w = dist[ u ] + cost[ u ][ v ];
  auto &nodeV = dist[ v ];
  if ( nodeV > new_w )
  {
    nodeV = new_w;
    return true;
  }
  return false;
}

void explore( const vector< vector< long long > > &adj, vector< bool > &visited, long long v )
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

std::set< long long > bfs( vector< vector< long long > > &adj, std::set< long long > &from )
{
  std::set< long long > infarbs;

  for ( auto f : from )
  {
    std::vector< bool > visited( adj.size(), false );

    explore( adj, visited, f );

    for ( unsigned long i = 0; i < visited.size(); ++i )
    {
      if ( visited[ i ] )
        infarbs.insert( i );
    }
  }
  return infarbs;
}

std::tuple< std::set< long long >, map< long long, Node > >
bellman_ford( vector< vector< long long > > &adj, const vector< vector< long long > > &cost, long long s )
{
  map< long long, Node > dist;
  for ( unsigned long i = 0; i < adj.size(); ++i )
  {
    dist[ i ] = Node();
  }

  dist[ s ] = Node( 0ll );

  std::set< long long > cycles;
  const unsigned long V = adj.size();
  for ( unsigned long i = 0; i < V; ++i )
  {
    for ( unsigned long j = 0; j < adj.size(); ++j )
    {
      long long u = j;
      const auto &es = adj[ u ];
      for ( long long v : es )
      {
        if ( relax( u, v, dist, cost ) )
        {
          if ( i == ( V - 1 ) )
          {
            cycles.insert( v );
          }
        }
      }
    }
  }

  return std::make_tuple( bfs( adj, cycles ), dist );
}

map< long long, Node > dijkstra( const vector< vector< long long > > &adj, const vector< vector< long long > > &cost,
                                 long long s )
{
  map< long long, Node > dist;
  for ( unsigned long i = 0; i < adj.size(); ++i )
  {
    dist[ i ] = Node();
  }

  dist[ s ] = Node( 0ll );

  auto cmp = [&dist]( long long left, long long right ) { return dist[ left ] > dist[ right ]; };

  std::priority_queue< long long, std::vector< long long >, decltype( cmp ) > h( cmp );

  for ( unsigned long i = 0; i < adj.size(); ++i )
  {
    h.push( i );
  }

  while ( !h.empty() )
  {
    long long u = h.top();
    h.pop();

    const auto &edges = adj[ u ];
    for ( auto v : edges )
    {
      long long w = cost[ u ][ v ];
      auto n = dist[ u ] + w;
      if ( dist[ v ] > n )
      {
        dist[ v ] = n;
        h.push( v );
      }
    }
  }

  return dist;
}

void shortest_paths( vector< vector< long long > > &adj, const vector< vector< long long > > &cost, unsigned long s,
                     vector< long long > &distance, vector< long long > &reachable, vector< long long > &shortest )
{
  std::set< long long > cycles;
  map< long long, Node > dist;
  std::tie( cycles, dist ) = bellman_ford( adj, cost, s );

  if ( cycles.empty() )
  {
    dist = dijkstra( adj, cost, s );
  }

  for ( unsigned long i = 0; i < adj.size(); ++i )
  {
    if ( i == s )
    {
      reachable[ i ] = 1;
      distance[ i ] = 0ll;
      continue;
    }

    long long r = dist[ i ].isinf ? 0 : 1;
    reachable[ i ] = r;

    if ( r == 1 )
    {
      if ( !cycles.empty() )
      {
        if ( cycles.find( i ) == cycles.end() )
        {
          distance[ i ] = dist[ i ].val;
        }
        else
        {
          shortest[ i ] = 0;
        }
      }
      else
      {
        distance[ i ] = dist[ i ].val;
      }
    }
  }
}

int main()
{
  long long n, m, s;
  std::cin >> n >> m;

  vector< vector< long long > > adj( n, vector< long long >() );
  vector< vector< long long > > cost( n, vector< long long >( n, -1 ) );

  for ( long long i = 0; i < m; i++ )
  {
    long long x, y, w;
    std::cin >> x >> y >> w;

    adj[ x - 1 ].push_back( y - 1 );
    cost[ x - 1 ][ y - 1 ] = w;
  }

  std::cin >> s;
  s--;

  vector< long long > distance( n, std::numeric_limits< long long >::max() );
  vector< long long > reachable( n, 0 );
  vector< long long > shortest( n, 1 );
  shortest_paths( adj, cost, s, distance, reachable, shortest );
  for ( long long i = 0; i < n; i++ )
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
