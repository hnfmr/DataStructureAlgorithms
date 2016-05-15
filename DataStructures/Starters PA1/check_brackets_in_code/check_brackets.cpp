#include <iostream>
#include <stack>
#include <string>

struct Bracket
{
  Bracket( int type, int position ) : type( type ), position( position ) {}

  bool Matchc( char c )
  {
    if ( type == '[' && c == ']' )
      return true;
    if ( type == '{' && c == '}' )
      return true;
    if ( type == '(' && c == ')' )
      return true;
    return false;
  }

  char type;
  int position;
};


int main()
{
  std::string text;
  getline( std::cin, text );

  std::stack< Bracket > opening_brackets_stack;

  bool exit = false;
  for ( size_t position = 0; position < text.length(); ++position )
  {
    char next = text[ position ];

    if ( next == '(' || next == '[' || next == '{' )
    {
      opening_brackets_stack.push( Bracket( next, position ) );
      // Process opening bracket, write your code here
    }

    if ( next == ')' || next == ']' || next == '}' )
    {
      if (!opening_brackets_stack.empty()) {
        auto left = opening_brackets_stack.top();
        if (!left.Matchc(next)) {
          std::cout << position+1 << "\n";
          exit = true;
          break;
        }
        else {
          opening_brackets_stack.pop();
        }
      }
      else {
        std::cout << position+1 << "\n";
        exit = true;
        break;
      }
      
      // Process closing bracket, write your code here
    }
  }

  // Printing answer, write your code here
  if (opening_brackets_stack.empty() && !exit) {
    std::cout << "Success\n";
  }
  else if (!exit) {
    auto left = opening_brackets_stack.top();
    std::cout << left.position+1 << "\n";
  }
  return 0;
}
