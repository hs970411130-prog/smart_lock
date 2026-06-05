/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "timers.h"
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum {
    AUTH_METHOD_NONE = 0,
    AUTH_METHOD_FINGERPRINT = 1,
    AUTH_METHOD_RFID = 2,
    AUTH_METHOD_PASSWORD = 3,
    AUTH_METHOD_OTP = 4,
    AUTH_METHOD_ADMIN = 5,
} auth_method_t;

typedef struct {
    auth_method_t method;
    union {
        uint16_t fingerprint_id;
        uint8_t  rfid_uid[4];
        char     password[16];
        char     otp_code[8];
    } credential;
    uint32_t timestamp_ms;
} auth_request_t;

typedef enum {
    AUTH_SUCCESS = 0,
    AUTH_FAIL_WRONG = 1,
    AUTH_FAIL_LOCKOUT = 2,
    AUTH_FAIL_NOT_FOUND = 3,
    AUTH_FAIL_TIMEOUT = 4,
} auth_result_t;

typedef enum {
    ROLE_GUEST = 0,
    ROLE_USER = 1,
    ROLE_ADMIN = 2,
} user_role_t;

typedef struct {
    uint32_t    id;
    char        name[16];
    uint8_t     rfid_uid[4];
    char        password_hash[32];
    uint8_t     fingerprint_ids[5];
    uint8_t     fp_count;
    user_role_t role;
    uint32_t    created_time;
    uint32_t    expire_time;
    uint8_t     enabled;
} user_record_t;

typedef enum {
    LOG_LOCK_OPEN = 0,
    LOG_LOCK_CLOSE = 1,
    LOG_AUTH_FAIL = 2,
    LOG_SYSTEM_LOCKOUT = 3,
    LOG_ADMIN_CONFIG = 4,
    LOG_WIFI_CONNECT = 5,
    LOG_WIFI_REMOTE = 6,
    LOG_SYSTEM_BOOT = 7,
} log_type_t;

typedef struct {
    log_type_t  type;
    uint32_t    timestamp;
    uint32_t    user_id;
    auth_method_t method;
    char        detail[32];
} log_entry_t;

typedef enum {
    STATE_IDLE,
    STATE_WAITING_AUTH,
    STATE_AUTHENTICATING,
    STATE_UNLOCKED,
    STATE_LOCKED_OUT,
    STATE_ADMIN_MODE,
    STATE_ERROR,
} system_state_t;

typedef enum {
    PAGE_HOME,
    PAGE_AUTH_RESULT,
    PAGE_SETTINGS,
    PAGE_LOG_VIEW,
} display_page_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
