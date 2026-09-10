// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include "../../../../ex03/ft_point.h"
#include "../../../utils/constants.h"

void set_point(t_point *point)
{
	point->x = 42;
	point->y = 21;
}

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	t_point point;
	int ok;

	set_point(&point);
	ok = (point.x == 42 && point.y == 21);
	if (!ok)
		printf("    " RED "[1] t_point did not hold x=42, y=21 after set_point(), got x=%d, y=%d\n" DEFAULT, point.x, point.y);
	else
		printf("  " GREEN CHECKMARK GREY " [1] t_point held x=42, y=21 after set_point()\n" DEFAULT);
	return (ok ? 0 : -1);
}
