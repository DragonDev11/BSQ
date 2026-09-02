/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:16:36 by mhmichi           #+#    #+#             */
/*   Updated: 2026/09/02 12:23:14 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_HANDLER_H
# define FT_FILE_HANDLER_H
# define PATH_MAX 4095
# define FILE_NAME_MAX 255
# define SEEK_CURRENT 0
# define SEEK_LIMIT 1
# define SEEK_PUT 2

typedef struct
{
	int		fd;
	int		offset;
	int		size;
	int		map_offset;
	char	*buffer;
	char	*path;
	char	*modes;
}	FT_FILE;

typedef struct
{
	int	height;
	int	width;
	char	*tiles;
	int	**map;
}	FT_MAP;

int			ft_read(unsigned int buffer_size, char *buffer, FT_FILE *file);
FT_FILE		*ft_open(char *path, char *modes);
int			ft_close(FT_FILE *file);
int			ft_write(unsigned int buffer_size, char *buffer, FT_FILE *file);
char		ft_is_file_valid(FT_FILE *file);
char		**ft_extract_lines(FT_FILE *file);
int			ft_prep_file(FT_FILE *file);
FT_FILE		*ft_reset_offset(FT_FILE *file);
int		ft_lseek(FT_FILE *file, int offset, int mode);
FT_MAP	*ft_extract_map(FT_FILE *file);
int     ft_get_map_offset(char *buffer);
#endif

