/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:21:55 by abaur             #+#    #+#             */
/*   Updated: 2019/11/18 17:31:13 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

static void PrintBuffer(const char* buffer, int size)
{
	for (int i=0; i<size; i++) {
		unsigned char c = buffer[i];
		if (isprint(c))
			printf("  %c ", c);
		else
			printf(" %02X ", c);
	}
}

static void ComparateBuffer(const void* expected, const void* returned, int size)
{
	char *src = (char*)expected;
	char *dst = (char*)returned;

	for (int i=0; i<size; i++)
	if (src[i] != dst[i]){
		printf("Difference found. \n Expected: ");
		PrintBuffer(src, size);
		printf(" \n Returned: ");
		PrintBuffer(dst, size);
		printf(" \n");
		return;
	}
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

static void TestOneCcpy(const char* src, char c)
{
	int size = strlen(src);
	char* dst    = (char*)malloc(size + 10);
	char* dstexp = (char*)malloc(size);
	char* result    = NULL;
	char* resultexp = NULL;

	bzero(dst, size);
	resultexp = memccpy(dst, src, c, size);
	memcpy(dstexp, dst, size);

	bzero(dst, size + 10);
	result = ft_memccpy(dst, src, c, size);

	ComparateBuffer(dstexp, dst, size);
	if (CheckUntouched(&dst[size], 10, 0))
		printf("[%c] Buffer overflow", c);
	if (result != resultexp)
		printf("[%c] Unexpected return value. \n Expected: %p \n Returned: %p \n", c, resultexp, result);

	free (dst);
}
static void TestCcpy()
{
	printf("\n\n\tft_memccpy\n");

	TestOneCcpy("", 'N');
	TestOneCcpy("Banana", 'A');
	TestOneCcpy("0123456789", '5');
	TestOneCcpy("abcdefghij", '9');
	TestOneCcpy("0101010101", '\0');
}

static void TestOneMemcmp(const void* s1, const void* s2, size_t n)
{
	int	expected =    memcmp(s1, s2, n);
	int	returned = ft_memcmp(s1, s2, n);

	if (expected != returned)
		printf("`%s` vs `%s` \n Expected: %d \n Returned: %d \n", s1, s2, expected, returned);
}
static void TestMemcmp()
{
	printf("\n\n\tft_memcmp\n");

	TestOneMemcmp("Je", "Je", 3);
	TestOneMemcmp("suis", "suis", 4);
	TestOneMemcmp("une bulle", "ton pe1re", 10);
	TestOneMemcmp("frere", "", 0);
	TestOneMemcmp("", "\0naaaonn!", 1);
}

static void TestOneMemchr(const char* src, char c, int len)
{
	void* expected =    memchr(src, c, len);
	void* returned = ft_memchr(src, c, len);

	if (expected != returned)
		printf("`%c` in `%s` \n Expected: %p \n Returned: %p \n", c, src, expected, returned);
}
static void TestMemchr()
{
	printf("\n\n\tft_memchr\n");

	TestOneMemchr("Je suis une bulle", 'l', 17);
	TestOneMemchr("aaa eee iii ooo uuu", 'i', 5);
	TestOneMemchr("", 'v', 0);
}

void TestMemory()
{
	TestBzero();
	TestMemset();
	TestMemcpy();
	TestCcpy();
	TestMemcmp();
	TestMemchr();
}
