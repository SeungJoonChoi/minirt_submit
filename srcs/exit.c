#include "minirt.h"

void exit_err(char *msg)
{
    ft_putendl_fd(msg, 2);
    exit(1);
}