/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:01:17 by ozini             #+#    #+#             */
/*   Updated: 2024/06/22 16:11:31 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_slice_height(t_data *data, double ray_distance)
{
	double	projected_slice_height;
	double	distance_projection_plane;

	distance_projection_plane = ((double)data->win.width / 2)
		/ tan(degrees_to_radians (FOV / 2));
	if (ray_distance >= 1)
		projected_slice_height = GRID_SIZE / ray_distance
			* distance_projection_plane;
	else
		projected_slice_height = data->win.height;
	return (projected_slice_height);
}

double	precise_slice_position(t_orientation orientation,
	t_pixel_point relative_slice_position)
{
	double	p_s_position;

	p_s_position = 0;
	if (orientation == SOUTH)
		p_s_position = relative_slice_position.x
			- (floor (relative_slice_position.x / GRID_SIZE) * GRID_SIZE);
	else if (orientation == EAST)
		p_s_position = (ceil (relative_slice_position.y / GRID_SIZE)
				* GRID_SIZE) - relative_slice_position.y;
	else if (orientation == NORTH)
		p_s_position = (ceil (relative_slice_position.x / GRID_SIZE)
				* GRID_SIZE) - relative_slice_position.x;
	else if (orientation == WEST)
		p_s_position = relative_slice_position.y
			- (floor (relative_slice_position.y / GRID_SIZE) * GRID_SIZE);
	return (p_s_position);
}
