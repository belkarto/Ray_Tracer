/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/19 00:59:26 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	hit(t_data *data, t_hitrecod *rec,	t_object *obj)
{
	if (obj->type == SPHERE)
		return (hit_sphere(data, rec, obj));
	else if (obj->type == PLANE)
		return (hit_plane(data, rec, obj));
	else if (obj->type == CYLINDER)
		return (hit_cylinder(data, rec, obj));
	else if (obj->type == TRIANGLE)
		return (hit_triangle(data, rec, obj));
	return (false);
}

bool	hittable_list_hit(t_data *data, t_hitrecod *rec)
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
	rec->shadow_ratio = 1;
	rec->light_ratio = 0;
	rec->specular = fill_color(0, 0, 0);
	if (hit_anything == true)
		aplly_light(data, rec);
	return (hit_anything);
}
