/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:17:10 by mhmichi           #+#    #+#             */
/*   Updated: 2026/09/02 11:42:19 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file_handler.h"
#include "ft_string.h"
#include "ft_errors_handler.h"
#include "ft_math.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

FT_FILE	*ft_open(char *path, char *modes)
{
	char	**file_names;
	char	**tmp;
	int		i;
	FT_FILE	*file;

	if (ft_strlen(path) >= PATH_MAX)
		return (NULL);
	file_names = ft_split(path, "/");
	if (file_names == NULL)
		ft_putstr("Warning: Failed to check the path\nfix it, continuing anyways.\n");
	else
	{
		i = 0;
		tmp = file_names;
		while (*file_names)
		{
			if (ft_strlen(*file_names) > FILE_NAME_MAX)
			{
				ft_putstr("Error: Invalid file name ");
				ft_putstr(*file_names);
				ft_putstr("\nfix it, enter a valid path.\n");
				return (NULL);
			}
			file_names++;
			i++;
		}
		free_double_pointer((void **)tmp, i, sizeof(char *));
	}
	if (ft_strlen(modes) != 2)
		return (NULL);
	file = (FT_FILE *)malloc(sizeof(FT_FILE));
	if (file == NULL)
		return (NULL);
	if (ft_str_contains('w', modes) > -1 && ft_str_contains('r', modes) > -1)
		file->fd = open(path, O_RDWR | O_CREAT, 0644);
	else if (ft_str_contains('w', modes) > -1)
		file->fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_str_contains('r', modes) > -1)
		file->fd = open(path, O_RDONLY);
	file->buffer = NULL;
	file->offset = 0;
	file->size = 0;
	file->modes = ft_strdup(modes);
	if (file->modes == NULL)
		return (NULL);
	file->path = ft_strdup(path);
	if (file->path == NULL)
		return (NULL);
	if (file->fd == -1)
	{
		free(file);
		return (NULL);
	}
	return (file);
}

int	ft_read(unsigned int size, char *buffer, FT_FILE *file)
{
	int	bytes_read;

	if (file == NULL || buffer == NULL)
		return (-1);
	if (file->fd == -1)
		return (-1);
	bytes_read = read(file->fd, buffer, size);
	if (bytes_read != -1)
	{
		file->offset += bytes_read;
		return (bytes_read);
	}
	return (-1);
}

int	ft_write(unsigned int size, char *buffer, FT_FILE *file)
{
	int	bytes_written;

	if (file == NULL)
		return (-1);
	if (file->fd == -1)
		return (-1);
	bytes_written = write(file->fd, buffer, size);
	if (bytes_written != -1)
	{
		file->offset += bytes_written;
		return (bytes_written);
	}
	return (-1);
}

int	ft_close(FT_FILE *file)
{
	int	ret;

	if (file == NULL)
		return (-1);
	if (file->fd == -1)
		return (-1);
	ret = close(file->fd);
	if (ret != -1)
	{
		if (file->buffer != NULL)
			free(file->buffer);
		free(file->path);
		free(file->modes);
		free(file);
	}
	return (ret);
}

FT_FILE	*ft_reset_offset(FT_FILE *file)
{
	FT_FILE *new;

	if (file == NULL)
		return (NULL);
	new = ft_open(file->path, file->modes);
	if (new == NULL)
		return (NULL);
	if (new->fd == -1)
	{
		free(new->path);
		free(new->modes);
		free(new);
		return (NULL);
	}
	new->length = temp.length;
	if (ft_close(file) != 0)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int	ft_prep_file(FT_FILE *file)
{
	char	c;
	char	*buffer;

	if (file == NULL)
		return (-1);
	if (file->fd == -1)
		return (-1);
	while (read(file->fd, &c, 1) > 0)
		file->length++;
	file = ft_reset_offset(file);
	if (file == NULL)
		return (-1);
	buffer = (char *)malloc(sizeof(char) * file->length + 1);
	if (buffer == NULL)
		return (-1);
	i = 0;
	while (read(file->fd, &c, 1) > 0 && i < length - 1)
		buffer[i++] = c;
	buffer[i] = '\0';
	file = ft_reset_offset(file);
	file->offset = 0;
	file->buffer = buffer;
	return (0);
}

char	**ft_extract_lines(FT_FILE *file)
{
	char	**lines;

	if (file == NULL)
		return (NULL);
	if (file->fd == -1 || file->buffer == NULL)
		return (NULL);
	lines = ft_split(file->buffer, "\n");
	if (lines == NULL)
		return (NULL);
	return (lines);
}

char	ft_is_file_valid(FT_FILE *file)
{
	char	**lines;
	int	i;
	int	j;
	int	k;
	char	charset[4];
	char	*num_str;
	int	width;
	int	actual_height;
	int	expected_height;
	
	width = 0;
	expected_height = 0;
	actual_height = 0;
	if (file == NULL)
		return (0);
	if (file->fd == -1 || file->buffer == NULL)
		return (0);
	lines = ft_extract_lines(file);
	if (lines == NULL)
		return (0);
	i = 0;
	while (lines[i])
		i++;
	actual_height = i - 1;
	i = 0;
	while (lines[i])
	{
		j = 0;
		if (i == 0)
		{
			while(lines[i][j] >= '0' && lines[i][j] <= '9')
				j++;
			num_str = ft_strndup(lines[i], j);
			if (num_str == NULL)
				return (NULL);
			expected_height = ft_atoi(num_str);
			free(num_str);
			if (actual_height != expected_height || j == 0)
			{
				free_double_pointer((void **)lines, actual_height + 1, sizeof(char *));
				return (0);
			}
			k = j + 4;
			while (j < k - 1)
			{
				if (!ft_is_printable(lines[i][j]) || lines[i][j] == '\n')
				{
					free_double_pointer((void **)lines, actual_height + 1, sizeof(char *));
					return (0);
				}
				charset[ABS(k - 2 - j)] = lines[i][j];
				j++;
			}
			charset[3] = '\0';
			if (lines[i][j] != '\n')
			{
				free_double_pointer((void **)lines, actual_height + 1, sizeof(char *));
				return (0);
			}
		}
		while (lines[i][j] && ft_str_contains(lines[i][j], charset) > -1)
			j++;
		if (width == 0)
			width = j;
		if (j != width)
		{
			free_double_pointer((void **)lines, actual_height + 1, sizeof(char *));
			return (0);
		}
		i++;
	}
	free_double_pointer((void **)lines, actual_height + 1, sizeof(char *));
	if (actual_height != expected_height)
		return (0);
	return (1);
}

int	ft_calculate_file_size(FT_FILE *file)
{
	char	c;

	if (file == NULL || file->fd == -1)
		return (-1);
	file = ft_reset_offset(file);
	file->size = 0;
	while (read(file->fd, &c, 1) > 0)
		file->size++;
	return (file->size);
}

int	ft_lseek(FT_FILE *file, int offset, int mode)
{
	char	*trash;
	int	ret;

	if (file == NULL || file->fd == -1)
		return (-1);
	if (mode == SEEK_CURRENT)
	{
		trash = malloc(sizeof(char) * offset);
		ret = ft_read(offset, trash, file);
	}
	else if (mode == SEEK_LIMIT)
	{
		file = ft_reset_offset(file);
		if (file == NULL)
			return (-1);
		trash = malloc(sizeof(char) * file->size);
		ret = ft_read(file->size, trash, file);
	}
	else if (mode == SEEK_PUT)
	{
		if (offset > file->size)
			return (-1);
		file = ft_reset_offset(file);
		if (file == NULL)
			return (-1);
		trash = malloc(sizeof(char) * offset);
		ret = ft_read(offset, trash, file);
	}
	free(trash);
	return (ret);
}

char	*ft_extract_charset(char **lines)
{
	char	*charset;
	int	i;
	int	j;

	if (lines == NULL || lines[0] == NULL)
		return (NULL);
	charset = malloc(sizeof(char *) * 3);
	if (charset == NULL)
		return (NULL);
	i = 0;
	while (lines[0][i] && (lines[0][i] >= '0' && lines[0][i] <= '9'))
		i++;
	j = 0;
	while (lines[0][i] && lines[0][i] != '\n')
		charset[j++] = lines[0][i++];
	return (charset);
}

int	**ft_extract_map(FT_FILE *file)
{
	FT_MAP	*map;
	char	**lines;

	if (file == NULL)
		return (NULL);
	if (file->fd == -1 || !ft_is_file_valid(file))
		return (NULL);
	map = malloc(sizeof(FT_MAP));
	if (map == NULL)
		return (NULL);
	lines = ft_extract_lines(file);
	if (lines == NULL)
		return (NULL);
	map->tileset = ft_extract_tileset(lines);
	if (map->tileset == NULL)
		return (NULL);
	map->height = 1;
	while (lines[map->height] != NULL)
		map->height++;
	map->height--;
	map->map = malloc(sizeof(int *) * height);
	if (map->map == NULL)
		return (NULL);
	map->width = ft_strlen(lines[1]) - 1;
	if (map->width != map->height)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map->map[i] = malloc(sizeof(int) * width);
		if (map->map[i] == NULL)
		{
			free_double_pointer((void **)map->map, map->height + 1, sizeof(int *));
			free(map->tileset);
			free(map);
		}
		j = 0;
		while (j < width)
		{
			if (lines[i + 1][j] == charset[0])
				map->map[i][j] = 0;
			else if (lines[i + 1][j] == charset[1])
				map->map[i][j] = 1;
		}
		i++;
	}
	free_double_pointer((void **)lines, map->height + 1, sizeof(char *));
	return (map);
}

void	map_to_buffer(FT_MAP *map, FT_FILE *file)
{
	int	i;
	int	j;

	if (map == NULL || file == NULL || map->tilset == NULL || file->buffer == NULL)
		return (NULL);
	i = 0;
	while (i < map->height
}
