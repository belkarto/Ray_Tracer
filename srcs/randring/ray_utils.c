/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/22 18:13:20 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdbool.h>

t_ray ray_new(t_camera * cam, double x, double y)
{
	t_ray ray;
	t_vect tmp;
	t_vect tmp2;

	tmp = vect_scale(cam->horizontal, x);
	tmp2 = vect_scale(cam->vertical, y);
	ray.origin = cam->origin;
	ray.direction = vect_add(cam->lower_left_corner, tmp);
	ray.direction = vect_add(ray.direction, tmp2);
	ray.direction = vect_sub(ray.direction, cam->origin);
	/* t_ray ray;

	   ray.origin = origin;
	   ray.direction = direction; */
	return (ray);
}

t_vect	ray_at(t_ray *r, double t)
{
	return (vect_add(r->origin, vect_scale(r->direction, t)));
}

void set_face_normal(t_ray *r, t_hitrecod *rec)
{
	rec->front_face = vect_dot(r->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vect_scale(rec->normal, -1);
}

//hittable list
//linked list for hittable list
t_sphere	*sphere_new(t_vect center, double radius)
{
	t_sphere *sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	return (sp);
}

/* t_vect av_color(t_vect color1, t_vect color2)
{
	t_vect tmp;

	if (color1.x == 0 && color1.y == 0 && color1.z == 0)
		return (color2);
	if (color2.x == 0 && color2.y == 0 && color2.z == 0)
		return (color1);
	tmp.x = (color1.x + color2.x) / 2;
	tmp.y = (color1.y + color2.y) / 2;
	tmp.z = (color1.z + color2.z) / 2;
	return (tmp);
} */



t_vect vect_reflect(t_vect v, t_vect n)
{
	return (vect_sub(v, vect_scale(n, 2 * vect_dot(v, n))));
}

bool	hit(t_ray *r, double t_min, double t_max, t_hitrecod *rec,	t_object *obj)
{
	if (obj->type == SPHERE)
		return (hit_sphere(r, t_min, t_max, rec, obj));
	else if (obj->type == PLANE)
		return (hit_plane(r, t_min, t_max, rec, obj));
	return (false);
}

bool hittable_list_hit(t_object *list, t_ray *r, double t_min, double t_max, t_hitrecod *rec)
{
	t_hitrecod	tmp_rec;
	bool		hit_anything;
	double		closest_so_far;
	t_object	*tmp;

	hit_anything = false;
	closest_so_far = t_max;
	tmp_rec.color_set = false;
	tmp = list;
	while (tmp)
	{
		if (hit(r, t_min, closest_so_far, &tmp_rec, tmp))
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}
