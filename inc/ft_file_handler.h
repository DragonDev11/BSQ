/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:16:36 by mhmichi           #+#    #+#             */
/*   Updated: 2026/08/31 16:35:29 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_HANDLER_H
# define FT_FILE_HANDLER_H
# define PATH_MAX 4095
# define FILE_NAME_MAX 255

typedef struct FT_FILE
{
	int		fd;
	int		offset;
	int		size;
	char	*buffer;
	char	*path;
}	FT_FILE;

unsigned int	ft_read(unsigned int buffer_size, char *buffer, FT_FILE file);
FT_FILE		ft_open(char *path, char *modes);
unsigned int	ft_close(FT_FILE file);
unsigned int	ft_write(unsigned int buffer_size, char *buffer, FT_FILE file);
char		ft_is_file_valid(FT_FILE file);
#endif

