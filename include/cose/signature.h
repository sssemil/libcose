/*
 * Copyright (C) 2018 Freie Universitat Berlin
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    cose_signature COSE signature defintions
 * @ingroup     cose
 * @{
 *
 * @file
 * @brief       API definitions for COSE signatures
 *
 * @author      Koen Zandberg <koen@bergzand.net>
 */

#ifndef COSE_SIGNATURE_H
#define COSE_SIGNATURE_H

#include "cose/conf.h"
#include "cose/hdr.h"
#include "cose/key.h"
#include <cbor.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Signature struct
 * @brief Contains signature and headers related to the signatures
 * @{
 */
typedef struct cose_signature {
    struct cose_signature *next;    /**< Next signature in list */
    cose_headers_t hdrs;            /**< Headers */
    const uint8_t *signature;       /**< Pointer to the signature */
    size_t signature_len;           /**< Length of the signature */
    const cose_key_t *signer;       /**< Pointer to the signer used for this signature */
} cose_signature_t;
/** @} */

static inline void cose_signature_init(cose_signature_t *signature)
{
    memset(signature, 0, sizeof(cose_signature_t));
}

size_t cose_signature_serialize_protected(const cose_signature_t *sig,
 bool encode, uint8_t *buf, size_t buflen);
bool cose_signature_unprot_to_map(cose_signature_t *sig,
 CborEncoder *map);
CborError cose_signature_unprot_cbor(cose_signature_t *sig,
        CborEncoder *enc);
bool cose_signature_decode(cose_signature_t *signature, CborValue *arr);
size_t cose_signature_num(cose_signature_t *signature);
/**
 * Get the key ID from a signature
 *
 * @param      sign     Sign struct to check
 * @param      idx      Signature slot to fetch
 * @param[out] kid      Filled with a pointer to the key ID
 *
 * @return              Size of the key ID
 * @return              0 in case of no key ID
 */
COSE_ssize_t cose_signature_get_kid(cose_signature_t *signature, const uint8_t **kid);

/**
 * Retrieve a header from a signature object by key lookup
 *
 * @param   signature   The signature object to operate on
 * @param   hdr         hdr struct to fill
 * @param   key         The key to look up
 *
 * @return              A header object with matching key
 * @return              NULL if there is no header with the key
 */
bool cose_signature_get_header(cose_signature_t *signature, cose_hdr_t *hdr, int32_t key);

/**
 * Retrieve a protected header from a signature object by key lookup
 *
 * @param   signature   The signature object to operate on
 * @param   hdr         hdr struct to fill
 * @param   key         The key to look up
 *
 * @return              A protected header object with matching key
 * @return              NULL if there is no header with the key
 */
bool cose_signature_get_protected(cose_signature_t *signature, cose_hdr_t *hdr, int32_t key);

/**
 * Retrieve an unprotected header from a signature object by key lookup
 *
 * @param   signature   The signature object to operate on
 * @param   hdr         hdr struct to fill
 * @param   key         The key to look up
 *
 * @return              A protected header object with matching key
 * @return              NULL if there is no header with the key
 */
bool cose_signature_get_unprotected(cose_signature_t *signature, cose_hdr_t *hdr, int32_t key);

/**
 * Add a header to a signatures protected bucket
 *
 * @note This function does not protect against setting duplicate keys
 *
 * @param   signature   The signature object to operate on
 * @param   hdr         The header to add
 *
 * @return              0 on success
 * @return              Negative when failed
 */
static inline void cose_signature_insert_prot(cose_signature_t *signature,
        cose_hdr_t *hdr)
{
    cose_hdr_insert(&signature->hdrs.prot.c, hdr);
}

/**
 * Add a header to a signatures unprotected bucket
 *
 * @note This function does not protect against setting duplicate keys
 *
 * @param   signature   The signature object to operate on
 * @param   hdr         The header to add
 *
 * @return              0 on success
 * @return              Negative when failed
 */
static inline void cose_signature_insert_unprot(cose_signature_t *signature,
        cose_hdr_t *hdr)
{
    cose_hdr_insert(&signature->hdrs.unprot.c, hdr);
}

#ifdef __cplusplus
}
#endif

#endif