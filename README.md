# a-raft-transport

`a-raft-transport` is the strict binary codec and serialization layer for the `a-raft` consensus stack.

In hostile WAN environments, the codec is the first line of defense. This library translates in-memory `raft_msg_t` structs into tightly packed, Big-Endian binary frames, enforcing strict ceilings on network payloads to prevent Denial of Service (DoS) attacks.

## Key Features
* **Strict Payload Ceilings:** Enforces global boundaries (`RAFT_MAX_FRAME_SIZE`, `RAFT_CODEC_MAX_ENTRIES`) to prevent out-of-memory (OOM) attacks from malicious or malformed packets.
* **Zero-Padding Serialization:** Bit-packed frame headers ensure maximum network throughput.
* **Fail-Closed Decoding:** Invalid magic bytes, mismatched lengths, or trailing garbage instantly abort the decode sequence before memory is allocated.

## Usage
```c
size_t sz = raft_msg_encoded_size(&msg);
uint8_t* buf = malloc(sz);
raft_msg_encode(&msg, buf, sz);

// ... network transmission ...

raft_msg_t out;
if (raft_msg_decode(recv_buf, recv_len, &out)) {
    raft_step_remote(core, &out);
}
```
