#include "DLockPacket.hpp"

DLockPacket::DLockPacket(char opcode, QByteArray data) {
	char flags = (version & 0xf) << 4 | (opcode & 0xf);
	packet.append(flags);

	// setting crc16 field to zero
	quint8 empty = 0x00;
	packet.append(empty);
	packet.append(empty);
	packet.append(data);

	// generating the checksum and replacing the empty crc16 field
	quint16 crc = qChecksum(packet.constData(), packet.length());
	char low = crc;
	char high = (crc >> 8) & 0xff;
	packet.replace(1, 1, &high, 1);
	packet.replace(2, 1, &low, 1);
}

QByteArray DLockPacket::getPacket() {
	return packet.toHex();
}
