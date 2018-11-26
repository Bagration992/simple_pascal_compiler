CC=clang++
CPPFLAGS=-Wno-unknown-warning-option $(shell llvm-config --cxxflags)
LDFLAGS=$(shell llvm-config --ldflags --libs --system-libs)

pascal: lex.yy.o parser.tab.o ast.o izraz.o
	$(CC) -o $@ $^ $(LDFLAGS)
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CPPFLAGS) -Wno-sign-compare -c -o $@ $<
lex.yy.c: lexer.lex ast.hpp
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
ast.o: ast.cpp ast.hpp izraz.hpp
	$(CC) -Wno-unknown-warning-option $(CPPFLAGS) -c -o $@ $<
izraz.o: izraz.cpp izraz.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean


clean:
	rm -f *~ *.o pascal *.output *tab* lex.yy.c