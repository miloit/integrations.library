/******************************************************************************
 *
 * Copyright (C) 2019 Christian Riedl <ric@rts.co.at>
 *
 * This file is part of the YIO-Remote software project.
 *
 * YIO-Remote software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * YIO-Remote software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with YIO-Remote software. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *****************************************************************************/

#include "yio-plugin/integration.h"

// FIXME redo Integration implementation once the project is cleary separated from remote-software
// and the common headers are working!
/*
Integration::Integration(const QVariantMap& config, QObject *entities, QObject *notifications, QObject* api,
 QObject *configObj, Plugin* parent) :
    QObject(parent),
    m_state(DISCONNECTED),
    m_log(parent->m_logCategory) {
    for (QVariantMap::const_iterator iter = config.begin(); iter != config.end(); ++iter) {
        if (iter.key() == "friendly_name")
            m_friendlyName = iter.value().toString();
        else if (iter.key() == "id")
            m_integrationId =  iter.value().toString();
    }
    m_entities = qobject_cast<EntitiesInterface*>(entities);
    m_notifications = qobject_cast<NotificationsInterface *>(notifications);
    m_yioapi = qobject_cast<YioAPIInterface *>(api);
    m_config = qobject_cast<ConfigInterface *>(configObj);
}

// Used for proxy
Integration::Integration (Plugin* parent) :
    QObject(parent),
    m_state(DISCONNECTED),
    m_entities(nullptr),
    m_notifications(nullptr),
    m_yioapi(nullptr),
    m_config(nullptr),
    m_log(parent->m_logCategory)
{}
*/
