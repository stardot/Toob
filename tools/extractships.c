#include <stdio.h>
#include <stdint.h>

typedef struct sprite_t
{
	int x_start, y_start;
	int x_size, y_size;
	int x_offset, y_offset;
} sprite_t;

sprite_t ship_sprites[] = 
{
        {0,0, 5,22, 9,17},  /*0*/
        {64,0, 5,22, 8,18},  /*1*/
        {128,0, 5,23, 8,18},  /*2*/
        {192,0, 5,24, 10,19},  /*3*/
        {256,0, 6,24, 11,19},  /*4*/
        {0,32, 6,25, 13,20},  /*5*/
        {64,32, 7,25, 15,20},  /*6*/
        {128,32, 7,25, 17,20},  /*7*/
        {192,32, 8,25, 18,20},  /*8*/
        {256,32, 8,25, 20,20},  /*9*/
        {0,64, 8,25, 21,20},  /*10*/
        {64,64, 8,25, 22,20},  /*11*/
        {128,64, 8,25, 23,20},  /*12*/
        {192,64, 8,25, 24,20},  /*13*/
        {256,64, 8,25, 24,19},  /*14*/
        {0,96, 8,24, 25,19},  /*15*/
        {64,96, 8,24, 25,18},  /*16*/

#if 0
        {0,0, 8,22, 23,17},  /*0*/
        {64,0, 8,23, 23,18},  /*1*/
        {128,0, 8,23, 22,18},  /*2*/
        {192,0, 8,24, 20,19},  /*3*/
        {256,0, 7,23, 17,18},  /*4*/
        {0,32, 6,23, 14,18},  /*5*/
        {64,32, 6,22, 11,18},  /*6*/
        {128,32, 5,21, 7,17},  /*7*/
        {192,32, 5,20, 9,16},  /*8*/
#endif
/*	{0,0, 17,24, 8*2,23},
	{0,32, 15,23+7, 7*2,22},
	{0,64, 12,22+6, 6*2,21},
	{0,96, 11,20+6, 5*2,19}*/
};

#define NR_SHIP_SPRITES 17

sprite_t diamond_sprites[] =
{
        {0,0, 2,39, 4,31},  /*1*/
        {40,0, 2,39, 3,31},  /*2*/
        {80,0, 2,39, 2,31},  /*3*/
        {120,0, 2,39, 3,31},  /*4*/
        {160,0, 3,39, 5,31},  /*9*/
        {200,0, 3,39, 5,31},  /*10*/
        {240,0, 2,39, 4,31},  /*11*/
        {280,0, 3,39, 5,31},  /*12*/
        {0,48, 3,37, 6,29},  /*17*/
        {40,48, 3,37, 6,29},  /*18*/
        {80,48, 3,37, 6,29},  /*19*/
        {120,48, 3,37, 6,29},  /*20*/
        {160,48, 4,34, 8,26},  /*25*/
        {200,48, 4,34, 8,26},  /*26*/
        {240,48, 3,33, 8,26},  /*27*/
        {280,48, 4,34, 8,26},  /*28*/
        {0,96, 4,31, 11,22},  /*33*/
        {40,96, 4,30, 11,22},  /*34*/
        {80,96, 4,29, 11,22},  /*35*/
        {120,96, 4,30, 11,22},  /*36*/
        {160,96, 5,26, 13,17},  /*41*/
        {200,96, 5,25, 13,17},  /*42*/
        {240,96, 4,24, 13,17},  /*43*/
        {280,96, 5,25, 13,17},  /*44*/
        {0,144, 5,22, 14,13},  /*49*/
        {40,144, 5,21, 14,12},  /*50*/
        {80,144, 5,19, 14,12},  /*51*/
        {120,144, 5,21, 14,12},  /*52*/
        {160,144, 5,19, 15,11},  /*57*/
        {200,144, 5,18, 15,10},  /*58*/
        {240,144, 5,14, 15,8},  /*59*/
        {280,144, 5,18, 15,10},  /*60*/
        {0,192, 5,16, 15,8},  /*65*/
        {40,192, 5,15, 15,7},  /*66*/
        {80,192, 5,11, 15,5},  /*67*/
        {120,192, 5,14, 15,7},  /*68*/
};

sprite_t diamond2_sprites[] =
{
        {0,0, 2,29, 3,23},  /*1*/
        {40,0, 2,29, 2,23},  /*2*/
        {80,0, 1,29, 2,23},  /*3*/
        {120,0, 2,29, 2,23},  /*4*/
        {160,0, 2,29, 4,23},  /*9*/
        {200,0, 2,29, 3,23},  /*10*/
        {240,0, 2,29, 3,23},  /*11*/
        {280,0, 2,29, 3,23},  /*12*/
        {0,48, 2,27, 5,22},  /*17*/
        {40,48, 2,27, 4,22},  /*18*/
        {80,48, 2,27, 4,22},  /*19*/
        {120,48, 2,27, 4,22},  /*20*/
        {160,48, 3,25, 6,19},  /*25*/
        {200,48, 3,25, 6,19},  /*26*/
        {240,48, 3,25, 6,19},  /*27*/
        {280,48, 3,25, 6,19},  /*28*/
        {0,96, 3,23, 8,16},  /*33*/
        {40,96, 3,22, 8,16},  /*34*/
        {80,96, 3,22, 8,16},  /*35*/
        {120,96, 3,22, 8,16},  /*36*/
        {160,96, 4,20, 9,13},  /*41*/
        {200,96, 3,19, 9,13},  /*42*/
        {240,96, 3,18, 9,13},  /*43*/
        {280,96, 3,19, 9,13},  /*44*/
        {0,144, 4,16, 11,10},  /*49*/
        {40,144, 4,16, 11,9},  /*50*/
        {80,144, 4,14, 11,9},  /*51*/
        {120,144, 4,15, 11,9},  /*52*/
        {160,144, 4,14, 11,8},  /*57*/
        {200,144, 4,13, 11,7},  /*58*/
        {240,144, 4,11, 11,6},  /*59*/
        {280,144, 4,13, 11,7},  /*60*/
        {0,192, 4,12, 11,6},  /*65*/
        {40,192, 4,11, 11,5},  /*66*/
        {80,192, 4,8, 11,4},  /*67*/
        {120,192, 4,11, 11,5},  /*68*/
};

sprite_t diamond3_sprites[] =
{
        {0,0, 1,19, 2,15},  /*1*/
        {40,0, 1,19, 1,15},  /*2*/
        {80,0, 1,19, 1,15},  /*3*/
        {120,0, 1,19, 1,15},  /*4*/
        {160,0, 1,19, 2,15},  /*9*/
        {200,0, 1,19, 2,15},  /*10*/
        {240,0, 1,19, 2,15},  /*11*/
        {280,0, 1,19, 2,15},  /*12*/
        {0,48, 2,18, 3,14},  /*17*/
        {40,48, 2,18, 3,14},  /*18*/
        {80,48, 1,18, 3,14},  /*19*/
        {120,48, 2,18, 3,14},  /*20*/
        {160,48, 2,17, 4,13},  /*25*/
        {200,48, 2,17, 4,13},  /*26*/
        {240,48, 2,16, 4,13},  /*27*/
        {280,48, 2,17, 4,13},  /*28*/
        {0,96, 2,15, 5,11},  /*33*/
        {40,96, 2,15, 5,11},  /*34*/
        {80,96, 2,14, 5,11},  /*35*/
        {120,96, 2,15, 5,11},  /*36*/
        {160,96, 2,13, 6,8},  /*41*/
        {200,96, 2,12, 6,8},  /*42*/
        {240,96, 2,12, 6,8},  /*43*/
        {280,96, 2,12, 6,8},  /*44*/
        {0,144, 3,11, 7,6},  /*49*/
        {40,144, 3,10, 7,6},  /*50*/
        {80,144, 3,9, 7,6},  /*51*/
        {120,144, 3,10, 7,6},  /*52*/
        {160,144, 3,9, 7,5},  /*57*/
        {200,144, 3,9, 7,5},  /*58*/
        {240,144, 3,7, 7,4},  /*59*/
        {280,144, 3,9, 7,5},  /*60*/
        {0,192, 3,8, 7,4},  /*65*/
        {40,192, 3,7, 7,3},  /*66*/
        {80,192, 3,5, 7,2},  /*67*/
        {120,192, 3,7, 7,3},  /*68*/
};

sprite_t diamond4_sprites[] =
{
        {0,0, 1,13, 1,10},  /*1*/
        {40,0, 1,13, 1,10},  /*2*/
        {80,0, 1,13, 0,10},  /*3*/
        {120,0, 1,13, 1,10},  /*4*/
        {160,0, 1,13, 1,10},  /*9*/
        {200,0, 1,13, 1,10},  /*10*/
        {240,0, 1,13, 1,10},  /*11*/
        {280,0, 1,13, 1,10},  /*12*/
        {0,48, 1,12, 2,9},  /*17*/
        {40,48, 1,12, 2,9},  /*18*/
        {80,48, 1,12, 2,9},  /*19*/
        {120,48, 1,12, 2,9},  /*20*/
        {160,48, 1,11, 2,8},  /*25*/
        {200,48, 1,11, 2,8},  /*26*/
        {240,48, 1,11, 2,8},  /*27*/
        {280,48, 1,11, 2,8},  /*28*/
        {0,96, 2,10, 3,7},  /*33*/
        {40,96, 2,10, 3,7},  /*34*/
        {80,96, 1,9, 3,7},  /*35*/
        {120,96, 2,10, 3,7},  /*36*/
        {160,96, 2,8, 4,5},  /*41*/
        {200,96, 2,8, 4,5},  /*42*/
        {240,96, 2,8, 4,5},  /*43*/
        {280,96, 2,8, 4,5},  /*44*/
        {0,144, 2,7, 4,4},  /*49*/
        {40,144, 2,7, 4,4},  /*50*/
        {80,144, 2,6, 4,4},  /*51*/
        {120,144, 2,7, 4,4},  /*52*/
        {160,144, 2,6, 5,3},  /*57*/
        {200,144, 2,6, 5,3},  /*58*/
        {240,144, 2,4, 5,2},  /*59*/
        {280,144, 2,6, 5,3},  /*60*/
        {0,192, 2,5, 5,2},  /*65*/
        {40,192, 2,5, 5,2},  /*66*/
        {80,192, 2,3, 5,1},  /*67*/
        {120,192, 2,4, 5,2},  /*68*/
};

sprite_t shiprot1_sprites[] = 
{
        {0,0, 5,21, 9,16},  /*1*/
        {64,0, 5,25, 9,18},  /*2*/
        {128,0, 5,28, 9,19},  /*3*/
        {192,0, 5,30, 10,20},  /*4*/
        {256,0, 4,33, 10,21},  /*5*/
        {0,64, 4,34, 10,20},  /*6*/
        {64,64, 4,34, 9,19},  /*7*/
        {128,64, 3,36, 9,19},  /*8*/
        {192,64, 3,36, 8,18},  /*9*/
};
sprite_t shiprot2_sprites[] = 
{
        {0,0, 4,15, 6,12},  /*10*/
        {64,0, 4,18, 7,14},  /*11*/
        {128,0, 3,21, 7,14},  /*12*/
        {192,0, 3,22, 7,15},  /*13*/
        {256,0, 3,24, 7,15},  /*14*/
        {0,64, 3,25, 7,15},  /*15*/
        {64,64, 3,25, 7,14},  /*16*/
        {128,64, 3,27, 7,14},  /*17*/
        {192,64, 2,27, 6,13},  /*18*/
};
sprite_t shiprot3_sprites[] = 
{
        {0,0, 3,10, 4,8},  /*19*/
        {64,0, 3,12, 4,9},  /*20*/
        {128,0, 2,14, 4,9},  /*21*/
        {192,0, 2,15, 5,10},  /*22*/
        {256,0, 2,16, 5,10},  /*23*/
        {0,64, 2,17, 5,10},  /*24*/
        {64,64, 2,17, 4,9},  /*25*/
        {128,64, 2,18, 4,9},  /*26*/
        {192,64, 2,18, 4,9},  /*27*/
};
sprite_t shiprot4_sprites[] = 
{
        {0,0, 2,7, 3,5},  /*28*/
        {64,0, 2,8, 3,6},  /*29*/
        {128,0, 2,9, 3,6},  /*30*/
        {192,0, 2,10, 3,6},  /*31*/
        {256,0, 2,11, 3,7},  /*32*/
        {0,64, 2,11, 3,6},  /*33*/
        {64,64, 1,11, 3,6},  /*34*/
        {128,64, 1,12, 3,6},  /*35*/
        {192,64, 1,12, 2,6},  /*36*/
};

#define NR_DIAMOND_SPRITES 36
#define NR_SHIPROT_SPRITES 9

#define NR_SPRITES (NR_SHIP_SPRITES+NR_DIAMOND_SPRITES*4+NR_SHIPROT_SPRITES*4)

struct
{
	uint16_t base;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t x_offset;
	uint8_t y_offset;
	uint8_t bank;
	uint8_t filler;
} bbc_sprites[NR_SPRITES];

static FILE *files[6];
static int bank = 5;

static uint16_t process_sprites(sprite_t *sprites, char *fn, uint16_t base, int spr_offset, int nr_sprites)
{
	FILE *f_in = fopen(fn, "rb");
	int spr;

	for (spr = 0; spr < nr_sprites; spr++)
	{
		int size = sprites[spr].x_size * ((sprites[spr].y_size + 7) & ~7);

/*		if (size > 0x100 && (size + (base & 0xff)) >= 0x200)
			base = (base + 0xff) & ~0xff;
		if ((0x100 - (base & 0xff)) % sprites[spr].y_size)
		{
			printf("  %04x %i ", base, sprites[spr].y_size);
			base += (0x100 - (base & 0xff)) % sprites[spr].y_size;
			printf("%04x %i\n", base, (0x100 - (base & 0xff)) % sprites[spr].y_size);
		}
*/
		if ((base + size) > 0xc000)
		{
			base = 0x8000;
			bank++;
		}		
printf("spr=%i base=%04x\n", spr, base);
//		if ((base & 0xff00) != ((base + sprites[spr].x_size*sprites[spr].y_size) & 0xff00))
//			base += (0x100 - (base & 0xff));
		bbc_sprites[spr+spr_offset].base = base;
		bbc_sprites[spr+spr_offset].bank = bank;
		bbc_sprites[spr+spr_offset].x_size = sprites[spr].x_size;
		bbc_sprites[spr+spr_offset].y_size = sprites[spr].y_size;
		bbc_sprites[spr+spr_offset].x_offset = sprites[spr].x_offset;
		bbc_sprites[spr+spr_offset].y_offset = sprites[spr].y_offset;
		base += sprites[spr].x_size * ((sprites[spr].y_size + 7) & ~7);
	}

	for (spr = 0; spr < nr_sprites; spr++)
	{
		int y;
printf("  seek from %04x to %04x\n", ftell(files[bbc_sprites[spr+spr_offset].bank]), bbc_sprites[spr+spr_offset].base - 0x8000);
		fseek(files[bbc_sprites[spr+spr_offset].bank], bbc_sprites[spr+spr_offset].base - 0x8000, SEEK_SET);

		for (y = 0; y < sprites[spr].y_size; y += 8)
		{
			int x;

			for (x = 0; x < sprites[spr].x_size; x++)
			{
				int yy;

				for (yy = 0; yy < 8; yy++)
				{
					int temp_y = y + yy + sprites[spr].y_start;
					int temp_x = x + (sprites[spr].x_start/8);
					uint32_t addr = (temp_y & 7) + ((temp_y >> 3) * 320);

					addr += temp_x*8;

					fseek(f_in, addr, SEEK_SET);
					putc(getc(f_in), files[bbc_sprites[spr+spr_offset].bank]);
				}
			}
		}
	}

	fclose(f_in);

	return base;
}

int main()
{
//	FILE *f_out = fopen("sprites5", "wb");
	int spr;
	uint16_t base = 0x8000 + 8*NR_SPRITES;

	files[5] = fopen("sprites5", "wb");
	files[6] = fopen("sprites6", "wb");

	putc(0, files[5]);
	putc(0, files[6]);

/*	for (spr = 0; spr < NR_SPRITES; spr++)
	{
		bbc_sprites[spr].base = base;
		bbc_sprites[spr].x_size = sprites[spr].x_size;
		bbc_sprites[spr].y_size = sprites[spr].y_size;
		bbc_sprites[spr].x_offset = sprites[spr].x_offset;
		bbc_sprites[spr].y_offset = sprites[spr].y_offset;
		base += sprites[spr].x_size * sprites[spr].y_size;
	}*/

	fwrite(bbc_sprites, sizeof(bbc_sprites), 1, files[5]);

	base = process_sprites(ship_sprites, "ship/ship1", base, 0, NR_SHIP_SPRITES);
	base = process_sprites(diamond_sprites, "diamonds", base, NR_SHIP_SPRITES, NR_DIAMOND_SPRITES);
	base = process_sprites(diamond2_sprites, "diamonds2", base, NR_SHIP_SPRITES+NR_DIAMOND_SPRITES, NR_DIAMOND_SPRITES);
	base = process_sprites(diamond3_sprites, "diamonds3", base, NR_SHIP_SPRITES+NR_DIAMOND_SPRITES*2, NR_DIAMOND_SPRITES);
	base = process_sprites(diamond4_sprites, "diamonds4", base, NR_SHIP_SPRITES+NR_DIAMOND_SPRITES*3, NR_DIAMOND_SPRITES);
	base = process_sprites(shiprot1_sprites, "shiprot1", base, NR_SHIP_SPRITES+NR_DIAMOND_SPRITES*4, NR_SHIPROT_SPRITES);
	base = process_sprites(shiprot2_sprites, "shiprot2", base, NR_SHIP_SPRITES+NR_DIAMOND_SPRITES*4+NR_SHIPROT_SPRITES, NR_SHIPROT_SPRITES);
	base = process_sprites(shiprot3_sprites, "shiprot3", base, NR_SHIP_SPRITES+NR_DIAMOND_SPRITES*4+NR_SHIPROT_SPRITES*2, NR_SHIPROT_SPRITES);
	base = process_sprites(shiprot4_sprites, "shiprot4", base, NR_SHIP_SPRITES+NR_DIAMOND_SPRITES*4+NR_SHIPROT_SPRITES*3, NR_SHIPROT_SPRITES);

	fseek(files[5], 0, SEEK_SET);
	fwrite(bbc_sprites, sizeof(bbc_sprites), 1, files[5]);

	fclose(files[6]);
	fclose(files[5]);
	return 0;
}
