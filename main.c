/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:06:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/20 10:44:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
