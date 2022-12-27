#include "minirt.h"

void obj_list_init(t_obj *head)
{
    head->element = NULL;
    head->type = -1;
    head->next = NULL;
}

void obj_add(t_obj *head, int type, void *object)
{
    t_obj *cur;

    cur = head;
    while (cur->next)
        cur = cur->next;
    cur->next = (t_obj*)malloc(sizeof(t_obj));
    cur->next->next = NULL;
    cur->next->type = type;
    cur->next->element = object;
}

void obj_clear(t_obj *head)
{
    t_obj *temp;

    while (head->next)
    {
        temp = head->next->next;
        free(head->next->element);
        free(head->next);
        head->next = temp;
    }
}