#include <QMetaObject>
#include <QCoreApplication>
#include <QHostAddress>

#include "DLockManager.hpp"

DLockManager::DLockManager(quint16 _port) {
	port = _port;
}

void DLockManager::initSocket() {
	udpSocket.bind(port);
	qDebug("Server listening!");

	connect(&udpSocket, SIGNAL(readyRead()),
		this, SLOT(readPendingDatagrams()));
}

void DLockManager::readPendingDatagrams() {
	while (udpSocket.hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket.pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		udpSocket.readDatagram(datagram.data(), datagram.size(),
			&sender, &senderPort);

		//parse(datagram);
	}
}

void DLockManager::terminate() {
	qDebug("Exiting cleanly");
	QCoreApplication::quit();
}
