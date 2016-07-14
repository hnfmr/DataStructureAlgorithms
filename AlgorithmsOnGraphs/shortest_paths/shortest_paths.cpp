#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include <cstdint>

using std::vector;
using std::map;

struct Node
{
  Node() : isinf( true ), val( 0 ) {}
  explicit Node( std::int64_t val ) : isinf( false ), val( val ) {}
  bool isinf;
  std::int64_t val;
};

inline Node operator+( const Node &n, std::int64_t c )
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

inline bool relax( std::uint32_t u, std::uint32_t v, map< std::uint32_t, Node > &dist, const vector< vector< std::int64_t > > &cost )
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

void explore( const vector< vector< std::uint32_t > > &adj, vector< bool > &visited, std::uint32_t v )
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

std::set< std::uint32_t > bfs( vector< vector< std::uint32_t > > &adj, std::set< std::uint32_t > &from )
{
  std::set< std::uint32_t > infarbs;

  for ( auto f : from )
  {
    std::vector< bool > visited( adj.size(), false );

    explore( adj, visited, f );

    for ( std::uint32_t i = 0; i < visited.size(); ++i )
    {
      if ( visited[ i ] )
        infarbs.insert( i );
    }
  }
  return infarbs;
}

std::tuple< std::set< std::uint32_t >, map< std::uint32_t, Node > >
bellman_ford( vector< vector< std::uint32_t > > &adj, const vector< vector< std::int64_t > > &cost, std::uint32_t s )
{
  map< std::uint32_t, Node > dist;
  for ( std::uint32_t i = 0; i < adj.size(); ++i )
  {
    dist[ i ] = Node();
  }

  dist[ s ] = Node( 0ll );

  std::set< std::uint32_t > cycles;
  const std::uint32_t V = adj.size();
  for ( std::uint32_t i = 0; i < V; ++i )
  {
    for ( std::uint32_t j = 0; j < adj.size(); ++j )
    {
      std::uint32_t u = j;
      const auto &es = adj[ u ];
      for (std::uint32_t v : es )
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

void shortest_paths( vector< vector< std::uint32_t > > &adj, const vector< vector< std::int64_t > > &cost, std::uint32_t s,
                     vector< std::int64_t > &distance, vector< bool > &reachable, vector< bool > &shortest )
{
  std::set< std::uint32_t > cycles;
  map< std::uint32_t, Node > dist;
  std::tie( cycles, dist ) = bellman_ford( adj, cost, s );

  for ( std::uint32_t i = 0; i < adj.size(); ++i )
  {
    if ( i == s )
    {
      reachable[ i ] = true;
      distance[ i ] = 0ll;
      continue;
    }

    reachable[ i ] = !dist[ i ].isinf;

    if ( reachable[ i ] )
    {
      if ( cycles.find( i ) == cycles.end() )
      {
        distance[ i ] = dist[ i ].val;
      }
      else
      {
        shortest[ i ] = false;
      }
    }
  }
}

int main()
{
  std::uint32_t n, m, s;
  std::cin >> n >> m;

  vector< vector< std::uint32_t > > adj( n, vector< std::uint32_t >() );
  vector< vector< std::int64_t > > cost( n, vector< std::int64_t >( n, -1 ) );

  for ( std::uint32_t i = 0; i < m; i++ )
  {
    std::uint32_t x, y;
    std::int64_t w;
    std::cin >> x >> y >> w;

    adj[ x - 1 ].push_back( y - 1 );
    cost[ x - 1 ][ y - 1 ] = w;
  }

  std::cin >> s;
  s--;

  vector< std::int64_t > distance( n, std::numeric_limits< std::int64_t >::max() );
  vector< bool > reachable( n, false );
  vector< bool > shortest( n, true );
  shortest_paths( adj, cost, s, distance, reachable, shortest );
  for ( std::uint32_t i = 0; i < n; i++ )
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
