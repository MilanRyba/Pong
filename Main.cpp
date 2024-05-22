#define _POSIX_C_SOURCE 200112L
 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <time.h>
#include <unistd.h>
 
#include "mz_apo/mzapo_parlcd.h"
#include "mz_apo/mzapo_phys.h"
#include "mz_apo/mzapo_regs.h"

#include "src/Pong.h"

#include <iostream>

// TODO: Test if pressing two knobs is ok
int main()
{
    Application::Application pong;
    std::cout << "Running\n";
    pong.Run();
    std::cout << "Exited\n";
}
