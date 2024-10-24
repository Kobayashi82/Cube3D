/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:28:59 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 16:25:49 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Hook to wait for a key press (ESC and Q)
void	key_hook(mlx_key_data_t keydata, void *vdata)
{
	t_data	*data;
	int		key;

	data = vdata;
	key = keydata.key;
	if (key == MLX_KEY_ESCAPE || key == MLX_KEY_Q)
		mlx_close_window(data->mlx);
}

//	Rotate with the mouse
void	set_mouse_angle(t_data *data)
{
	int32_t	n_y;
	int32_t	n_x;
	int		m_a;

	mlx_get_mouse_pos(data->mlx, &n_x, &n_y);
	if (data->pl.l_x == -2)
		data->pl.l_x = -1;
	else if (data->pl.l_x == -1)
		data->pl.l_x = n_x;
	if (data->pl.l_x != -1 && n_x != data->pl.l_x)
	{
		m_a = roundf((double)n_x - (double)data->pl.l_x) / 10.0;
		if (m_a < 0)
			data->pl.dir -= ft_max(-5, m_a);
		else
			data->pl.dir -= ft_min(5, m_a);
		data->pl.l_x = n_x;
		if (data->pl.dir > 359)
			data->pl.dir = data->pl.dir - 360;
		if (data->pl.dir < 0)
			data->pl.dir = 360 + data->pl.dir;
	}
	data->pl.ms_accum_time = 0;
}

//	Check delta times for movements and drawings
void	check_timings(t_data *data)
{
	if (data->pl.m_accum_time >= data->pl.move_time)
		check_moves(data);
	if (data->pl.r_accum_time >= data->pl.rotate_time)
		rotate_player(data);
	if (data->pl.ms_accum_time >= data->pl.mouse_time)
		set_mouse_angle(data);
	if (data->map.accum_time >= data->map.draw_time)
	{
		set_up_view(data);
		draw_image(data);
		data->map.accum_time = 0.0;
	}
}

//	Update delta time
void	delta_time(void *vdata)
{
	t_data	*data;
	double	dif_sec;
	double	dif_mcsec;

	data = vdata;
	gettimeofday(&data->now, NULL);
	dif_sec = (data->now.tv_sec - data->last_update.tv_sec);
	dif_mcsec = (data->now.tv_usec - data->last_update.tv_usec) / 1000000.0;
	data->pl.m_accum_time += dif_sec + dif_mcsec;
	data->pl.r_accum_time += dif_sec + dif_mcsec;
	data->pl.ms_accum_time += dif_sec + dif_mcsec;
	data->map.accum_time += dif_sec + dif_mcsec;
	check_timings(data);
	data->last_update = data->now;
}
