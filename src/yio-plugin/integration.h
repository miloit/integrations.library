/******************************************************************************
 *
 * Copyright (C) 2018-2019 Marton Borzak <hello@martonborzak.com>
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

#pragma once

#include <QObject>

#include "plugin.h"
#include "yio-interface/entities/entitiesinterface.h"
#include "yio-interface/integrationinterface.h"

/**
 * @brief The Integration class is the base class of an integration plugin defining all required QML accessors.
 */
class Integration : public QObject, public IntegrationInterface {
    Q_OBJECT
    Q_INTERFACES(IntegrationInterface)

 public:
    // Common configuration keys. Initialized in integration.cpp
    // HELP: anyone knows how to properly define "static const QString" constants across Qt plugin boundaries?
    static const QString KEY_ID;
    static const QString KEY_FRIENDLYNAME;
    static const QString KEY_ENTITY_ID;
    static const QString KEY_AREA;
    static const QString KEY_INTEGRATION;
    static const QString KEY_SUPPORTED_FEATURES;
    static const QString KEY_TYPE;
    static const QString KEY_MDNS;
    static const QString KEY_WORKERTHREAD;
    static const QString OBJ_DATA;
    static const QString KEY_DATA_IP;
    static const QString KEY_DATA_TOKEN;

    Integration(const QVariantMap& config, EntitiesInterface* entities, NotificationsInterface* notifications,
                YioAPIInterface* api, ConfigInterface* configObj, Plugin* plugin);
    explicit Integration(Plugin* plugin);

    ~Integration();

    Q_PROPERTY(int state READ state NOTIFY stateChanged)

    Q_INVOKABLE void connect()    = 0;                                             // Must be implemented by integration
    Q_INVOKABLE void disconnect() = 0;                                             // Must be implemented by integration
    Q_INVOKABLE void enterStandby() {}                                             // Can be overriden by integration
    Q_INVOKABLE void leaveStandby() {}                                             // Can be overriden by integration
    QStringList      getAllAvailableEntities() { return m_allAvailableEntities; }  // Can be overriden by integration
    Q_INVOKABLE void sendCommand(const QString& type, const QString& entity_id, int command, const QVariant& param) = 0;

    // get the state
    int state() { return m_state; }

    // set the state
    void setState(int state);

    // get the id of the integration
    QString integrationId() { return m_integrationId; }

    // set the id of the integration
    void setIntegrationId(QString value) { m_integrationId = value; }

    // get the friendly name of the integration
    QString friendlyName() { return m_friendlyName; }

    // set the friendly name of the integration
    void setFriendlyName(QString value) { m_friendlyName = value; }

 signals:
    void connected();
    void connecting();
    void disconnected();
    void stateChanged();

 protected:
    int                     m_state;
    QString                 m_integrationId;
    QString                 m_friendlyName;
    EntitiesInterface*      m_entities;
    bool                    m_useWorkerThread;
    NotificationsInterface* m_notifications;
    YioAPIInterface*        m_yioapi;
    ConfigInterface*        m_config;
    QLoggingCategory&       m_logCategory;
    QStringList             m_allAvailableEntities;
};
