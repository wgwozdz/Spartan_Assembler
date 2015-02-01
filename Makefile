assember: assembler.tab.cpp assembler.tab.h lex.yy.cpp Program.cpp Location.cpp Util.cpp Program.h Location.h Util.h
	clang++ -std=c++11 -stdlib=libc++ -Wno-write-strings assembler.tab.cpp lex.yy.cpp Program.cpp Location.cpp Util.cpp -o assembler

assembler.tab.cpp: assembler.y
	bison -d assembler.y
	mv assembler.tab.c assembler.tab.cpp

assembler.tab.h: assembler.y
	bison -d assembler.y

lex.yy.cpp: assembler.l assembler.tab.h
	flex assembler.l
	mv lex.yy.c lex.yy.cpp

clean:
	rm -f *.tab.* lex.yy.cpp assembler
