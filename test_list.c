/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:33:58 by abaur             #+#    #+#             */
/*   Updated: 2019/11/13 11:15:50 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

#include "../libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char data[] = "0123456789";

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
#endif
