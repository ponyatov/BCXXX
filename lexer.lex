%{
#include "BCX.hpp"
%}

										/* avoid yywrap() function */
%option noyywrap
										/* automatically count line number */
%option yylineno

%%
\#[^\n]*			{}						// line comments

nop					C0(OP_NOP)
halt				C0(OP_HALT)

.go					{ VM(); }				// start VM

[ \t\r\n]+			{}						// drop spaces
.					{ yyerror("lexer"); }	// syntax error on undetected char
