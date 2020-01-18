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

#include "integration.h"

const QString Integration::KEY_ID = CFG_KEY_ID;
const QString Integration::KEY_FRIENDLYNAME = CFG_KEY_FRIENDLYNAME;
const QString Integration::KEY_ENTITY_ID = CFG_KEY_ENTITY_ID;
const QString Integration::KEY_AREA = CFG_KEY_AREA;
const QString Integration::KEY_INTEGRATION = CFG_KEY_INTEGRATION;
const QString Integration::KEY_SUPPORTED_FEATURES = CFG_KEY_SUPPORTED_FEATURES;
const QString Integration::KEY_TYPE = CFG_KEY_TYPE;
const QString Integration::KEY_MDNS = CFG_KEY_MDNS;
const QString Integration::KEY_WORKERTHREAD = CFG_KEY_WORKERTHREAD;
const QString Integration::OBJ_DATA = CFG_OBJ_DATA;

Integration::Integration(const QVariantMap& config, EntitiesInterface* entities, NotificationsInterface* notifications,
                         YioAPIInterface* api, ConfigInterface* configObj, Plugin* plugin)
    : QObject(plugin),
      m_state(DISCONNECTED),
      m_entities(entities),
      m_notifications(notifications),
      m_yioapi(api),
      m_config(configObj),
      m_logCategory(plugin->m_logCategory) {

    // FIXME remove QVariantMap indirection for friendlyName and integrationId:
    //       plugins MUST set them themself. Otherwise it's just very confusing without any benefits.
    for (QVariantMap::const_iterator iter = config.begin(); iter != config.end(); ++iter) {
        if (iter.key() == Integration::KEY_FRIENDLYNAME)
            m_friendlyName = iter.value().toString();
        else if (iter.key() == Integration::KEY_ID)
            m_integrationId = iter.value().toString();
    }
}

// Used for integration threading adapter
Integration::Integration(Plugin* plugin)
    : QObject(plugin),
      m_state(DISCONNECTED),
      m_entities(nullptr),
      m_notifications(nullptr),
      m_yioapi(nullptr),
      m_config(nullptr),
      m_logCategory(plugin->m_logCategory) {}

Integration::~Integration() {}

void Integration::setState(int state) {
    if (state == m_state) {
        return;
    }
    m_state = state;
    emit stateChanged();
    switch (state) {
        case CONNECTING:
            emit connecting();
            break;
        case CONNECTED:
            emit connected();
            m_entities->setConnected(m_integrationId, true);
            break;
        case DISCONNECTED:
            emit disconnected();
            m_entities->setConnected(m_integrationId, false);
            break;
    }
}
