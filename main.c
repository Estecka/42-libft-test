/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:06:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/18 15:23:09 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BONUS = 1

#include "../libft.h"

void	TestCharacters();
void	TestStrings();
void	TestIntegers();
void	TestMemory();
#ifdef BONUS
void	TestList();
#endif

int	main()
{
	TestCharacters();
	TestStrings();
	TestIntegers();
	TestMemory();

	#ifdef BONUS
	TestList();
	#endif
}
