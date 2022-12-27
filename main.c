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

static int close(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}

int main()
{
    t_data data;
    
    // t_ray ray;
    t_color pixel_color;
    t_vars vars;

    t_scene scene;

    scene = scene_init(image(1600, 900), camera(vec(0, 0, 0), \
    vec(0, 0, 1), 90.0, 1600.0 / 900.0), 0.2, color(1, 1, 1));

    //object
    obj_add(&scene.world, SPHERE, sphere(vec(-5, 0, 10), 3, color(0.7, 0.2, 0.2)));
    // obj_add(&scene.world, SPHERE, sphere(vec(0, 0, 0), 20, color(0.2, 0.7, 0.2)));
    obj_add(&scene.world, SPHERE, sphere(vec(5, 0, 10), 3, color(0.2, 0.2, 0.7)));
    // obj_add(&scene.world, PLANE, plane(vec(0, 0, 0), vec(0, 1, 0), color(0.5, 0.5, 0.5)));
    // obj_add(&scene.world, PLANE, plane(vec(0, 20, 0), vec(0, 1, 0), color(0.5, 0.1, 0.5)));
    obj_add(&scene.world, PLANE, plane(vec(0, -20, 0), vec(0, 1, 0), color(0.5, 0.1, 0.5)));
    obj_add(&scene.world, CYLINDER, cylinder(vec(0, 0, 10), vec(0.5, -0.3, -1), 4, 8, color(0.3, 0.7, 0.3)));
    // obj_add(&scene.world, CYLINDER, cylinder(vec(0, 4, 20), vec(0, 1, 0), 4, 8, color(0.3, 0.7, 0.3)));
    // obj_add(&scene.world, CYLINDER, cylinder(vec(0, 0, 0), vec(0, 0, 1), 20, 50, color(0.3, 0.7, 0.3)));

    //light
    obj_add(&scene.light, POINT, point_light(vec(-15, 15, -10), color(1, 1, 1), 0.3));
    // obj_add(&scene.light, POINT, point_light(vec(15, 15, -10), color(1, 1, 1), 0.2));
    // obj_add(&scene.light, POINT, point_light(vec(2, 2, -9), color(1, 1, 1), 0.6));

    int j;
    int i;
    double u;
    double v;



    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, scene.image.image_width, scene.image.image_height, "seunchoi_minirt");
    data.img = mlx_new_image(vars.mlx, scene.image.image_width, scene.image.image_height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
    // 뷰포트의 왼쪽하단부터 그리기 위해 i = 0, j = 높이 부터 시작
    j = scene.image.image_height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene.image.image_width)
        {
            u = (double)i / (double)(scene.image.image_width - 1);
            v = (double)j / (double)(scene.image.image_height - 1);
            scene.ray = ray_viewport(&scene, u, v);
            pixel_color = ray_color(&scene);
            // mlx_pixel_put(mlx_ptr, mlx_win, i, img.image_height - 1 - j, rgb_to_int(0.0, &color));
            my_mlx_pixel_put(&data, i, scene.image.image_height - 1 - j, rgb_to_int(0.0, &pixel_color));
            ++i;
        }
        --j;
    }

    mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
    mlx_hook(vars.win, X_EVENT_KEY_PRESS, 0, &key_press, &vars);
    mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &close, &vars);
    mlx_loop(vars.mlx);

    obj_clear(&scene.world);

    return (0);
}