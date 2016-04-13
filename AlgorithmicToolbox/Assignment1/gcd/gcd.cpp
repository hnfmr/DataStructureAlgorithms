#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int gcd( int a, int b )
{
  // write your code here
  int current_gcd = 1;
  for ( int d = 2; d <= a && d <= b; d++ ) {
    if ( a % d == 0 && b % d == 0 ) {
      if ( d > current_gcd ) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_euclid( int a, int b )
{
  if ( b == 0 ) {
    return a;
  }
  int r = a % b;
  return gcd_euclid( b, r );
}

int main()
{
  int c = 0;
  while ( c < 10000 ) {
    int a = std::rand() % 1000 + 1;
    int b = std::rand() % 1000 + 1;

    int gcd_x = gcd( a, b );
    int gcd_y = gcd_euclid( a, b );
    if ( gcd_x != gcd_y ) {
      std::stringstream ss;
      ss << "a: " << a << " b: " << b << "\n";
      throw std::runtime_error( ss.str().c_str() );
    }
    ++c;
  }
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd( a, b ) << std::endl;
  return 0;
}
