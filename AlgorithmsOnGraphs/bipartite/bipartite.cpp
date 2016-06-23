#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using std::vector;
using std::queue;


enum class Color {
  blue, red, nocolor
};

Color flip(Color c) {
  if (c == Color::blue) return Color::red;
  if (c == Color::red) return Color::blue;

  return Color::nocolor;
}

bool bfs( vector< vector< int > > &adj )
{
  std::unordered_map< int, Color > color;

  for ( size_t i = 0; i < adj.size(); ++i )
  {
    color[ i ] = Color::nocolor;
  }

  for ( size_t s = 0; s < adj.size(); ++s )
  {
    if ( color[ s ] != Color::nocolor )
      continue;

    std::queue< int > q;

    q.push( s );
    color[ s ] = Color::blue;

    while ( !q.empty() )
    {
      int u = q.front();
      q.pop();
      const auto &es = adj[ u ];

      for ( int e : es )
      {
        if ( color[ e ] == Color::nocolor )
        {
          q.push( e );
        }
        color[ e ] = flip( color[ u ] );
      }
    }
  }

  for ( size_t i = 0; i < adj.size(); ++i )
  {
    const auto &es = adj[ i ];
    Color c = color[ i ];
    for ( int e : es )
    {
      Color bc = color[ e ];
      if ( c == bc )
        return false;
    }
  }
  return true;
}

int bipartite( vector< vector< int > > &adj )
{
  //write your code here
  return bfs( adj );
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
