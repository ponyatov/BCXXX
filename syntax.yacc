%{
#include "BCX.hpp"
%}

%defines %union {	// === yylval structure definition ===
	byte opcode;	// opcodes for VM commands
	string *str;	// string value for label, variable names etc 
}

%token <opcode> CMD0 CMD1		/* commands		*/
%token dirGO					/* directives	*/
%token <str> ID					/* label id		*/
%token COLON					/* :			*/

%%
REPL :
	| REPL CMD0		{ byteCompile($2); }					// no param command
	| REPL dirGO	{ VM(); }								// .go
	| REPL ID COLON	{ label($2); }							// label:
	| REPL CMD1 ID	{ byteCompile($2); labelCompile($3); }	// jmp label
	;
%%
