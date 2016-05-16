#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
//#include <stack>

class TreeHeight
{
  int n;
  std::vector< int > parent;

public:
  void read()
  {
    std::cin >> n;
    parent.resize( n );
    for ( int i = 0; i < n; i++ )
      std::cin >> parent[ i ];
  }

  int compute_height()
  {
    // Replace this code with a faster implementation
    //int maxHeight = 0;

    std::map< int, int > countMap;

    //for (int i = 0; i < parent.size(); ++i)
    //{
    //  if (parent[i] == -1)
    //    countMap[i] = 1;
    //  else
    //    countMap[i] = 0;
    //}

    int maxHeight = 0;
    int height = 0;
    for ( int i = 0; i < n; ++i )
    {
      int n = parent[ i ];
      if ( n == -1 )
        continue;

      int c = 0;
      int j = n;

      if ( countMap.find( parent[ n ] ) != countMap.end() )
      {
        height = countMap[ parent[ n ] ] + 1;
        //countMap[ parent[ n ] ] = height;
      }
      else
      {
        while ( parent[ j ] != -1 )
        {
          j = parent[ j ];
          ++c;
        }
        height = ++c;
        countMap[ n ] = height;
      }

      if ( height > maxHeight )
        maxHeight = height;
    }

    //for ( int vertex = 0; vertex < n; vertex++ )
    //{
    //  int height = 0;
    //  for ( int i = vertex; i != -1; i = parent[ i ] )
    //    height++;
    //  maxHeight = std::max( maxHeight, height );
    //}
    return maxHeight+1;
  }
};

int main()
{
  std::ios_base::sync_with_stdio( 0 );
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;

  return 0;
}
