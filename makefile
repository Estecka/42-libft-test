SRCS	= main.c ../*.c

test: 
	gcc ${SRCS} -Wall -Wextra

autorun: test
	./a.out

clean:
	rm -f ${OBJS}
	rm -f *.gch

fclean: clean
	rm -f a.out

re: fclean test

.PHONY: all clean fclean re test autorun
