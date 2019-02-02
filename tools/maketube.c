#include <allegro.h>
#include <math.h>
#include <stdio.h>

int main()
{
	BITMAP *b;
	FILE *f;
	int x, y;
	unsigned char dat[2][64][64];
	unsigned char out_dat[8192];

	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 200, 0, 0);
	b = create_bitmap(64,64);
	if (!b)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		printf("Failed to create bitmap\n");
		return -1;
	}


	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 64; x++)
		{
			double dx = 31.5 - (double)x;
			double dy = 31.5 - (double)y;
			//double dist = sqrt(dx*dx + dy*dy) * (255 / sqrt(2048));
//max dist = 45.255
//			double dist = (16384.0 / (dx*dx + dy*dy));
			double sq = sqrt(dx*dx+dy*dy);
			double dist = 255.0 - ((1.0 - (5.0 / sq)) * (255.0 / 0.89));

			double ang = (atan2(dx, dy) * (128.0 / M_PI)) + 128.0;
			if (dist > 235.0)
				dist = 235.0;
if (x == 32) printf("%i,%i - %g,%g %g   %g\n", x,y, dx,dy, dist, ang);
			putpixel(b, x, y,((unsigned long)dist & 0xff));// | (((unsigned long)ang & 0xff) << 8));

			dat[0][y][x] = (unsigned long)dist & 0xff;
			dat[1][y][x] = (unsigned long)ang & 0xff;
		}
	}

	save_bmp("tube.bmp", b, NULL);

	f = fopen("dat", "wb");

	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			unsigned long addr = (y & 7) | (x << 3) | ((y >> 3) << 8);
//printf("%i,%i - %08x %02x %02x\n", x, y, addr, dat[0][y][x], dat[1][y][x]);
			out_dat[addr] = dat[0][y][x];
			out_dat[addr+1024] = dat[1][y][x];
		}
	}

	fwrite(out_dat, 2048, 1, f);
	fclose(f);

	printf("xang:\n");
	for (x = 0; x < 256; x++)
	{
		double ang = ((double)x * 2.0 * M_PI) / 256.0;
		int rx = (int)(sin(ang) * 64.0);
		int ry = (int)(cos(ang) * 128.0) + 128;

		if (!(x & 15)) printf("        .byte ");
		printf("$%02x", rx & 0xff);
		if ((x & 15) == 15)
			printf("\n");
		else
			printf(",");
		//printf("x=%03i: ang=%g sin=%g cos=%g rx=%i ry=%i\n", x, ang, sin(ang), cos(ang), rx, ry);
	}
	printf("yang:\n");
	for (x = 0; x < 256; x++)
	{
		double ang = ((double)x * 2.0 * M_PI) / 256.0;
		int rx = (int)(sin(ang) * -64.0) + 64;
		int ry = (int)(cos(ang) * -128.0);

		if (ry == 128)
			ry = 127;

		if (!(x & 15)) printf("        .byte ");
		printf("$%02x", ry & 0xff);
		if ((x & 15) == 15)
			printf("\n");
		else
			printf(",");
		//printf("x=%03i: ang=%g sin=%g cos=%g rx=%i ry=%i\n", x, ang, sin(ang), cos(ang), rx, ry);
	}

	for (x = 0; x < 32; x++)
	{
		double dx = 31.5 - (double)x;
		double dist = (16384.0 / (dx*dx));

		printf("%02i : %g %g\n", x, dist, dx);
	}
	printf("%g\n", 31.5-sqrt(16384.0/(16.512+256.0)));

/*	printf("disttable:\n");
	for (x = 0; x < 256; x++)
	{

//			double dist = (16384.0 / (dx*dx + dy*dy));

		double d = 16384.0 / (double)((255-x) + 16.5);
		double dx = (31.5-sqrt(d));
		int mul = (int)((31.5 - dx) * (127 / 31.5));

//		double d = sqrt((double)(255-x));
//		double d2 = (d / 15.9687) * (127.0 - 30.77) + 30.77;
		//min=128/((31.5-23.7462) * 4) = 128/31.0152  = 30.77/127

//		printf("%03i: %g %g %i\n", x, d, dx, mul);

		if (!(x & 15)) printf("        .byte ");
		printf("$%02x", 0x7f-(int)mul);
		if ((x & 15) == 15)
			printf("\n");
		else
			printf(",");

	}*/
printf("disttable:\n");
	for (x = 0; x < 256; x++)
	{
//		double dist = 255.0 - ((1.0 - (5.0 / sq)) * (255.0 / 0.89));


		double dist = 5.0 / (1.0 + ((((255.0 - x) + 14.0) - 255.0)/(255.0/0.89)));
		double mul;

		dist = 4.0 * dist;
//		dist = 45.4545454545-dist;
//		dist *= (23.73171675/40.4545454545);

		mul = dist;//(31.5-dist)*(127.0/31.5);

//		mul = ((dist - 5.0) / 40.45454545) * (127.0 - 31.5);// + 31.5;

//		mul = 95.0 - mul;
//		mul += 31.5;

//printf("%i: %g %g\n", x, dist, mul);

//		double dx = (31.5-sqrt(d));
//		int mul = (int)((31.5 - dx) * (127 / 31.5));

//		double d = sqrt((double)(255-x));
//		double d2 = (d / 15.9687) * (127.0 - 30.77) + 30.77;
		//min=128/((31.5-23.7462) * 4) = 128/31.0152  = 30.77/127

//		printf("%03i: %g %g %i\n", x, d, dx, mul);

		if (!(x & 15)) printf("        .byte ");
		printf("$%02x", (int)mul);
		if ((x & 15) == 15)
			printf("\n");
		else
			printf(",");

	}


	printf("MultTableHigh:\n");
	for (x = 0; x < 256; x++)
	{
		double a = ((((double)(x*x) / 4.0) * 256.0) / 127.0) + 0.5;

		if (!(x & 15)) printf("        .byte ");
		printf("$%02x", (int)(a / 256.0));
		if ((x & 15) == 15)
			printf("\n");
		else
			printf(",");
	}

	return 0;
}
END_OF_MAIN()