%{
#include "BCX.hpp"
%}

%defines %union { uint8_t cmd0; }

%token <cmd0> CMD0
%token dirGO

%%
REPL :
	| REPL CMD0		{ M[Cp++] = $2; }
	| REPL dirGO	{ VM(); }
	;
%%