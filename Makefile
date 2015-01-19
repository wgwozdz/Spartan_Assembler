assember: assembler.tab.c assembler.tab.h lex.yy.c Program.cpp Location.cpp
	clang++ -std=c++11 -stdlib=libc++ -Wno-write-strings assembler.tab.c lex.yy.c Program.cpp Location.cpp -o assembler

assembler.tab.c: assembler.y
	bison -d assembler.y

assembler.tab.h: assembler.y
	bison -d assembler.y

lex.yy.c: assembler.l assembler.tab.h
	flex assembler.l

clean:
	rm -f *.tab.* lex.yy.c assembler