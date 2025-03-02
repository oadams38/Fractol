/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oladams <oladams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:33:34 by oladams           #+#    #+#             */
/*   Updated: 2023/07/22 21:38:59 by oladams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include "mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define WIN_TITLE "Fractol"

# define ON_KEYDOWN 2
# define ON_DESTROY 17

# define ESC		53
# define SPACE		49
# define DEL		51
# define ENTER		36
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define PLUS		69
# define MINUS		78
# define ONE		83
# define TWO		84
# define S			1

# define MOVE_RATE	0.03
# define MAX_ITER	200

typedef struct s_fract
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_id;
	char	*img_addr;
	int		bits_pix;
	int		width;
	int		bytes_line;
	int		height;
	int		endian;
	double	x_start;
	double	x_end;
	double	y_start;
	double	y_end;
	int		max_iter;
	double	c_real;
	double	c_imag;
	char	type;
	int		(*colourizer)(struct s_fract *f, double n);
	int		seed;
	int		r_sin_ratio;
	int		v_sin_ratio;
	int		b_sin_ratio;
	int		smooth;
}				t_fract;

//init.c
int		fract_init(t_fract *f);
void	set_start_frame_values(t_fract *f);
int		parse_input(int ac, char **av, t_fract *f);

//draw_1.c
void	draw_fractal(t_fract *f);
void	move_frame(t_fract *f, int key);

//draw_2.c
int		get_colour(int t, int r, int g, int b);
double	log_multiplicator(int n);
int		colour_hippie(t_fract *f, double n);
int		colour_electric(t_fract *f, double n);
void	change_colour_scheme(t_fract *f, int key);

//events.c
int		deal_key(int key, t_fract *f);
int		deal_mouse(int button, int x, int y, t_fract *f);
int		handle_no_event(t_fract *f);
int		end_program(t_fract *f);

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
double	ft_atof(char *str);
int		pseudo_random(int min, int max, t_fract *f);

#endif