#include <QByteArray>

class DLockPacket {

public:
	enum Operation {
		PEER_ANNOUNCE = 0x0,
		LOCK_REQUEST  = 0x1,
		LOCK_RESPONSE = 0x2,
		LOCK_ANNOUNCE = 0x3
	};

	DLockPacket(char opcode, QByteArray data);
	DLockPacket setOpcode(char opcode, bool updateCrc = false);
	DLockPacket setData(QByteArray data, bool updateCrc = false);
	char getOpcode();
	QByteArray getData();
	QByteArray getPacket();
	void updateCrc();

private:
	char version = 0x0;
	char opcode;
	QByteArray data;
	QByteArray packet;

};
