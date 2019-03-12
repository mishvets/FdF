/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:25:08 by mshvets           #+#    #+#             */
/*   Updated: 2019/03/12 19:25:12 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

void	matrix_mul(double (*c)[3][3], double b[3][3])
{
	double		a[3][3];
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			a[i][j] = (*c)[i][j];
	}
	i = 0;
	while (i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			k = -1;
			(*c)[i][j] = 0;
			while (++k < 3)
				(*c)[i][j] += a[i][k] * b[k][j];
		}
		++i;
	}
}

void	ft_rotate_x(t_point **all, int key)
{
	int	sign;

	if (key == 89)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
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

void	ft_rotate_y(t_point **all, int key)
{
	int	sign;

	if (key == 91)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
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

void	ft_rotate_z(t_point **all, int key)
{
	int	sign;

	if (key == 92)
		sign = 1;
	else
		sign = -1;
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
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

void	ft_clear(t_point **all)
{
	mlx_clear_window((*all)->mlx_ptr, (*all)->win_ptr);
}
