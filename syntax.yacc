%{
#include "BCX.hpp"
%}

%defines %union { uint8_t cmd0; }

%token <cmd0> CMD0
%%
REPL : | REPL CMD0 { cout << $2 << endl; };
%%