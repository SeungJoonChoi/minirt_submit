#include "minirt.h"

static t_vec stov(char *str)
{
    t_vec ret;

    ret.x = atod(str);
    while (*str != ',')
        ++str;
    ++str;
    ret.y = atod(str);
    while (*str != ',')
        ++str;
    ++str;
    ret.z = atod(str);
    return (ret);
}

static t_color ctov(char *str)
{
    t_color ret;

    ret.x = atod(str) / 255.0;
    while (*str != ',')
        ++str;
    ++str;
    ret.y = atod(str) / 255.0;
    while (*str != ',')
        ++str;
    ++str;
    ret.z = atod(str) / 255.0;
    return (ret);
}

static int put_elements(t_scene *s, char **e)
{
    int ret;

    ret = 0;
    if (!ft_strcmp(e[0], "A"))
        s->ambient = v_mul(ctov(e[2]), atod(e[1]));
    else if (!ft_strcmp(e[0], "C"))
        s->camera = camera(stov(e[1]), stov(e[2]), atod(e[3]), 16.0 / 9.0);
    else if (!ft_strcmp(e[0], "L"))
        ret = obj_add(&s->light, POINT, point_light(stov(e[1]), \
        ctov(e[3]), atod(e[2])));
    else if (!ft_strcmp(e[0], "sp"))
        ret = obj_add(&s->world, SP, sphere(stov(e[1]), atod(e[2]), ctov(e[3])));
    else if (!ft_strcmp(e[0], "pl"))
        ret = obj_add(&s->world, PL, plane(stov(e[1]), stov(e[2]), ctov(e[3])));
    else if (!ft_strcmp(e[0], "cy"))
        ret = obj_add(&s->world, CY, cylinder(stov(e[1]), stov(e[2]), \
        atod(e[3]), atod(e[4]), ctov(e[5])));
    return (ret);
}

// void scene_init(t_scene* scene, int infile)
// {
//     char* buf;
//     char **e;

//     scene->image = image(1600, 900);
//     obj_list_init(&scene->world);
//     obj_list_init(&scene->light);
//     while (1)
//     {
//         buf = get_next_line(infile);
//         if (buf)
//         {
//             e = ft_split(buf, ' ');
//             if(!e || put_elements(scene, e))
//             {
//                 free(buf);
//                 free_strs(e);
//                 scene_clear(scene);
//                 exit_err("Failed to initialize components.");
//             }
//             free(buf);
//             free_strs(e);
//         }
//         else
//             break ;
//     }
// }

void scene_init(t_scene* scene, t_compo *compo)
{
    t_compo *cur;

    scene->image = image(1600, 900);
    obj_list_init(&scene->world);
    obj_list_init(&scene->light);

    cur = compo->next;
    while (cur)
    {
        if (put_elements(scene, cur->split_line))
        {
            minirt_clear(scene, compo);
            exit_err("Failed to initialize components.");
        }
        cur = cur->next;
    }
}