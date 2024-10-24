/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:47:29 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/18 18:38:16 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Check for unclosed borders of the map (top & bottom)
static int	check_map_top_bottom(char **map, int h, int y, int x)
{
	int	len;

	if (x <= 0 || !ft_strchr("NSWE01", map[y][x - 1]))
		return (1);
	if (map[y][x + 1] == '\0' || !ft_strchr("NSWE01", map[y][x + 1]))
		return (1);
	if (y == 0)
		return (1);
	len = ft_strlen(&map[y - 1][0]);
	if (len - 1 < x - 1 || !ft_strchr("NSWE01", map[y - 1][x - 1]))
		return (1);
	if (len - 1 < x || !ft_strchr("NSWE01", map[y - 1][x]))
		return (1);
	if (len - 1 < x + 1 || !ft_strchr("NSWE01", map[y - 1][x + 1]))
		return (1);
	if (y == h - 1)
		return (1);
	len = ft_strlen(&map[y + 1][0]);
	if (len - 1 < x - 1 || !ft_strchr("NSWE01", map[y + 1][x - 1]))
		return (1);
	if (len - 1 < x || !ft_strchr("NSWE01", map[y + 1][x]))
		return (1);
	if (len - 1 < x + 1 || !ft_strchr("NSWE01", map[y + 1][x + 1]))
		return (1);
	return (0);
}

//	Check for unclosed borders of the map and invalid characters
static int	check_map(char **map, int h, int y, int x)
{
	if (ft_strchr("NSWE0", map[y][x]))
	{
		if (check_map_top_bottom(map, h, y, x))
			return (1);
	}
	else if (!ft_strchr(" 1", map[y][x]))
		return (2);
	return (0);
}

//	Validate a position of the map
static int	validate_pos(t_data *data, int x, int y, int p)
{
	int	error;

	error = check_map(data->map.map, data->map.map_h, y, x);
	if (error)
	{
		if (error == 1 && (data->extra == 0 || data->extra == 2))
			data->extra++;
		if (error == 2 && (data->extra == 0 || data->extra == 1))
			data->extra += 2;
	}
	if (ft_strchr("NSWE", data->map.map[y][x]))
	{
		if (data->map.map[y][x] == 'N')
			data->pl.dir = 90;
		if (data->map.map[y][x] == 'S')
			data->pl.dir = 270;
		if (data->map.map[y][x] == 'W')
			data->pl.dir = 180;
		if (data->map.map[y][x] == 'E')
			data->pl.dir = 0;
		data->pl.pos_y = y;
		data->pl.pos_x = x;
		p++;
	}
	return (p);
}

//	Validate a map (not the file, the content)
void	validate_map(t_data *data)
{
	int	y;
	int	x;
	int	p;

	y = -1;
	p = 0;
	data->extra = 0;
	while (data->map.map && data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
			p = validate_pos(data, x, y, p);
	}
	data->pl.x = data->pl.pos_x * GRID_SIZE + GRID_SIZE / 2;
	data->pl.y = data->pl.pos_y * GRID_SIZE + GRID_SIZE / 2;
	if (data->extra == 1 || data->extra == 3)
		data->error = exit_error(data, MAP_BORDER, NULL, false);
	if (data->extra == 2 || data->extra == 3)
		data->error = exit_error(data, MAP_CHAR, NULL, false);
	if (p == 0)
		data->error = exit_error(data, MAP_NO_P, NULL, false);
	if (p > 1)
		data->error = exit_error(data, MAP_EXTRA_P, NULL, false);
	data->extra = 0;
}
