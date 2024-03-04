#include "Matriz.h"

Matriz::Matriz(float n)
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			Mat[i][j] = n;
		}
	}
}

Matriz::Matriz()
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			Mat[i][j] = 0;
		}
	}
}



