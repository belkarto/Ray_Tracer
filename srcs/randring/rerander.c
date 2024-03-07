/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:37:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 02:30:15 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	put_text(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img, 300, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->menu_img.img, 0, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 80, 550, 0xFF0000,
		"RERANDER IMAGE");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 20, 0x0000C0FF,
		"Plane checkboard");
	if (data->switches.checkboard_plane)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 17, 25, 0x0000C0FF, "X");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 50, 0x0000C0FF,
		"Sphere specular");
	if (data->switches.specular)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 17, 55, 0x0000C0FF, "X");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 80, 0x0000C0FF,
		"Sphere gradient");
	if (data->switches.sphere_gradient)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 17, 85, 0x0000C0FF, "X");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 110, 0x0000C0FF,
		"Cylinder gradient");
	if (data->switches.cylinder_gradient)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 17, 115, 0x0000C0FF, "X");
}

void	rerander(t_data *data)
{
	int		x;
	int		y;
	t_color	pixel_color;

	pixel_color = fill_color(0, 0, 0);
	init_camera(data->camera);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->empty_img.img, 300, 0);
	y = -1;
	data->img.samples_count = -1;
	while (++data->img.samples_count < data->img.samples_per_pixel)
	{
		while (++y < data->img.height)
		{
			x = -1;
			while (++x <= data->img.width)
			{
				data->r = calculate_ray(data, x, y);
				av_color(&pixel_color, ray_color(data));
				my_mlx_pixel_put(&data->img, x, y, rgb(pixel_color));
			}
		}
	}
	put_text(data);
}
