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

/*
** $Id: //Department/DaVinci/TRUNK/MT6620_5931_WiFi_Driver/include/mgmt/assoc.h#2 $
*/

/*! \file  assoc.h
    \brief This file contains the ASSOC REQ/RESP of
           IEEE 802.11 family for MediaTek 802.11 Wireless LAN Adapters.
*/




#ifndef _ASSOC_H
#define _ASSOC_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                         D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/* Routines in assoc.c                                                        */
/*----------------------------------------------------------------------------*/
WLAN_STATUS
assocSendReAssocReqFrame(
    IN P_ADAPTER_T prAdapter,
    IN P_STA_RECORD_T prStaRec
);

WLAN_STATUS
assocCheckTxReAssocReqFrame(
    IN P_ADAPTER_T      prAdapter,
    IN P_MSDU_INFO_T    prMsduInfo
);

WLAN_STATUS
assocCheckTxReAssocRespFrame(
    IN P_ADAPTER_T prAdapter,
    IN P_MSDU_INFO_T prMsduInfo
);

WLAN_STATUS
assocCheckRxReAssocRspFrameStatus(
    IN P_ADAPTER_T  prAdapter,
    IN P_SW_RFB_T   prSwRfb,
    OUT PUINT_16    pu2StatusCode
);

WLAN_STATUS
assocSendDisAssocFrame(
    IN P_ADAPTER_T    prAdapter,
    IN P_STA_RECORD_T prStaRec,
    IN UINT_16        u2ReasonCode
);

WLAN_STATUS
assocProcessRxDisassocFrame(
    IN P_ADAPTER_T  prAdapter,
    IN P_SW_RFB_T prSwRfb,
    IN UINT_8 aucBSSID[],
    OUT PUINT_16 pu2ReasonCode
);

WLAN_STATUS
assocProcessRxAssocReqFrame(
    IN P_ADAPTER_T  prAdapter,
    IN P_SW_RFB_T prSwRfb,
    OUT PUINT_16 pu2StatusCode
);

WLAN_STATUS
assocSendReAssocRespFrame(
    IN P_ADAPTER_T      prAdapter,
    IN P_STA_RECORD_T   prStaRec
);

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _ASSOC_H */

