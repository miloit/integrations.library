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

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QObject>
#include <QLoggingCategory>
#include <QMetaEnum>

#include "../remote-software/sources/integrations/integrationinterface.h"
#include "../remote-software/sources/entities/entitiesinterface.h"
#include "../remote-software/sources/notificationsinterface.h"
#include "../remote-software/sources/yioapiinterface.h"
#include "../remote-software/sources/configinterface.h"
#include "plugin.h"

class Integration : public QObject, public IntegrationInterface
{
    Q_OBJECT
    Q_INTERFACES (IntegrationInterface)

public:
    Integration(const QVariantMap& config, QObject *entities, QObject *notifications, QObject* api, QObject *configObj, Plugin* parent);
    Integration(Plugin* parent);
    ~Integration();

    const int INITIAL_STATE = DISCONNECTED;

    Q_PROPERTY(int              state           READ state          WRITE setState          NOTIFY stateChanged)
    Q_PROPERTY(QString          integrationId   READ integrationId  WRITE setIntegrationId)
    Q_PROPERTY(QString          friendlyName    READ friendlyName   WRITE setFriendlyName)

    Q_INVOKABLE void            connect()       = 0;            // Must be implemented by integration
    Q_INVOKABLE void            disconnect()    = 0;            // Must be implemented by integration
    Q_INVOKABLE void            enterStandby()  {}              // Can be overriden by integration
    Q_INVOKABLE void            leaveStandby()  {}              // Can be overriden by integration
    Q_INVOKABLE void            sendCommand     (const QString& type, const QString& entity_id, int command, const QVariant& param) = 0;

    // get the if the state
    int state()                                 { return m_state; }

    // set the state
    void setState(int state);

    // get the id of the integration
    QString integrationId()                     { return m_integrationId; }

    // set the id of the integration
    void setIntegrationId(QString value)        { m_integrationId = value; }

    // get the friendly name of the integration
    QString friendlyName()                      { return m_friendlyName; }

    // set the friendly name of the integration
    void setFriendlyName(QString value)         { m_friendlyName = value; }

protected:
    int                     m_state;
    bool                    m_workerThread;
    QString                 m_integrationId;
    QString                 m_friendlyName;
    EntitiesInterface*      m_entities;
    NotificationsInterface* m_notifications;
    YioAPIInterface*        m_yioapi;
    ConfigInterface*        m_config;
    QLoggingCategory&       m_log;

signals:
    void integrationIdChanged();
    void connected();
    void connecting();
    void disconnected();
    void stateChanged();
};

#endif // PLUGIN_H
