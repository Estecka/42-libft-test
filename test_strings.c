/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:18:50 by abaur             #+#    #+#             */
/*   Updated: 2019/11/14 15:43:45 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

static int Comparate(const char *src, const char *dst)
{
	int i = 0;
	do {
		if (src[i] == '\0' && dst[i] != '\0')
			printf("Not Null Terminated.\n");
		else if (src[i] != dst[i]){
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

void TestStrings()
{
	TestDup();
	TestSubs();
}

