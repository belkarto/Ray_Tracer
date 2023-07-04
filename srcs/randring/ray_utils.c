/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/04 03:39:53 by belkarto         ###   ########.fr       */
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
	return (ray);
}

//ray at is used to determine the point at which the ray hits the sphere
t_vect	ray_hit_point(t_ray *r, double t)
{
	t_vect tmp;

	tmp = vect_scale(r->direction, t);
	tmp = vect_add(r->origin, tmp);
	return (tmp);
}

// -------- to delet later if not used ---------
//set face normal is used to determine if the ray is inside or outside the sphere 
//if the ray is inside the sphere, the normal is inverted 
/* void set_face_normal(t_ray *r, t_hitrecod *rec)
{
	rec->front_face = vect_dot(r->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vect_scale(rec->normal, -1);
} */

//hittable list
//linked list for hittable list

bool	hit(t_data *data, t_hitrecod *rec,	t_object *obj)
{
	if (obj->type == SPHERE)
		return (hit_sphere(data, rec, obj));
	else if (obj->type == PLANE)
		return (hit_plane(data, rec, obj));
	return (false);
}




bool	is_in_shadow(t_data *data, t_hitrecod *rec)
{
	t_vect ray_to_light;
	t_ray shadow_ray;
	t_hitrecod shadow_rec;
	t_object *tmp;

	ray_to_light = vect_sub(data->lighting->light->point, rec->p);
	shadow_ray.origin = vect_add(rec->p, vect_normalize(rec->normal));
	shadow_ray.direction = ray_to_light;
	tmp = data->head;
	while (tmp)
	{
		if (hit(data, &shadow_rec, tmp))
		{
			if (shadow_rec.hit_point_distance < vect_length(ray_to_light))
				return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}










bool hittable_list_hit(t_data *data, t_hitrecod *rec)
{
	t_hitrecod	tmp_rec;
	bool		hit_anything;

	hit_anything = false;
	data->r.t_max = INFINITY;
	data->r.t_min = EPSILON;
	tmp_rec.hit_point_distance = data->r.t_max;
	while (data->object)
	{
		if (hit(data, &tmp_rec, data->object))
		{
			hit_anything = true;
			data->r.t_max = tmp_rec.hit_point_distance;
			*rec = tmp_rec;
		}
		data->object = data->object->next;
	}
	
	data->object = data->head;
	if (is_in_shadow(data, rec))
	{
		rec->color = color_scalar(rec->color, 0.4);
	}

	double		dot;
	if (data->lighting->light->ratio > EPSILON)
	{
		if (rec->type == SPHERE)
		{
			dot = fmax(vect_dot(data->lighting->light->point, rec->normal), 0.0);
			rec->color = color_scalar(rec->color, dot);
		}
		else if (rec->type == PLANE)
		{
			dot = fmax(vect_dot(rec->normal, vect_sub(data->lighting->light->point, rec->p)), 0.0);
			rec->color = color_scalar(rec->color, dot);
		}
	}
	rec->color = ambient_light(data, rec->color);
	return (hit_anything);
}
