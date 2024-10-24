/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:58:43 by ozini             #+#    #+#             */
/*   Updated: 2024/06/22 16:06:49 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	recalculate_angle(double angle_value)
{
	if (angle_value >= 360)
		angle_value = angle_value - 360;
	else if (angle_value < 0)
		angle_value = angle_value + 360;
	return (angle_value);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.0));
}

void	set_up_wall_orientation(t_data *data, int i, double angle_value,
	bool is_horizontal)
{
	if (is_horizontal)
	{
		if (angle_value >= 0 && angle_value <= 180)
			data->projection[i].orientation = SOUTH;
		else
			data->projection[i].orientation = NORTH;
	}
	else
	{
		if ((angle_value >= 0 && angle_value <= 90)
			|| (angle_value >= 270 && angle_value <= 360))
			data->projection[i].orientation = WEST;
		else
			data->projection[i].orientation = EAST;
	}
}
