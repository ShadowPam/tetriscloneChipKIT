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


/********************************* GAME ***********************************************/
#define ROWS 20
#define COLS 10

#define TRUE 1
#define FALSE 0 

void *stderr, *stdin, *stdout;

int running = false;
int score = 0;
int tme = 0;
uint8_t board[512];

typedef struct {
    uint8_t data[4][4];
    int width, row, col;
    
} tetromino;

tetromino current;

const tetromino shapes[6] = {
    {   {{0xf,0xf,0xf,0xf}
        ,{0xff,0xff,0xff,0xff}
        ,{0xf0,0xf0,0xf0,0xf0}
        ,{0,0,0,0}}, 4},

    {   {{0xf0,0xf0,0xf0,0xf0}
        ,{0xff,0xff,0xff,0xff}
        ,{0xf,0xf,0xf,0xf}
        ,{0,0,0,0}}, 4},   

    {   {{0xf0,0xf0,0xf0,0xf0}
        ,{0xff,0xff,0xff,0xff}
        ,{0xf0,0xf0,0xf0,0xf0}
        ,{0,0,0,0}}, 4},  

    {   {{0xf0,0xf0,0xf0,0xf0}
        ,{0xf0,0xf0,0xf0,0xf0}
        ,{0xff,0xff,0xff,0xff}
        ,{0,0,0,0}}, 4},            

    {   {{0xff,0xff,0xff,0xff}
        ,{0xff,0xff,0xff,0xff}
        ,{0,0,0,0}
        ,{0,0,0,0}}, 4}, 

    {   {{0xf,0xf,0xf,0xf}
        ,{0xf,0xf,0xf,0xf}
        ,{0xf,0xf,0xf,0xf}
        ,{0xf,0xf,0xf,0xf}}, 4}
};

tetromino CopyMino(tetromino tetro){
    tetromino temp;
    temp.width = tetro.width;
    temp.col = tetro.col;
    temp.row = tetro.row;
/*     for(int k = 0; k < tetro.width; k++){
        for(int l = 0; l < tetro.width; l++){
            copyData[k][l] = tetro.data[k][l];
        }
    } */

    //temp.data = (char**)malloc(temp.width*sizeof(char*));
    int i, j;
    for(i = 0; i < tetro.width; i++){
        //temp.data[i] = (char*)malloc(temp.width*sizeof(char));
        for(j = 0; j < tetro.width; j++){
            temp.data[i][j] = tetro.data[i][j];
        }
    }
    return temp;
}

void DeleteMino(tetromino tetro){
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

    DeleteMino(temp);
}

tetromino NewRandomTetro(){
    int r2 = rand2(0,10000);
    tetromino temp = CopyMino(shapes[r2%6]);

    int r1 = rand2(0, 10000);
    temp.col = r1%(COLS-temp.width+1);
    temp.row = 0;

    DeleteMino(current);

    return temp;
}

/* typedef struct {
    //Game variables
    int row;
    int col;
    int score;
    int running;
    int time;

    //Current and next block
    tetromino current;
    tetromino next;


    int *board;
} game; */

/* Implementation of stdlib.h rand() function*/
int rand2(int start_range,int end_range){
    static int rand = 0xACE1U; /* Any nonzero start state will work. */

    /*check for valid range.*/
    if(start_range == end_range) {
        return start_range;
    }

    /*get the random in end-range.*/
    rand += 0x3AD;
    rand %= end_range;

    /*get the random in start-range.*/
    while(rand < start_range){
        rand = rand + end_range - start_range;
    }

    return rand;
  }

void user_isr(){

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


void OledClear()
	{

	OledClearBuffer();
	updateOLED();

}

void OledClearBuffer(){
	int i;
    uint8_t* pb;

	pb = board;

	/* Fill the memory buffer with 0.
	*/
	for (i = 0; i < 512; i++) {
		pb[i] = 0x00;
	}

}

void updateOLED(void){
    int i, j;
    uint8_t* updateBuffer;

    updateBuffer = board;

    for (i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        spi_send_byte(0x22);
        spi_send_byte(i);

        spi_send_byte(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

        /* Copy this memory page of display data.
        */
       for (j = 0; j < 128; j++){
           uint8_t u = updateBuffer[j + 128*i];
           spi_send_byte(u);
       }
        //spi_send_large(128, updateBuffer);
        //updateBuffer += 128;
    }
}



int main(){
    
    OledInit();
    tetromino seed = CopyMino(shapes[0]);
    int data = seed.data[0][1];
    data = data << 10;
    data = data * 32;
    srand();
    int rands = rand();
    tetromino temp = CopyMino(shapes[rands&6]);
    int i,j;

    int count = -1;
     for(i = 0; i < temp.width; i++){
        for(j = 0; j < temp.width; j++){
            count++;
            board[count] = temp.data[i][j] & 0xFF;
        }
    }

   
/*  board[0] = 0xff;
    board[1] = 0xff;
   board[2] = 0xff;
   board[3] = 0xff;

     board[4] = 0xff;
    board[5] = 0xff;
   board[6] = 0xff;
   board[7] = 0xff;

   board[8] = 0xf0;
    board[9] = 0xf0;
   board[10] = 0xf0;
   board[11] = 0xf0;  
 */



    updateOLED();
/*     tetromino temp = CopyMino(shapes[0]);

    printf("%d %d %d", temp.width, temp.row, temp.col);

    printf("\n");
    printf("space");
    printf("\n");
    for(int i = 0; i < temp.width; i++){
        printf("\n");
        for(int j = 0; j < temp.width; j++){

            printf("%d", temp.data[i][j]);
        }
    }

    RotateMino(&temp);

    printf("\n\n");
    printf("space");
    printf("\n");
    for(int i = 0; i < temp.width; i++){
        printf("\n");
        for(int j = 0; j < temp.width; j++){

            printf("%d", temp.data[i][j]);
        }
    }
 
    RotateMino(&temp);

    printf("\n");
    printf("space");
    printf("\n");
    for(int i = 0; i < temp.width; i++){
        printf("\n");
        for(int j = 0; j < temp.width; j++){

            printf("%d", temp.data[i][j]);
        }
    } 

    RotateMino(&temp);

    printf("\n\n");
    printf("space");
    printf("\n");
    for(int i = 0; i < temp.width; i++){
        printf("\n");
        for(int j = 0; j < temp.width; j++){

            printf("%d", temp.data[i][j]);
        }
    } */
    return 0;
}