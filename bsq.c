/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 12:57:51 by mhmichi           #+#    #+#             */
/*   Updated: 2026/09/02 13:29:57 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_file_handler.h>
#include <ft_errors_handler.h>
#include <ft_string.h>
#include <ft_math.h>

int main(int argc, char **argv)
{
	FT_FILE *file = ft_open(argv[1], "wr");
	if (file == NULL)
	{
		ft_puterror("Failed to open file.");
		return (1);
	}
	if (ft_prep_file(file) == -1)
		ft_puterror("Failed to prepare file.");
	else
		ft_putnotice("Preparation successful.");
	FT_MAP *map = ft_extract_map(file);
	if (map == NULL)
		ft_puterror("Failed to extract map.");
	else
		ft_putnotice("Map extraction successful.");
	for (int i=0; i<map->height; i++)
	{
		for (int j=0; j<map->width; j++)
		{
			ft_putnbr(map->map[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	if (ft_close(file) == -1)
	{
		ft_puterror("Failed to open file.");
		return (1);
	}
	return (0);
}
