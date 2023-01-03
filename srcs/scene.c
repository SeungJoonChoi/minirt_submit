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

    ret.x = atod(str) / 255.999;
    while (*str != ',')
        ++str;
    ++str;
    ret.y = atod(str) / 255.999;
    while (*str != ',')
        ++str;
    ++str;
    ret.z = atod(str) / 255.999;
    return (ret);
}

int put_elements(t_scene *scene, char *buf)
{
    char **e;

    e = ft_split(buf, ' ');
    if (!e)
        return (1);
    if (!ft_strcmp(e[0], "A"))
        scene->ambient = v_mul(ctov(e[2]), atod(e[1]));
    else if (!ft_strcmp(e[0], "C"))
        scene->camera = camera(stov(e[1]), stov(e[2]), atod(e[3]), 16.0 / 9.0);
    else if (!ft_strcmp(e[0], "L"))
    {
        if (obj_add(&scene->light, POINT, point_light(stov(e[1]), ctov(e[3]), atod(e[2]))))
            return (1);
    }
    else if (!ft_strcmp(e[0], "sp"))
    {
        if (obj_add(&scene->world, SPHERE, sphere(stov(e[1]), atod(e[2]), ctov(e[3]))))
            return (1);
    }
    else if (!ft_strcmp(e[0], "pl"))
    {
        if (obj_add(&scene->world, PLANE, plane(stov(e[1]), stov(e[2]), ctov(e[3]))))
            return (1);
    }
    else if (!ft_strcmp(e[0], "cy"))
    {
        if (obj_add(&scene->world, CYLINDER, cylinder(stov(e[1]), stov(e[2]), \
        atod(e[3]), atod(e[4]), ctov(e[5]))))
            return (1);
    }
    free_strs(e);
    return (0);
}

t_scene scene_init(char *infile)
{
    t_scene scene;
    int fd;
    char* buf;

    scene.image = image(1600, 900);
    obj_list_init(&(scene.world));
    obj_list_init(&(scene.light));
    fd = open(infile, O_RDONLY);
    while (1)
    {
        buf = get_next_line(fd);
        if (buf)
        {
            if(put_elements(&scene, buf))
            {
                free(buf);
                exit(1);
            }
            free(buf);
        }
        else
            break ;
    }
    close(fd);
    return (scene);
}