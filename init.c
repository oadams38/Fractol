/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:36:01 by oladams           #+#    #+#             */
/*   Updated: 2023/07/17 19:08:26 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_start_frame_values(t_fract *f)
{
	if (f->type == 'm')
	{
		f->x_start = -2.5;
		f->x_end = 1.5;
		f->y_start = -2;
		f->y_end = 2;
	}
	else
	{
		f->x_start = -2.5;
		f->x_end = 2.5;
		f->y_start = -2.5;
		f->y_end = 2.5;
	}
	if (WIN_HEIGHT > WIN_WIDTH)
	{
		f->y_start *= (double)WIN_HEIGHT / (double)WIN_WIDTH;
		f->y_end *= (double)WIN_HEIGHT / (double)WIN_WIDTH;
	}
	if (WIN_WIDTH > WIN_HEIGHT)
	{
		f->x_start *= (double)WIN_WIDTH / (double)WIN_HEIGHT;
		f->x_end *= (double)WIN_WIDTH / (double)WIN_HEIGHT;
	}
}

int	fract_init(t_fract *f)
{
	f->bits_pix = 8;
	f->width = WIN_WIDTH;
	f->bytes_line = WIN_WIDTH * 4;
	f->height = WIN_HEIGHT;
	f->endian = 1;
	f->colourizer = colour_electric;
	f->smooth = -1;
	f->r_sin_ratio = 2;
	f->v_sin_ratio = 3;
	f->b_sin_ratio = 19;
	f->seed = 282441635;
	f->mlx_ptr = mlx_init();
	if (!(f->mlx_ptr))
		return (0);
	f->win_ptr = mlx_new_window(f->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!(f->win_ptr))
		return (0);
	f->img_id = mlx_new_image(f->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!(f->img_id))
		return (0);
	f->img_addr = mlx_get_data_addr(f->img_id, &(f->bits_pix),
			&(f->bytes_line), &(f->endian));
	f->max_iter = MAX_ITER;
	set_start_frame_values(f);
	return (1);
}

static int	ft_is_float(char *num)
{
	int	i;
	int	point;
	int	dec;

	i = 0;
	point = 0;
	dec = 0;
	while (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i] >= '0' && num[i] <= '9')
		i++;
	if (num[i] == '.')
	{
		point++;
		i++;
	}
	while (num[i] >= '0' && num[i] <= '9')
	{
		dec++;
		i++;
	}
	if (num[i] != '\0' || (point && !dec))
		return (0);
	return (1);
}

int	parse_input(int ac, char **av, t_fract *f)
{
	if (ac != 2 && ac != 4)
		return (0);
	if (!ft_strncmp(av[1], "julia", 6) || !ft_strncmp(av[1], "Julia", 6))
	{
		if (ac != 4 || !ft_is_float(av[2]) || !ft_is_float(av[3]))
			return (0);
		f->type = 'j';
		f->c_real = ft_atof(av[2]);
		f->c_imag = -ft_atof(av[3]);
	}
	else if (!ft_strncmp(av[1], "mandelbrot", 11)
		|| !ft_strncmp(av[1], "Mandelbrot", 11))
	{
		if (ac != 2)
			return (0);
		f->type = 'm';
	}
	else
		return (0);
	return (1);
}
