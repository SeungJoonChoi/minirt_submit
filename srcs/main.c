#include "minirt.h"

static int key_press(int keycode, t_vars *vars)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

static int quit_window(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}

int main(int argc, char **argv)
{
    t_vars vars;
    t_scene scene;
    t_compo compo;
    int fd;

    if (argc != 2)
        return (1);
    fd = open_file(argv[1]);
    init_compo(&compo, fd);

    scene_init(&scene, &compo);
    close(fd);

    // scene = scene_init(image(1600, 900), camera(vec(0, 0, 0), \
    // vec(0, 0, 1), 90.0, 1600.0 / 900.0), 0.2, color(1, 1, 1));

    // //object
    // obj_add(&scene.world, SPHERE, sphere(vec(-5, 0, 10), 3, color(0.7, 0.2, 0.2)));
    // // obj_add(&scene.world, SPHERE, sphere(vec(0, 0, 0), 20, color(0.2, 0.7, 0.2)));
    // obj_add(&scene.world, SPHERE, sphere(vec(5, 0, 10), 3, color(0.2, 0.2, 0.7)));
    // // obj_add(&scene.world, PLANE, plane(vec(0, 0, 0), vec(0, 1, 0), color(0.5, 0.5, 0.5)));
    // // obj_add(&scene.world, PLANE, plane(vec(0, 20, 0), vec(0, 1, 0), color(0.5, 0.1, 0.5)));
    // obj_add(&scene.world, PLANE, plane(vec(0, -20, 0), vec(0, 1, 0), color(0.5, 0.1, 0.5)));
    // obj_add(&scene.world, CYLINDER, cylinder(vec(0, 0, 10), vec(0.5, -0.3, -1), 4, 8, color(0.3, 0.7, 0.3)));
    // // obj_add(&scene.world, CYLINDER, cylinder(vec(0, 4, 20), vec(0, 1, 0), 4, 8, color(0.3, 0.7, 0.3)));
    // // obj_add(&scene.world, CYLINDER, cylinder(vec(0, 0, 0), vec(0, 0, 1), 20, 50, color(0.3, 0.7, 0.3)));

    // //light
    // obj_add(&scene.light, POINT, point_light(vec(-15, 15, -10), color(1, 1, 1), 0.3));
    // // obj_add(&scene.light, POINT, point_light(vec(15, 15, -10), color(1, 1, 1), 0.2));
    // // obj_add(&scene.light, POINT, point_light(vec(2, 2, -9), color(1, 1, 1), 0.6));

    set_mlx(&vars, &scene);
    image_put(&vars, &scene);

    minirt_clear(&scene, &compo);

    mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
    mlx_hook(vars.win, X_EVENT_KEY_PRESS, 0, &key_press, &vars);
    mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &quit_window, &vars);
    mlx_loop(vars.mlx);

    return (0);
}