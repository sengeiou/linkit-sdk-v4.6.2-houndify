/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#ifndef __CMUX_SETTING_H__
#define __CMUX_SETTING_H__

#define CMUX_CHANNEL_PRE_PN             KAL_TRUE

#define DEFAULT_N1                      512
#define CL_CL1                          0
#define CL_CL4                          3

#define DEFAULT_COMMAND_BUF_SIZE        1024
#define DEFAULT_COMMAND_HIGH_THRESHOLD  512
#define DEFAULT_COMMAND_N1              DEFAULT_N1
#define DEFAULT_COMMAND_CL              CL_CL1

#define DEFAULT_IPDATA_BUF_SIZE         2048
#define DEFAULT_IPDATA_HIGH_THRESHOLD   1024
#define DEFAULT_IPDATA_N1               DEFAULT_N1
#define DEFAULT_IPDATA_CL               CL_CL4

#endif /* __CMUX_SETTING_H__ */

/* CHANNEL_0 Settings */
CMUX_CH_BUFFER( CMUX_CONTROL_CHANNEL, 256,                      256,                      0, 192 )
CMUX_CH_CONFIG( 0,  CL_CL1,              0,  512)

/* CHANNEL_2 Settings */
CMUX_CH_BUFFER( CMUX_URC_CHANNEL,     DEFAULT_COMMAND_BUF_SIZE, DEFAULT_COMMAND_BUF_SIZE, 0, DEFAULT_COMMAND_HIGH_THRESHOLD )
CMUX_CH_CONFIG( 2,  DEFAULT_COMMAND_CL,  10, DEFAULT_COMMAND_N1)

/* CHANNEL_3 Settings */
CMUX_CH_BUFFER( CMUX_AT_CHANNEL,      DEFAULT_COMMAND_BUF_SIZE, DEFAULT_COMMAND_BUF_SIZE, 0, DEFAULT_COMMAND_HIGH_THRESHOLD )
CMUX_CH_CONFIG( 3,  DEFAULT_COMMAND_CL,  10, DEFAULT_COMMAND_N1)

/* CHANNEL_4 Settings */
CMUX_CH_BUFFER( CMUX_AT_CHANNEL,      DEFAULT_COMMAND_BUF_SIZE, DEFAULT_COMMAND_BUF_SIZE, 0, DEFAULT_COMMAND_HIGH_THRESHOLD )
CMUX_CH_CONFIG( 4,  DEFAULT_COMMAND_CL,  10, DEFAULT_COMMAND_N1)

/* CHANNEL_5 Settings */
CMUX_CH_BUFFER( CMUX_AT_CHANNEL,      DEFAULT_COMMAND_BUF_SIZE, DEFAULT_COMMAND_BUF_SIZE, 0, DEFAULT_COMMAND_HIGH_THRESHOLD )
CMUX_CH_CONFIG( 5,  DEFAULT_COMMAND_CL,  10, DEFAULT_COMMAND_N1)

/* CHANNEL_6 Settings */
#ifdef __CMUX_CL4_SUPPORT__
CMUX_CH_BUFFER( CMUX_IP_CHANNEL,      DEFAULT_IPDATA_BUF_SIZE,  DEFAULT_IPDATA_BUF_SIZE,  0, DEFAULT_IPDATA_HIGH_THRESHOLD )
CMUX_CH_CONFIG( 6,  DEFAULT_IPDATA_CL,   30, DEFAULT_IPDATA_N1)
#endif

