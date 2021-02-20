/*
 * This is a cool header :D
 */

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

uint8_t ucHeap[configTOTAL_HEAP_SIZE];

#define mainQUEUE_RECEIVE_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define mainQUEUE_SEND_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

#define mainQUEUE_SEND_FREQUENCY_MS (1000 / portTICK_PERIOD_MS)

#define mainQUEUE_LENGTH (1)

#define mainQUEUE_SEND_PARAMETER (0x1111UL)
#define mainQUEUE_RECEIVE_PARAMETER (0x22UL)

static QueueHandle_t xQueue = NULL;

static void ledOnTask(void) {

}

static void ledOffTask(void) {

}

int main(void) {
    xTaskCreate();
    xTaskCreate();

    vTaskStartScheduler();

    configAssert(0);
    return -1;
}
