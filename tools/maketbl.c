#include <stdio.h>

int main()
{
	int c;

	printf("masktable:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x55;
		int r_col = c & 0xaa;
		int mask = 0;

		if (!(c & 15)) printf("        .byte ");

		if (l_col == 0x11)
			mask |= 0x55;
		if (r_col == 0x22)
			mask |= 0xaa;

		printf("$%02x", mask);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("ortable:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x55;
		int r_col = c & 0xaa;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		if (l_col != 0x11)
			col |= l_col;
		if (r_col != 0x22)
			col |= r_col;

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_masktable:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x55;
		int r_col = c & 0xaa;
		int mask = 0;

		if (!(c & 15)) printf("        .byte ");

		if (l_col == 0x11)
			mask |= 0xaa;
		if (r_col == 0x22)
			mask |= 0x55;

		printf("$%02x", mask);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_ortable:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x55;
		int r_col = c & 0xaa;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		if (l_col != 0x11)
			col |= l_col << 1;
		if (r_col != 0x22)
			col |= r_col >> 1;

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");


	printf("masktable_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x88;
		int r_col = c & 0x44;
		int mask = 0;

		if (!(c & 15)) printf("        .byte ");

		if (!l_col)
			mask |= 0xaa;
		if (!r_col)
			mask |= 0x55;

		printf("$%02x", mask);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("masktable_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x22;
		int r_col = c & 0x11;
		int mask = 0;

		if (!(c & 15)) printf("        .byte ");

		if (!l_col)
			mask |= 0xaa;
		if (!r_col)
			mask |= 0x55;

		printf("$%02x", mask);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("ortable_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 3) & 0x11;
		int l_col = (c >> 2) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x20; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x10; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("ortable_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 1) & 0x11;
		int l_col = (c >> 0) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x20; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x10; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");

	printf("flip_masktable_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x11;
		int r_col = c & 0x22;
		int mask = 0;

		if (!(c & 15)) printf("        .byte ");

		if (!l_col)
			mask |= 0xaa;
		if (!r_col)
			mask |= 0x55;

		printf("$%02x", mask);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_masktable_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int l_col = c & 0x44;
		int r_col = c & 0x88;
		int mask = 0;

		if (!(c & 15)) printf("        .byte ");

		if (!l_col)
			mask |= 0xaa;
		if (!r_col)
			mask |= 0x55;

		printf("$%02x", mask);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_ortable_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 0) & 0x11;
		int l_col = (c >> 1) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x20; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x10; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_ortable_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 2) & 0x11;
		int l_col = (c >> 3) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x20; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x10; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");



	printf("ortable1_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 3) & 0x11;
		int l_col = (c >> 2) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x02; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x01; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("ortable1_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 1) & 0x11;
		int l_col = (c >> 0) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x02; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x01; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_ortable1_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 0) & 0x11;
		int l_col = (c >> 1) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x02; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x01; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_ortable1_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 2) & 0x11;
		int l_col = (c >> 3) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x02; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x01; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");

	printf("ortable2_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 3) & 0x11;
		int l_col = (c >> 2) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x08; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x04; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("ortable2_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 1) & 0x11;
		int l_col = (c >> 0) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x08; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x04; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_ortable2_exp1:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 0) & 0x11;
		int l_col = (c >> 1) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x08; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x04; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");
	printf("flip_ortable2_exp2:\n");
	for (c = 0; c < 256; c++)
	{
		int r_col = (c >> 2) & 0x11;
		int l_col = (c >> 3) & 0x11;
		int col = 0;

		if (!(c & 15)) printf("        .byte ");

		switch (r_col)
		{
			case 0x10: col |= 0x08; break;
			case 0x11: col |= 0x2a; break;
		}
		switch (l_col)
		{
			case 0x10: col |= 0x04; break;
			case 0x11: col |= 0x15; break;
		}

		printf("$%02x", col|0x80);
		if ((c & 15) == 15) printf("\n");
		else                printf(",");
	}
	printf("\n");

	return 0;
}
