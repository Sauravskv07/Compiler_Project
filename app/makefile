pars : adt.o lexer.o hash_table.o parseTable.o parseRules.o parser_copy2.o \
       remove.o utils.o
	gcc -o pars driver_trial.c adt.o lexer.o hash_table.o parseTable.o parseRules.o parser_copy2.o remove.o utils.o -lm
	./pars

adt.o : adt.c adt.h
	gcc -c adt.c
lexer.o : lexer.c lexer.h
	gcc -c lexer.c
hash_table.o : hash_table.c hash_table.h
	gcc -c hash_table.c
parser_copy2.o : parser_copy2.c parser.h
	gcc -c parser_copy2.c
parseTable.o : parseTable.c parseTable.h
	gcc -c parseTable.c
parseRules.o : parseRules.c parseRules.h
	gcc -c parseRules.c
remove.o : remove.c
	gcc -c remove.c
utils.o : utils.c utils.h
	gcc -c utils.c
clean :
	rm pars adt.o hash_table.o parser_copy2.o parseRules.o remove.o utils.o

