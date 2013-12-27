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

import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    CoverActionList {
        id: coverActions

        CoverAction {
            iconSource: app.hotspot_enabled ? "image://theme/icon-cover-pause" : "image://theme/icon-cover-play"
            onTriggered: app.toggleHotspot()
        }
    }

    Label {
        id: label
        anchors.centerIn: parent
        text: "Hotspot: " + (app.hotspot_enabled ? "Enabled" : "Disabled") + "<br>tx: " + counter.bytesTransmitted + "<br>rx: " + counter.bytesReceived
    }
}


