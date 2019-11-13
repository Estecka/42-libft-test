/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:33:58 by abaur             #+#    #+#             */
/*   Updated: 2019/11/13 17:08:24 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

#include "../libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char data[] = "0123456789";
static char output[10];

void TestNew()
{
	printf("\n\n	ft_lstnew\n");
	int size = sizeof(t_list);

	char *boop = "Boop !";
	t_list *elt = ft_lstnew(boop);
	char *neighbour = malloc(size);

	if (elt == NULL)
		return (void)printf("Return value is NULL");

	if (elt->content != boop)
		printf("Unexpected content. \n Expected: %p \n Got: %p\n", boop, elt->content);
	if (elt->next != NULL)
		printf("Next element is not NULL. \n Got: %p \n", elt->next);

	char *buffer = (char*)elt;
	for  (int i=0; i<size; i++)
		neighbour[i] = ~0;
	for (int i=0; i<size; i++)
		buffer[i] = 0;
	for (int i=0; i<size; i++)
	if (neighbour[i] != ~0) {
		printf("Buffer overflow at index %d. Got %d Expected %d", i, (int)neighbour[i], (int)(char)~0);
		break;
	}

	free(neighbour);
	free(buffer);
}

void TestSize()
{
	t_list array[10];
	bzero(array, 10 * sizeof(t_list));

	for (int i=1; i<10; i++)
		array[i-1].next = &array[i];

	printf("\n\n	ft_lstsize\n");
	int size = ft_lstsize(array);
	if (size != 10)
		printf("Wrong result. \n Expected: 10 \n Got: %d \n", size);
	size = ft_lstsize(NULL);
	if (size != 0)
		printf("NULL lists not supported. \n Expected: 0 \n Got: %d \n", size);

	printf("\n\n	ft_lstlast\n");
	t_list *last = ft_lstlast(array);
	if (last != &array[9])
		printf("Wrong result. \n Expected: %p \n Got: %p \n", &array[9], last);
}

void TestAddFront()
{
	printf("\n\n	ft_lstadd_front\n");
	t_list	array[10];
	t_list	*result = NULL;

	// Initialize all desired elements
	bzero(array, 10 * sizeof(t_list));
	for (int i=0; i<10; i++)
		array[i].content = &data[i];

	// Chain them together
	for (int i=9; i>=0; i--){
		ft_lstadd_front(&result, &array[i]);
		if (!result){
			printf("[%d] Unexpected NULL return value.\n", i);
			result = &array[i];
		}
		else if (result != &array[i]){
			printf("[%d] Unexpected return value.\n Expected %p \n Got %p \n", i, &array[i], result);
		}
		else if (!result->content)
			printf("[%d] Unexpected NULL content\n", i);
		else if (result->content != &data[i])
			printf("[%d] Unexpected content. \n Expected: %p \n Got: %p\n", i, &data[i], result->content);
	}

	// Check the final list.
	t_list *cursor = result;
	for (int i=0; i<10; i++, cursor=cursor->next)
		if (!cursor || !cursor->content || cursor->content != &data[i]){
			printf("Unexpected final product. \n Expected: %s \n Got: ", data);
			while (result){
				printf("%c", *(char*)result->content);
				result = result->next;
			}
			printf("\n");
			break;
		}
}

void TestAddBack()
{
	printf("\n\n	ft_lstadd_back\n");
	t_list	array[10];
	t_list	*result = NULL;

	// Initialize all desired elements
	bzero(array, 10 * sizeof(t_list));
	for (int i=0; i<10; i++)
		array[i].content = &data[i];

	// Chain them together
	for (int i=0; i<10; i++){
		int start = i / 2;
		if (i > 0)
			result = &array[start];
		ft_lstadd_back(&result, &array[i]);
		if (!result){
			printf("[%d] Unexpected NULL return value.\n", i);
		}
		else if (result != &array[start]){
			printf("[%d] Unexpected return value.\n Expected %p \n Got %p \n", i, &array[i], result);
		}
		else if (!result->content)
			printf("[%d] Unexpected NULL content\n", i);
		else if (result->content != &data[start])
			printf("[%d] Unexpected content. \n Expected: %p \n Got: %p\n", i, &data[i], result->content);
	}

	// Check the final list.
	t_list *cursor = &array[0];
	for (int i=0; i<10; i++, cursor=cursor->next)
		if (!cursor || !cursor->content || cursor->content != &data[i]){
			printf("Unexpected final product. \n Expected: %s \n Got: ", data);
			while (result){
				printf("%c", *(char*)result->content);
				result = result->next;
			}
			printf("\n");
			break;
		}
}

static void _iterate(void *elt)
{
	char content = *(char*)elt;

	for (int i=0; i<10; i++)
	{
		if (!output[i]){
			if (content != i + '0')
				printf("[%d] Unexpected content: %c \n", i, content);
			output[i] = content;
			return;
		}
	}

	printf("Index out of range : %c \n", content);
}
static void _nulliter(void *arg)
{
	(void)arg;
	printf("Iterating over a null list.\n");
}
void TestIter()
{
	printf("\n\n	ft_lstiter\n");
	t_list array[10];
	bzero(array, 10 * sizeof(t_list));
	bzero(output, 10);

	for (int i=0; i<10; i++){
		array[i].content = &data[i];
		if (i > 0)
			array[i-1].next = &array[i];
	}

	ft_lstiter(array, _iterate);
	for (int i=0; i<10; i++)
	if (output[i] != data[i]) {
		printf("Unexpected final product \n Expected: %s \n Got: ", data);
		for (int j=0; j<10; j++)
			printf("%c", output[j]);
		printf(" \n");
		break;
	}

	ft_lstiter(NULL, _nulliter);
}

static void *_map(void *obj)
{
	char *content = (char*)obj;
	for (int i=0; i<10; i++)
		if (!output[i])
		{
			output[i] = 'a' + (*content) - '0';
			if (content != &data[i])
				printf("[0][%d] Unexpected content. \n Expected: %c @ %p \n Got: %c @ %p \n", i, data[i], &data[i], *content, content);
			return &output[i];
		}
	printf("Index out of range. (%c)\n", *content);
	return (NULL);
}
static void *_nullmap(void *arg)
{
	(void)arg;
	printf("Mapping over a NULL list\n");
	return NULL;
}
static void _noop (void* c) { (void)c; }
void TestMap()
{
	printf("\n\n	ft_lstmap\n");

	// Init dat all
	bzero(output, 10);

	t_list array[10];
	bzero(array, 10 * sizeof(t_list));
	for (int i=0; i<10; i++)
	{
		array[i].content = &data[i];
		if (i>0)
			array[i-1].next = &array[i];
	}

	// Ju-dee, do the thing
	t_list *result = ft_lstmap(array, _map, _noop);

	//Check the order of execution
	for (int i=0; i<10; i++)
	if (output[i] != 'a' + i)
	{
		printf("Unexpected order of execution. \n Expected: abcdefghij \n Got : ");
		for (int j=0; j<10; j++)
			printf("%c", output[j]);
		printf("\n");
		break;
	}

	// Check the order of chaining
	t_list *cursor = result;
	for (int i=0; cursor!=NULL; i++, cursor=cursor->next) {
		char *content = cursor->content;
		if (i >= 10)
			printf("[1][%d] Index out of range. (%c)", i, *content);
		else if (content != &output[i])
			printf("[1][%d] Unexpected content. \n Expected: %c @ %p \n Got: %c @ %p \n", i, output[i], &output[i], *content, content);
	}

	// free the bees
	cursor = result;
	while (cursor) {
		t_list *next = cursor->next;
		free(cursor);
		cursor = next;
	}

	//Null check
	result = ft_lstmap(NULL, _nullmap, _noop);
	if (result != NULL) {
		printf("NULL list yields result.");

		cursor = result;
		while (cursor) {
			t_list *next = cursor->next;
			free(cursor);
			cursor = next;
		}
	}
}

void _delone(void *obj)
{
	*(char*)obj = 0;
}
void TestDelone()
{
	t_list array[2];

	memset(output, ~0, 3);
	bzero(array, 2 * sizeof(t_list));
	for (int i=0; i<2; i++)
		array[i].content = &output[i+1];
	array[0].next = &array[1];

	t_list *target = (t_list*)malloc(sizeof(t_list));
	target->content = output;
	target->next = &array[0];

	printf ("\n\n\tft_lstdelone\n");
	ft_lstdelone(target, _delone);

	if (output[0] != 0)
		printf("Content not deleted.\n");
	if ((output[1] & output [2]) != ~0)
		printf("Excessive deletion.\n");

	if (array[0].next != &array[1])
		printf("Following element was unliked\n");
	if (array[0].content != &output[1]
	 || array[1].content != &output[2])
		printf("Following elements were messed with.\n");
}
#endif
