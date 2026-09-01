/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 17:41:40 by mhmichi           #+#    #+#             */
/*   Updated: 2026/08/31 21:02:46 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_errors_handler.h"
#include "ft_string.h"

void	free_double_pointer(void **p, unsigned int elements, unsigned int element_size)
{
	unsigned int	i;

	i = 0;
	while (i < elements && *(p + i))
	{
		free(*(p + i));
		i += element_size;
	}
	free(p);
}

void	ft_puterror(char *msg)
{
	ft_putstr("Error: ");
	ft_putstr(msg);
	ft_putstr("\n");
}
