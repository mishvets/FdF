/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 19:34:30 by mshvets           #+#    #+#             */
/*   Updated: 2019/01/16 19:34:49 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

static void	ft_adddata(t_point **all, char **arr, int y)
{
	t_data	*new;
	t_data	*crawler;
	int		i;

	i = -1;
	if (!(new = (t_data *)malloc(sizeof(*new))))
		exit(1);
	if (!(new->row = (int *)malloc((*all)->nx * sizeof(int))))
		exit(1);
	while (++i < (*all)->nx)
		new->row[i] = ft_atoi(arr[i]);
	ft_strdelarr(arr, i);
	new->y = y;
	new->next = NULL;
	crawler = (*all)->map;
	if (y > 0)
	{
		while (crawler->next)
			crawler = crawler->next;
		crawler->next = new;
	}
	else
		(*all)->map = new;
}

static int	ft_valid(t_point **all, char **arr, char *line)
{
	int i;
	int j;

	i = 0;
	if ((*all)->nx < 0)
		(*all)->nx = (int)ft_cntwrd(line, ' ');
	else if ((*all)->nx != (int)ft_cntwrd(line, ' '))
	{
		ft_printf("Number elem in rows not constant %d/%d\n",
				(*all)->nx, (int)ft_cntwrd(line, ' '));
		return (0);
	}
	while (i < (*all)->nx)
	{
		j = 0;
		while (arr[i][j])
		{
			if ((arr[i][j] < '0' || arr[i][j] > '9') && (arr[i][j] != '-'))
				return (0);
			++j;
		}
		++i;
	}
	free(line);
	return (1);
}

static int	*ft_colorinit(void)
{
	int *color;

	if (!(color = (int *)malloc(sizeof(int) * 8)))
		return (0);
	color[0] = 0xFFFFFF;
	color[1] = 0x800080;
	color[2] = 0x0000FF;
	color[3] = 0x00FFFF;
	color[4] = 0x008000;
	color[5] = 0xFFFF00;
	color[6] = 0xFF0000;
	color[7] = 0x000000;
	return (color);
}

static int	ft_init(t_point **all)
{
	(*all)->start_x = WIDTH / 2;
	(*all)->start_y = HEIGHT / 2;
	if ((*all)->nx > (*all)->ny)
		(*all)->c_size = 6 * HEIGHT / (8 * (*all)->nx);
	else
		(*all)->c_size = 6 * HEIGHT / (8 * (*all)->ny);
	(*all)->base_m[0][0] = 1;
	(*all)->base_m[0][1] = 0;
	(*all)->base_m[0][2] = 0;
	(*all)->base_m[1][0] = 0;
	(*all)->base_m[1][1] = 1;
	(*all)->base_m[1][2] = 0;
	(*all)->base_m[2][0] = 0;
	(*all)->base_m[2][1] = 0;
	(*all)->base_m[2][2] = 1;
	(*all)->angl = 0;
	(*all)->del_angl = 18 * 3.14 / 180;
	(*all)->z_size = 10;
	(*all)->color = ft_colorinit();
	(*all)->color_pos = 0;
	return (1);
}

int			ft_map(char *file, t_point **all)
{
	int		fd;
	char	*line;
	char	**arr;
	int		y;
	int		c;

	y = 0;
	(*all)->nx = -1;
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error(1);
	while ((c = get_next_line(fd, &line)) == 1)
	{
		if (!(arr = ft_strsplit(line, ' ')))
			exit(1);
		if (!ft_valid(all, arr, line))
			ft_error(2);
		ft_adddata(all, arr, y++);
	}
	if (c == -1)
		ft_error(1);
	free(line);
	(*all)->ny = y;
	if (!(ft_init(all)))
		exit(1);
	return (0);
}
