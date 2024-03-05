/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:06:56 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 03:21:18 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIN_W 1024
# define SUCCESS_RETURN 0
# define FAILURE_RETURN 1
# define EPSILON 1e-6
# define MAX_DEPTH 50

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include "../libs/linux/mlx.h"
# include "../libs/libft/libft.h"
# include "vectors.h"
# include "camera.h"
# include "image.h"
# include "colors.h"
# include "ray.h"
# include "lighting.h"
# include "objects.h"
# include "error.h"
# include "linked_list_utils.h"
# include "char_utils.h"
# include "data.h"
# include "hited.h"
# include "parsing.h"
# include "key_hook.h"
# include "matrix.h"

void		rerander(t_data *data);
bool		hit_plane(t_data *r, t_hitrecod *rec, t_object *obj);
t_color		ray_color(t_data *data);
t_color		ambient_light(t_lighting *light, t_color color);
void		aplly_light(t_data *data, t_hitrecod *rec);
t_ray		calculate_ray(t_data *data, int x, int y);
bool		get_closet_hit(t_ray r, t_hitrecod *rec, t_cylinder *cy,
				t_qua_sol solution);
t_qua_sol	calc_quadratic_sphere(t_ray r, t_sphere *sp);
t_qua_sol	calculate_quadratic_cylinder(t_ray r, t_cylinder *cy);
void		initialize_rotated_ray(t_ray *rotated_ray, t_ray r, t_mat4 mat);
t_vect		calculate_normal(t_hitrecod *rec, t_cylinder *cy);
bool		sphere_shadow(t_ray r, t_sphere *sphere);
bool		cylinder_shadow(t_ray r, t_cylinder *cy);
bool		intesect_shadow(t_ray r, t_object *obj);

#endif
