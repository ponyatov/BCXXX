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

uint8_t M[Msz];

uint32_t Ip =0;
uint32_t Cp =0;

uint8_t op =0;

void VM() {
	for (;;) {				// infty loop
		op = M[Ip++];		// fetch next command opcode
		switch (op) {
			case OP_NOP:	NOP();	break;
			case OP_HALT:	HALT();	break;
			default:
				fprintf(stderr,"\n\n unknown command opcode: %.2X \n\n",op);
				abort();
		}
	}
}

void NOP(void)	{}
void HALT(void)	{ exit(0); }

