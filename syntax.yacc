%{
#include "BCX.hpp"
%}

%defines %union {
	byte cmd0, cmd1;
	string *str;
	}

%token <cmd0> CMD0
%token <cmd1> CMD1
%token dirGO
%token <str> ID
%token COLON

%%
REPL :
	| REPL CMD0		{ byteCompile($2); }					// no param command
	| REPL dirGO	{ VM(); }								// .go
	| REPL ID COLON	{ label($2); }							// label:
	| REPL CMD1 ID	{ byteCompile($2); labelCompile($3); }	// jmp label
	;
%%
