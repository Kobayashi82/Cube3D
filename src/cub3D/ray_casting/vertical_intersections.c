/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersections_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:05:18 by ozini             #+#    #+#             */
/*   Updated: 2024/06/22 17:12:33 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_grid_point	first_vertical_intersection(t_data *data,
	t_pixel_point *pixel_p, double angle_value)
{
	double			angle_radians;
	t_grid_point	grid_p;

	angle_radians = degrees_to_radians(angle_value);
	if ((angle_value >= 0 && angle_value <= 90)
		|| (angle_value >= 270 && angle_value <= 360))
	{
		(*pixel_p).x = ceil((double)data->pl.x / GRID_SIZE) * GRID_SIZE;
		grid_p.x = (int)floor((*pixel_p).x / GRID_SIZE);
	}
	else
	{
		(*pixel_p).x = floor((double)data->pl.x / GRID_SIZE) * GRID_SIZE - 1;
		grid_p.x = (int)floor((*pixel_p).x / GRID_SIZE);
		(*pixel_p).x++;
	}
	(*pixel_p).y = (double)data->pl.y + ((double)data->pl.x - (*pixel_p).x)
		* tan(angle_radians);
	grid_p.y = (int)floor((*pixel_p).y / GRID_SIZE);
	return (grid_p);
}

static t_grid_point	subsequent_vertical_intersection(t_pixel_point *pixel_p,
	double angle_value)
{
	double			angle_radians;
	double			vertical_increase;
	t_grid_point	grid_p;

	angle_radians = degrees_to_radians(angle_value);
	vertical_increase = GRID_SIZE * tan(angle_radians);
	if ((angle_value >= 0 && angle_value <= 90)
		|| (angle_value >= 270 && angle_value <= 360))
	{
		(*pixel_p).y = (*pixel_p).y - vertical_increase;
		(*pixel_p).x = (*pixel_p).x + GRID_SIZE;
		grid_p.x = (int)floor((*pixel_p).x / GRID_SIZE);
	}
	else
	{
		(*pixel_p).y = (*pixel_p).y + vertical_increase;
		(*pixel_p).x = (*pixel_p).x - GRID_SIZE - 1;
		grid_p.x = (int)floor((*pixel_p).x / GRID_SIZE);
		(*pixel_p).x++;
	}
	grid_p.y = (int)floor((*pixel_p).y / GRID_SIZE);
	return (grid_p);
}

bool	vertical_intersection(t_data *data, double angle_value,
	t_pixel_point *pixel_p)
{
	t_grid_point	grid_p;
	bool			out_of_boundaries;

	out_of_boundaries = false;
	if ((angle_value >= 89.99 && angle_value <= 90.01)
		|| (angle_value >= 269.99 && angle_value <= 270.01))
		out_of_boundaries = true;
	if ((*pixel_p).x == 0 && (*pixel_p).y == 0)
		grid_p = first_vertical_intersection(data, pixel_p, angle_value);
	else
		grid_p = subsequent_vertical_intersection(pixel_p, angle_value);
	out_of_boundaries = outside_map(data, &grid_p);
	if (out_of_boundaries || data->map.map[grid_p.y][grid_p.x] == '1')
		return (true);
	else
		return (false);
}
