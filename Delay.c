#include <INTRINS.H>

void Delay(unsigned int a)		//@11.0592MHz
{
	while (a--)
	{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	}

}
