/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:33:58 by abaur             #+#    #+#             */
/*   Updated: 2019/11/12 14:54:03 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>
#include <stdio.h>

void TestNew(){
	printf("\n	ft_lstnew\n");
	int size = sizeof(t_list);

	char *boop = "Boop !";
	t_list *elt = ft_lstnew(boop);
	char *neighbour = malloc(size);

	if (elt == NULL){
		printf("Return value is NULL");
		return;
	}

	if (elt->content != boop)
		printf("Unexpected content. \n Got: %lu \nExpected: %lu", elt->content, boop);

	char *buffer = (char*)elt;
	for  (int i=0; i<size; i++)
		neighbour[i] = ~0;
	for (int i=0; i<size; i++)
		buffer[i] = 0;
	for (int i=0; i<size; i++)
	if (neighbour[i] != ~0) {
		prinf("Buffer overflow at index %zu. Got %c.", i, neighbour[i]);
		break;
	}
}
