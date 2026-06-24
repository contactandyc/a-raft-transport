// SPDX-FileCopyrightText: 2026 Andy Curtis <contactandyc@gmail.com>
// SPDX-License-Identifier: Apache-2.0
//
// Maintainer: Andy Curtis <contactandyc@gmail.com>

#ifndef RAFT_CODEC_H
#define RAFT_CODEC_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Must include core types to know what we are serializing
#include "a-raft-core/raft.h"

// Global network limit: 10 MB maximum frame size
#define RAFT_MAX_FRAME_SIZE (1024 * 1024 * 10)

#ifdef __cplusplus
extern "C" {
#endif

// Safe Serialization API
size_t raft_msg_encoded_size(const raft_msg_t* msg);
bool   raft_msg_encoded_size_checked(const raft_msg_t* msg, size_t* out);

bool   raft_msg_encode(const raft_msg_t* msg, uint8_t* buf, size_t cap);
bool   raft_msg_decode(const uint8_t* buf, size_t len, raft_msg_t* out_msg);

void   raft_msg_free_payloads(raft_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif // RAFT_CODEC_H
