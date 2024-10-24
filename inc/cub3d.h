/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:08:17 by vzurera-          #+#    #+#             */
/*   Updated: 2024/06/18 18:31:43 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "colors.h"
# include "libft.h"
# include "MLX42.h"
# include <math.h>
# include <sys/time.h>

# define PI 3.14159265358979323846
# define GRID_SIZE 64.0
# define FOV 60.0
# define MOV_SP 8
# define ROT_SP 4

typedef enum e_orientation
{
	NORTH = 40,
	SOUTH = 41,
	WEST = 42,
	EAST = 43,
}	t_orientation;

enum e_error
{
	NOTHING = 0,
	INV_ARGS = 1,
	MAP_NO = 3,
	MAP_EMPTY_ROW = 4,
	MAP_BORDER = 5,
	MAP_CHAR = 6,
	MAP_NO_P = 7,
	MAP_EXTRA_P = 8,
	MAP_F_RGB = 9,
	MAP_C_RGB = 10,
	MAP_MISSING_RGB = 11,
	MAP_REPE_RGB = 12,
	FILE_NO_EXIST = 13,
	FILE_ERR = 14,
	FILE_FORMAT = 15,
	FILE_R_PERM = 16,
	MLX_OPEN = 20,
	MLX_ERROR = 21,
	MLX_OPEN_TXT = 22,
	MLX_MISSING_TXT = 23,
	MLX_REPE = 24,
	MLX_OPEN_SPR = 25,
	NO_MEMORY = 30,
};

typedef struct s_pixel_point
{
	double	y;
	double	x;
}	t_pixel_point;

typedef struct s_grid_point
{
	int	y;
	int	x;
}	t_grid_point;

typedef struct s_projection
{
	t_orientation	orientation;
	double			relative_slice_position;
	int				column_index;
	double			ray_distance;
	double			projected_slice_height;

}	t_projection;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	int				f_no;
	int				f_so;
	int				f_we;
	int				f_ea;
	uint8_t			f[4];
	uint8_t			c[4];
}	t_textures;

typedef struct s_map
{
	char	**map;
	int		map_h;
	int		map_w;
	int		empty_line;
	int		fd;
	double	draw_time;
	double	accum_time;
}	t_map;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		x;
	int		y;
	double	m_x;
	double	m_y;
	int		dir;
	double	move_time;
	double	rotate_time;
	double	mouse_time;
	double	m_accum_time;
	double	r_accum_time;
	double	ms_accum_time;
	int32_t	l_y;
	int32_t	l_x;
}	t_player;

typedef struct s_map_lst	t_map_lst;
struct s_map_lst
{
	char		*row;
	t_map_lst	*next;
	t_map_lst	*prev;
};

typedef struct s_data
{
	t_map			map;
	t_map_lst		*map_lst;
	t_textures		txs;
	t_win			win;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*info;
	t_player		pl;
	t_projection	*projection;
	bool			error;
	int				error_msg;
	int				extra;
	struct timeval	last_update;
	struct timeval	now;
}	t_data;

//	ERRORS
void			free_data(t_data *data);
void			*safe_malloc(t_data *data, int size);
int				exit_error(t_data *data, int error, char *value, bool is_exit);
//	PARSING	
void			load_map(t_data *data, char *file);
int				load_rgb_f(t_data *data, char *line, int error);
int				load_rgb_c(t_data *data, char *line, int error);
bool			load_textures(t_data *data, char *line);
void			load_images(t_data *data);
int				map_to_array(t_data *data);
void			map_to_list(t_data *data, char *line);
void			validate_map(t_data *data);
//	RAY CASTING
double			recalculate_angle(double angle_value);
double			degrees_to_radians(double degrees);
void			set_up_wall_orientation(t_data *data, int i, double angle_value,
					bool is_horizontal);
double			calculate_distance(t_data *data, double angle_value, int i,
					t_pixel_point *relative_slice_position);
bool			horizontal_intersection(t_data *data, double angle_value,
					t_pixel_point *pixel_p);
bool			vertical_intersection(t_data *data, double angle_value,
					t_pixel_point *pixel_p);
double			calculate_slice_height(t_data *data, double ray_distance);
double			precise_slice_position(t_orientation orientation,
					t_pixel_point relative_slice_position);
bool			outside_map(t_data *data, t_grid_point *grid_p);
void			draw_image(t_data *data);
void			set_up_view(t_data *data);
//	DELTA TIME
void			key_hook(mlx_key_data_t keydata, void *vdata);
void			delta_time(void *vdata);
//	MOVES	
void			rotate_player(t_data *data);
void			check_moves(t_data *data);

#endif	
