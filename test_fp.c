#include <float.h>
#include <stdio.h>

int main()
{
	printf("%e\n", FLT_EPSILON);
	printf("%e\n", DBL_EPSILON);
	printf("%Le\n", LDBL_EPSILON);
	return (0);
}
