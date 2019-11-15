/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:18:50 by abaur             #+#    #+#             */
/*   Updated: 2019/11/15 15:18:11 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <stdio.h>
#include <string.h>

static int Comparate(const char *src, const char *dst)
{
	if (!dst && src) {
		printf("Result is NULL. Expected: %s \n", src);
		return (0);
	}

	if (!src && dst){
		printf("Expected NULL string, got: %s", dst);
		return 0;
	}

	int i = 0;
	do {
		if (src[i] != dst[i]){
			printf("Difference found \n Expected: %s \n Returned: %s \n", src, dst);
			return (0);
		}
	}
	while (src[i++]);
	return i;
}
static void Discomparate(const char *src, const char *dst)
{
	while (*src == *dst){
		if (*src == 0)
			return (void)printf("Probably seeking out too far.");
		src++;
		dst++;
	}
}

static void TestDup()
{
	printf("\n\n\tft_strdup\n");
	char *src = "Je suis une bulle.\0";
	char *dst = ft_strdup(src);
	Comparate(src, dst);
}

static void TestSubOne(const char *src, int start, int len, const char *expected)
{
	int size;
	char *dst = ft_substr(src, start, len);
	size = Comparate(expected, dst);
	if (size > 0)
		Discomparate(&src[size + start], &dst[size]);
	free (dst);
}
static void TestSubs()
{
	printf("\n\n\tft_substr\n");
	char *src = "0123456789\0abcdef";

	TestSubOne(src, 0, 18, src);
	TestSubOne(src, 2, 4, "2345\0");
	TestSubOne(src, 10, 4, "\0");
}


static void TestJoinOne(const char *src1, const char *src2, const char *expected)
{
	char *dst = ft_strjoin(src1, src2);
	Comparate(expected, dst);
	if (dst)
		free(dst);
}
static void TestJoin()
{
	char *src1 = "01234\0";
	char *src2 = "56789\0";

	printf("\n\n\tft_strjoin\n");

	TestJoinOne(src1, src2, "0123456789\0");
	TestJoinOne(src1, "",   "01234\0");
	TestJoinOne("",   src2, "56789\0");
	TestJoinOne("",   "",   "\0");
}

static void TestTrimOne(char const *src, char const *set, char const *expected)
{
	char *dst = ft_strtrim(src, set);
	Comparate(dst, expected);
	if (dst)
		free(dst);
}
static void TestTrim()
{
	printf("\n\n\tft_strtrim\n");

	TestTrimOne("-+-+Be+ep+-+-", "+-*", "Be+ep");
	TestTrimOne("Boop+*+-+-+-+", "+-*", "Boop" );
	TestTrimOne("+-+*Bo*p",      "+-*", "Bo*p" );
}

static void TestSplitOne(const char *src, char c, char **expected)
{
	char **result = ft_split(src, c);

	if (!result){
		printf("NULL result. \n");
		return;
	}

	for (int i=0, j=0; expected[i] || result[j]; i++, j++){
		Comparate(expected[i], result[j]);
		if (!expected[i])
			i--;
		if (!result[j])
			j--;
	}

	for (char **cursor=result; *cursor; cursor++)
		free(*cursor);
	free(result);
}
static void TestSplit()
{
	char *src = "Je suis une bulle\0";

	char *solusp[5] = {"Je", "suis", "une", "bulle", NULL};
	char *solue [4] = {"J", " suis un", " bull", NULL};
	char *solul [3] = {"Je suis une bu", "e", NULL};

	printf("\n\n\tft_split\n");

	TestSplitOne(src, ' ', solusp);
	TestSplitOne(src, 'e', solue );
	TestSplitOne(src, 'l', solul );
}

static char _mapi(unsigned int i, char c)
{
	return (i%2) ? '0'+i : c;
}
static void TestMapiOne(const char *src, const char *expected)
{
	char *result = ft_strmapi(src, _mapi);
	Comparate(expected, result);
	if (result)
		free (result);
}
static void TestMapi()
{
	printf("\n\n\tft_strmapi\n");

	TestMapiOne("Megalodon", "M1g3l5d7n");
	TestMapiOne("", "");
	TestMapiOne("M", "M");
}

void TestStrings()
{
	TestDup();
	TestSubs();
	TestJoin();
	TestTrim();
	TestSplit();
	TestMapi();
}

