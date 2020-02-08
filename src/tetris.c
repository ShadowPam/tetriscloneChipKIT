#include <stdlib.h>
#include <stdint.h>
#include <pic32mx.h>



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
int ticksToGravity[5] = {2, 12, 9, 5, 4};
int ticks;
int seed;
int linesremaining;
int level; //take -1 when calculating ticksToGravity.
int board[128];
int staticBoard[128];
char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


typedef struct {
    char name[4];
    int score;
} ScoreEntry;

ScoreEntry highscores[10];


typedef struct {
    uint8_t data[4][4];
    int width, row, col;

} tetromino;

tetromino current;
tetromino next;


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

inline int modulo(int a, int b) {
    if(b < 0) return modulo(-a, -b);
    const int result = a % b;
    return result >= 0 ? result : result + b;
}


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
    temp.row = 8;
    return temp;
}

int checkLines(){
    int i, j, k, l;
    for(i = 0; i < 128; i = i + 4){
        if(board[i] == 0xffffffff){
            for(j = i; j < (i+4); j++){
                board[j] = 0x00;
                staticBoard[j] = 0x00;
            }

            int temp[128] = {0};
            for(l = 0; l < i; l++){
                temp[l+4] = staticBoard[l];
            }

            for(k = 0; k < i+4; k++){
                staticBoard[k] = temp[k];
            }
            return TRUE;
        }
    }
    return FALSE;
}

int checkMino(tetromino tetro){
    int i, j;
    int state = TRUE;
    for(i = 0; i < tetro.width; i++) {
        for(j = 0; j < tetro.width ;j++){
            if(tetro.data[i][j] == 0){
                continue;
            }
            uint8_t elem = staticBoard[tetro.col+(4*j)] >> (4*i+tetro.row);
            elem = elem & 0x0f;

            if((tetro.col+(4*j) >= 128 || tetro.row < 0 || tetro.row+tetro.width+i+4 >= 31)){
                if(tetro.data[i][j]){
                    state = FALSE;
                }
            }else if(elem && tetro.data[i][j]){
                state = FALSE;
            }
        }
    }
    return state;
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

int compareScores (const void * a, const void * b)
{
  if ( ((ScoreEntry*)a)->score <  ((ScoreEntry*)b)->score ) return 1;
  if ( ((ScoreEntry*)a)->score == ((ScoreEntry*)b)->score ) return 0;
  if ( ((ScoreEntry*)a)->score >  ((ScoreEntry*)b)->score ) return -1;
}

int min(int a, int b){
    return a < b ? a : b;
}

int max(int a, int b){
    return a > b ? a : b;
}

/*
 * itoa
 * Taken from lab 3
 */
#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";
  
  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
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
    clearText();
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

void clearText(){
    int i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 16; j++){
            textbuffer[i][j] = 0;
        }
    }
}

void concatenate(char p[], char q[], char out[]) {
   int c, d;
   
   c = 0;
 
   while (p[c] != '\0') {
       out[c] = p[c];
      c++;      
   }
 
   out[c] = ' ';
   c++;
   d = 0;
 
   while (q[d] != '\0') {
      out[c] = q[d];
      d++;
      c++;    
   }
 
   out[c] = '\0';
}


int getbtns(){
    int result = (PORTD >> 5) & 0x7;
    return result;
}

int getsw(){
    unsigned int result = ((PORTD >> 9) & 0x7);
    return result;
}

void writeToBoard(tetromino temp){
    int i,j,k;
    for(i = 0; i < temp.width; i++){
        for(j = 0; j < temp.width; j++){
            if(temp.data[i][j] == 0){
                continue;
            }
            for(k = 0; k < temp.width; k++){
                if(temp.data[i][j]){
                    board[temp.col + k + (4*j)] |= temp.data[i][j] << (4*i+temp.row);
                }
            }
        }
    }
}

void writeToStaticBoard(tetromino temp){
    int i,j,k;
    for(i = 0; i < temp.width; i++){
        for(j = 0; j < temp.width; j++){
            if(temp.data[i][j] == 0){
                continue;
            }
            for(k = 0; k < temp.width; k++){
                if(temp.data[i][j]){
                    staticBoard[temp.col + k + (4*j)] |= temp.data[i][j] << (4*i+temp.row);
                }
            }
        }
    }
}

void deleteFromBoard(tetromino tetro){
    int i,j,k;
    for(i = 0; i < tetro.width; i++){
        for(j = 0; j < tetro.width; j++){
            if(tetro.data[i][j] == 0){
                continue;
            }
            for(k = 0; k < tetro.width; k++){
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

/* Taken from lab 3*/
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

/* Taken from lab 3*/
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

void printHighscore(){
    int index = 0;
    int i;

    for(i = 0; i < 4; i++){
            char temp[14];

            concatenate(itoaconv(i+1), highscores[i].name, temp);
            concatenate(temp, itoaconv(highscores[i].score), temp);

            text_update(i, temp);
    }

    display_text();
    while(1){
        int btns = getbtns();
        int btn4 = (btns>>2) & 0x1;
        int btn3 = (btns>>1) & 0x1;

        int close = getsw();
        if(!close){
            OledClear();
            updateOLED();
            break;
        }

        if(btns){
            if(btn4){
                index = min(index+1, 6);
            }

            if(btn3){
                index = max(index-1, 0);
            }

            
            for(i = 0; i < 4; i++){
                char temp[14];

                concatenate(itoaconv(i+index+1), highscores[i+index].name, temp);

                concatenate(temp, itoaconv(highscores[i+index].score), temp);

                text_update(i, temp);
            }
            display_text();
        }

        quicksleep(999999);
    }

}

void timerInit(){
    T2CON = 0x70;
    PR2 = 38250;
    IECSET(0) = 1<<8;
    IPCSET(2) = 0x7<<2;
    TMR2 = 0;
    T2CONSET = 1<<15;
}

/* Initialize game and startscreen, wait for starting input*/
void startup(){
    //Initialize screen
    OledInit();

    //Initialize timer
    timerInit();

    //Setup button and switch ports
    TRISD |= 0x8e0;
    TRISF |= 0x1;

    int i;
    for(i = 0; i<10; i++){
        ScoreEntry temp = {"AAA", 0};
        highscores[i] = temp;
    }

}

void gameInit(){
    //Intialize parameters
    running = TRUE;
    score = 10;
    won = FALSE;
    level = 1;
    linesremaining = 5;
    ticks = ticksToGravity[level-1];

    text_update(0,"Tetris!");
    text_update(1, "To start game:");
    display_text();
    quicksleep(100000);
    text_update(2,"Press BTN2");
    display_text();

    //Wait for input
    while(1){
        seed += 1;
        if(PORTD >>5 & 0x1){
            OledClear();
            text_update(2, "Good luck");
            text_update(3, "Have fun!");
            display_text();
            quicksleep(10000000);
            OledClear();
            return;
        }
    }
}

int checkGameOver(){
    int state = FALSE;
    state = checkMino(current);
    return state;
}

/* Gameloop for the game */
int gameLoop(){
    int state = TRUE;

    if((IFS(0)>>8) & 1){

        IFSCLR(0) = 1<<8;
        int btnStart = getbtns();
        int swStart = getsw();
        ticks--;

        deleteFromBoard(current);
        int i;
        for(i = 0; i < 128; i++){
            board[i] = staticBoard[i];
        }

        if(ticks == 0){
            tetromino temp = CopyMino(current);
            temp.col += 4;

            /* Hit bottom*/
            if(!checkMino(temp)){
                writeToStaticBoard(current);
                writeToBoard(current);

                if(checkLines()){
                    score += 10;
                    linesremaining--;

                    if(linesremaining == 0){
                        nextLevel();
                        if(level == 6){
                            won = TRUE;
                            state = FALSE;
                        }
                    }
                }
                current = next;
                next = NewRandomTetro();
                state = checkGameOver();
            }else{
                int currentcoltemp = current.col + 4;
                while(1){
                        current.col += 1;
                        writeToBoard(current);
                        updateOLED();
                        deleteFromBoard(current);
                        int i;
                        for(i = 0; i < 128; i++){
                            board[i] = staticBoard[i];
                        }
                        quicksleep(100000);
                    
                    if(current.col == currentcoltemp){
                        break;
                    }
                }
            }
            ticks = ticksToGravity[level-1];
        }

        if(btnStart){
            int btn4 = (btnStart>>2) & 0x1;
            int btn3 = (btnStart>>1) & 0x1;
            int btn2 = btnStart & 0x1;

            if(btn4){
                tetromino temp = CopyMino(current);
                RotateMino(&temp);
                if(checkMino(temp)){
                    RotateMino(&current);
                }
            }

            if(btn3){
                tetromino temp = CopyMino(current);
                temp.row += 4;
                if(checkMino(temp)){
                    int currentrowtemp = current.row + 4;
                    while(1){
                            current.row += 1;
                            writeToBoard(current);
                            updateOLED();
                            deleteFromBoard(current);
                            int i;
                            for(i = 0; i < 128; i++){
                                board[i] = staticBoard[i];
                            }
                            quicksleep(100000);
                        
                        if(current.row == currentrowtemp){
                            break;
                        }
                    }
                }
            }

            if(btn2){
                tetromino temp = CopyMino(current);
                temp.row -= 4;
                if(checkMino(temp)){
                    int currentrowtemp = current.row - 4;
                    while(1){
                            current.row -= 1;
                            writeToBoard(current);
                            updateOLED();
                            deleteFromBoard(current);
                            int i;
                            for(i = 0; i < 128; i++){
                                board[i] = staticBoard[i];
                            }
                            quicksleep(100000);
                        
                        if(current.row == currentrowtemp){
                            break;
                        }
                    }
                }
            }

        }
        if(swStart){
            int sw1 = (swStart>>2) & 0x1; 
            int sw2 = (swStart>>1) & 0x1;
            int sw3 = swStart & 0x1;

            if(sw1){
                int *temp = board;
                OledClear();
                text_update(0, "Level,score,lines");
                text_update(1, itoaconv(level));
                text_update(2, itoaconv(score));
                text_update(3, itoaconv(linesremaining));
                display_text();
                while(1){
                    int close = getsw();
                    if(!close){
                        OledClear();
                        updateOLED();
                        break;
                    }
                }
                int i;
                for(i = 0; i < 128; i++){
                    board[i] = temp[i];
                }
            }

            if(sw2){
                int *tempgame = board;
                OledClear();
                text_update(0, "Next block:");
                display_text();

                int tempboard[128];
                tetromino temp = CopyMino(next);
                temp.col = 50;
                temp.row = 14;

                int q;
                int* pb;

                pb = tempboard;

                /* Fill the memory buffer with 0.
                */
                for (q = 0; q < 128; q++) {
                    pb[q] = 0;
                }

                int p,l,s;
                for(p = 0; p < temp.width; p++){
                    for(l = 0; l < temp.width; l++){
                        if(temp.data[p][l] == 0){
                            continue;
                        }
                        for(s = 0; s < temp.width; s++){
                            if(temp.data[p][l]){
                                tempboard[temp.col + s + (4*l)] |= temp.data[p][l] << (4*p+temp.row);
                            }
                        }
                    }
                }

                int i, j;
                int* updateBuffer;
                updateBuffer = tempboard;

                for(i = 2; i < 4; i++){
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
                while(1){
                    int close = getsw();
                    if(!close){
                        OledClear();
                        updateOLED();
                        break;
                    }
                }


                int loopgame;
                for(loopgame = 0; loopgame < 128; loopgame++){
                    board[i] = tempgame[i];
                }
            }

            if(sw3){
                int *tempgame = board;
                OledClear();
                printHighscore();

                int loopgame;
                for(loopgame = 0; loopgame < 128; loopgame++){
                    board[i] = tempgame[i];
                }  
            }
        }

        writeToBoard(current);
        updateOLED();
    }

    return state;
}

void gameEnd(){
    text_update(0, "GAME OVER, too bad :(");

    addHighscore();

    text_update(2, "Press BTN2 to try again");
    display_text();

    int btn = getbtns();

    while(1){
        int btn = getbtns();

        if(btn & 0x1){
            break;
        }
    }
    quicksleep(999999);
}

void addHighscore(){
    OledClear();

    if(score <= highscores[9].score){
        text_update(0, "Score not in top10");
        text_update(2, "Press btn2");
        display_text();
        while(1){
            int btn = getbtns();

            if(btn & 0x1){
                break;
            }
        }
        return;
    }

    ScoreEntry temp = {"AAA", 0};
    temp.score = score;
    int letterPos = 0;
    int alphabetPos = 0;
    text_update(0, "Enter your name:");

    text_update(1, temp.name);
    text_update(2, "*");
    display_text();

    while(1){
        
        int btns = getbtns();
        int btn4 = (btns>>2) & 0x1;
        int btn3 = (btns>>1) & 0x1;
        int btn2 = btns & 0x1;

        if(btn4){
            alphabetPos = modulo(alphabetPos-1, 26);
            temp.name[letterPos] = alphabet[alphabetPos];
        }

        if(btn3){
            alphabetPos = modulo(alphabetPos+1, 26);
            temp.name[letterPos] = alphabet[alphabetPos];
        }

        if(btn2){
            alphabetPos = 0;
            letterPos++;
            if(letterPos == 1){
                text_update(2, " *");
            }
            if(letterPos == 2){
                text_update(2, "  *");
            }
            if(letterPos == 3){
                break;
            }
        }

        text_update(1, temp.name);
        display_text();
        quicksleep(999945);
    }
    
    highscores[9] = temp;
    qsort(highscores, 10, sizeof(ScoreEntry), compareScores);

    clearText();
    while(1){
            int btn = getbtns();

            if(btn & 0x1){
                break;
            }
    }
    
}

void gameWin(){
    text_update(0, "YOU'RE THE BEST, WELL DONE!");
    text_update(1, "You defeated level 6");
    text_update(3, "To play again press BTN2");
    while(1){
        int btn = getbtns();

        if(btn & 0x1){
            break;
        }
    }
}

int main(){

    seed = 0;
    startup();
    gameInit();
    seed = seed*seed;
    srand(seed);


    while(1){ 
        current = NewRandomTetro();
        next = NewRandomTetro();
        writeToBoard(current);
        updateOLED();

        //Clear static board
        int i;
        for(i = 0; i < 128; i++){
            staticBoard[i] = 0;
        }

        while(running){
            running = gameLoop();
        }
        if(won){
            gameWin();
        }else{
            gameEnd();
        }
        gameInit();
    }

    return 0;
}
