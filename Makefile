.PHONY: all
all: doxy empty.log 

empty.log: empty.src ./BCX.exe
	./BCX.exe < ./BCX.exe > $@ && tail $(TAIL) $@
	
C = BCX.cpp ypp.tab.cpp lex.yy.c
H = BCX.hpp ypp.tab.hpp

#CXXFLAGS += -std=gnu++11
./BCX.exe: $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
	
ypp.tab.cpp: syntax.yacc
	bison -o $@ $<

lex.yy.c: lexer.lex
	flex -o $@ $<

.PHONY: doxy
doxy:
	rm -rf docs ; doxygen doxy.gen 1> /dev/null
