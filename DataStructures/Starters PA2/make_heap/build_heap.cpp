#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (size_t i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  int LeftChild( size_t i ) { return 2 * i + 1; }

  int RightChild( size_t i ) { return 2 * i + 2; }

  int Parent( size_t i )
  {
    if ( i == 0 )
      return 0;
    else
      return ( i - 1 ) / 2;
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void SiftUp(size_t i) {
    int c = i;
    while ( c > 0 && data_[ Parent( c ) ] > data_[ c ] )
    {
      swaps_.push_back( make_pair( Parent( c ), c ) );
      swap( data_[ Parent( c ) ], data_[ c ] );
      c = Parent( c );
    }
  }
  void GenerateSwaps() {
    swaps_.clear();
    size_t n = data_.size();
    size_t mid = n / 2;
    for ( size_t i = n - 1; i != mid; --i)
    {
      SiftUp( i );
    }

    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    /* for (size_t i = 0; i < data_.size(); ++i) */
    /*   for (size_t j = i + 1; j < data_.size(); ++j) { */
    /*     if (data_[i] > data_[j]) { */
    /*       swap(data_[i], data_[j]); */
    /*       swaps_.push_back(make_pair(i, j)); */
    /*     } */
    /*   } */
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
