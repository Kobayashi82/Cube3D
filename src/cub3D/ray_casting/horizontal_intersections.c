/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersections_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:00:58 by ozini             #+#    #+#             */
/*   Updated: 2024/06/22 17:12:28 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_grid_point	first_horizontal_intersection(t_data *data,
	t_pixel_point *pixel_p, double angle_value)
{
	double			angle_radians;
	t_grid_point	grid_p;

	angle_radians = degrees_to_radians(angle_value);
	if (angle_value >= 0 && angle_value <= 180)
	{
		(*pixel_p).y = floor((double)(data->pl.y) / GRID_SIZE) * GRID_SIZE - 1;
		grid_p.y = (int)floor((*pixel_p).y / GRID_SIZE);
		(*pixel_p).y++;
	}
	else
	{
		(*pixel_p).y = ceil((double)(data->pl.y) / GRID_SIZE) * GRID_SIZE;
		grid_p.y = (int)floor((*pixel_p).y / GRID_SIZE);
	}
	(*pixel_p).x = (double)data->pl.x + ((double)data->pl.y - (*pixel_p).y)
		/ tan(angle_radians);
	grid_p.x = (int)floor((*pixel_p).x / GRID_SIZE);
	return (grid_p);
}

static t_grid_point	subsequent_horizontal_intersection(t_pixel_point *pixel_p,
	double angle_value)
{
	double			angle_radians;
	double			horizontal_increase;
	t_grid_point	grid_p;

	angle_radians = degrees_to_radians(angle_value);
	horizontal_increase = GRID_SIZE / tan(angle_radians);
	if (angle_value >= 0 && angle_value <= 180)
	{
		(*pixel_p).x = (*pixel_p).x + horizontal_increase;
		(*pixel_p).y = (*pixel_p).y - GRID_SIZE - 1;
		grid_p.y = (int)floor((*pixel_p).y / GRID_SIZE);
		(*pixel_p).y++;
	}
	else
	{
		(*pixel_p).x = (*pixel_p).x - horizontal_increase;
		(*pixel_p).y = (*pixel_p).y + GRID_SIZE;
		grid_p.y = (int)floor((*pixel_p).y / GRID_SIZE);
	}
	grid_p.x = (int)floor((*pixel_p).x / GRID_SIZE);
	return (grid_p);
}

bool	horizontal_intersection(t_data *data, double angle_value,
	t_pixel_point *pixel_p)
{
	t_grid_point	grid_p;
	bool			out_of_boundaries;

	out_of_boundaries = false;
	if ((angle_value >= 359.99 && angle_value <= 0.01)
		|| (angle_value >= 179.99 && angle_value <= 180.01))
		out_of_boundaries = true;
	if ((*pixel_p).x == 0.0 && (*pixel_p).y == 0.0)
		grid_p = first_horizontal_intersection(data, pixel_p, angle_value);
	else
		grid_p = subsequent_horizontal_intersection(pixel_p, angle_value);
	out_of_boundaries = outside_map(data, &grid_p);
	if (out_of_boundaries || data->map.map[grid_p.y][grid_p.x] == '1')
		return (true);
	else
		return (false);
}
