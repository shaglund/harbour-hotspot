/*
    WiFi Hotspot - use your Sailfish device to create a WiFi hotspot
    Copyright (C) 2013 Sami Remes <sami.remes@gmail.com>.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TETHERING_H
#define TETHERING_H

#include<QString>
#include<QObject>
#include <QtCore/QPointer>

#include<iostream>

#include<connman-qt5/networkmanager.h>
#include<connman-qt5/networktechnology.h>
#include<connman-qt5/counter.h>

class Tethering : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32 bytesReceived READ bytesReceived NOTIFY bytesReceivedChanged)
    Q_PROPERTY(quint32 bytesTransmitted READ bytesTransmitted NOTIFY bytesTransmittedChanged)
    Q_PROPERTY(quint32 secondsOnline READ secondsOnline NOTIFY secondsOnlineChanged)

public:
    explicit Tethering(QObject* parent = 0);

    Q_INVOKABLE void enable_tethering(QString ssid, QString passwd);
    Q_INVOKABLE void disable_tethering();

    quint32 bytesReceived() const;
    quint32 bytesTransmitted() const;
    quint32 secondsOnline() const;

private:
    QPointer<NetworkManager> manager;
    QPointer<Counter> counter;
    quint32 received, initial_received;
    quint32 transmitted, initial_transmitted;
    quint32 seconds, initial_seconds;

signals:
    void bytesReceivedChanged(quint32 bytesRx);
    void bytesTransmittedChanged(quint32 bytesTx);
    void secondsOnlineChanged(quint32 seconds);

private slots:
    void updateBytesReceived(quint32 bytes);
    void updateBytesTransmitted(quint32 bytes);
    void updateSecondsOnline(quint32 secs);
};

#endif // TETHERING_H
