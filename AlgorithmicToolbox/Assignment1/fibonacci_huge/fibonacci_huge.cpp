#include <cstdint>
#include <iostream>

std::uint64_t get_fibonaccihuge( std::uint64_t n, std::uint64_t m )
{
  // write your code here
  return 0;
}

std::uint64_t calc_fib( std::uint64_t n )
{
  if ( n <= 1 ) return n;
  std::uint64_t a = 0;
  std::uint64_t b = 1;

  std::uint64_t c = 0;
  for ( std::uint64_t i = 2; i <= n; ++i ) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}

std::uint64_t pisano_period( std::uint64_t n, std::uint64_t q )
{

  std::uint64_t a = 0;
  std::uint64_t b = 1;

  std::uint64_t c = 2;

  std::uint64_t r1 = 1;
  std::uint64_t r = 0;

  std::uint64_t m = 0;

  for ( std::uint64_t i = 2; i <= n; ++i ) {
    c = a + b;
    r = c % q;
    m = i - 1;
    if ( r1 == 0 && r == 1 ) {
      std::cout << "FOUND!\n";
      break;
    }
    r1 = r;
    a = b;
    b = c;
  }

  return m;
}

int main()
{
  //std::uint64_t n, m;
  //std::cin >> n >> m;
  // std::cout << get_fibonaccihuge( n, m ) << '\n';

  //auto c = pisano_period( n, m );
  //auto r = n % c;
  std::uint64_t m = 30524;
  auto r_fib = calc_fib( 22318 );
  auto rr = r_fib % m;

  return 0;
}
