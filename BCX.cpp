/// @file
/// @brief Virtual Machine C++ source code

#include "BCX.hpp"

/// @defgroup startup System startup

/// @brief compiler and VM start here
/// @ingroup startup
int main(int argc, char *argv[]) {
	#ifdef TRACE
	for (int i=0;i<argc;i++) printf("argv[%i] = %s\n",i,argv[i]);
	#endif
	return yyparse();
}

/// error message template
#define YYERR "\n\n" << yylineno << ':' << msg << "[" << yytext << "]\n\n"
void yyerror(const char* msg) { cout << YYERR; cerr << YYERR; exit(-1); }

uint8_t M[Msz];

uint32_t Ip =0;
uint32_t Cp =0;

uint8_t op =0;

void VM() {
	for (;;) {								// infty loop
		op = M[Ip++];						// fetch next command opcode
		#ifdef TRACE
		printf("\n%.8X: %.2X\t",Ip-1,op);	// print trace header addr: opcode
		#endif
		switch (op) {						// decode & execute command
			case OP_NOP:	NOP();	break;
			case OP_HALT:	HALT();	break;
											// error on unknown command opcode
			default:
				fprintf(stderr,"\n\n unknown command opcode: %.2X \n\n",op);
				abort();
		}
	}
}

void NOP(void) {
	#ifdef TRACE
	printf("nop");
	#endif
}

void HALT(void) {
	#ifdef TRACE
	printf("halt\n\n");
	#endif
	exit(0);
}
