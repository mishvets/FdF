/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 13:26:51 by mshvets           #+#    #+#             */
/*   Updated: 2019/01/18 13:27:30 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //printf

void ft_clear(t_point **all)
{
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
}

t_line	*ft_drawline_init(t_xyz p1, t_xyz p2, t_point *all)
{
	t_line *line;

	if (!(line = (t_line *)malloc(sizeof(t_line))))
		exit (1);
	line->x1 = all->start_x + (int)p1.x;
	line->x2 = all->start_x + (int)p2.x;
	line->y1 = all->start_y + (int)p1.y;
	line->y2 = all->start_y + (int)p2.y;
	line->deltaX = abs((line->x2 - line->x1));
	line->deltaY = abs((line->y2 - line->y1));
	line->signX = line->x1 < line->x2 ? 1 : -1;
	line->signY = line->y1 < line->y2 ? 1 : -1;
	line->error = line->deltaX - line->deltaY;
	return (line);

}

void	ft_drawline(t_xyz p1, t_xyz p2, t_point *all)
{
	t_line *line;

	line = ft_drawline_init(p1, p2, all);
	mlx_pixel_put(all->mlx_ptr, all->win_ptr, line->x2, line->y2,
			all->color[all->color_pos]);
	while(line->x1 != line->x2 || line->y1 != line->y2)
	{
		mlx_pixel_put(all->mlx_ptr, all->win_ptr, line->x1, line->y1,
				all->color[all->color_pos]);
		line->error2 = line->error * 2;
		if(line->error2 > -line->deltaY)
		{
			line->error -= line->deltaY;
			line->x1 += line->signX;
		}
		if(line->error2 < line->deltaX)
		{
			line->error += line->deltaX;
			line->y1 += line->signY;
		}
	}
	free(line);
}

//void	ft_drawline(t_xyz p1, t_xyz p2, t_point *all)
//{
//	int deltaX;
//	int deltaY;
//	int signX;
//	int signY;
//	int error;
//	int error2;
//
//	p1.x = all->start_x + (int)p1.x;
//	p2.x = all->start_x + (int)p2.x;
//	p1.y = all->start_y + (int)p1.y;
//	p2.y = all->start_y + (int)p2.y;
//	deltaX = abs((int)(p2.x - p1.x));
//	deltaY = abs((int)(p2.y - p1.y));
//	signX = p1.x < p2.x ? 1 : -1;
//	signY = p1.y < p2.y ? 1 : -1;
//	error = deltaX - deltaY;
//	mlx_pixel_put(all->mlx_ptr, all->win_ptr, p2.x, p2.y, all->color[all->color_pos]);
//	while(p1.x != p2.x || p1.y != p2.y)
//	{
//		mlx_pixel_put(all->mlx_ptr, all->win_ptr, p1.x, p1.y, all->color[all->color_pos]);
//		error2 = error * 2;
//		if(error2 > -deltaY)
//		{
//			error -= deltaY;
//			p1.x += signX;
//		}
//		if(error2 < deltaX)
//		{
//			error += deltaX;
//			p1.y += signY;
//		}
//	}
//}

void     matrix_mul(double (*C)[3][3], double B[3][3])
{
	double		A[3][3];
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			A[i][j] = (*C)[i][j];
	}
	i = 0;
	while (i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			k = -1;
			(*C)[i][j] = 0;
			while (++k < 3)
				(*C)[i][j] += A[i][k] * B[k][j];
		}
		++i;
	}
}

t_xyz	ft_coordinates(t_data *crawler, int x, t_point *all, t_xyz p2)
{
	p2.x = (x - all->nX/2) * all->base_m[0][0] * all->c_size
			+ (crawler->y - all->nY/2) * all->base_m[1][0] * all->c_size
			+ crawler->row[x] * all->base_m[2][0] * all->z_size;
	p2.y = (x - all->nX/2) * all->base_m[0][1] * all->c_size
			+ (crawler->y - all->nY/2) * all->base_m[1][1] * all->c_size
			+ crawler->row[x] * all->base_m[2][1] * all->z_size;
	p2.z = (x - all->nX/2) * all->base_m[0][2] * all->c_size
			+ (crawler->y - all->nY/2) * all->base_m[1][2] * all->c_size
			+ crawler->row[x] * all->base_m[2][2] * all->z_size;
	return (p2);
}

int 	ft_drawmap(t_point **all)
{
	int		j;
	t_data	*crawler;
	t_xyz	*line;
	t_xyz	p2;

	if (!(line = (t_xyz *)malloc(sizeof(*line) * (*all)->nX)))
		return (0);
	crawler = (*all)->map;
	while (crawler)
	{
		j = 0;
		while (j < (*all)->nX)
		{
			p2 = ft_coordinates(crawler, j, *all, p2);
			if (j)
				ft_drawline(line[j - 1], p2, *all);
			if (crawler->y)
				ft_drawline(line[j], p2, *all);
			line[j] = p2;
			++j;
		}
		crawler = crawler->next;
	}
	free(line);
	return (1);
}

void	ft_draw(t_point **all)
{
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 0,
			(*all)->color[(*all)->color_pos], "Rotate:");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 20,
				   (*all)->color[(*all)->color_pos], "    X - 7 or 4;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 40,
				   (*all)->color[(*all)->color_pos], "    Y - 8 or 5;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 60,
				   (*all)->color[(*all)->color_pos], "    Z - 9 or 6.");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 80,
				   (*all)->color[(*all)->color_pos], "Color - c");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 100,
				   (*all)->color[(*all)->color_pos], "Scale: ");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 120,
				   (*all)->color[(*all)->color_pos], "    Z - z or x;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 140,
				   (*all)->color[(*all)->color_pos], " case - + or -;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 160,
				   (*all)->color[(*all)->color_pos],
				   "Move:  Up, Down, Left, Right;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 180,
				   (*all)->color[(*all)->color_pos], "Clear - p;");
	mlx_string_put((*all)->mlx_ptr, (*all)->win_ptr, 10, 200,
				   (*all)->color[(*all)->color_pos], "Exit  - ESC.");
	ft_drawmap(all);
}

void	ft_rotateX(t_point **all, int key)
{
	int	sign;

	if (key == 89)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->angl = sign * (*all)->del_angl;
	(*all)->rotate_m[0][0] = 1;
	(*all)->rotate_m[0][1] = 0;
	(*all)->rotate_m[0][2] = 0;
	(*all)->rotate_m[1][0] = 0;
	(*all)->rotate_m[1][1] = cos((*all)->angl);
	(*all)->rotate_m[1][2] = -sin((*all)->angl);
	(*all)->rotate_m[2][0] = 0;
	(*all)->rotate_m[2][1] = sin((*all)->angl);
	(*all)->rotate_m[2][2] = cos((*all)->angl);
	matrix_mul(&((*all)->base_m), (*all)->rotate_m);
	ft_draw(all);
}

void	ft_rotateY(t_point **all, int key)
{
	int	sign;

	if (key == 91)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->angl = sign * (*all)->del_angl;
	(*all)->rotate_m[0][0] = cos((*all)->angl);
	(*all)->rotate_m[0][1] = 0;
	(*all)->rotate_m[0][2] = sin((*all)->angl);
	(*all)->rotate_m[1][0] = 0;
	(*all)->rotate_m[1][1] = 1;
	(*all)->rotate_m[1][2] = 0;
	(*all)->rotate_m[2][0] = -sin((*all)->angl);
	(*all)->rotate_m[2][1] = 0;
	(*all)->rotate_m[2][2] = cos((*all)->angl);
	matrix_mul(&((*all)->base_m), (*all)->rotate_m);
	ft_draw(all);
}

void	ft_rotateZ(t_point **all, int key)
{
	int	sign;

	if (key == 92)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->angl = sign * (*all)->del_angl;
	(*all)->rotate_m[0][0] = cos((*all)->angl);
	(*all)->rotate_m[0][1] = -sin((*all)->angl);
	(*all)->rotate_m[0][2] = 0;
	(*all)->rotate_m[1][0] = sin((*all)->angl);
	(*all)->rotate_m[1][1] = cos((*all)->angl);
	(*all)->rotate_m[1][2] = 0;
	(*all)->rotate_m[2][0] = 0;
	(*all)->rotate_m[2][1] = 0;
	(*all)->rotate_m[2][2] = 1;
	matrix_mul(&((*all)->base_m), (*all)->rotate_m);
	ft_draw(all);
}

void	ft_startpointX(t_point **all, int key)
{
	int	sign;

	if (key == 125)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->start_y = (*all)->start_y + sign * (*all)->c_size;
	ft_draw(all);
}

void	ft_startpointY(t_point **all, int key)
{
	int	sign;

	if (key == 124)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->start_x = (*all)->start_x + sign * (*all)->c_size;
	ft_draw(all);
}

void	ft_z(t_point **all, int key)
{
	int	sign;

	if (key == 6)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->z_size = (*all)->z_size + sign * 5;
	ft_draw(all);
}

void	ft_case(t_point **all, int key)
{
	int	sign;

	if (key == 69)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->c_size = (*all)->c_size + sign * 5;
	ft_draw(all);
}

void	ft_color(t_point **all)
{
	mlx_clear_window ((*all)->mlx_ptr, (*all)->win_ptr);
	(*all)->color_pos = ((*all)->color_pos + 1) % 8;
	ft_draw(all);
}