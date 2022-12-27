#include "minirt.h"

t_scene scene_init(t_image img, t_camera cam, double ka, t_color ambient_color)
{
    t_scene scene;

    scene.image = img;
    scene.camera = cam;
    obj_list_init(&(scene.world));
    obj_list_init(&(scene.light));
    scene.ambient = vec_mul(ambient_color, ka);
    return (scene);
}