/*
 * Copyright (C) 2018 Freie Universitat Berlin
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    cose_encrypt COSE encrypt defintions
 * @ingroup     cose
 * constants for encryption
 * @{
 *
 * @file
 * @brief       API definitions for COSE encryption objects
 *
 * @author      Koen Zandberg <koen@bergzand.net>
 */

#ifndef COSE_RECIPIENT_H
#define COSE_RECIPIENT_H

#include "cose_defines.h"
#include "cose/hdr.h"
#include "cose/key.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name COSE recipient struct definition
 */
typedef struct cose_recp {
    struct cose_recp *parent;           /**< Parent recipient structure */
    const cose_key_t *key;              /**< Pointer to the key structure used */
    const uint8_t *skey;                /**< Secret key used */
    size_t key_len;                     /**< Length of the secret key */
    cose_headers_t hdrs;                /**< Headers included with this recipient */
} cose_recp_t;

/**
 * @name COSE recipient decoding struct
 */
typedef struct cose_recp_dec {
    const uint8_t *buf;     /**< Buffer containing the full recipient data */
    size_t len;             /**< Length of the recipient data */
} cose_recp_dec_t;

int cose_recp_encrypt_to_map(cose_recp_t *recps, size_t num_recps,
                                  const uint8_t *cek, size_t ceklen,
                                  nanocbor_encoder_t *enc);

/**
 * @brief Initialize a recipient decoding context from a buffer
 *
 * @param   recp    Recipient context to initialize
 * @param   buf     Buffer to initialize from
 * @param   len     Length of the buffer
 */
void cose_recp_decode_init(cose_recp_dec_t *recp, const uint8_t *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
