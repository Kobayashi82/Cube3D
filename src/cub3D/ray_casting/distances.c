/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:12:25 by ozini             #+#    #+#             */
/*   Updated: 2024/06/22 16:32:13 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	apply_correction_factor(t_data *data,
	double angle_value, double calculated_distance)
{
	double	angle_radians;
	double	player_dir_radians;
	double	angle_offset;
	double	corrected_distance;

	angle_radians = degrees_to_radians(angle_value);
	player_dir_radians = degrees_to_radians((double)data->pl.dir);
	angle_offset = fabs(angle_radians - player_dir_radians);
	corrected_distance = cos(angle_offset) * calculated_distance;
	return (corrected_distance);
}

static double	distance(t_data *data, t_pixel_point b, double angle_value)
{
	double			player_x_position;
	double			player_y_position;
	double			calculated_distance;
	t_grid_point	grid_p;

	player_x_position = (double)data->pl.x;
	player_y_position = (double)data->pl.y;
	grid_p.x = b.x / GRID_SIZE;
	grid_p.y = b.y / GRID_SIZE;
	if (outside_map(data, &grid_p))
		return (10000000000.0);
	else
	{
		calculated_distance = (sqrt(pow((player_x_position - b.x), 2)
					+ pow((player_y_position - b.y), 2)));
		calculated_distance = apply_correction_factor(data, angle_value,
				calculated_distance);
		return (calculated_distance);
	}
}

static double	horizontal_ray_distance(t_data *data, t_pixel_point *pixel_wall,
	double angle_value)
{
	ft_memset(pixel_wall, 0, sizeof(t_pixel_point));
	while (1)
		if (horizontal_intersection(data, angle_value, pixel_wall))
			break ;
	return (distance(data, *pixel_wall, angle_value));
}

static double	vertical_ray_distance(t_data *data, t_pixel_point *pixel_wall,
	double angle_value)
{
	ft_memset(pixel_wall, 0, sizeof(t_pixel_point));
	while (1)
		if (vertical_intersection(data, angle_value, pixel_wall))
			break ;
	return (distance(data, *pixel_wall, angle_value));
}

double	calculate_distance(t_data *data, double angle_value, int i,
	t_pixel_point *relative_slice_position)
{
	double			horz_int_dist;
	double			vert_int_dist;
	t_pixel_point	hor_pixel_wall;
	t_pixel_point	ver_pixel_wall;

	horz_int_dist = horizontal_ray_distance(data, &hor_pixel_wall, angle_value);
	vert_int_dist = vertical_ray_distance(data, &ver_pixel_wall, angle_value);
	if (horz_int_dist <= vert_int_dist)
	{
		(*relative_slice_position).x = hor_pixel_wall.x;
		(*relative_slice_position).y = hor_pixel_wall.y;
		set_up_wall_orientation(data, i, angle_value, true);
		return (horz_int_dist);
	}
	else
	{
		(*relative_slice_position).x = ver_pixel_wall.x;
		(*relative_slice_position).y = ver_pixel_wall.y;
		set_up_wall_orientation(data, i, angle_value, false);
		return (vert_int_dist);
	}
}
