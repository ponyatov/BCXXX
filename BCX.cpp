#include "BCX.hpp"

int main() { return yyparse(); }

#define YYERR "\n\n" << yylineno << ':' << msg << "[" << yytext << "]\n\n"
void yyerror(string msg) { cout << YYERR; cerr << YYERR; exit(-1); }
