#include "mbed.h"

Serial pc(USBTX, USBRX); // USBTX, USBRX
Serial board(D10, D2); // D10:tx, D2:rx

DigitalOut myled1(LED1);
DigitalOut power(D4); // power line
char buff[1024];

int main() {
    power =1; //default.  
    pc.baud(115200);
    board.baud(115200);
    pc.printf("Power control..");

    //pc.printf("Power on and wait key input.\r\n");
    power =0;
    wait(1.5);
    power =1; //default.
    pc.printf("[Done]\r\n");

    pc.printf("Wait 6 sec...\r\n");
    wait(6);
    pc.printf("Send message...\r\n");
   
    int a=0, i=0; 
    while (1) {
        pc.printf("Send AT command\r\n");
        board.printf("ati\r\n");

        for(a=0; a<1024; a++) {
            if(board.readable()) {
        		buff[i]=board.getc();
                i++;
            }
    
            if(buff[i]=='\r')
                break;
    	}
        for(i=0; i<1024; i++) {
    		pc.printf("%c",buff[i]);
            myled1 = !myled1;
    	}
        
        i=0;
        wait(1.5);
        pc.printf("\r\n[%d]Message check done...\r\n",a++);
    }
}
