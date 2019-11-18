SRCS	= *.c ../*.c

OBJS	= ${SRCS:.c=.o}

test: 
	gcc ${SRCS} -Wall -Wextra

autorun: test
	./a.out
	norminette ../*.c ../*.h

clean:
	rm -f ${OBJS}
	rm -f *.gch

fclean: clean
	rm -f a.out

re: fclean test

.PHONY: all clean fclean re test autorun
