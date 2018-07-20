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
#define YYERR "\n\n" << yylineno << ": " << msg << " [" << yytext << "]\n\n"
void yyerror(const char* msg) { cout << YYERR; cerr << YYERR; exit(-1); }

uint8_t		M[Msz];		// memory

uint32_t	Ip =0;		// instruction pointer
uint32_t	Cp =0;		// compiler pointer

uint8_t		op =0;		// opcode

void VM() {
	if (undef.size()) { DUMP(); yyerror("unresolved labels found"); }
	#ifdef TRACE
	DUMP();
	#endif
	for (;;) {								// infty loop
		op = M[Ip++];						// fetch next command opcode
		#ifdef TRACE
		printf("\n%.8X: %.2X\t",Ip-1,op);	// print trace header addr: opcode
		#endif
		switch (op) {						// decode & execute command

			case OP_NOP:	NOP();	break;
			case OP_HALT:	HALT();	break;

			case OP_JMP:	JMP();	break;
//			case OP_qJMP:	qJMP();	break;
//			case OP_CALL:	CALL();	break;
//			case OP_RET:	RET();	break;

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

void JMP(void) {
	addr target = cellGet(Ip);
	Ip += sizeof(cell);				// skip jmp param
	#ifdef TRACE
	printf("jmp\t\t%.8X",target);
	#endif
}

void DUMP(void) {
	printf("\n");
	for (int i=0;i<Cp;i++) {
		if (i % 0x10 == 0) printf("\n%.8X: ",i);
		else if (i % 0x08 == 0) printf(" ");
		printf("%.2X ",M[i]);
	}
	printf("\n\nKNOWN\n");
	for (auto it=known.begin(),e=known.end(); it!=e; it++)
		printf("\t%.8X: %s\n",it->second,it->first.c_str());
	printf("\nUNDEF\n");
	for (auto it=undef.begin(),e=undef.end(); it!=e; it++)
		printf("\t%s:\n",it->first.c_str());
	fflush(stdout);
}

void byteCompile(byte B) {
	M[Cp++] = B;
}

cell cellGet(cell C) {
	#if defined(__i386__) | defined(__amd64__)
	return *((cell*)&M[C]);
	#else
	#error CPU
	//	return (M[C+0]<< 0|M[C+1]<< 8|M[C+2]<<16|M[C+3]<<24);
	#endif
}

void cellSet(addr A, cell C) {
	#if defined(__i386__) | defined(__amd64__)
		*((cell*)&M[A]) = C;
	#else
	#error CPU
	#endif
}

void cellCompile(cell C) {
	#if defined(__i386__) | defined(__amd64__)
	*((cell*)&M[Cp]) = C; Cp += sizeof(cell);
	#else
	#error CPU
	//	byteCompile(C>> 0); byteCompile(C>> 8);
	//	byteCompile(C>>16); byteCompile(C>>24);
	#endif
}

												// ============= SYMBOL TABLE:
map<string,addr>		known;					// known labels
map<string,addrvector*>	undef;					// forward reference table

void label(string *name) {
	known[*name] = Cp;							// register in known symtable
	auto record	= undef.find(*name);			// search undefined by name
	if (record != undef.end()) {				// if exists in undef
		auto first = record->second->begin();
		auto end   = record->second->end();
		for (auto it = first; it != end; it++)	// iterate over undef[name]
			cellSet(*it,Cp);					// patch all saved addresses
		undef.erase(record);					// remove the whole record
		cout << endl;
	}
}

void labelCompile(string* name) {
	if (known.find(*name) != known.end())	// if exists in known
		cellCompile(known[*name]);
	else {
		auto record = undef.find(*name);	// find undef by name
		auto end    = undef.end();
		if (record != end) {				// has existing record
			cout << ">" << Cp << endl;
			record->second->push_back(Cp);	// append current compiler pointer
		} else {
			undef[*name] = new addrvector();// create new vector with Cp
			undef[*name]->push_back(Cp);
		}
		cellCompile(-1);					// compile stub to command
	}
}
