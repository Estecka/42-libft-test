/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:06:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/13 11:12:58 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BONUS = 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../libft.h"

#ifdef BONUS
#include "test_list.c"
#endif

int	main()
{

	// Bonus
	#ifdef BONUS
	TestNew();
	TestSize();
	TestAddFront();
	TestAddBack();
	#endif
}
