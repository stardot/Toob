#include <allegro.h>
#include <stdio.h>
#include <math.h>

//11.25 degrees
double scale_factor[8][2] =
{
/*	{1.0, 0.5},
	{0.990, 0.598},
	{0.962, 0.691},
	{0.916, 0.778},
	{0.854, 0.854},
	{0.778, 0.916},
	{0.691, 0.962},
	{0.598, 0.990}*/

	{1.0, 0.25},
	{0.986, 0.396},
	{0.943, 0.537},
	{0.874, 0.667},
	{0.780, 0.780},
	{0.667, 0.874},
	{0.537, 0.943},
	{0.396, 0.986}
};

int main()
{
	int c;
	BITMAP *b_bigs[4];
	int bx = 0, by = 0;

	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	b_bigs[0] = create_bitmap(320, 256);
	rectfill(b_bigs[0], 0,0, 319,255, makecol(255,0,255));
	b_bigs[1] = create_bitmap(320, 256);
	rectfill(b_bigs[1], 0,0, 319,255, makecol(255,0,255));
	b_bigs[2] = create_bitmap(320, 256);
	rectfill(b_bigs[2], 0,0, 319,255, makecol(255,0,255));
	b_bigs[3] = create_bitmap(320, 256);
	rectfill(b_bigs[3], 0,0, 319,255, makecol(255,0,255));

	for (c = /*1*/1; c <= /*64*/9*4; c++)
	{
		BITMAP *b_big;
		char fn[16];
		BITMAP *b_in, *b_out, *b_temp, *b_shad, *b_prerot, *b_postrot, *b_realout, *b_scale, *b_dblscale;
		int y_low = 0, y_high = 0, x_low = 0, x_high = 0;
		int x, y;
		int new_x, new_y;
		int off_x = 0, off_y = 0;
		int start_off_x, start_off_y;
		int top_off_x = 0, top_off_y = 0;
		int shad_off;
		int shad_w, shad_h;
		int bytes;
		int ang;
		double scale;

		if (c > 27)
			b_big = b_bigs[3];
		else if (c > 18)
			b_big = b_bigs[2];
		else if (c > 9)
			b_big = b_bigs[1];
		else
			b_big = b_bigs[0];

		if (!((c-1) % 9))
			bx = by = 0;


//		if ((c-1) & 4)
//			continue;

//		printf("rot_w=%g rot_h=%g  rot_ang=%g rot_radian=%g\n", rot_w, rot_h, rot_ang, rot_radian);

		sprintf(fn, "sp0.bmp");
		b_in = load_bmp(fn, NULL);

		for (y = 0; y < 540; y++)
		{
			for (x = 0; x < 960; x++)
			{
				if (getpixel(b_in, x, y) != makecol(64, 64, 64))
				{
					y_low = y;
					break;
				}
				if (y_low)
					break;
			}
			if (y_low)
				break;
		}
		for (y = 539; y >= 0; y--)
		{
			for (x = 0; x < 960; x++)
			{
				if (getpixel(b_in, x, y) != makecol(64, 64, 64))
				{
					y_high = y;
					break;
				}
			}
			if (y_high)
				break;
		}
		for (x = 0; x < 960; x++)
		{
			for (y = 0; y < 540; y++)
			{
				if (getpixel(b_in, x, y) != makecol(64, 64, 64))
				{
					x_low = x;
					break;
				}
			}
			if (x_low)
				break;
		}
		for (x = 959; x >= 0; x--)
		{
			for (y = 0; y < 540; y++)
			{
				if (getpixel(b_in, x, y) != makecol(64, 64, 64))
				{
					x_high = x;
					break;
				}
			}
			if (x_high)
				break;
		}

		/*Offset from midpoint*/
		start_off_x = 0;//(x_high - x_low) / 2;
		start_off_y = (y_high - y_low) / 2;

		for (x = 0; x < 960; x++)
		{
			for (y = 0; y < 540; y++)
			{
				if (getpixel(b_in, x, y) == makecol(64, 64, 64))
					putpixel(b_in, x, y, makecol(255, 0, 255));
			}
		}
//		printf("Frame %i: %i,%i-%i,%i %08x %08x %08x\n", c, x_low,y_low, x_high, y_high, getpixel(b_in, 0, 0), getpixel(b_in, 1, 1), makecol(64,64,64));

		b_temp = create_bitmap(960, 540);
		b_out = create_bitmap(960, 540);
		rectfill(b_temp, 0,0, 959,539, makecol(255, 0, 255));
		rectfill(b_out, 0,0, 959,539, makecol(255, 0, 255));

		blit(b_in, b_out, x_low, y_low, 0, 0, (x_high-x_low), (y_high-y_low));

		new_x = x_high - x_low;
		new_y = y_high - y_low;

		for (y = 0; y < (y_high-y_low); y++)
		{
			for (x = 0; x < (x_high-x_low); x++)
			{
				int nx = ((x_high-x_low) - 1) - x;
				int ny = ((y_high-y_low) - 1) - y;
//if (!y)
//	printf("      xy=%i,%i nxy=%i,%i  %i,%i\n", x,y, nx,ny, x_low+x,y_low+y);
				if (getpixel(b_in, x_low+x, y_low+y) != makecol(255, 0, 255))
					putpixel(b_temp, x, ny, makecol(0, 255, 0));
			}
		}


			for (y = 0; y < new_y; y++)
			{
				for (x = 0; x < new_x; x++)
				{
					if (getpixel(b_out, x, y) != makecol(255, 0, 255))
					{
						top_off_x = x;
						top_off_y = y;
						break;
					}
				}
				if (top_off_x)
					break;
			}

			for (y = new_y-1; y >= 0; y--)
			{
				for (x = new_x-1; x >= 0; x--)
				{
					if (getpixel(b_out, x, y) != makecol(255, 0, 255))
					{
						off_x = x;
						off_y = y;
						break;
					}
				}
				if (off_x)
					break;
			}

			shad_off = (new_x-1) - off_x;
			stretch_blit(b_temp, b_out, 0, 0, new_x, new_y, /*off_x-shad_off*/0, new_y, new_x, new_y/4);

		start_off_x = new_x / 2;
		start_off_y = new_y;


		x_high = y_high = 0;
		for (y = 539; y >= 0; y--)
		{
			for (x = 0; x < 960; x++)
			{
				if (getpixel(b_out, x, y) != makecol(255, 0, 255))
				{
					y_high = y+1;
					break;
				}
			}
			if (y_high)
				break;
		}
		for (x = 959; x >= 0; x--)
		{
			for (y = 0; y < 540; y++)
			{
				if (getpixel(b_out, x, y) != makecol(255, 0, 255))
				{
					x_high = x+1;
					break;
				}
			}
			if (x_high)
				break;
		}

		b_prerot = create_bitmap(x_high, y_high);
		blit(b_out, b_prerot, 0, 0, 0, 0, x_high, y_high);
//printf(" %i,%i %i,%i\n",start_off_x,start_off_y, x_high, y_high);
		start_off_x -= (x_high / 2);
		start_off_y -= (y_high / 2);

//	save_bmp("b_prerot.bmp", b_prerot, NULL);

		b_postrot = create_bitmap(960, 540);
		rectfill(b_postrot, 0, 0, 959, 539, makecol(255, 0, 255));

		ang = -((((c-1) % 9) * 8) << 16);

		rotate_sprite(b_postrot, b_prerot, 480, 270, ang);

		off_x = fmul(itofix(start_off_x), fixcos(ang)) + fmul(itofix(start_off_y), -fixsin(ang));
		off_y = fmul(itofix(start_off_x), fixsin(ang)) + fmul(itofix(start_off_y),  fixcos(ang));
//		printf("Offsets: %i,%i -> %i,%i  %i,%i\n", start_off_x, start_off_y,
//				fixtoi(off_x), fixtoi(off_y), new_x,new_y);

		x_low = x_high = y_low = y_high = 0;
		for (y = 0; y < 540; y++)
		{
			for (x = 0; x < 960; x++)
			{
				if (getpixel(b_postrot, x, y) != makecol(255, 0, 255))
				{
					y_low = y;
					break;
				}
				if (y_low)
					break;
			}
			if (y_low)
				break;
		}
		for (y = 539; y >= 0; y--)
		{
			for (x = 0; x < 960; x++)
			{
				if (getpixel(b_postrot, x, y) != makecol(255, 0, 255))
				{
					y_high = y+1;
					break;
				}
			}
			if (y_high)
				break;
		}
		for (x = 0; x < 960; x++)
		{
			for (y = 0; y < 540; y++)
			{
				if (getpixel(b_postrot, x, y) != makecol(255, 0, 255))
				{
					x_low = x;
					break;
				}
			}
			if (x_low)
				break;
		}
		for (x = 959; x >= 0; x--)
		{
			for (y = 0; y < 540; y++)
			{
				if (getpixel(b_postrot, x, y) != makecol(255, 0, 255))
				{
					x_high = x+1;
					break;
				}
			}
			if (x_high)
				break;
		}

		off_x = fixtoi(off_x) + ((x_high - x_low) / 2);
		off_y = fixtoi(off_y) + ((y_high - y_low) / 2);
//		printf("  %i,%i\n", off_x, off_y);

		if (c <= 9)
			scale = 1.0;
		else if (c <= 18)
			scale = 3.0 / 4.0;
		else if (c <= 27)
			scale = 0.5;
		else
			scale = 1.0 / 3.0;

		scale /= 2.0;
		scale /= (64.0 / 36.0);

		off_x = (int)((double)off_x * scale);
		off_y = (int)((double)off_y * scale);
//		printf("  %i,%i\n", off_x, off_y);

		new_x = (int)(double)(((x_high-x_low) / 2.0) * scale);
		new_y = (int)(double)(((y_high-y_low) / 1.0) * scale);

		b_scale = create_bitmap(new_x, new_y);
		rectfill(b_scale, 0, 0, new_x, new_y, makecol(255, 0, 255));
/*
		if (c < 30)
		{
			off_x = off_y = 0;
			for (y = (y_high-y_low)-1; y >= 0; y--)
			{
				for (x = (x_high-x_low)-1; x >= 0; x--)
				{
					int nx = (int)(((double)x / 2.0) * scale);
					int ny = (int)(((double)y / 1.0) * scale);
	
					if (getpixel(b_postrot, x+x_low, y+y_low) != makecol(255, 0, 255) &&
					    getpixel(b_postrot, x+x_low, y+y_low) != makecol(0, 255, 0))
					{
						off_x = nx;
						off_y = ny;
//						printf("%i,%i %i,%i\n", x+x_low,y+y_low, nx,ny);
						break;
					}
				}
				if (off_x || off_y)
					break;
			}
		}
		else
		{
			off_x = off_y = 0;
			for (x = (x_high-x_low)-1; x >= 0; x--)
			{
				for (y = (y_high-y_low)-1; y >= 0; y--)
				{
					int nx = (int)(((double)x / 2.0) * scale);
					int ny = (int)(((double)y / 1.0) * scale);
	
					if (getpixel(b_postrot, x+x_low, y+y_low) != makecol(255, 0, 255) &&
					    getpixel(b_postrot, x+x_low, y+y_low) != makecol(0, 255, 0))
					{
						off_x = nx;
						off_y = ny;
//						printf("%i,%i %i,%i\n", x+x_low,y+y_low, nx,ny);
						break;
					}
				}
				if (off_x || off_y)
					break;
			}
		}
*/

		for (y = 0; y < (y_high-y_low); y++)
		{
			for (x = 0; x < (x_high-x_low); x++)
			{
				int nx = (int)(((double)x / 2.0) * scale);
				int ny = (int)(((double)y / 1.0) * scale);

				if (getpixel(b_postrot, x+x_low, y+y_low) != makecol(255, 0, 255) &&
				    getpixel(b_postrot, x+x_low, y+y_low) != makecol(0, 255, 0))
					putpixel(b_scale, nx, ny, getpixel(b_postrot, x+x_low, y+y_low));
				if (getpixel(b_postrot, x+x_low, y+y_low) == makecol(0, 255, 0))
				{
					if ((nx ^ ny) & 1)
						putpixel(b_scale, nx, ny, makecol(0, 0, 0));
				}
			}
		}



//		printf("offset=%i,%i\n", off_x, off_y);

		bytes = (new_x + 1) >> 1;
		bytes = (bytes + 1) >> 1;
		printf("        {%i,%i, %i,%i, %i,%i},  /*%i*/\n", bx,by, bytes,new_y, off_x/2,off_y, c);

		b_dblscale = create_bitmap(new_x*2, new_y);
		stretch_blit(b_scale, b_dblscale, 0, 0, new_x, new_y, 0, 0, new_x*2, new_y);

		sprintf(fn, "x%04i.bmp", c);
		save_bmp(fn, b_dblscale, NULL);


//		sprintf(fn, "x%04ip.bmp", c);
//		save_bmp(fn, b_postrot, NULL);

		blit(b_dblscale, b_big, 0, 0, bx, by, new_x*2, new_y);

		bx += 64;
		if (bx > 256)
		{
			bx = 0;
			by += 64;
		}


		destroy_bitmap(b_dblscale);
		destroy_bitmap(b_scale);
		destroy_bitmap(b_postrot);
		destroy_bitmap(b_prerot);
		destroy_bitmap(b_out);
		destroy_bitmap(b_temp);
		destroy_bitmap(b_in);
	}

	save_bmp("ship1.bmp", b_bigs[0], NULL);
	destroy_bitmap(b_bigs[0]);
	save_bmp("ship2.bmp", b_bigs[1], NULL);
	destroy_bitmap(b_bigs[1]);
	save_bmp("ship3.bmp", b_bigs[2], NULL);
	destroy_bitmap(b_bigs[2]);
	save_bmp("ship4.bmp", b_bigs[3], NULL);
	destroy_bitmap(b_bigs[3]);

	return 0;
}
END_OF_MAIN()