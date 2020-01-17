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

#include "plugin.h"

#include <QDebug>

#include "integration_threadadapter.h"
#include "yio-plugin/integration.h"

Plugin::Plugin(const char* pluginName, bool useWorkerThread)
    : m_logCategory(pluginName), m_useWorkerThread(useWorkerThread) {}

void Plugin::create(const QVariantMap& config, EntitiesInterface* entities, NotificationsInterface* notifications,
                    YioAPIInterface* api, ConfigInterface* configObj) {
    QMap<QObject*, QVariant> returnData;

    QVariantList data;
    QString      mdns;

    for (QVariantMap::const_iterator iter = config.begin(); iter != config.end(); ++iter) {
        if (iter.key() == "mdns") {
            mdns = iter.value().toString();
        } else if (iter.key() == "data") {
            data = iter.value().toList();
        } else if (iter.key() == "workerThread") {
            m_useWorkerThread = iter.value().toBool();
        }
    }

    for (int i = 0; i < data.length(); i++) {
        Integration* integration = createIntegration(data[i].toMap(), entities, notifications, api, configObj);
        QVariantMap  d = data[i].toMap();
        d.insert("mdns", mdns);
        d.insert("type", config.value("type").toString());
        if (m_useWorkerThread) {
            qCDebug(m_logCategory) << "Using ThreadAdapter to run integration in its own thread";
            IntegrationThreadAdapter* integrationThread = new IntegrationThreadAdapter(*integration, this);
            returnData.insert(integrationThread, d);
        } else {
            returnData.insert(integration, d);
        }
    }
    emit createDone(returnData);
}

void Plugin::setLogEnabled(QtMsgType msgType, bool enable) { m_logCategory.setEnabled(msgType, enable); }

Integration* Plugin::createIntegration(const QVariantMap& config, EntitiesInterface* entities,
                                       NotificationsInterface* notifications, YioAPIInterface* api,
                                       ConfigInterface* configObj) {
    Q_UNUSED(config)
    Q_UNUSED(entities)
    Q_UNUSED(notifications)
    Q_UNUSED(api)
    Q_UNUSED(configObj)
    Q_ASSERT(false);  // Must be overriden
    return nullptr;
}
