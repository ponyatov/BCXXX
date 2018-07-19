.PHONY: all
all: empty.log
#doxy 

empty.log: empty.src ./BCX.exe
	./BCX.exe < $< > $@ && tail $(TAIL) $@
	
C = BCX.cpp ypp.tab.cpp lexer.cpp
H = BCX.hpp ypp.tab.hpp

CXXFLAGS += $(TRACE)
#CXXFLAGS += -std=gnu++11
./BCX.exe: $(C) $(H) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C)
	
ypp.tab.cpp: syntax.yacc
	bison -o $@ $<

lexer.cpp: lexer.lex
	flex -o $@ $<

.PHONY: doxy
doxy:
	rm -rf docs ; doxygen doxy.gen 1> /dev/null
