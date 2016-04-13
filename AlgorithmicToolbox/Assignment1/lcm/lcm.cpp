#include <iostream>

int gcd_euclid( int a, int b )
{
  if ( b == 0 ) {
    return a;
  }
  int r = a % b;
  return gcd_euclid( b, r );
}

long long lcm( int a, int b )
{
  // write your code here
  return static_cast< long long >( a ) * b / gcd_euclid( a, b );
}

int main()
{
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm( a, b ) << std::endl;

  return 0;
}
