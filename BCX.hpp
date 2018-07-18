#ifndef _H_BCX
#define _H_BCX

#include <iostream>
using namespace std;


extern int yylex();
extern int yylineno;
extern char* yytext;
#define C0(X) { yylval.cmd0 = X; return CMD0; }

extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_BCX
