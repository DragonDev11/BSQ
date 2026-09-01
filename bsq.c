/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 12:57:51 by mhmichi           #+#    #+#             */
/*   Updated: 2026/08/31 12:58:13 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_file_handler.h>
#include <ft_errors_handler.h>

int main(int argc, char **argv)
{
	FT_FILE *file = ft_open(argv[1], "wr");
	if (file == NULL)
	{
		ft_puterror("Failed to open file.");
		return (1);
	}
	if (ft_close(file) == -1)
	{
		ft_puterror("Failed to open file.");
		return (1);
	}
	return (0);
}
