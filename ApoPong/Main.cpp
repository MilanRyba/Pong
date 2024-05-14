
#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 
#include "mz_apo/mzapo_parlcd.h"
#include "mz_apo/mzapo_phys.h"
#include "mz_apo/mzapo_regs.h"

#include "src/Pong.h"

#include <iostream>
 
unsigned short *framebuffer;
 
void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    framebuffer[x+480*y] = color;
  }
}
 
int main()
{
    Pong::Pong pong;
    std::cout << "Running\n";
    pong.Run();
    std::cout << "Exited\n";
}

int main(int argc, char *argv[])
{
    unsigned char *parlcd_mem_base, *mem_base;
    int i,j;
    int ptr;
    unsigned int c;
    framebuffer  = (unsigned short *)malloc(320*480*2);
    
    printf("Hello world\n");
    
    parlcd_mem_base = (unsigned char*)map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcd_mem_base == NULL)
      exit(1);
    
    mem_base = (unsigned char*)map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (mem_base == NULL)
      exit(1);
    
    parlcd_hx8357_init(parlcd_mem_base);
    
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    ptr=0;
    for (i = 0; i < 320 ; i++)
    {
        for (j = 0; j < 480 ; j++)
        {
            c = 0;
            framebuffer[ptr]=c;
            parlcd_write_data(parlcd_mem_base, framebuffer[ptr++]);
        }
    }
    
    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;
    int xx=0, yy=0;
    while (1)
    {
    
        int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        if ((r&0x7000000)!=0)
          break;

        xx = ((r & 0xff) * 480) / 64;
        yy = (((r >> 8) & 0xff) * 320) / 64;
        
        int red_y = (((r >> 16) & 0xff) * 320) / 64;
        int blue_y = ((r & 0xff) * 320) / 64;
        
        for (ptr = 0; ptr < 320 * 480 ; ptr++)
            framebuffer[ptr]=0x7500;
        
        // Render red paddle
        uint16_t red = 0b1111100000000000;
        for (j=0; j<120; j++)
            for (i=20; i<40; i++)
                draw_pixel(i,j+red_y, red);
        
        // Render blue paddle
        uint16_t blue = 0b0000000000011111;
        for (j=0; j<120; j++)
            for (i=440; i<460; i++)
                draw_pixel(i,j+blue_y, blue);
        
        // Render ball
        uint16_t white = 0xffff;
        for (j=236; j<243; j++)
            for (i=156; i<163; i++)
                draw_pixel(i + red_y,j + blue_y, white);
        
        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (ptr = 0; ptr < 480*320 ; ptr++)
            parlcd_write_data(parlcd_mem_base, framebuffer[ptr]);
        
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
    
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < 480*320 ; ptr++)
        parlcd_write_data(parlcd_mem_base, 0);
    
    printf("Goodbye world\n");
    
    return 0;
}
