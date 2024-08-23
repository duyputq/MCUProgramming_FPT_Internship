#include <stdio.h>
#include "MKE16Z4.h"

#include "app/inc/app.h"
#include "driver/inc/driver.h"
#include "hal/inc/hal.h"

int main(void)
{
    initLed();

    while (1)
    {
        Mode1();
        Mode2();
    }

    return 0;
}
