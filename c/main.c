#include "Minefield_I.c"
#include "console.h"

void initField(int size){
	int i, p;
	int32_t field[Minefield__TOTAL+1];
	for (i = 0; i <= Minefield__TOTAL; ++i){
		field[i] = Minefield__NONE;
	}
	srand(time(NULL));
	for (i = 0; i < size; ++i){
		p = rand() % Minefield__TOTAL;
		while (field[p] == Minefield__MINE)
			p = rand() % Minefield__TOTAL+1;
		field[p] = Minefield__MINE;
	}
	Minefield__initField(field);
}

void showField(int a){
	int i, j, z;
	char c;
	for (i = 0; i < Minefield__sizeX; ++i){
		for (j = 0; j < Minefield__sizeY; ++j){
			z = Minefield__FIELD[ i + Minefield__sizeX * j ];
			if(z == 0)
				c = ' ';
			else if(z > 0)
				c = z + 48;
			else if(a && z == Minefield__MINE)
				c = '*';
			else
				c = '.';
			SetCharOnPoint(i+1, j+1, c);
		}
	}
}

void run(){
	int x = 0, y = 0;
	Minefield__MSG r;
	Gotoxy(1, 1);
	while (true) {
		switch(getch()){
			case 'w':
				y = y > 0 ? y -1 : y;
				break;
			case 'd':
				x = x < Minefield__sizeX -1 ? x +1 : x;
				break;
			case 's':
				y = y < Minefield__sizeY -1 ? y +1 : y;
				break;
			case 'a':
				x = x > 0 ? x -1 : x;
				break;
			case ' ':
			case '\n':
				Minefield__select(x, y, &r);
				if(r == Minefield__KILLED){
					showField(1);
					Gotoxy(1, Minefield__sizeY+1);
					printf("-- The bombs exploded! -- ");
					return;
				}
				Minefield__isWinner(&r);
				if(r == Minefield__OK){
					showField(1);
					Gotoxy(1, Minefield__sizeY+1);
					printf("-- You're a winner!!! -- ");
					return;
				}
				showField(0);
				break;
			case 'q':
			case '\e':
				Clear();
				return;
		}
		Gotoxy(x+1, y+1);
	}
}

int main(int argc, const char *argv[]){
	int size, isNotExit = 0;
	Minefield__INITIALISATION();
	do {
		Clear();
		printf("The field has %d x %d and a maximum of %d mines.\nHow many mines in the field do you want? ",
			Minefield__sizeX, Minefield__sizeY, Minefield__TOTAL);
		scanf("%d", &size);
		Clear();
		initField(size);
		showField(0);
		run();
		printf("Want to play again? (y|n) ");
		isNotExit = getch() == 'y';
	} while (isNotExit);
	return 0;
}