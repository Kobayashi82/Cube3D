/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:31:53 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 08:36:12 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Open and validate a map file
static int	open_map(t_data *data, char *file)
{
	int	fd;

	if (!file)
		exit_error(data, FILE_ERR, file, true);
	fd = open(file, O_RDONLY);
	if ((fd != -1 || errno == EACCES) && ft_strstr(file, ".cub") == NULL)
	{
		if (fd != -1)
		{
			close (fd);
			data->map.fd = -1;
		}
		exit_error(data, FILE_FORMAT, file, true);
	}
	if (fd == -1)
	{
		if (errno == EACCES)
			exit_error(data, FILE_R_PERM, file, true);
		else if (errno == ENOENT)
			exit_error(data, FILE_NO_EXIST, file, true);
		else
			exit_error(data, FILE_ERR, file, true);
	}
	return (fd);
}

//	Read a map file and load its data
void	load_map(t_data *data, char *file)
{
	char	*line;
	bool	is_map;

	data->map.fd = open_map(data, file);
	is_map = false;
	line = ft_get_next_line(data->map.fd);
	while (line)
	{
		if (is_map == false)
			is_map = load_textures(data, line);
		if (is_map == true)
			map_to_list(data, line);
		free(line);
		line = ft_get_next_line(data->map.fd);
	}
	close(data->map.fd);
	data->map.fd = -1;
	data->extra = map_to_array(data);
	validate_map(data);
	if (data->error && data->map.empty_line == 2)
		exit_error(data, MAP_EMPTY_ROW, NULL, false);
	if (data->error)
		exit_error(data, NOTHING, NULL, true);
}
