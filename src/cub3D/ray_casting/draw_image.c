/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:31:14 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 16:25:26 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Get a pixel from a wall texture
static int	get_pixel(t_data *data, int x, int y, mlx_texture_t *wall)
{
	int	pixel_x;
	int	pixel_y;
	int	y_zero;

	pixel_x = (data->projection[x].relative_slice_position / GRID_SIZE) \
		* wall->width;
	y_zero = (data->win.height - \
		data->projection[x].projected_slice_height) / 2;
	pixel_y = ((y - y_zero) / data->projection[x].projected_slice_height) \
		* wall->height;
	return ((pixel_y * wall->width + pixel_x) * sizeof(uint32_t));
}

//	Set a pixel to the main image
static void	set_pixel(t_data *data, int x, int y, uint8_t *not_wall)
{
	mlx_texture_t	*wall;
	int				pos1;
	int				pos2;
	int				i;

	i = -1;
	pos1 = ((y * data->img->width) + x) * sizeof(uint32_t);
	if (not_wall)
	{
		while (++i < 4)
			data->img->pixels[pos1 + i] = not_wall[i];
		return ;
	}
	if (data->projection[x].orientation == NORTH)
		wall = data->txs.no;
	if (data->projection[x].orientation == SOUTH)
		wall = data->txs.so;
	if (data->projection[x].orientation == WEST)
		wall = data->txs.we;
	if (data->projection[x].orientation == EAST)
		wall = data->txs.ea;
	pos2 = get_pixel(data, x, y, wall);
	while (++i < 4)
		if (pos2 + i < (int)(wall->width * wall->height * sizeof(uint32_t)))
			data->img->pixels[pos1 + i] = wall->pixels[pos2 + i];
}

//	Draw the image into the window
void	draw_image(t_data *data)
{
	int			top;
	int			bottom;
	int			y;
	int			x;

	x = -1;
	while (data->projection && ++x < data->win.width)
	{
		top = data->win.height / 2 - \
			data->projection[x].projected_slice_height / 2;
		bottom = data->win.height / 2 + \
			data->projection[x].projected_slice_height / 2;
		y = -1;
		while (++y < data->win.height)
		{
			if (y < top && y < data->win.height / 2)
				set_pixel(data, x, y, data->txs.c);
			if (y >= top && y <= bottom)
				set_pixel(data, x, y, NULL);
			if (y > bottom && y >= data->win.height / 2)
				set_pixel(data, x, y, data->txs.f);
		}
	}
}
