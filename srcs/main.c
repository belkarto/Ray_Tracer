/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/12 06:00:18 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <stdio.h>

int	rgb(double r, double g, double b)
{
	int	rgb;

	rgb = 0x00;
	r = 255.999 * r;
	g = 255.999 * g;
	b = 255.999 * b;
	rgb += (int)r << 16;
	rgb += (int)g << 8;
	rgb += (int)b;
	return (rgb);
}

bool	hit_sphere(t_vect center, double radius, t_ray *r)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vect_sub(r->origin, center);
	a = vect_dot(r->direction, r->direction);
	b = 2.0 * vect_dot(oc, r->direction);
	c = vect_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

t_vect ray_color(t_ray *r)
{
	t_vect unit_direction;
	double t;

	if (hit_sphere(vect_new(0, 0, -2), 1.0, r))
		return (vect_new(0.5, 0.5, 0.5));
	unit_direction = vect_unit(r->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	// this calculate t between 0 and 1
	// remove the comment below to make background yellow
	// return(vect_new(1.0, 1.0, 0.0));
	return (vect_add(vect_scale(vect_new(0.0, 0.0, 1.0), 1.0 - t), vect_scale(vect_new(1, 0.0, 0.0), t)));
}

void	fill_img(t_img *img)
{
	int	x;
	int	y;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	double	focal_length;
	double	image_width;
	double	image_height;
	t_vect	origin;
	t_vect	horizontal;
	t_vect	vertical;
	t_vect	lower_left_corner;

	//image
	//put this in a struct later
	//and put it befor mlx_new_window and mlx_new_image
	//and put it in a function and use those values in mlx_new_window and 
	//mlx_new_image
	//and maybe put put them as global variables
	aspect_ratio = 16.0 / 9.0;
	image_width = WIN_W;
	image_height = (int)(image_width / aspect_ratio);
	//camera
	//viewport is the rectangle that we project the world
	viewport_height = 2.0;
	viewport_width = aspect_ratio * viewport_height;
	//focal_length is the distance between the camera and the viewport_height
	focal_length = 1.0;
	//origin is the position of the camera
	origin = vect_new(0, 0, 0);
	//horizontal is the width of the viewport
	horizontal = vect_new(viewport_width, 0, 0);
	//vertical is the height of the viewport 
	vertical = vect_new(0, viewport_height, 0);
	//lower_left_corner is the bottom left corner of the viewport 
	//we need the lower_left_corner to calculate the ray 
	//that goes from the camera to the pixel 
	lower_left_corner = vect_sub(vect_sub(vect_sub(origin, vect_scale(horizontal, 1.0/2)), vect_scale(vertical, 1.0/2)), vect_new(0, 0, focal_length));
	//render
	y = 0;
	while (y < image_height)
	{
		x = 0;
		while (x <= image_width)
		{
			//u is the position of the pixel on the horizontal axis
			double u = (double)x / (image_width - 1);
			//v is the position of the pixel on the vertical axis
			double v = (double)(image_height - y) / (image_height - 1);
			//r is the ray that goes from the camera to the pixel
			t_ray r = ray_new(origin, vect_add(lower_left_corner, vect_add(vect_scale(horizontal, u), vect_scale(vertical, v))));
			//pixel_color is the color of the pixel 
			//we used vector as a color because it's easier to work with 
			//-------------------------------------------------------------
			//          note!! need to creat color struct later	           |
			//          inside ray struct and use it here                  |
			//-------------------------------------------------------------
			t_vect pixel_color = ray_color(&r);
			// printf("pixel_color: %f %f %f\n", pixel_color.x, pixel_color.y, pixel_color.z);
			my_mlx_pixel_put(img, x, y, rgb(pixel_color.x, pixel_color.y, pixel_color.z));
			// my_mlx_pixel_put(img, x, y, rgb((double)x / WIN_W, (double)(WIN_H - y) / WIN_H, 0.25));
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_data	mlx;
	t_img	img;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, "miniRT");
	img.img = mlx_new_image(mlx.mlx_ptr, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	fill_img(&img);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, 0, 0);
	mlx_hook(mlx.win_ptr, 17, 0, close_win, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, key_hook, &mlx);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
