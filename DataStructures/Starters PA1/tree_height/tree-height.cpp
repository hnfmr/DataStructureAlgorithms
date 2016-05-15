#include <algorithm>
#include <iostream>
#include <vector>

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
    int maxHeight = 0;
    auto it = std::lower_bound( parent.begin(), parent.end(), -1 );
    int diff = 0;
    if (it != parent.end()) {
      diff = std::distance( parent.begin(), it );
    }
    std::cout << "diff: " << diff << "\n";

    /* for ( int vertex = 0; vertex < n; vertex++ ) */
    /* { */
    /*   int height = 0; */
    /*   for ( int i = vertex; i != -1; i = parent[ i ] ) */
    /*     height++; */
    /*   maxHeight = std::max( maxHeight, height ); */
    /* } */
    return maxHeight;
  }
};

int main()
{
  std::ios_base::sync_with_stdio( 0 );
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;
}
