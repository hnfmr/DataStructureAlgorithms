#include <iostream>
#include <vector>

int get_fibonacci_last_digit( int n )
{
  std::vector< int > fs( n + 1 );
  fs[0] = 0;
  fs[1] = 1;

  for ( int i = 2; i < n + 1; ++i ) {
    fs[i] = ( fs[i - 1] + fs[i - 2] ) % 10;
  }
  return fs.back();
}

int main() {
  int n;
  std::cin >> n;
  int c = get_fibonacci_last_digit(n);
  std::cout << c << '\n';
}
