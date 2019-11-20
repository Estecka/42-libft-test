BONUS	= 1;



test: test.out
test.out: libft
ifeq ($(BONUS), 0)
	gcc *.c -o test.out -Wall -Wextra -L ../ -lft
else
	gcc *.c -o test.out -Wall -Wextra -L ../ -lft -D BONUS
endif


libft: ../libft.a
../libft.a:
ifeq ($(BONUS), 0)
	make -C ../
else
	make bonus -C ../
endif


autorun: fclean test
	norminette ../*.c ../*.h
	./test.out


all: libft test

clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f test.out
	make fclean -C ../

re: fclean test

.PHONY: all clean fclean re autorun libft test
