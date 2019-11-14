/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:06:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/14 15:11:52 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BONUS = 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../libft.h"

#include "test_characters.c"
#include "test_strings.c"

#ifdef BONUS
#include "test_list.c"
#endif

int	main()
{
	TestCharacters();
	TestStrings();

	// Bonus
	#ifdef BONUS
	TestNew();
	TestSize();
	TestAddFront();
	TestAddBack();
	TestIter();
	TestMap();
	TestDelone();
	TestClear();
	#endif
}
