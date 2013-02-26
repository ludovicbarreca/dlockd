#include "DLockPacket.hpp"

DLockPacket::DLockPacket(char opcode, QByteArray data) {
	this->setOpcode(opcode);
	this->setData(data);

	// 2 nibbles = 1 byte :)
	char flags = (version & 0xf) << 4 | (opcode & 0xf);
	packet.append(flags);

	// setting crc16 field to zero
	quint8 empty = 0x00;
	packet.append(empty);
	packet.append(empty);
	packet.append(data);
	this->updateCrc();
}

DLockPacket DLockPacket::setOpcode(char opcode, bool updateCrc) {
	this->opcode = opcode;
	char flags = (version & 0xf) << 4 | (opcode & 0xf);
	packet.replace(0, 1, &flags, 1);

	if (updateCrc == true) {
		this->updateCrc();
	}

	return *this;
}

DLockPacket DLockPacket::setData(QByteArray data, bool updateCrc) {
	this->data = data;
	packet.replace(3, data.length(), data.constData());

	if (updateCrc == true) {
		this->updateCrc();
	}

	return *this;
}

char DLockPacket::getOpcode() {
	return this->opcode;
}

QByteArray DLockPacket::getData() {
	return this->data;
}

void DLockPacket::updateCrc() {
	// setting back to 0 first
	char empty = 0x00;
	packet.replace(1, 1, &empty, 1);
	packet.replace(2, 1, &empty, 1);
	// then generating the crc
	quint16 crc = qChecksum(packet.constData(), packet.length());
	char low = crc;
	char high = (crc >> 8) & 0xff;
	// finally updating it
	packet.replace(1, 1, &high, 1);
	packet.replace(2, 1, &low, 1);
}

QByteArray DLockPacket::getPacket() {
	return packet;
}
