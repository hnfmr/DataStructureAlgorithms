#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <functional>

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

bool relax( int u, int v, vector< long long > &prev,
            unordered_map< int, Node > &dist,
            const vector< vector< int > > &cost )
{
  auto new_w = dist[ u ] + cost[ u ][ v ];
  if ( dist[ v ] > new_w )
  {
    dist[ v ] = new_w;
    prev[ v ] = u;
    return true;
  }
  return false;
}

std::tuple< bool, unordered_map< int, Node >, int, int >
negative_cycle( vector< vector< int > > &adj, vector< vector< int > > &cost,
                int s )
{
  std::unordered_map< int, Node > dist;
  std::vector< long long > prev( adj.size(), -1 );
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
      if ( relax( u, v, prev, dist, cost ) )
        return std::make_tuple( true, dist, u, v );
    }
  }
  return std::make_tuple( false, dist, -1, -1 );
}

std::tuple< unordered_map< int, Node >, vector< long long > >
get_distance( const vector< vector< int > > &adj,
              const vector< vector< int > > &cost, int s )
{
  std::unordered_map< int, Node > dist;
  std::vector< long long > prev( adj.size(), -1 );
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
  int negU = -1;
  int negV = -1;
  std::tie( negCycle, dist, negU, negV ) = negative_cycle( adj, cost, s );

  unordered_map< int, Node > dist0;
  vector< long long > prev0;
  std::function<int(int,int)> get_dist0;

  if ( !negCycle )
  {
    std::tie( dist0, prev0 ) = get_distance( adj, cost, s );

    get_dist0 = [&dist0, &prev0, &cost]( int u, int v ) {
      int tmp = v;
      int sum = 0;
      while ( tmp != u )
      {
        if ( tmp == -1 || prev0[ tmp ] == -1 )
          return -1;
        int w = cost[ prev0[ tmp ] ][ tmp ];
        if ( w == -1 )
          return -1;
        sum += 1;
        tmp = prev0[ tmp ];
      }
      return sum;
    };
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
        if ( reach( adj, negV, i ) == 0 )
        {
          distance[ i ] = dist[ i ].val;
        }
        else {
          shortest[ i ] = 0;
        }
        //
        // case 2: if u is in inside 
      }
      else
      {
        distance[ i ] = get_dist0( s, i );
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
