/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_integers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:26:33 by abaur             #+#    #+#             */
/*   Updated: 2019/11/18 15:26:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <stdlib.h>
#include <stdio.h>

char* errorHeader = NULL;

static void ComparateInt(int expected, int returned)
{
	if (expected != returned){
		printf("%s\n", errorHeader ? errorHeader : "Difference found");
		printf(" Expected: %d \n Returned: %d \n", expected, returned);
	}
}

static void TestAtoiOne(char *arg)
{
	errorHeader = arg;
	ComparateInt(atoi(arg), ft_atoi(arg));
}
static void TestAtoi()
{
	printf("\n\n\tft_atoi\n");

	TestAtoiOne("11");
	TestAtoiOne("-22");
	TestAtoiOne("- 33");
	TestAtoiOne(" -44");
	TestAtoiOne("++--55");
	TestAtoiOne("");
	TestAtoiOne("abc");
	TestAtoiOne("-def");
	TestAtoiOne("2147483647");
	TestAtoiOne("-2147483648");
	TestAtoiOne("  -2147483647a");
	TestAtoiOne("   ---2147483648b");
	TestAtoiOne("");
}

void TestIntegers()
{
	TestAtoi();
}
