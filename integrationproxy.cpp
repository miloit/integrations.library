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

#include "integrationproxy.h"

IntegrationProxy::IntegrationProxy (Integration& integration, Plugin* plugin) :
    Integration(plugin),
    m_integrationThread(integration)
{
    setFriendlyName(integration.friendlyName());
    setIntegrationId(integration.integrationId());

    integration.moveToThread(&m_thread);

    // connect signals and slots
    QObject::connect(&m_thread, &QThread::finished, &integration, &QObject::deleteLater);

    QObject::connect(this, &IntegrationProxy::connectSignal, &integration, &Integration::connect);
    QObject::connect(this, &IntegrationProxy::disconnectSignal, &integration, &Integration::disconnect);
    QObject::connect(this, &IntegrationProxy::enterStandbySignal, &integration, &Integration::enterStandby);
    QObject::connect(this, &IntegrationProxy::leaveStandbySignal, &integration, &Integration::leaveStandby);
    QObject::connect(this, &IntegrationProxy::sendCommandSignal, &integration, &Integration::sendCommand);

    QObject::connect(&integration, &Integration::stateChanged, this, &IntegrationProxy::onStateChanged);

    m_thread.start();

}
IntegrationProxy::~IntegrationProxy()
{
    if (m_thread.isRunning()) {
        m_thread.exit();
        m_thread.wait(5000);
    }
}
void IntegrationProxy::connect ()
{
    qCDebug(m_log) << "Proxy connect";
    emit connectSignal();
}
void IntegrationProxy::disconnect ()
{
    qCDebug(m_log) << "Proxy disconnect";
    emit disconnectSignal();
}
void IntegrationProxy::enterStandby ()
{
    qCDebug(m_log) << "Proxy enterStandby";
    emit enterStandbySignal();
}
void IntegrationProxy::leaveStandby ()
{
    qCDebug(m_log) << "Proxy leaveStandby";
    emit leaveStandbySignal();
}
void IntegrationProxy::sendCommand (const QString& type, const QString& entity_id, int command, const QVariant& param)
{
    qCDebug(m_log) << "Proxy sendCommand" << type << entity_id << command << param;
    emit sendCommandSignal(type, entity_id, command, param);
}
// set the state
void IntegrationProxy::onStateChanged()
{
    m_state = m_integrationThread.state();
    qCDebug(m_log) << "Proxy state changed" << static_cast<States>(m_state);
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
