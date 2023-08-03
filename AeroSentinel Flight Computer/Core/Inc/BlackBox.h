/*
 * BlackBox.h
 *
 *  Created on: Jul 20, 2023
 *      Author: yaxsomo
 */

#ifndef INC_BLACKBOX_H_
#define INC_BLACKBOX_H_

#include <stdbool.h>

void UART_Transmit_Messages_BlackBox(const char* str);
bool file_exists(const char* filename);
int buf_size(char *buf);
void buf_clear(void);
void mount_sd_card();
void check_free_space();
//void create_file();
void create_file(const char* filename);
void append_data_to_file(const char* filename, const char* data);
void read_file();
void unmount_sd_card();

#endif /* INC_BLACKBOX_H_ */
