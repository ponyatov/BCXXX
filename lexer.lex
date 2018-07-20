%{
#include "BCX.hpp"
%}

										/* avoid yywrap() function */
%option noyywrap
										/* automatically count line number */
%option yylineno

										/* regexp substitutions */
az  [_A-Za-z]
azn [_A-Za-z0-9]

%%
\#[^\n]*			{}						// line comments

nop					C0(OP_NOP)
halt				C0(OP_HALT)

jmp					C1(OP_JMP)
\?jmp				C1(OP_qJMP)
call				C1(OP_CALL)
ret					C0(OP_RET)

\:					{ return COLON; }
{az}{azn}*			{ yylval.str = new string(yytext); return ID; }

.go					{ return dirGO; }		// .go directive: start VM

[ \t\r\n]+			{}						// drop spaces
.					{ yyerror("lexer"); }	// syntax error on undetected char
%%
