#include <QByteArray>

class DLockPacket {

public:
	char const PEER_ANNOUNCE = 0x0;
	char const LOCK_REQUEST = 0x1;
	char const LOCK_RESPONSE = 0x2;
	char const LOCK_ANNOUNCE = 0x3;

	DLockPacket(char opcode, QByteArray data);
	QByteArray getPacket();

private:
	char version = 0x0;
	QByteArray packet;

};
