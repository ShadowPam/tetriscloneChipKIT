#include <stdio.h>
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

#define ROWS 21
#define COLS 11
#define TRUE 1
#define FALSE 0 

int running = false;
int score = 0;
int tme = 0;
char board[ROWS*COLS];

typedef struct {
    char data[4][4];
    int width, row, col;
    
} tetromino;

tetromino current;

const tetromino shapes[6] = {
    {   {(char []){0,0,0,0}
        ,(char []){0,0,1,1}
        ,(char []){0,1,1,0}
        ,(char []){0,0,0,0}}, 4},

    {   {(char []){0,0,0,0}
        ,(char []){0,1,1,0}
        ,(char []){0,0,1,1}
        ,(char []){0,0,0,0}}, 4},   

    {   {(char []){0,0,0,0}
        ,(char []){0,0,1,0}
        ,(char []){0,1,1,1}
        ,(char []){0,0,0,0}}, 4},  

    {   {(char []){0,0,0,0}
        ,(char []){0,0,0,1}
        ,(char []){0,1,1,1}
        ,(char []){0,0,0,0}}, 4},            

    {   {(char []){0,0,0,0}
        ,(char []){0,1,1,0}
        ,(char []){0,1,1,0}
        ,(char []){0,0,0,0}}, 4}, 

    {  {(char  []){0,0,0,0}
        ,(char []){1,1,1,1}
        ,(char []){0,0,0,0}
        ,(char []){0,0,0,0}}, 4}
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
    tetromino temp = CopyMino(shapes[rand()%6]);

    temp.col = rand()%(COLS-temp.width+1);
    temp.row = 0;

    //DeleteMino(current);

    return temp;
}

typedef struct {
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
} game;

/* Taken from Lab 3 main function*/
void spiSetup(){
    /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
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
	SPI2BRG = 4;
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
void display_init(){
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



void spi_send_large(int size, char* data){
    int i;
    for(i = 0; i < size; i++){
        while(!(SPI2STAT & 0x08));
        SPI2BUF = *data++;
        while(!(SPI2STAT & 1));
    }
}

void updateOLED(){
    int i;
    char* updateBuffer;
    updateBuffer = board;
    for (i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        spi_send_byte(0x22);
        spi_send_byte(i);

        spi_send_byte(0x00);
        spi_send_byte(0x10);

        DISPLAY_CHANGE_TO_COMMAND_MODE;
        
        /* Copy this memory page of display data.
        */
        spi_send_large(4, updateBuffer);
        updateBuffer += 4;
    }
}



int main(){

    spiSetup();
    display_init();

    updateOLED();

    int i;
    for(i = 0; i < (ROWS*COLS); i++){
        board[i] = 1;
    }
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
    while(1){
        updateOLED();
    }
    return 0;
}