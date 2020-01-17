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

#include "integration_threadadapter.h"

// FIXME quick and dirty workaround until logging integration is fixed
static Q_LOGGING_CATEGORY(CLASS_LC, "integration.threadAdapter");

IntegrationThreadAdapter::IntegrationThreadAdapter(Integration& integration, Plugin* plugin)
    :  //    Integration(plugin),
      m_integration(integration) {
    setFriendlyName(integration.friendlyName());
    setIntegrationId(integration.integrationId());

    integration.moveToThread(&m_thread);

    // connect signals and slots
    QObject::connect(&m_thread, &QThread::finished, &integration, &QObject::deleteLater);

    QObject::connect(this, &IntegrationThreadAdapter::connectSignal, &integration, &Integration::connect);
    QObject::connect(this, &IntegrationThreadAdapter::disconnectSignal, &integration, &Integration::disconnect);
    QObject::connect(this, &IntegrationThreadAdapter::enterStandbySignal, &integration, &Integration::enterStandby);
    QObject::connect(this, &IntegrationThreadAdapter::leaveStandbySignal, &integration, &Integration::leaveStandby);
    QObject::connect(this, &IntegrationThreadAdapter::sendCommandSignal, &integration, &Integration::sendCommand);

    QObject::connect(&integration, &Integration::stateChanged, this, &IntegrationThreadAdapter::onStateChanged);

    m_thread.start();
}

IntegrationThreadAdapter::~IntegrationThreadAdapter() {
    if (m_thread.isRunning()) {
        m_thread.exit();
        m_thread.wait(5000);
    }
}

void IntegrationThreadAdapter::connect() {
    qCDebug(CLASS_LC) << "ThreadAdapter connect";
    emit connectSignal();
}

void IntegrationThreadAdapter::disconnect() {
    qCDebug(CLASS_LC) << "ThreadAdapter disconnect";
    emit disconnectSignal();
}

void IntegrationThreadAdapter::enterStandby() {
    qCDebug(CLASS_LC) << "ThreadAdapter entering standby";
    emit enterStandbySignal();
}

void IntegrationThreadAdapter::leaveStandby() {
    qCDebug(CLASS_LC) << "ThreadAdapter leaving standby";
    emit leaveStandbySignal();
}

void IntegrationThreadAdapter::sendCommand(const QString& type, const QString& entity_id, int command,
                                           const QVariant& param) {
    qCDebug(CLASS_LC) << "ThreadAdapter sendCommand" << type << entity_id << command << param;
    emit sendCommandSignal(type, entity_id, command, param);
}

void IntegrationThreadAdapter::onStateChanged() {
    m_state = m_integration.state();
    qCDebug(CLASS_LC) << "ThreadAdapter state changed" << static_cast<States>(m_state);
    emit stateChanged();
    switch (m_state) {
        case CONNECTING:
            emit connecting();
            break;
        case CONNECTED:
            emit connected();
            break;
        case DISCONNECTED:
            emit disconnected();
            break;
    }
}
