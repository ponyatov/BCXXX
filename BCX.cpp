/// @file
/// @brief Virtual Machine C++ source code

#include "BCX.hpp"

/// @defgroup startup System startup

/// @brief compiler and VM start here
/// @ingroup startup
int main() { return yyparse(); }

/// error message template
#define YYERR "\n\n" << yylineno << ':' << msg << "[" << yytext << "]\n\n"
void yyerror(const char* msg) { cout << YYERR; cerr << YYERR; exit(-1); }
