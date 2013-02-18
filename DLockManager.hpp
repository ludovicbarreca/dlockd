#include <QObject>
#include <QUdpSocket>

class DLockManager: public QObject {
	Q_OBJECT;

public:
	DLockManager(quint16 port);
	void initSocket();

public slots:
	void readPendingDatagrams();
	void terminate();

private:
	quint16 port;
	QUdpSocket udpSocket;
};

