#include "minirt.h"

int rgb_to_int(double trans, t_vec *color)
{
    int t;
    int r;
    int g;
    int b;

    t = trans * 255.999;
    r = color->x * 255.999;
    g = color->y * 255.999;
    b = color->z * 255.999;
    return (t << 24 | r << 16 | g << 8 | b);
}


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    // 1차원으로 나열된 메모리 구조안에서 y * 가로길이 + x * 픽셀당 저장된 데이터크기(4바이트)
	*(unsigned int*)dst = color;
}