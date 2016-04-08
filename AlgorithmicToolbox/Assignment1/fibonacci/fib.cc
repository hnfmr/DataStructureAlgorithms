#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

long long calc_fib( int n )
{
  if ( n <= 1 ) return n;
  long long a = 0;
  long long b = 1;

  long long c = 0;
  for ( int i = 2; i <= n; ++i ) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}

// reference answer
long long fib_analytic( int n )
{
  if ( n <= 1 ) return n;

  long double ksi = static_cast< long double >( ( 1 + std::sqrt( 5 ) ) / 2 );
  long double phi = static_cast< long double >( -1 / ksi );

  return static_cast< long long >( ( std::pow( ksi, n ) - std::pow( phi, n ) ) / std::sqrt( 5 ) );
}

int main()
{
// stress test
#if 1
  for ( int i = 0; i < 100; ++i ) {
    int j = rand() % 100 + 2;
    auto a = calc_fib( j );
    auto b = fib_analytic( j );
    if ( a != b ) {
      std::stringstream ss;
      ss << "a: " << a << " b: " << b << "\n";
      throw std::runtime_error( ss.str().c_str() );
    }
  }
#endif

  int n = 0;
  std::cin >> n;

  std::cout << calc_fib( n ) << '\n';
  return 0;
}
