/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:21:55 by abaur             #+#    #+#             */
/*   Updated: 2019/11/18 15:30:29 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <string.h>
#include <stdio.h>

static void ComparateBuffer(const void* expected, const void* returned, int size)
{
	char *src = (char*)expected;
	char *dst = (char*)returned;

	for (int i=0; i<size; i++)
	if (src[i] != dst[i])
		return (void)printf("Difference found. \n Expected: %.*s \n Returned: %.*s \n", size, src, size, dst);
}
static short CheckUntouched(char* buffer, int size, char content)
{
	for (int i=0; i<size; i++)
		if (buffer[i] != content)
			return 1;
	return 0;
}

static void TestBzeroOne(int n)
{
	char* buffer = (char*)malloc(n+8);

	memset(buffer, ~0, n+8);
	ft_bzero(buffer, n);

	for (int i=0; i<n; i++)
		if (buffer[i])
			printf("[%d][%d] Not zero: 0x%0x\n", n, i, buffer[i]);

	if (CheckUntouched(&buffer[n], 8, ~0))
		printf("[%d] Buffer overflow \n", n);

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
	if (CheckUntouched(&buffer[n], 10, 0))
		printf("[%x-%d] Buffer overflow \n", c, n);

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

static void TestOneCpy(const char* src)
{
	int size = strlen(src);
	char* dst = (char*)malloc(size + 10);

	bzero(dst, size + 10);
	ft_memcpy(dst, src, size);

	ComparateBuffer(src, dst, size);
	if (CheckUntouched(&dst[size], 10, 0))
		printf("Buffer overflow: %.*s \n", size, dst);

	free(dst);
}
static void TestMemcpy()
{
	printf("\n\n\tft_memcpy\n");

	TestOneCpy("");
	TestOneCpy("Je\0suis");
	TestOneCpy("ton\0peeeeere");
}

void TestMemory()
{
	TestBzero();
	TestMemset();
	TestMemcpy();
}
