/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:30:40 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 09:16:37 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Manage MLX errors
static void	errors_mlx(int error, char *value)
{
	if (error == NO_MEMORY)
		printf("\n"RD"\tERROR: "C"No memory left on the device"NC);
	if (error == MLX_OPEN || error == MLX_ERROR)
		printf("\n"RD"\tERROR: "C"MLX42 library failed"NC);
	if (error == MLX_MISSING_TXT)
		printf("\n"RD"\tERROR: "C"Missing texture for '"Y"%s"C"'"NC, value);
	if (error == MLX_OPEN_TXT)
		printf("\n"RD"\tERROR: "C"Unable to load texture '"Y"%s"C"'"NC, value);
	if (error == MLX_REPE)
		printf("\n"RD"\tERROR: "C"Texture for '"Y"%s"C"' already set"NC, value);
	if (error == MLX_OPEN_SPR)
		printf("\n"RD"\tERROR: "C"Unable to load textures for '"
			Y"sprites"C"'"NC);
}

//	Manage map errors
static void	errors_map(int error, char *value)
{
	if (error == MAP_F_RGB)
		printf("\n"RD"\tERROR: "C"Invalid RGB values for the '"Y"floor"C"'"NC);
	if (error == MAP_C_RGB)
		printf("\n"RD"\tERROR: "C"Invalid RGB values for the '"
			Y"ceiling"C"'"NC);
	if (error == MAP_MISSING_RGB)
		printf("\n"RD"\tERROR: "C"Missing RGB values for '"Y"%s"C"'"NC, value);
	if (error == MAP_REPE_RGB)
		printf("\n"RD"\tERROR: "C"RGB values for '"Y"%s"
			C"' already set"NC, value);
	if (error == MAP_NO)
		printf("\n"RD"\tERROR: "C"No map available to load"NC);
	if (error == MAP_EMPTY_ROW)
		printf("\n"RD"\tERROR: "C"The map is split into multiple parts"NC);
	if (error == MAP_BORDER)
		printf("\n"RD"\tERROR: "C"The map is not enclosed by walls"NC);
	if (error == MAP_CHAR)
		printf("\n"RD"\tERROR: "C"The map contains invalid characters"NC);
	if (error == MAP_NO_P)
		printf("\n"RD"\tERROR: "C"No starting position"NC);
	if (error == MAP_EXTRA_P)
		printf("\n"RD"\tERROR: "C"Multiple starting positions"NC);
}

//	Manage input errors
static void	errors_input(int error, char *value)
{
	if (error == INV_ARGS)
		printf("\n"RD"\tERROR: "
			C"Invalid number of arguments provided"NC);
	if (error == FILE_ERR)
		printf("\n"RD"\tERROR: "
			C"Unable to open file '"Y"%s"C"'"NC, value);
	if (error == FILE_FORMAT)
		printf("\n"RD"\tERROR: "C"Incorrect format for file '"
			Y"%s"C"'"NC, value);
	if (error == FILE_R_PERM)
		printf("\n"RD"\tERROR: "C"Read permission denied for file '"
			Y"%s"C"'"NC, value);
	if (error == FILE_NO_EXIST)
		printf("\n"RD"\tERROR: "
			C"File '"Y"%s"C"' does not exist"NC, value);
}

//	Print an error and close the program... or not
int	exit_error(t_data *data, int error, char *value, bool is_exit)
{
	if (error != NOTHING && !data->error_msg)
		data->error_msg = printf("Error\n");
	errors_input(error, value);
	errors_map(error, value);
	errors_mlx(error, value);
	if (is_exit)
	{
		printf("\n\n");
		free_data(data);
		exit((error != NOTHING));
	}
	return ((error != NOTHING));
}
