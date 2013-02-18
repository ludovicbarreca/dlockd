# Dlock Protocol

## Introduction

This document describe the protocol used in dlock. Dlock could be
seen as a peer-to-peer lock system.

## Framing Protocol

  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-------+-------+-----------------------------------------------+
 |version| opcode|                    checksum                   |
 |  (4)  |  (4)  |                      (32)                     |
 |       |       |                                               |
 +-------+-------+ - - - - - - - - - - - - - - - - - - - - - - - +
 |    checksum   |
 |       ...     |                      data ...
 |      (32)     |
 +---------------+-------------------------------------------- ...

### Version: 4 bits

Defines the protocol version to use. Version should always be 0 for now.

### Opcode: 4 bits

Defines the interpretation of the packet. Endpoint must ignore if
opcode is unknown. Following are the defined values :

 * %x0 denotes a _peer announce_
 * %x1 denotes a _lock request_
 * %x2 denotes a _lock response_
 * %x3 denotes a _lock announce_
 * %x4-F are reserved for further opcodes

### Checksum: 4 bytes

When generating the checksum, this field must be set to 0 prior
generation. It must be generated for all packets sent using crc32
hash.

### Data: x bytes

Data to be sent along with the packet. Mandatory in some cases.

## Procedures

### Peer announce

Peer announce packet is sent to each known peer at launch. To
maintain accuracy inside the network, each node should renew its
announce every sixty seconds.

Each peer announce received must be transferred to all other peers
except to the emitter, and include source ip as data.

Example data payload:

 +--------------------+
 |   source ip:port   |
 |       (ascii)      |
 +--------------------+

A client should keep a record of known peers and withdraw any node
that has been unreachable for a twenty-four consecutive hours.

### Lock Request

Lock request data must contain the uuid the emitter wishes to lock.
Any request without correct uuid should be withdraw and ignored.

Example data payload:

 +-----------+
 |    UUID   |
 | 16 octets |
 +-----------+

A receiver will then check if a lock has already been requested for
this ressource, and will respond accordingly.

This lock request must be sent to every known peer and must no be
forwarded when received.

### Lock Response

After validation, a response packet is sent back to the emitter.
Data structure is as follow:

 +-----------+----------+
 |    UUID   | Response |
 | 16 octets | 1 octet  |
 +-----------+----------+

 * UUID is the system uuid and must complies with ISO 9834-8
 * Response is used to specify the state of the request

Response status are the following :

 * %x0 for a refusal
 * %x1 for a success
 * %x1-FF are reserved for later use

### Lock Announce

Lock annouce is sent to every peers whenever the emitter is able to
acquiere the lock for a given UUID. See "Lock Acquirement" section
below for details about how to be sure to get the lock.

Lock announce data must be formatted in accordance with the lock
response structure.

### Lock Acquierement

As as lock request is evaluated by the emitter itself, some strict
rules must be followed. Lock can only be considered acquiered when at
least half plus one of all the known peers approves the lock request.

Should a lock be refused, the emitting client should queue the
request and send it back after a reasonable amount of time, and may
send a lock announce containing a refusal.
