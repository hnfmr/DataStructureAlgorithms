#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cin;

template < size_t N, size_t L = 16 > class Map {
public:
  Map() : data_( N, nullptr ) {}
  ~Map()
  {
    for ( size_t i = 0; i < data_.size(); ++i ) {
      if ( auto addr = data_[i] ) delete[] addr;
    }
  }

  void insert( int key, const std::string& value )
  {
    char* b = data_[key];

    if ( b == nullptr ) {
      b = new char[L];
    }

    std::memset( b, '\0', L );
    for ( size_t i = 0; i < value.size(); ++i ) {
      b[i] = value[i];
    }

    data_[key] = b;
  }

  std::string find( int key )
  {
    char* b = data_[key];
    if ( b == nullptr )
      return "not found";
    else
      return std::string( b );
  }

  void del( int key )
  {
    char* b = data_[key];
    if ( b != nullptr ) {
      delete[] b;
      b = nullptr;
    }
    data_[key] = nullptr;
  }
  // void insert( int key, const std::string& value ) { data_[key] = value; }

private:
  std::vector< char* > data_;
};

struct Query {
  string type, name;
  int number;
};

vector< Query > read_queries()
{
  int n;
  cin >> n;
  vector< Query > queries( n );
  for ( int i = 0; i < n; ++i ) {
    cin >> queries[i].type;
    if ( queries[i].type == "add" )
      cin >> queries[i].number >> queries[i].name;
    else
      cin >> queries[i].number;
  }
  return queries;
}

void write_responses( const vector< string >& result )
{
  for ( size_t i = 0; i < result.size(); ++i ) std::cout << result[i] << "\n";
}

vector< string > p_queries( const vector< Query >& qs )
{
  vector< string > result;
  std::map< int, std::string > m;
  for ( size_t i = 0; i < qs.size(); ++i ) {
    const auto& q = qs[i];
    if ( q.type == "add" ) {
      m[q.number] = q.name;
    }
    else if ( q.type == "del" ) {
      m.erase( q.number );
    }
    else {
      if ( m.find( q.number ) != m.end() ) {
        result.push_back( m[q.number] );
      }
      else {
        result.emplace_back( "not found" );
      }
    }
  }
  return result;
}
vector< string > process_queries( const vector< Query >& queries )
{
  vector< string > result;
  // Keep list of all existing (i.e. not deleted yet) contacts.
  // vector< Query > contacts;
  Map< 10000000 > m;
  for ( size_t i = 0; i < queries.size(); ++i ) {
    const auto& q = queries[i];
    if ( q.type == "add" ) {
      m.insert( q.number, q.name );
    }
    else if ( q.type == "del" ) {
      m.del( q.number );
    }
    else {
      result.push_back( m.find( q.number ) );
    }
  }
  return result;
}

int main()
{
  // write_responses(p_queries(read_queries()));

  write_responses( process_queries( read_queries() ) );
  return 0;
}
