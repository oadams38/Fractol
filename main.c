/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:58:41 by oladams           #+#    #+#             */
/*   Updated: 2023/07/11 17:27:14 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fract	f;

	if (parse_input(ac, av, &f))
	{
		if (!fract_init(&f))
			return (1);
		draw_fractal(&f);
		mlx_mouse_hook(f.win_ptr, deal_mouse, &f);
		mlx_hook(f.win_ptr, ON_KEYDOWN, 0, deal_key, &f);
		mlx_hook(f.win_ptr, ON_DESTROY, 0, end_program, &f);
		mlx_loop(f.mlx_ptr);
	}
	else
	{
		write(1, "\nLaunch the program as such:\n\n./fractol ", 40);
		write(1, "fractal_set [real] [imaginary]\n\nfractal_set ", 44);
		write(1, "= \"Julia\" or \"Mandelbrot\"\n[real] and ", 37);
		write(1, "[imaginary] are the julia set parameters\n\n", 42);
	}
	return (0);
}
