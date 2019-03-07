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

#ifndef DRIVER_H
#define DRIVER_H

#define WPA_SUPPLICANT_DRIVER_VERSION 2

typedef enum { WPA_ALG_NONE, WPA_ALG_WEP, WPA_ALG_TKIP, WPA_ALG_CCMP } wpa_alg;
typedef enum { CIPHER_NONE, CIPHER_WEP40, CIPHER_TKIP, CIPHER_CCMP,
               CIPHER_WEP104
#if 1 //#ifdef __WAPI_SUPPORT__
, CIPHER_SMS4
#endif
             } wpa_cipher;
typedef enum { KEY_MGMT_802_1X, KEY_MGMT_PSK, KEY_MGMT_NONE,
               KEY_MGMT_802_1X_NO_WPA, KEY_MGMT_WPA_NONE
#if 1 //#ifdef __WAPI_SUPPORT__
, KEY_MGMT_WAPI_PSK, KEY_MGMT_WAPI_WAI
#endif
#if 1  //#ifdef __WPS_SUPPORT__
, KEY_MGMT_WPS_OPEN, KEY_MGMT_WPS_WPA, KEY_MGMT_WPS_WPA2
#endif
             } wpa_key_mgmt;

#define AUTH_ALG_OPEN_SYSTEM    0x01
#define AUTH_ALG_SHARED_KEY 0x02
#define AUTH_ALG_LEAP       0x04
/*
#define IEEE80211_MODE_INFRA    0
#define IEEE80211_MODE_IBSS 1
*/
#define SSID_MAX_WPA_IE_LEN 40
typedef struct wpa_scan_result {
    u8 bssid[ETH_ALEN];
    u8 ssid[32];
    wpa_size_t ssid_len;
    u8 wpa_ie[SSID_MAX_WPA_IE_LEN];
    wpa_size_t wpa_ie_len;
    u8 rsn_ie[SSID_MAX_WPA_IE_LEN];
    wpa_size_t rsn_ie_len;
    int freq; /* MHz */
    int caps; /* e.g. privacy */
    int qual; /* signal quality */
    int noise;
    int level;
    int maxrate;
} wpa_scan_result;

/* Parameters for associate driver_ops. */
struct wpa_driver_associate_params {
    /* BSSID of the selected AP */
    const u8 *bssid;

    /* The selected SSID and its length in bytes */
    const u8 *ssid;
    wpa_size_t ssid_len;
    kal_uint32 channel_number;

    /* frequency that the selected AP is using (in MHz as
     * reported in the scan results) */
    int freq;

    /* WPA information element to be included in (Re)Association
     * Request (including information element id and length). Use
     * of this WPA IE is optional. If the driver generates the WPA
     * IE, it can use @pairwise_suite, @group_suite, and
     * @key_mgmt_suite to select proper algorithms. In this case,
     * the driver has to notify wpa_supplicant about the used WPA
     * IE by generating an event that the interface code will
     * convert into EVENT_ASSOCINFO data (see wpa_supplicant.h).
     * When using WPA2/IEEE 802.11i, @wpa_ie is used for RSN IE
     * instead. The driver can determine which version is used by
     * looking at the first byte of the IE (0xdd for WPA, 0x30 for
     * WPA2/RSN). @wpa_ie_len: length of the @wpa_ie */
    const u8 *wpa_ie;
    wpa_size_t wpa_ie_len;

    /* The selected pairwise/group cipher and key management
     * suites. These are usually ignored if @wpa_ie is used. */
    wpa_cipher pairwise_suite;
    wpa_cipher group_suite;
    wpa_key_mgmt key_mgmt_suite;

    int auth_alg; /* bit field of AUTH_ALG_* */
    int mode; /* IEEE80211_MODE_* */
    kal_uint8 wep_enabled;
    wndrv_wep_info_struct wep_info[4];
};

struct wpa_driver_capa {
#define WPA_DRIVER_CAPA_KEY_MGMT_WPA        0x00000001
#define WPA_DRIVER_CAPA_KEY_MGMT_WPA2       0x00000002
#define WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK    0x00000004
#define WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK   0x00000008
#define WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE   0x00000010
    unsigned int key_mgmt;

#define WPA_DRIVER_CAPA_ENC_WEP40   0x00000001
#define WPA_DRIVER_CAPA_ENC_WEP104  0x00000002
#define WPA_DRIVER_CAPA_ENC_TKIP    0x00000004
#define WPA_DRIVER_CAPA_ENC_CCMP    0x00000008
    unsigned int enc;

#define WPA_DRIVER_AUTH_OPEN        0x00000001
#define WPA_DRIVER_AUTH_SHARED      0x00000002
#define WPA_DRIVER_AUTH_LEAP        0x00000004
    unsigned int auth;

    /* Driver generated WPA/RSN IE */
#define WPA_DRIVER_FLAGS_DRIVER_IE  0x00000001
#define WPA_DRIVER_FLAGS_SET_KEYS_AFTER_ASSOC 0x00000002
    unsigned int flags;
};


struct wpa_driver_ops {
    /* name of the driver interface */
    const char *name;
    /* one line description of the driver interface */
    const char *desc;

    /**
     * get_bssid - get the current BSSID
     * @priv: private driver interface data
     * @bssid: buffer for BSSID (ETH_ALEN = 6 bytes)
     *
     * Returns: 0 on success, -1 on failure
     *
     * Query kernel driver for the current BSSID and copy it to @bssid.
     * Setting @bssid to 00:00:00:00:00:00 is recommended if the STA is not
     * associated.
     */
    int (*get_bssid)(void *priv, u8 *bssid);

    /**
     * get_ssid - get the current SSID
     * @priv: private driver interface data
     * @ssid: buffer for SSID (at least 32 bytes)
     *
     * Returns: length of the SSID on success, -1 on failure
     *
     * Query kernel driver for the current SSID and copy it to @ssid.
     * Returning zero is recommended if the STA is not associated.
     *
     * Note: SSID is an array of octets, i.e., it is not nul terminated and
     * can, at least in theory, contain control characters (including nul)
     * and as such, should be processed as binary data, not a printable
     * string.
     */
    int (*get_ssid)(void *priv, u8 *ssid);

    /**
     * set_wpa - enable/disable WPA support
     * @priv: private driver interface data
     * @enabled: 1 = enable, 0 = disable
     *
     * Returns: 0 on success, -1 on failure
     *
     * Configure the kernel driver to enable/disable WPA support. This may
     * be empty function, if WPA support is always enabled. Common
     * configuration items are WPA IE (clearing it when WPA support is
     * disabled), Privacy flag for capability field, roaming mode (need to
     * allow wpa_supplicant to control roaming).
     */
    int (*set_wpa)(void *priv, int enabled);

    /**
     * set_key - configure encryption key
     * @priv: private driver interface data
     * @alg: encryption algorithm (%WPA_ALG_NONE, %WPA_ALG_WEP,
     *  %WPA_ALG_TKIP, %WPA_ALG_CCMP); %WPA_ALG_NONE clears the key.
     * @addr: address of the peer STA or ff:ff:ff:ff:ff:ff for
     *  broadcast/default keys
     * @key_idx: key index (0..3), always 0 for unicast keys
     * @set_tx: configure this key as the default Tx key (only used when
     *  driver does not support separate unicast/individual key
     * @seq: sequence number/packet number, @seq_len octets, the next
     *  packet number to be used for in replay protection; configured
     *  for Rx keys (in most cases, this is only used with broadcast
     *  keys and set to zero for unicast keys)
     * @seq_len: length of the @seq, depends on the algorithm:
     *  TKIP: 6 octets, CCMP: 6 octets
     * @key: key buffer; TKIP: 16-byte temporal key, 8-byte Tx Mic key,
     *  8-byte Rx Mic Key
     * @key_len: length of the key buffer in octets (WEP: 5 or 13,
     *  TKIP: 32, CCMP: 16)
     *
     * Returns: 0 on success, -1 on failure
     *
     * Configure the given key for the kernel driver. If the driver
     * supports separate individual keys (4 default keys + 1 individual),
     * @addr can be used to determine whether the key is default or
     * individual. If only 4 keys are supported, the default key with key
     * index 0 is used as the individual key. STA must be configured to use
     * it as the default Tx key (@set_tx is set) and accept Rx for all the
     * key indexes. In most cases, WPA uses only key indexes 1 and 2 for
     * broadcast keys, so key index 0 is available for this kind of
     * configuration.
     */
    int (*set_key)(void *priv, wpa_alg alg, const u8 *addr,
                   int key_idx, int set_tx, const u8 *seq, wpa_size_t seq_len,
                   const u8 *key, wpa_size_t key_len);

    /**
     * init - initialize driver interface
     * @ctx: context to be used when calling wpa_supplicant functions,
     * e.g., wpa_supplicant_event()
     * @ifname: interface name, e.g., wlan0
     *
     * Return: pointer to private data, %NULL on failure
     *
     * Initialize driver interface, including event processing for kernel
     * driver events (e.g., associated, scan results, Michael MIC failure).
     * This function can allocate a private configuration data area for
     * @ctx, file descriptor, interface name, etc. information that may be
     * needed in future driver operations. If this is not used, non-NULL
     * value will need to be returned because %NULL is used to indicate
     * failure. The returned value will be used as 'void *priv' data for
     * all other driver_ops functions.
     *
     * The main event loop (eloop.c) of wpa_supplicant can be used to
     * register callback for read sockets (eloop_register_read_sock()).
     *
     * See wpa_supplicant.h for more information about events and
     * wpa_supplicant_event() function.
     */
    void *(*init)(void *ctx, const char *ifname);

    /**
     * deinit - deinitialize driver interface
     * @priv: pointer to private data (from matching
     *  wpa_driver_events_init())
     *
     * Shut down driver interface and processing of driver events. Free
     * private data buffer if one was allocated in init() handler.
     */
    void (*deinit)(void *priv);

    /**
     * set_countermeasures - enable/disable TKIP countermeasures
     * @priv: private driver interface data
     * @enabled: 1 = countermeasures enabled, 0 = disabled
     *
     * Return: 0 on success, -1 on failure
     *
     * Configure TKIP countermeasures. When these are enabled, the driver
     * should drop all received and queued frames that are using TKIP.
     */
    int (*set_countermeasures)(void *priv, int enabled);

    /**
     * set_drop_unencrypted - enable/disable unencrypted frame filtering
     * @priv: private driver interface data
     * @enabled: 1 = unencrypted Tx/Rx frames will be dropped, 0 = disabled
     *
     * Return: 0 on success, -1 on failure
     *
     * Configure the driver to drop all non-EAPOL frames (both receive and
     * transmit paths). Unencrypted EAPOL frames (ethertype 0x888e) must
     * still be allowed for key negotiation.
     */
    int (*set_drop_unencrypted)(void *priv, int enabled);

    /**
     * scan - request the driver to initiate scan
     * @priv: private driver interface data
     * @ssid: specific SSID to scan for (ProbeReq) or %NULL to scan for
     *  all SSIDs (either active scan with broadcast SSID or passive
     *  scan
     * @ssid_len: length of the SSID
     *
     * Return: 0 on success, -1 on failure
     *
     * Once the scan results are ready, the driver should report scan
     * results event for wpa_supplicant which will eventually request the
     * results with wpa_driver_get_scan_results().
     */
    int (*scan)(void *priv, const u8 *ssid, wpa_size_t ssid_len);

    /**
     * get_scan_results - fetch the latest scan results
     * @priv: private driver interface data
     * @results: pointer to buffer for scan results
     * @max_size: maximum number of entries (buffer size)
     *
     * Return: number of scan result entries used on success, -1 on failure
     *
     * If scan results include more than @max_size BSSes, @max_size will be
     * returned and the remaining entries will not be included in the
     * buffer.
     */
    int (*get_scan_results)(void *priv,
                            struct wpa_scan_result *results,
                            wpa_size_t max_size);

    /**
     * deauthenticate - request driver to deauthenticate
     * @priv: private driver interface data
     * @addr: peer address (BSSID of the AP)
     * @reason_code: 16-bit reason code to be sent in the deauthentication
     *  frame
     *
     * Return: 0 on success, -1 on failure
     */
    int (*deauthenticate)(void *priv, const u8 *addr, int reason_code);

    /**
     * disassociate - request driver to disassociate
     * @priv: private driver interface data
     * @addr: peer address (BSSID of the AP)
     * @reason_code: 16-bit reason code to be sent in the disassociation
     *  frame
     *
     * Return: 0 on success, -1 on failure
     */
    int (*disassociate)(void *priv, const u8 *addr, int reason_code);

    /**
     * associate - request driver to associate
     * @priv: private driver interface data
     * @params: association parameters
     *
     * Return: 0 on success, -1 on failure
     */
    int (*associate)(void *priv,
                     struct wpa_driver_associate_params *params);

    /**
     * set_auth_alg - set IEEE 802.11 authentication algorithm
     * @priv: private driver interface data
     * @auth_alg: bit field of AUTH_ALG_*
     *
     * If the driver supports more than one authentication algorithm at the
     * same time, it should configure all supported algorithms. If not, one
     * algorithm needs to be selected arbitrarily. Open System
     * authentication should be ok for most cases and it is recommended to
     * be used if other options are not supported. Static WEP configuration
     * may also use Shared Key authentication and LEAP requires its own
     * algorithm number. For LEAP, user can make sure that only one
     * algorithm is used at a time by configuring LEAP as the only
     * supported EAP method. This information is also available in
     * associate() params, so set_auth_alg may not be needed in case of
     * most drivers.
     *
     * Return: 0 on success, -1 on failure
     */
    int (*set_auth_alg)(void *priv, int auth_alg);

    /**
     * add_pmkid - add PMKSA cache entry to the driver
     * @priv: private driver interface data
     * @bssid: BSSID for the PMKSA cache entry
     * @pmkid: PMKID for the PMKSA cache entry
     *
     * Return: 0 on success, -1 on failure
     *
     * This function is called when a new PMK is received, as a result of
     * either normal authentication or RSN pre-authentication.
     *
     * If the driver generates RSN IE, i.e., it does not use @wpa_ie in
     * associate(), add_pmkid() can be used to add new PMKSA cache entries
     * in the driver. If the driver uses @wpa_ie from wpa_supplicant, this
     * driver_ops function does not need to be implemented. Likewise, if
     * the driver does not support WPA, this function is not needed.
     */
    int (*add_pmkid)(void *priv, const u8 *bssid, const u8 *pmkid);

    /**
     * remove_pmkid - remove PMKSA cache entry to the driver
     * @priv: private driver interface data
     * @bssid: BSSID for the PMKSA cache entry
     * @pmkid: PMKID for the PMKSA cache entry
     *
     * Return: 0 on success, -1 on failure
     *
     * This function is called when the supplicant drops a PMKSA cache
     * entry for any reason.
     *
     * If the driver generates RSN IE, i.e., it does not use @wpa_ie in
     * associate(), remove_pmkid() can be used to synchronize PMKSA caches
     * between the driver and wpa_supplicant. If the driver uses @wpa_ie
     * from wpa_supplicant, this driver_ops function does not need to be
     * implemented. Likewise, if the driver does not support WPA, this
     * function is not needed.
     */
    int (*remove_pmkid)(void *priv, const u8 *bssid, const u8 *pmkid);

    /**
     * flush_pmkid - flush PMKSA cache
     * @priv: private driver interface data
     *
     * Return: 0 on success, -1 on failure
     *
     * This function is called when the supplicant drops all PMKSA cache
     * entries for any reason.
     *
     * If the driver generates RSN IE, i.e., it does not use @wpa_ie in
     * associate(), remove_pmkid() can be used to synchronize PMKSA caches
     * between the driver and wpa_supplicant. If the driver uses @wpa_ie
     * from wpa_supplicant, this driver_ops function does not need to be
     * implemented. Likewise, if the driver does not support WPA, this
     * function is not needed.
     */
    int (*flush_pmkid)(void *priv);

    /**
     * flush_pmkid - flush PMKSA cache
     * @priv: private driver interface data
     *
     * Return: 0 on success, -1 on failure
     *
     * Get driver/firmware/hardware capabilities.
     */
    int (*get_capa)(void *priv, struct wpa_driver_capa *capa);

    /**
     * poll - poll driver for association information
     * @priv: private driver interface data
     *
     * This is an option callback that can be used when the driver does not
     * provide event mechanism for association events. This is called when
     * receiving WPA EAPOL-Key messages that require association
     * information. The driver interface is supposed to generate associnfo
     * event before returning from this callback function. In addition, the
     * driver interface should generate an association event after having
     * sent out associnfo.
     */
    void (*poll)(void *priv);

    /**
     * get_ifname - get interface name
     *
     * This optional function can be used to allow the driver interface to
     * replace the interface name with something else, e.g., based on an
     * interface mapping from a more descriptive name.
     *
     * Returns a pointer to the interface name. This can differ from the
     * interface name used in init() call.
     */
    const char *(*get_ifname)(void *priv);

    /**
     * get_mac_addr - get own MAC address
     *
     * This optional function can be used to get the own MAC address of the
     * device from the driver interface code. This is only needed if the
     * l2_packet implementation for the OS does not provide easy access to
     * a MAC address. */
    const u8 *(*get_mac_addr)(void *priv);
};

#endif /* DRIVER_H */
