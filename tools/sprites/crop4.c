#include <allegro.h>
#include <stdio.h>

int main()
{
	int c;
	BITMAP *b_big;
	int bx = 0, by = 0;

	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	b_big = create_bitmap(320, 256);
	rectfill(b_big, 0,0, 319,255, makecol(255,0,255));

	for (c = 1; c <= 64; c++)
	{
		char fn[16];
		BITMAP *b_in, *b_out, *b_temp;
		int y_low = 0, y_high = 0, x_low = 0, x_high = 0;
		int x, y;
		int new_x, new_y;
		int off_x = 0, off_y = 0;
		int bytes;

		sprintf(fn, "%04i.bmp", c);
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

		for (x = 0; x < 960; x++)
		{
			for (y = 0; y < 540; y++)
			{
				if (getpixel(b_in, x, y) == makecol(64, 64, 64))
					putpixel(b_in, x, y, makecol(255, 0, 255));
			}
		}
//		printf("Frame %i: %i,%i-%i,%i %08x %08x %08x\n", c, x_low,y_low, x_high, y_high, getpixel(b_in, 0, 0), getpixel(b_in, 1, 1), makecol(64,64,64));

		new_x = (int)(((double)(x_high-x_low) / (5.15625*2.0)) * 1) / 3;
		new_y = (int)(((double)(y_high-y_low) / 5.15625 * 1) / 3);

		b_temp = create_bitmap(new_x, new_y);
		b_out = create_bitmap(new_x*2, new_y);
		stretch_blit(b_in, b_temp, x_low, y_low, x_high-x_low, y_high-y_low,
				0,0,new_x,new_y);

		stretch_blit(b_temp, b_out, 0,0, new_x,new_y, 0,0, new_x*2,new_y);

		sprintf(fn, "x%04i.bmp", c);
		save_bmp(fn, b_out, NULL);

		blit(b_out, b_big, 0, 0, bx, by, new_x*2, new_y);

		if (c < 30)
		{
			for (y = new_y-1; y >= 0; y--)
			{
				for (x = 0; x < new_x; x++)
				{
					if (getpixel(b_temp, x, y) != makecol(255, 0, 255))
					{
						off_x = x;
						off_y = y;
						break;
					}
				}
				if (off_x)
					break;
			}
		}
		else
		{
			for (x = new_x-1; x >= 0; x--)
			{
				for (y = new_y-1; y >= 0; y--)
				{
					if (getpixel(b_temp, x, y) != makecol(255, 0, 255))
					{
						off_x = x;
						off_y = y;
						break;
					}
				}
				if (off_x)
					break;
			}
		}

		bytes = (new_x + 1) >> 1;
//		if (!((c-1) & 3))
		if (!((c-1) & 1))
			printf("        {%i,%i, %i,%i, %i,%i},\n", bx,by, bytes,new_y, off_x,off_y);

		bx += 32;
		if (bx == 320)
		{
			bx = 0;
			by += 32;
		}
		destroy_bitmap(b_out);
		destroy_bitmap(b_temp);
		destroy_bitmap(b_in);
	}

	save_bmp("diamond4.bmp", b_big, NULL);
	destroy_bitmap(b_big);

	return 0;
}
END_OF_MAIN()