/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 17:28:26 by mshvets           #+#    #+#             */
/*   Updated: 2019/03/12 19:56:34 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include "../libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

# define HEIGHT	720
# define WIDTH	1280

typedef struct		s_data
{
	int				*row;
	int				y;
	struct s_data	*next;
}					t_data;

typedef struct		s_xyz
{
	double			x;
	double			y;
	double			z;
}					t_xyz;

typedef struct		s_point
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				c_size;
	int				z_size;
	int				start_x;
	int				start_y;
	int				nx;
	int				ny;
	double			base_m[3][3];
	double			rotate_m[3][3];
	double			angl;
	double			del_angl;
	int				*color;
	int				color_pos;
	t_data			*map;
}					t_point;

typedef struct		s_line
{
	int				delta_x;
	int				delta_y;
	int				sign_x;
	int				sign_y;
	int				error;
	int				error2;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
}					t_line;

int					ft_map(char *file, t_point **all);
void				ft_rotate_x(t_point **all, int key);
void				ft_rotate_y(t_point **all, int key);
void				ft_rotate_z(t_point **all, int key);
void				ft_draw(t_point **all);
void				ft_clear(t_point **all);
void				ft_color(t_point **all);
void				ft_startpoint_x(t_point **all, int key);
void				ft_startpoint_y(t_point **all, int key);
void				ft_z(t_point **all, int sign);
void				ft_case(t_point **all, int key);
void				ft_error(int i);

#endif
