/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:43:14 by ozini             #+#    #+#             */
/*   Updated: 2024/06/22 16:22:24 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	outside_map(t_data *data, t_grid_point *grid_p)
{
	return (grid_p->x < 0 || grid_p->y < 0
		|| (grid_p->x > data->map.map_w - 1)
		|| (grid_p->y > data->map.map_h - 1));
}

void	set_up_view(t_data *data)
{
	double			angle_increment;
	double			angle_value;
	t_pixel_point	relative_slice_position;
	int				i;

	i = -1;
	angle_increment = FOV / (data->win.width);
	angle_value = data->pl.dir + FOV / 2;
	free(data->projection);
	data->projection = safe_malloc(data,
			(data->win.width + 1) * sizeof(t_projection));
	while (++i < (data->win.width + 1))
	{
		angle_value = recalculate_angle(angle_value);
		data->projection[i].column_index = i;
		data->projection[i].ray_distance = calculate_distance(data,
				angle_value, i, &relative_slice_position);
		data->projection[i].projected_slice_height = \
			calculate_slice_height(data, data->projection[i].ray_distance);
		data->projection[i].relative_slice_position = \
			precise_slice_position(data->projection[i].orientation,
				relative_slice_position);
		angle_value -= angle_increment;
	}
}
