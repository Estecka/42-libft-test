/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:18:50 by abaur             #+#    #+#             */
/*   Updated: 2019/11/15 17:49:18 by abaur            ###   ########.fr       */
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
	const char *found = src;
	while (*src == *dst){
		if (*src == 0){
			printf("Probably seeking out too far.\n");
			printf("Found: %s \n", found);
			return;
		}
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

static void TestLen()
{
	char *bneh[4] = {"Bulle", "Balle\0hihi", "Gneh", ""};

	for (int i=0; i<4; i++) {
		int got = ft_strlen(bneh[i]);
		int exp = strlen(bneh[i]);
		if (got != exp)
			printf("%s \n Expected: %d \n Returned: %d \n", bneh[i], exp, got);
	}
}

static void TestlCpyOne(char *src, int l, char *expected)
{
	char *buffer = malloc(l+1);
	memset(buffer, ~0, l+1);

	ft_strlcpy(buffer, src, l);
	int size = Comparate(expected, buffer);
	if (size > 0)
		Discomparate(&src[size], &buffer[size]);
	free(buffer);
}
static void TestlCpy()
{
	printf("\n\n\tft_strlcpy\n");
	TestlCpyOne("Banana\0split", 9, "Banana");
	TestlCpyOne("Benene", 7, "Benene");
	TestlCpyOne("Binini", 6, "Binin\0");
	TestlCpyOne("Bonono", 4, "Bon");
	TestlCpyOne("\0Bununu", 6, "\0");
}

static void TestlCatOne(const char *src1, const char *src2, int l, const char *expected)
{
	char *buffer = malloc(l+1);
	memset(buffer, ~0, l+1);
	strcpy(buffer, src1);

	ft_strlcat(buffer, src2, l);
	int size = Comparate(expected, buffer);
	if (size>0)
		Discomparate(&expected[size], &buffer[size]);

	free(buffer);
}
static void TestlCat()
{
	printf("\n\n\tft_strlcat\n");

	TestlCatOne("Banana", "Split", 6+5+1, "BananaSplit");
	TestlCatOne("Beep", "\0Boop",  5+6+1, "Beep");
	TestlCatOne("\0Beep", "Boop",  6+5+1, "Boop");
	TestlCatOne("\0Beep", "\0Boop",6+6+1, "\0");
}

void TestnCmpOne(const char *src1, const char *src2, size_t n)
{
	int result = ft_strncmp(src1, src2, n);
	int expect =    strncmp(src1, src2, n);

	if (result != expect)
		printf("\"%s\" vs \"%s\" len %zu \n Expected: %d \n Returned: %d \n", src1, src2, n, expect, result);
}
void TestnCmp()
{
	printf("\n\n\tft_stncmp\n");

	TestnCmpOne("Bneh\0aaaaaa", "Bneh\0bbbbbb", 10);
	TestnCmpOne("Bnehaaaaaa", "Bnehbbbbbb", 4);
	TestnCmpOne("Pin", "Pon", 4);
	TestnCmpOne("", "", 4);
	TestnCmpOne("Beep", "", 0);
	TestnCmpOne("Beep", "", 2);
}

void TestChrOne(char *(*ft_)(const char*,int), char*(*lib)(const char*,int), const char *s, int c)
{
	char *exp = lib(s, c);
	char *got = ft_(s, c);

	if (exp != got)
		printf("%c in %s \n Expected: %s @\t%p \n Returned: %s @\t%p \n", c, s, exp, exp, got, got);
}
void TestChr()
{
	printf("\n\n\tft_strchr\n");
	TestChrOne(ft_strchr, strchr, "Banana", 'a');
	TestChrOne(ft_strchr, strchr, "Banana", 'n');
	TestChrOne(ft_strchr, strchr, "Banana", 'B');
	TestChrOne(ft_strchr, strchr, "Banana", '-');

	printf("\n\n\tft_strrchr\n");
	TestChrOne(ft_strrchr, strrchr, "Banana", 'a');
	TestChrOne(ft_strrchr, strrchr, "Banana", 'n');
	TestChrOne(ft_strrchr, strrchr, "Banana", 'B');
	TestChrOne(ft_strrchr, strrchr, "Banana", '-');
}

void TestStrnstrOne(const char *needle, const char *haystack, size_t len)
{
	char *exp =    strnstr(needle, haystack, len);
	char *got = ft_strnstr(needle, haystack, len);

	if (exp != got)
		printf("%s in %s \n Expected: %s \t @ %p \n Returned: %s \t @ %p \n", needle, haystack, exp, exp, got, got);
}
void TestStrnstr()
{
	printf("\n\n\tft_strnstr\n");

	TestStrnstrOne("BananananaSplit", "nana", 10);
	TestStrnstrOne("Bananano", "nano", 10);
	TestStrnstrOne("Bananano", "nano", 3);
	TestStrnstrOne("Bananano", "N/A", 100);
	TestStrnstrOne("Bananano", "", 0);
}

void TestStrings()
{
	TestDup();
	TestSubs();
	TestJoin();
	TestTrim();
	TestSplit();
	TestMapi();
	TestLen();
	TestlCpy();
	TestlCat();
	TestnCmp();
	TestChr();
	TestStrnstr();
}

