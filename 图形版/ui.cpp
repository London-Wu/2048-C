#include <graphics.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

int table[SIZE][SIZE];

void show_table() {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			PIMAGE img;
			img = newimage();
			switch (table[i][j]) {
				case 2: {
					getimage(img, "resource\\image\\block_2.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 4: {
					getimage(img, "resource\\image\\block_4.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 8: {
					getimage(img, "resource\\image\\block_8.png");
					putimage(j * 124, i * 124, img );
					break;
				}
				case 16: {
					getimage(img, "resource\\image\\block_16.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 32: {
					getimage(img, "resource\\image\\block_32.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 64: {
					getimage(img, "resource\\image\\block_64.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 128: {
					getimage(img, "resource\\image\\block_128.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 256: {
					getimage(img, "resource\\image\\block_256.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 512: {
					getimage(img, "resource\\image\\block_512.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 1024: {
					getimage(img, "resource\\image\\block_1024.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 2048: {
					getimage(img, "resource\\image\\block_2048.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 4096: {
					getimage(img, "resource\\image\\block_4096.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 8192: {
					getimage(img, "resource\\image\\block_8192.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 16384: {
					getimage(img, "resource\\image\\block_16384.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 32768: {
					getimage(img, "resource\\image\\block_32768.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 65536: {
					getimage(img, "resource\\image\\block_65536.png");
					putimage(j * 124, i * 124, img);
					break;
				}
				case 131072: {
					getimage(img, "resource\\image\\block_131072.png");
					putimage(j * 124, i * 124, img);
					break;
				}

			}
		}
	}
}

void game() {
	initgraph(500, 500);//³õÊ¼»¯
	setcaption("2048");
	setbkcolor(WHITE);
	srand((unsigned int)time(0));
	PIMAGE img;
	img = newimage();
	getimage(img, "resource\\image\\background.png");
	putimage(0, 0, img);
	getch();
}

int main()
{
	game();
}


