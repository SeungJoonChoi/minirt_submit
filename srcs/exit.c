#include "minirt.h"

void exit_err(char *msg)
{
    ft_putendl_fd(msg, 2);
    exit(1);
}

void exit_compo_clear(t_compo *head, char *msg)
{
    compo_clear(head);
    ft_putendl_fd(msg, 2);
    exit(1);
}