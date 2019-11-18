/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:21:55 by abaur             #+#    #+#             */
/*   Updated: 2019/11/18 14:22:47 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void ComparateBuffer(void* expected,  void* returned, int size)
{
	char *src = (char*)expected;
	char *dst = (char*)returned;

	for (int i=0; i<size; i++)
	if (src[i] != dst[i])
		return (void)printf("Difference found. \n Expected: %.*s \n Returned: %.*s \n", size, src, size, dst);
}

static void TestBzeroOne(int n)
{
	char* buffer = (char*)malloc(n+8);

	memset(buffer, ~0, n+8);
	ft_bzero(buffer, n);

	for (int i=0; i<n; i++)
		if (buffer[i])
			printf("[%d][%d] Not zero: 0x%0x\n", n, i, buffer[i]);

	for (int i=n; i<n+8; i++)
		if (buffer[i] != ~0)
			printf("[%d][%d] Overflowing buffer (0x%x) \n", n, i, buffer[i]);

	free(buffer);
}
static void TestBzero()
{
	printf("\n\n\tft_bzero\n");

	TestBzeroOne( 10);
	TestBzeroOne(  0);
}
static void TestOneMemset(char c, int n)
{
	char* buffer = (char*)malloc(n+10);

	bzero(buffer, n+10);
	ft_memset(buffer, c, n);

	for (int i=0; i<n; i++)
		if (buffer[i] != c)
			printf("[%x-%d][%d] Unexpected Character: %x \n", c, n, i, buffer[i]);
	for (int i=n; i<n+10; i++)
		if (buffer[i])
			printf("[%x-%d][%d] Overflowing buffer (0x%x) \n", c, n, i, buffer[i]);

	free(buffer);
}
static void TestMemset()
{
	printf("\n\n\tft_memset\n");

	TestOneMemset('\0', 10);
	TestOneMemset('a', 5);
	TestOneMemset('\n', 8);
	TestOneMemset('$', 12);
}

void TestMemory()
{
	TestBzero();
	TestMemset();
}
