#include "bsp.h"
#include "app.h"
#include "modbusSlaver.h"

void main(void)
{
    bsp_init();
    MBS_Init();
    enableInterrupts();
    app_init();
    system_run();
}

void assert_failed(u8 *file, u32 line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1);
}
