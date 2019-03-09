/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:51:44 by mshvets           #+#    #+#             */
/*   Updated: 2019/01/03 11:51:46 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
#include <stdio.h>
//
//void drawLine(int x, int y, t_point *all)
//{
//	int x1;
//	int x2;
//	int y2;
//	int y1;
//	const int deltaX;
//	const int deltaY;
//	const int signX;
//	const int signY;
//
//	x1 = all->start_x + x * all->c_size - all->arr[x][y] * 10;
//	x2 = all->start_x + (x + 1) * all->c_size - all->arr[x + 1][y] * 10;
//	y1 = all->start_y + y * all->c_size;
//	y2 = all->start_y + (y + 1) * all->c_size;
//	deltaX = abs(x2 - x1);
//	deltaY = abs(y2 - y1);
//	signX = x1 < x2 ? 1 : -1;
//	signY = y1 < y2 ? 1 : -1;
//
//	//
//	int error = deltaX - deltaY;
//	//
//	int color = 0xFFFFFF;
//	mlx_pixel_put(all->mlx_ptr, all->win_ptr, x2, y2, color);
//	while(x1 != x2 || y1 != y2)
//	{
//		mlx_pixel_put(all->mlx_ptr, all->win_ptr, x1, y1, color);
//		const int error2 = error * 2;
//		//
//		if(error2 > -deltaY)
//		{
//			error -= deltaY;
//			x1 += signX;
//		}
//		if(error2 < deltaX)
//		{
//			error += deltaX;
//			y1 += signY;
//		}
//	}
//}
//
//int drawall(t_point *all)
//{
//
//	y = 0;
//	while (y < (all)->ny)
//	{
//		x = 0;
//		while (x < (all)->nx)
//		{
//			drawLine(x, y, all);
//			++x;
//		}
//		++y;
//	}
//	return (0);
//}
//
int deal_key(int key, void *param)
{
	if (key == 53)
	{
		system("leaks fdf -q");
		exit(0);
	}
	else if (key == 35)
		ft_clear((t_point **)param);
	else if (key == 86 || key == 89)
		ft_rotateX((t_point **)param, key);
	else if (key == 87 || key == 91)
		ft_rotateY((t_point **)param, key);
	else if (key == 88 || key == 92)
		ft_rotateZ((t_point **)param, key);
	else if (key == 125 || key == 126)
		ft_startpointX((t_point **)param, key);
	else if (key == 123 || key == 124)
		ft_startpointY((t_point **)param, key);
	else if (key == 6 || key == 7)
		ft_z((t_point **)param, key);
	else if (key == 69 || key == 78)
		ft_case((t_point **)param, key);
	else if (key == 8)
		ft_color((t_point **)param);
	return (0);
}


//my
void ft_printmap(t_point *all)
{
	int		j;
	t_data	*crawler;

	crawler = all->map;
	while (crawler)
	{
		j = 0;
		while (j < all->nX)
		{
			ft_putnbr(crawler->row[j]);
			ft_putstr(" ");
			++j;
		}
		ft_putstr("\n");
		crawler = crawler->next;
	}
}

void	ft_specsize(char **argv, t_point **all)
{
	if (!ft_isdigit(argv[2][0]) || !ft_isdigit(argv[3][0]))
	{
		ft_putstr("Usage : ");
		ft_putstr(argv[0]);
		ft_putstr(" <filename> [ case_size z_size ]\n");
		exit(0);
	}
	(*all)->c_size = ft_atoi(argv[2]);
	(*all)->z_size = ft_atoi(argv[3]);
}

int main(int argc, char **argv)
{
	t_point *all;

	all = (t_point *)malloc(sizeof(*all));
	if (!(argc == 2 || argc == 4))
	{
		ft_putstr("Usage : ");
		ft_putstr(argv[0]);
		ft_putstr(" <filename> [ case_size z_size ]\n");
		exit(0);
	}
	ft_map(argv[1], &all);
	if (argc == 4)
		ft_specsize(argv, &all);
//	ft_printmap(all);
	if (!(all->mlx_ptr = mlx_init())) //the connection login to the graphical server
		exit(1);
	all->win_ptr = mlx_new_window(all->mlx_ptr, WIDTH, HEIGHT, "mlx 42");
	ft_draw(&all);
	mlx_hook(all->win_ptr, 2, 5, deal_key, &all); //was - mlx_key_hook(all->win_ptr, deal_key, &all);
	mlx_loop(all->mlx_ptr);
	system("leaks FdF -q");
	exit(0);
}
