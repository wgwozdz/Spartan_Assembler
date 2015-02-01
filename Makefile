assember: Assembler.tab.cpp Assembler.tab.h lex.yy.cpp Program.cpp Location.cpp Util.cpp Program.h Location.h Util.h
	clang++ -std=c++11 -stdlib=libc++ -Wno-write-strings Assembler.tab.cpp lex.yy.cpp Program.cpp Location.cpp Util.cpp -o assembler

Assembler.tab.cpp: Assembler.y
	bison -d Assembler.y
	mv Assembler.tab.c Assembler.tab.cpp

Assembler.tab.h: Assembler.y
	bison -d Assembler.y

lex.yy.cpp: Assembler.l Assembler.tab.h
	flex Assembler.l
	mv lex.yy.c lex.yy.cpp

clean:
	rm -f *.tab.* lex.yy.cpp assembler
