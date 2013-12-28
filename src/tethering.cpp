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

#include "tethering.h"

Tethering::Tethering(QObject *parent) : QObject(parent) {
    manager = new NetworkManager(this);
    counter = new Counter(this);
    connect(counter, SIGNAL(bytesReceivedChanged(quint32)), this, SLOT(updateBytesReceived(quint32)));
    connect(counter, SIGNAL(bytesTransmittedChanged(quint32)), this, SLOT(updateBytesTransmitted(quint32)));
    connect(counter, SIGNAL(secondsOnlineChanged(quint32)), this, SLOT(updateSecondsOnline(quint32)));
}

void Tethering::disable_tethering() {
    // Get the wifi technology
    NetworkTechnology* wifi = manager->getTechnology("wifi");

    if (wifi == 0) {
        std::cout << "Cannot find wifi!" << std::endl;
        return;
    }

    // Disable tethering
    wifi->setTethering(false);
    // Stop counter
    counter->setRunning(false);

    std::cout << "Disabled tethering" << std::endl;
}

void Tethering::enable_tethering(QString ssid, QString passwd) {
    // Get the wifi technology
    NetworkTechnology* wifi = manager->getTechnology("wifi");

    if (wifi == 0) {
        std::cout << "Cannot find wifi!" << std::endl;
        return;
    }

    // Enable tethering with given ssid and passwd
    wifi->setTetheringId(ssid);
    wifi->setTetheringPassphrase(passwd);
    wifi->setTethering(true);

    // Initialize and start counter
    received = transmitted = seconds = 0;
    initial_received = counter->bytesReceived();
    initial_transmitted = counter->bytesTransmitted();
    initial_seconds = counter->secondsOnline();
    counter->setRunning(true);

    std::cout << "Enabled tethering" << std::endl;
    std::cout << ssid.toStdString() << ":" << passwd.toStdString() << std::endl;
}

quint32 Tethering::bytesReceived() const
{
    return received;
}

quint32 Tethering::bytesTransmitted() const
{
    return transmitted;
}

quint32 Tethering::secondsOnline() const
{
    return seconds;
}

void Tethering::updateBytesReceived(quint32 bytes)
{
    received = bytes - initial_received;
    emit bytesReceivedChanged(received);
}

void Tethering::updateBytesTransmitted(quint32 bytes)
{
    transmitted = bytes - initial_transmitted;
    emit bytesTransmittedChanged(transmitted);
}

void Tethering::updateSecondsOnline(quint32 secs)
{
    seconds = secs - initial_seconds;
    emit secondsOnlineChanged(seconds);
}
