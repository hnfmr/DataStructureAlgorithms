#include <cstdint>
#include <inttypes.h>
#include <iostream>
#include <stdio.h>

/*
 * ** Using documented GCC type unsigned __int128 instead of undocumented
 * ** obsolescent typedef name __uint128_t.  Works with GCC 4.7.1 but not
 * ** GCC 4.1.2 (but __uint128_t works with GCC 4.1.2) on Mac OS X 10.7.4.
 * */
typedef unsigned __int128 uint128_t;

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER( x ) #x
#define TO_STRING( x ) STRINGIZER( x )

static int print_u128_u( uint128_t u128 )
{
  int rc;
  if ( u128 > UINT64_MAX ) {
    uint128_t leading = u128 / P10_UINT64;
    uint64_t trailing = u128 % P10_UINT64;
    rc = print_u128_u( leading );
    rc += printf( "%." TO_STRING( E10_UINT64 ) PRIu64, trailing );
  }
  else {
    uint64_t u64 = u128;
    rc = printf( "%" PRIu64, u64 );
  }
  return rc;
}

uint128_t get_fibonaccihuge( uint128_t n, uint128_t m )
{
  // write your code here
  return 0;
}

uint128_t calc_fib( uint128_t n )
{
  if ( n <= 1 ) return n;
  uint128_t a = 0;
  uint128_t b = 1;

  uint128_t c = 0;
  for ( uint128_t i = 2; i <= n; ++i ) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}

uint128_t pisano_period( std::uint64_t n, std::uint64_t q )
{
  uint128_t a = 0;
  uint128_t b = 1;

  uint128_t c = 2;

  uint128_t m = 0;

  for ( uint128_t i = 2; i <= n * n - 1; ++i ) {
    c = a + b;
    m = i - 1;

    if ( b == 0 && c == 1 ) {
      break;
    }
    a = b % q;
    b = c % q;
  }

  return m;
}

int main()
{
  std::uint64_t n, m;
  std::cin >> n >> m;

  auto c = pisano_period( n, m );
  auto r = n % c;

  auto r_fib = calc_fib( r );

  auto rr = r_fib % m;

  print_u128_u( rr );
  std::cout << "\n";

  return 0;
}
