#include "minirt.h"

t_vec lower_left_corner(t_camera *camera)
{
    t_vec ret;

    ret.x = camera->orig.x - (camera->horizontal.x / 2.0) - (camera->vertical.x / 2.0) + camera->w.x;
    ret.y = camera->orig.y - (camera->horizontal.y / 2.0) - (camera->vertical.y / 2.0) + camera->w.y;
    ret.z = camera->orig.z - (camera->horizontal.z / 2.0) - (camera->vertical.z / 2.0) + camera->w.z;
    return (ret);
}

t_camera camera(t_vec orig, t_vec dir, double fov, double aspect_ratio)
{
    t_camera ret;
    double theta;
    double h;
    double viewport_height;
    double viewport_width;
    t_vec vup;

    theta = degToRad(fov);
    h = tan(theta / 2.0); //탄젠트 세타로 h(뷰포트 높이의 절반) 길이 구하기
    viewport_height = 2.0 * h;
    viewport_width = aspect_ratio * viewport_height;

    // w와 외적해서 u 구하기
    vup = vec(0, 1, 0);
    if (dir.x == 0 && dir.y != 0 && dir.z == 0)
        vup = vec(0, 0, 1);
    
    ret.w = vec_unit(dir); // 뷰포트로 향한 카메라의 방향벡터
    ret.u = vec_unit(vec_cross(vup, ret.w)); // 뷰포트의 가로(x축) 방향벡터
    ret.v = vec_cross(ret.w, ret.u); // 뷰포트의 세로(y축) 방향벡터
    //왼손 좌표계에서는 왼손 법칙 -> https://stackoverflow.com/questions/4820400/does-the-method-for-computing-the-cross-product-change-for-left-handed-coordinat

    ret.orig = orig;

    ret.horizontal = vec_mul(ret.u, viewport_width); //뷰포트 가로 벡터
    ret.vertical = vec_mul(ret.v, viewport_height); //뷰포트 세로 벡터
    ret.lower_left_corner = lower_left_corner(&ret); //뷰포트 왼쪽 하단의 정점 좌표
    return (ret);
}