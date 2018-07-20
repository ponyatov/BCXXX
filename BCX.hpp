/// @file
/// @brief Virtual Machine C++ headers

#ifndef _H_BCX
#define _H_BCX

#include <iostream>
#include <map>
#include <vector>
using namespace std;

/// @defgroup vm Virtual Machine
/// @{

/// @defgroup types types
/// @{

/// byte
typedef uint8_t byte;

/// narrow 16-bit integer
typedef uint16_t narrow;

/// 32/16-bit VM machine word
typedef uint32_t cell;

/// address in virtual memory
typedef cell addr;

/// @}

/// @defgroup config configuration
/// @{

/// program/data memory size
#define Msz 0x1000

/// @}

/// flat memory for program & data
extern byte M[Msz];

/// instruction pointer
extern addr Ip;

/// opcode of current command
extern byte op;

/// Virtual Machine loop (bytecode interpreter)
extern void VM(void);

/// @defgroup cmd commands
/// @{

/// `NOP` : NO Operation , do nothing
extern void NOP(void);
/// `HALT` : stop the system
extern void HALT(void);

/// `JMP` : unconditional jump
extern void JMP(void);
/// `?JMP ( false -- )` : conditional jump if FALSE on stack
extern void qJMP(void);
/// `CALL` : nested call
extern void CALL(void);
/// `RET` : return from nested call
extern void RET(void);

/// `LIT ( -- cell )` : push constant on stack
extern void LIT(void);

/// `DUMP` : dump memory
extern void DUMP(void);

/// @defgroup op opcodes
/// @{

/// @ref NOP
#define OP_NOP		0x00

/// @ref HALT
#define OP_HALT		0xFF

/// @ref JMP
#define OP_JMP		0x01
/// @ref qJMP
#define OP_qJMP		0x02
/// @ref CALL
#define OP_CALL		0x03
/// @ref RET
#define OP_RET		0x04

/// @ref LIT
#define OP_LIT		0x05

/// @}

/// @}

/// @}

/// @defgroup compiler Compiler
/// @{

/// compiler pointer
extern addr Cp;

/// get cell from memory
/// @param[in] A address in VM memory
extern cell cellGet(addr A);

/// set cell in memory
/// @param[in] A address in VM memory
/// @param[in] C cell to be set
extern void cellSet(addr A, cell C);

/// compile byte
/// @param[in] B to be compiled
extern void byteCompile(byte B);

/// compile cell == VM machine word
/// @param[in] C 32-/16- bit integer
extern void cellCompile(cell C);

/// compile label by its name
/// @param[in] L label name to be lookup in symbol table
extern void labelCompile(string* L);

/// @defgroup symtable symbol table
/// @{

/// list of @ref addr esses
typedef std::vector<addr> addrvector;
/// known assembly labels
extern map<string,addr> known;
/// forward references to unknown labels
extern map<string,addrvector*> undef;

/// @}

/// process label in source code
extern void label(string *name);

/// @defgroup parser syntax parser interface
/// @{

/// @name lexer interface [lex/flex]
/// @{

/// get next token from source code stream
extern int yylex();
/// current line number @see lexer `%option yylineno`
extern int yylineno;
/// current lexeme matched
extern char* yytext;

/// @}

/// @name token macro
/// @{

/// `CMD0` zero parameters command
#define C0(X) { yylval.opcode = X; return CMD0; }

/// `CMD1` single parameter command
#define C1(X) { yylval.opcode = X; return CMD1; }

/// @}

/// @name parser interface [yacc/bison]
/// @{

extern int yyparse();

/// syntax error callback
extern void yyerror(const char*);

// tokens definitions generated by yacc
#include "ypp.tab.hpp"

/// @}

/// @}

/// @}

#endif // _H_BCX

