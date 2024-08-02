#include <assert.h>
#include <stdio.h>

extern int	skip_coordinate(const char **ptr);

int main(void)
{
	const char *str;

	str = "0.1,-00.3,+0.1";
	assert(skip_coordinate(&str) == 0 && *str == '\0');

	str = "+111,-0.3,+0.1   ";
	assert(skip_coordinate(&str) == 0 && *str == ' ');

	str = "123,321,";
	assert(skip_coordinate(&str) != 0);

	str = "123,,321.1";
	assert(skip_coordinate(&str) != 0);

	str = "123,321.1,321,123";
	assert(skip_coordinate(&str) != 0);

	printf("skip_coordinate: \033[92mOK\033[0m\n");
	return 0;
}
