#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pic32mx.h>
#include "tetris.h"


/********************************* FROM LABS ***********************************************/
#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)


const uint8_t const font[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 94, 0, 0, 0, 0,
	0, 0, 4, 3, 4, 3, 0, 0,
	0, 36, 126, 36, 36, 126, 36, 0,
	0, 36, 74, 255, 82, 36, 0, 0,
	0, 70, 38, 16, 8, 100, 98, 0,
	0, 52, 74, 74, 52, 32, 80, 0,
	0, 0, 0, 4, 3, 0, 0, 0,
	0, 0, 0, 126, 129, 0, 0, 0,
	0, 0, 0, 129, 126, 0, 0, 0,
	0, 42, 28, 62, 28, 42, 0, 0,
	0, 8, 8, 62, 8, 8, 0, 0,
	0, 0, 0, 128, 96, 0, 0, 0,
	0, 8, 8, 8, 8, 8, 0, 0,
	0, 0, 0, 0, 96, 0, 0, 0,
	0, 64, 32, 16, 8, 4, 2, 0,
	0, 62, 65, 73, 65, 62, 0, 0,
	0, 0, 66, 127, 64, 0, 0, 0,
	0, 0, 98, 81, 73, 70, 0, 0,
	0, 0, 34, 73, 73, 54, 0, 0,
	0, 0, 14, 8, 127, 8, 0, 0,
	0, 0, 35, 69, 69, 57, 0, 0,
	0, 0, 62, 73, 73, 50, 0, 0,
	0, 0, 1, 97, 25, 7, 0, 0,
	0, 0, 54, 73, 73, 54, 0, 0,
	0, 0, 6, 9, 9, 126, 0, 0,
	0, 0, 0, 102, 0, 0, 0, 0,
	0, 0, 128, 102, 0, 0, 0, 0,
	0, 0, 8, 20, 34, 65, 0, 0,
	0, 0, 20, 20, 20, 20, 0, 0,
	0, 0, 65, 34, 20, 8, 0, 0,
	0, 2, 1, 81, 9, 6, 0, 0,
	0, 28, 34, 89, 89, 82, 12, 0,
	0, 0, 126, 9, 9, 126, 0, 0,
	0, 0, 127, 73, 73, 54, 0, 0,
	0, 0, 62, 65, 65, 34, 0, 0,
	0, 0, 127, 65, 65, 62, 0, 0,
	0, 0, 127, 73, 73, 65, 0, 0,
	0, 0, 127, 9, 9, 1, 0, 0,
	0, 0, 62, 65, 81, 50, 0, 0,
	0, 0, 127, 8, 8, 127, 0, 0,
	0, 0, 65, 127, 65, 0, 0, 0,
	0, 0, 32, 64, 64, 63, 0, 0,
	0, 0, 127, 8, 20, 99, 0, 0,
	0, 0, 127, 64, 64, 64, 0, 0,
	0, 127, 2, 4, 2, 127, 0, 0,
	0, 127, 6, 8, 48, 127, 0, 0,
	0, 0, 62, 65, 65, 62, 0, 0,
	0, 0, 127, 9, 9, 6, 0, 0,
	0, 0, 62, 65, 97, 126, 64, 0,
	0, 0, 127, 9, 9, 118, 0, 0,
	0, 0, 38, 73, 73, 50, 0, 0,
	0, 1, 1, 127, 1, 1, 0, 0,
	0, 0, 63, 64, 64, 63, 0, 0,
	0, 31, 32, 64, 32, 31, 0, 0,
	0, 63, 64, 48, 64, 63, 0, 0,
	0, 0, 119, 8, 8, 119, 0, 0,
	0, 3, 4, 120, 4, 3, 0, 0,
	0, 0, 113, 73, 73, 71, 0, 0,
	0, 0, 127, 65, 65, 0, 0, 0,
	0, 2, 4, 8, 16, 32, 64, 0,
	0, 0, 0, 65, 65, 127, 0, 0,
	0, 4, 2, 1, 2, 4, 0, 0,
	0, 64, 64, 64, 64, 64, 64, 0,
	0, 0, 1, 2, 4, 0, 0, 0,
	0, 0, 48, 72, 40, 120, 0, 0,
	0, 0, 127, 72, 72, 48, 0, 0,
	0, 0, 48, 72, 72, 0, 0, 0,
	0, 0, 48, 72, 72, 127, 0, 0,
	0, 0, 48, 88, 88, 16, 0, 0,
	0, 0, 126, 9, 1, 2, 0, 0,
	0, 0, 80, 152, 152, 112, 0, 0,
	0, 0, 127, 8, 8, 112, 0, 0,
	0, 0, 0, 122, 0, 0, 0, 0,
	0, 0, 64, 128, 128, 122, 0, 0,
	0, 0, 127, 16, 40, 72, 0, 0,
	0, 0, 0, 127, 0, 0, 0, 0,
	0, 120, 8, 16, 8, 112, 0, 0,
	0, 0, 120, 8, 8, 112, 0, 0,
	0, 0, 48, 72, 72, 48, 0, 0,
	0, 0, 248, 40, 40, 16, 0, 0,
	0, 0, 16, 40, 40, 248, 0, 0,
	0, 0, 112, 8, 8, 16, 0, 0,
	0, 0, 72, 84, 84, 36, 0, 0,
	0, 0, 8, 60, 72, 32, 0, 0,
	0, 0, 56, 64, 32, 120, 0, 0,
	0, 0, 56, 64, 56, 0, 0, 0,
	0, 56, 64, 32, 64, 56, 0, 0,
	0, 0, 72, 48, 48, 72, 0, 0,
	0, 0, 24, 160, 160, 120, 0, 0,
	0, 0, 100, 84, 84, 76, 0, 0,
	0, 0, 8, 28, 34, 65, 0, 0,
	0, 0, 0, 126, 0, 0, 0, 0,
	0, 0, 65, 34, 28, 8, 0, 0,
	0, 0, 4, 2, 4, 2, 0, 0,
	0, 120, 68, 66, 68, 120, 0, 0,
};


char textbuffer[4][16];


/********************************* GAME ***********************************************/
#define TRUE 1
#define FALSE 0

void *stderr, *stdin, *stdout;

int running;
int won;
int score;
int ticksToGravity[5] = {20, 15, 10, 5, 3};
int ticks;
int seed;
int linesremaining;
int level; //take -1 when calculating ticksToGravity.
int board[128];


typedef struct {
    uint8_t data[4][4];
    int width, row, col;

} tetromino;

tetromino current;


const tetromino shapes[6] = {
    {   {(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0xf,0xf,0}
        ,(uint8_t []){0xf,0xf,0,0}}, 4},

    {   {(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0,0,0}
        ,(uint8_t []){0xf,0xf,0,0}
        ,(uint8_t []){0,0xf,0xf,0}}, 4},

    {   {(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0,0xf,0}
        ,(uint8_t []){0xf,0xf,0xf,0}}, 4},

    {   {(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0xf,0,0}
        ,(uint8_t []){0xf,0xf,0xf,0}}, 4},

    {   {(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0xf,0xf,0}
        ,(uint8_t []){0,0xf,0xf,0}
        ,(uint8_t []){0,0,0,0}}, 4},

    {   {(uint8_t []){0,0,0,0}
        ,(uint8_t []){0xf,0xf,0xf,0xf}
        ,(uint8_t []){0,0,0,0}
        ,(uint8_t []){0,0,0,0}}, 4}
};

tetromino CopyMino(tetromino tetro){
    tetromino temp;
    temp.width = tetro.width;
    temp.col = tetro.col;
    temp.row = tetro.row;

    int i, j;
    for(i = 0; i < tetro.width; i++){
        for(j = 0; j < tetro.width; j++){
            temp.data[i][j] = tetro.data[i][j];
        }
    }
    return temp;
}

void DeleteMino(tetromino* tetro){
    int i, j;
    for(i = 0; i < tetro->width; i++){
        for(j = 0; j < tetro->width; j++){
            tetro->data[i][j] = 0x00;
        }
    }
}

void RotateMino(tetromino* tetro){
    tetromino temp = CopyMino(*tetro);
    int swapCol, elem, swapRow, width;

    width = tetro->width;
    for(swapCol = 0; swapCol < width; swapCol++){
        for(elem = 0, swapRow = width-1; elem < width; elem++, swapRow--){
            tetro->data[swapCol][elem] = temp.data[swapRow][swapCol];
        }
    }

    DeleteMino(&temp);
}

tetromino NewRandomTetro(){
    tetromino temp = CopyMino(shapes[rand()%6]);

    temp.col = 0;
    temp.row = (rand()%9)*4 - temp.width;

    DeleteMino(&current);

    return temp;
}

int checkLines(){
    int i, j, k, l;
    for(i = 0; i < 128; i = i + 4){
        if(board[i] == 0xffffffff){
            for(j = i; j < (i+4); j++){
                board[j] = 0x00;
            }

            int temp[128] = {0};
            for(l = 0; l < i; l++){
                temp[l+4] = board[l];
            }

            for(k = 0; k < i+4; k++){
                board[k] = temp[k];
            }
            return TRUE;
        }
    }
    return FALSE;
}

int checkMino(tetromino tetro){
    int i, j;
    for(i = 0; i < tetro.width; i++) {
        for(j = 0; j < tetro.width ;j++){
            uint8_t elem = board[tetro.col+(4*j)] >> 4*i+tetro.row;
            elem = elem & 0x0f;
            if((tetro.col+(4*j) < 0 || tetro.col+(4*j) >= 128 || tetro.row+i >= 32)){
                if(tetro.data[i][j]){
                    return FALSE;
                }
            }
            else if(elem && tetro.data[i][j]){
                return FALSE;
            }
        }
    }
    return TRUE;
}

void nextLevel(){
    level += 1;
}

void OledInit(){

	/* Init the PIC32 peripherals used to talk to the display.
	*/
	OledHostInit();

	/* Init the OLED display hardware.
	*/
	display_init();

	/* Clear the display.
	*/
	OledClear();

}

void OledHostInit(){
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 15;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

}
uint8_t spi_send_byte(uint8_t data){
    while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void quicksleep(int cv){
    int i;
    for(i = 0; i < cv; i++){
    }
}

/* Display initialisation from Refrence sheet and lab 3 function*/
void display_init(void){
    DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);

	spi_send_byte(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spi_send_byte(0x8D);
	spi_send_byte(0x14);

	spi_send_byte(0xD9);
	spi_send_byte(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);

	spi_send_byte(0xA1);
	spi_send_byte(0xC8);

	spi_send_byte(0xDA);
	spi_send_byte(0x20);

	spi_send_byte(0xAF);
}


void OledClear(){
	OledClearBuffer();
	updateOLED();
}

void OledClearBuffer(){
	int i;
    int* pb;

	pb = board;

	/* Fill the memory buffer with 0.
	*/
	for (i = 0; i < 128; i++) {
		pb[i] = 0;
	}

}

int getbtns(){
    int result = (PORTD >> 5) & 0x7;
    return result;
}

int getsw(){
    unsigned int result = ((PORTD >> 11) & 0x1);
    return result;
}

void writeToBoard(tetromino temp){
    int i,j,k;
    for(i = 0; i < temp.width; i++){
        for(j = 0; j < temp.width; j++){
            for(k = 0; k < temp.width; k++){
                if(temp.data[i][j]){
                    board[temp.col + k + (4*j)] |= temp.data[i][j] << (4*i+temp.row);
                }
            }
        }
    }
}

void deleteFromBoard(tetromino tetro){
    int i,j,k;
    for(i = 0; i < tetro.width; i++){
        for(j = 0; j < tetro.width; j++){
            for(k = 0; k < tetro.width; k++){
                if(tetro.data[i][j] == 0){
                    continue;
                }
                board[tetro.col + k + (4*j)] &=  (~0x0f) << (4*i)+tetro.row;
            }
        }
    }
}

void updateOLED(void){
    int i, j;
    int* updateBuffer;

    updateBuffer = board;
    for(i = 0; i < 4; i++){
        DISPLAY_CHANGE_TO_COMMAND_MODE;

        spi_send_byte(0x22);
        spi_send_byte(i);

        spi_send_byte(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

        /* Copy this memory page of display data.
        */
        for (j = 0; j < 128; j++){
            uint8_t u = updateBuffer[j] >> 8*i;
            spi_send_byte(u);
        }
    }
}


/*
* The functions display_string and display_update are taken from labs, and have been modified to fit our project.
*/


void text_update(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;

	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}


void display_text(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_byte(0x22);
		spi_send_byte(i);

		spi_send_byte(0x0);
		spi_send_byte(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;

			for(k = 0; k < 8; k++)
				spi_send_byte(font[c*8 + k]);
		}
	}
}


void timerInit(){
    T2CON = 0x70;
    PR2 = 15625;
    IECSET(0) = 1<<8;
    IPCSET(2) = 0x7<<2;
    TMR2 = 0;
    T2CONSET = 1<<15;
}

/* Initialize game and startscreen, wait for starting input*/
void gameInit(){
    //Initialize screen
    OledInit();

    //Initialize timer
    timerInit();

    //Setup button and switch ports
    TRISD |= 0x8e0;
    TRISF |= 0x1;


    //Intialize parameters
    running = TRUE;
    score = 0;
    won = FALSE;
    level = 1;
    linesremaining = 20;
    ticks = ticksToGravity[level-1];


    //Print start text
    //TODO

    //Wait for input
    while(1){
        //displaytext

        int btn1 = PORTF & 0x1;
        if(btn1){
            OledClear();
            return;
        }
    }
}


// CHECK LINES AT GRAVITY TICK ALSO CREATE NEW SHAPE HERE

int gameLoop(){
    int state = TRUE;

    if((IFS(0)>>8) & 1){

        IFSCLR(0) = 1<<8;
        int btnStart = getbtns();
        int sw = getsw();
        ticks--;

        deleteFromBoard(current);

        if(btnStart){
            int btn4 = (t>>2) & 0x1;
            int btn3 = (t>>1) & 0x1;
            int btn2 = t & 0x1;

            if(btn4){
                tetromino temp = CopyMino(current);
                RotateMino(temp);
                if(checkMino(temp)){
                    RotateMino(current);
                }
            }

            if(btn3){
                tetromino temp = CopyMino(current);
                temp.row += 4;
                if(checkMino(temp)){
                    current.row += 4;
                }
            }

            if(btn2){
                tetromino temp = CopyMino(current);
                temp.row -= 4;
                if(checkMino(temp)){
                    current.row -= 4;
                }
            }

        }else{
            if(sw){
                int *temp = board;
                OledClear();
                //displaytext
                while(1){
                    int close = getsw();
                    if(!close){
                        OledClear();
                        break;
                    }
                }
                int i;
                for(i = 0; i < 128; i++){
                    board[i] = temp[i];
                }
            }
        }

        if(ticks == 0){
            tetromino temp = CopyMino(current);
            temp.col += 4;

            /* Hit bottom*/
            if(!checkMino(temp)){
                writeToBoard(temp);

                if(checkLines()){
                    score += 1000;
                    linesremaining--;

                    if(linesremaining == 0){
                        nextLevel();
                        if(level == 6){
                            won = TRUE;
                            state = FALSE;
                        }
                    }
                }
                current = NewRandomTetro();
            }else{
                current.col += 4;
            }
            ticks = ticksToGravity[level-1];
        }

        writeToBoard(current);
        updateOLED();
    }

    return state;
}

void gameEnd(){
    //Print finishing text, i.e. score and level
    //TODO

    //Ask for restart input
    // restart main();
}

int main(){
    gameInit();
    seed = 0;
    srand(seed);
    current = NewRandomTetro();
    writeToBoard();
    updateOLED();
    while(running){
        running = gameLoop();
    }
    if(won){
        gameWin();
    }else{
        gameEnd();
    }

    //ARRAY UTAN CURRENT I
    return 0;
}
