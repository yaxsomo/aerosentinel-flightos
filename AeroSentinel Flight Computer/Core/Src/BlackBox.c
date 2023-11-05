/*
 * BlackBox.c
 *
 *  Created on: Jul 20, 2023
 *      Author: yaxsomo
 */

#include "BlackBox.h"

#include "fatfs.h"
#include "fatfs_sd.h"
#include "string.h"

FATFS fs; // File System
FIL fil; // File
FRESULT fresult; // To store the result
char data_buffer[1024];
UINT br, rw; // File Read/Write count

//Capacity variables
FATFS *pfs;
DWORD fre_clust;
uint32_t total, free_space;

const char* fresultStrings[] = {
    "FR_OK",
    "FR_DISK_ERR",
    "FR_INT_ERR",
    "FR_NOT_READY",
    "FR_NO_FILE",
    "FR_NO_PATH",
    "FR_INVALID_NAME",
    "FR_DENIED",
    "FR_EXIST",
    "FR_INVALID_OBJECT",
    "FR_WRITE_PROTECTED",
    "FR_INVALID_DRIVE",
    "FR_NOT_ENABLED",
    "FR_NO_FILESYSTEM",
    "FR_MKFS_ABORTED",
    "FR_TIMEOUT",
    "FR_LOCKED",
    "FR_NOT_ENOUGH_CORE",
    "FR_TOO_MANY_OPEN_FILES",
    "FR_INVALID_PARAMETER"
};

extern UART_HandleTypeDef huart1;


void UART_Transmit_Messages_BlackBox(const char* str)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}



bool file_exists(const char* filename) {
    FILINFO fno;
    FRESULT result = f_stat(filename, &fno);
    return result == FR_OK && !(fno.fattrib & AM_DIR);
}



int buf_size(char *buf){
	int i = 0;
	while(*buf++ != '\0') i++;
	return i;

}

void buf_clear(void){
	for (int i = 0; i < 1024; i++ ){
		data_buffer[i] = '\0';
	}
}


void mount_sd_card(){
	fresult = f_mount(&fs, "",0);
	//UART_Transmit_Messages_BlackBox(fresultStrings[fresult]);
	if(fresult != FR_OK)
	{
		UART_Transmit_Messages_BlackBox("*               Error mounting the SD Card              *\r\n");
	} else {
		UART_Transmit_Messages_BlackBox("*              SD Card mounted successfully!            *\r\n");
	}
}


int mount_sd_card_plus(){
    fresult = f_mount(&fs, "", 0);

    if (fresult != FR_OK) {
        UART_Transmit_Messages_BlackBox("* Error mounting the SD Card *\r\n");
        return -1;
    } else {
        FIL test_file;
        fresult = f_open(&test_file, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
        if (fresult != FR_OK) {
            UART_Transmit_Messages_BlackBox("* SD Card not mounted. *\r\n");
            return -1;
        } else {
            f_close(&test_file);
            f_unlink("test.txt"); // Delete the test file
            UART_Transmit_Messages_BlackBox("* SD Card mounted successfully! *\r\n");
            return 0;
        }
    }
}




void check_free_space() {
    f_getfree("", &fre_clust, &pfs);

    total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    float total_GB = (float)total / (1024.0 * 1024.0);
    sprintf(data_buffer, "*              SD CARD Total Size: \t%.2f GB        *\r\n", total_GB);

    UART_Transmit_Messages_BlackBox(data_buffer);
    buf_clear();

    free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
    float free_space_GB = (float)free_space / (1024.0 * 1024.0);
    sprintf(data_buffer, "*              SD CARD Free Space: \t%.2f GB        *\r\n", free_space_GB);
    UART_Transmit_Messages_BlackBox(data_buffer);
	UART_Transmit_Messages_BlackBox("*********************************************************\r\n");
}






void create_file(const char* filename) {
    // Open file to write OR create it if it does not exist
    fresult = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
    char err[100];

    if (fresult == FR_OK) {
        UART_Transmit_Messages_BlackBox("File created successfully! \r\n");
        f_close(&fil);
    } else {
    	sprintf(err,"Error creating the file:  %d \r\n", fresult);
        UART_Transmit_Messages_BlackBox(err);
    }
}

void append_data_to_file(const char* filename, const char* data) {
    if (file_exists(filename)) {
        // Open file to append data at the end
        fresult = f_open(&fil, filename, FA_OPEN_APPEND | FA_READ | FA_WRITE);
    } else {
    	create_file(filename);
        // Open file to write OR create it if it does not exist
        fresult = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
    }

    if (fresult == FR_OK) {
        // Write data to the file
        UINT bytes_written;
        fresult = f_write(&fil, data, strlen(data), &bytes_written);

        if (fresult == FR_OK && bytes_written == strlen(data)) {
            //UART_Transmit_Messages_BlackBox("Data written to the file successfully! \r\n");
            // Synchronize file information with the disk
            f_sync(&fil);
        } else {
            if (fresult != FR_OK) {
                sprintf(data_buffer, "Error writing data to the file. Error code: %d \r\n", fresult);
                UART_Transmit_Messages_BlackBox(data_buffer);
            } else {
                sprintf(data_buffer, "Error: Incorrect number of bytes written. Expected: %d, Actual: %d \r\n",
                        strlen(data), bytes_written);
                UART_Transmit_Messages_BlackBox(data_buffer);
            }
        }

        // Close file
        f_close(&fil);
    } else {
        UART_Transmit_Messages_BlackBox("Error opening the file for writing. \r\n");
    }
}



void read_file(const char* filename) {
    // Open file to read
    fresult = f_open(&fil, filename, FA_OPEN_ALWAYS | FA_READ);

    if (fresult == FR_OK) {
        // Read string from the file
        f_read(&fil, data_buffer, sizeof(data_buffer) - 1, &br);

        // Null-terminate the data_buffer to treat it as a string
        data_buffer[br] = '\0';

        // Print the entire content of the file
        UART_Transmit_Messages_BlackBox("File content: \r\n");
        UART_Transmit_Messages_BlackBox(data_buffer);
        UART_Transmit_Messages_BlackBox("\r\n");

        // Close file
        f_close(&fil);
    } else {
        UART_Transmit_Messages_BlackBox("Error opening the file for reading. \r\n");
    }

    buf_clear();
}


void unmount_sd_card(){
	/* Unmount SDCARD */
	fresult = f_mount(NULL, "/", 1);
	if (fresult == FR_OK) UART_Transmit_Messages_BlackBox ("SD CARD UNMOUNTED successfully...\r\n");
}


