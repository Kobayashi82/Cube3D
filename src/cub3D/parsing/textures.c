/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:34:08 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/22 08:20:10 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Check if there are missing textures
static int	missing_texture(t_data *data)
{
	if (!data->txs.f_no && !data->txs.no)
		data->error = exit_error(data, MLX_MISSING_TXT, "north wall", false);
	if (!data->txs.f_so && !data->txs.so)
		data->error = exit_error(data, MLX_MISSING_TXT, "south wall", false);
	if (!data->txs.f_we && !data->txs.we)
		data->error = exit_error(data, MLX_MISSING_TXT, "west wall", false);
	if (!data->txs.f_ea && !data->txs.ea)
		data->error = exit_error(data, MLX_MISSING_TXT, "east wall", false);
	if (!data->txs.f[3])
		data->error = exit_error(data, MAP_MISSING_RGB, "floor", false);
	if (!data->txs.c[3])
		data->error = exit_error(data, MAP_MISSING_RGB, "ceiling", false);
	return (1);
}

//	Validate a texture file
static int	check_texture(t_data *data, char *file)
{
	int	fd;
	int	error;

	error = 0;
	if (!file)
		error = exit_error(data, FILE_ERR, file, false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			error = exit_error(data, FILE_R_PERM, file, false);
		else if (errno == ENOENT)
			error = exit_error(data, FILE_NO_EXIST, file, false);
		else if (errno == ENOENT)
			error = exit_error(data, FILE_ERR, file, false);
	}
	else
		close(fd);
	return (error);
}

//	Load a texture file
static int	load_txt(t_data *data, mlx_texture_t **txt, char *line, int error)
{
	int	len;

	if (!line || !*line)
		data->extra = exit_error(data, FILE_ERR, NULL, false);
	else
	{
		while (line && ft_isspace(*line))
			line++;
		len = ft_strlen(line);
		while (len-- && ft_isspace(line[len]))
			line[len] = '\0';
		if (!data->extra)
			data->extra = check_texture(data, line);
		else
			check_texture(data, line);
		if (!data->extra)
		{
			*txt = mlx_load_png(line);
			if (!*txt)
				exit_error(data, MLX_OPEN_TXT, line, false);
		}
	}
	data->error = (data->extra || error);
	data->extra = 0;
	return (1);
}

//	Check if a texture is set more than once
static int	check_repeated_texture(t_data *data, char *line)
{
	if (data->txs.no && !strncmp(line, "NO ", 3))
		data->error = exit_error(data, MLX_REPE, "north wall", false);
	else if (data->txs.so && !strncmp(line, "SO ", 3))
		data->error = exit_error(data, MLX_REPE, "south wall", false);
	else if (data->txs.we && !strncmp(line, "WE ", 3))
		data->error = exit_error(data, MLX_REPE, "west wall", false);
	else if (data->txs.ea && !strncmp(line, "EA ", 3))
		data->error = exit_error(data, MLX_REPE, "east wall", false);
	else if (data->txs.f[3] && !strncmp(line, "F ", 2))
		data->error = exit_error(data, MAP_REPE_RGB, "floor", false);
	else if (data->txs.c[3] && !strncmp(line, "C ", 2))
		data->error = exit_error(data, MAP_REPE_RGB, \
			"ceiling", false);
	else
	{
		missing_texture(data);
		return (2);
	}
	return (data->error);
}

//	Load all the textures and RGB values
bool	load_textures(t_data *data, char *line)
{
	while (line && ft_isspace(*line))
		line++;
	if (line && ft_strlen(line) - 1 >= 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!data->txs.no && !strncmp(line, "NO ", 3))
		data->txs.f_no = load_txt(data, &data->txs.no, line + 2, data->error);
	else if (!data->txs.so && !strncmp(line, "SO ", 3))
		data->txs.f_so = load_txt(data, &data->txs.so, line + 2, data->error);
	else if (!data->txs.we && !strncmp(line, "WE ", 3))
		data->txs.f_we = load_txt(data, &data->txs.we, line + 2, data->error);
	else if (!data->txs.ea && !strncmp(line, "EA ", 3))
		data->txs.f_ea = load_txt(data, &data->txs.ea, line + 2, data->error);
	else if (!data->txs.f[3] && !strncmp(line, "F ", 2))
		data->error = load_rgb_f(data, line + 1, data->error);
	else if (!data->txs.c[3] && !strncmp(line, "C ", 2))
		data->error = load_rgb_c(data, line + 1, data->error);
	else if (line && !ft_isspace_s(line))
	{
		if (check_repeated_texture(data, line) == 2)
			return (true);
	}
	if (!line)
		return (missing_texture(data));
	return (false);
}
