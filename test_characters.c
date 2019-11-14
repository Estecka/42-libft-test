/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_characters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:11:05 by abaur             #+#    #+#             */
/*   Updated: 2019/11/14 12:13:05 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

#include "../libft.h"
#include <stdio.h>

static void TestIs(int (*ft)(int), int (*lib)(int), char *title){
	printf("\n\n\t%s\n", title);
	for (unsigned char c=0; c<=(unsigned char)(c+1); c++) {
		int expected = lib(c);
		int returned = ft(c);

		if (expected != returned)
			printf("[ 0x%x ][ %c ] Expected 0x%x %c, got 0x%d %c\n", c, c, expected, expected, returned, returned);
	}
}

void TestCharacters(){
	TestIs(ft_isalpha, isalpha, "ft_isaplha");
	TestIs(ft_isdigit, isdigit, "ft_isdigit");
	TestIs(ft_isalnum, isalnum, "ft_isalnum");
	TestIs(ft_isascii, isascii, "ft_isascii");
	TestIs(ft_isprint, isprint, "ft_isprint");
	TestIs(ft_toupper, toupper, "ft_toupper");
	TestIs(ft_tolower, tolower, "ft_tolower");
}
