/*
 * RTOS_Attributes_Local.h
 *
 *  Created on: Sep 10, 2023
 *      Author: yaxsomo
 */

#ifndef INC_RTOS_ATTRIBUTES_LOCAL_H_
#define INC_RTOS_ATTRIBUTES_LOCAL_H_

// ---------  RTOS TASK ATTRIBUTES ---------//
// Define the attributes for the command wait task
osThreadAttr_t commandWaitTask_attributes = {
  .name = "StartCommandWaitTask",
  .priority = (osPriority_t) osPriorityNormal, // Set the desired priority
  .stack_size = 128 * 4 // Set the stack size as needed
};



osThreadAttr_t menuTask_attributes = {
  .name = "MenuTask",
  .priority = (osPriority_t) osPriorityNormal, // Set the desired priority
  .stack_size = 128 * 4 // Set the stack size as needed
};
// ---------  END RTOS TASK ATTRIBUTES ---------//


// ---------  RTOS SEMAPHORES ---------//

// ---------  END RTOS SEMAPHORES ---------//

#endif /* INC_RTOS_ATTRIBUTES_LOCAL_H_ */
