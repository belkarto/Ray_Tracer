/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:47:01 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/22 15:53:59 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdio.h>

//left lower corner 
// origin - horizontal/2 - vertical/2 - focal_length
// camera origin is lookfrom
// camera viewport is lookat
void	init_camera(t_camera *camera)
{
	double h;
	t_vect tmp;
	t_vect vup;

	vup = camera->normalized;
	camera->fov_rad = camera->fov * M_PI / 180;
	camera->focal_length = 1.0;
	h = tan(camera->fov_rad / 2);
	printf("h = %f\n", h);
	camera->viewport_height = 2.0 * h;
	camera->viewport_width = camera->aspect_ratio * camera->viewport_height;
	camera->w = vect_unit(vect_sub(camera->origin, camera->lookat));
	camera->u = vect_unit(vect_cross(vup, camera->w));
	camera->v = vect_cross(camera->w, camera->u);
	camera->horizontal = vect_scale(camera->u, camera->viewport_width);
	camera->vertical = vect_scale(camera->v, camera->viewport_height);
	tmp = vect_scale(camera->w, 1 / camera->focal_length);
	tmp = vect_sub(camera->origin, tmp);
	tmp = vect_sub(tmp, vect_scale(camera->horizontal, 0.5));
	tmp = vect_sub(tmp, vect_scale(camera->vertical, 0.5));
	camera->lower_left_corner = tmp;
}
