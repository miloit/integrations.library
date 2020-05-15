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
    static const QString KEY_DATA_SSL;
    static const QString KEY_DATA_SSL_IGNORE;

    Integration(const QVariantMap& config, EntitiesInterface* entities, NotificationsInterface* notifications,
                YioAPIInterface* api, ConfigInterface* configObj, Plugin* plugin);
    explicit Integration(Plugin* plugin);

    ~Integration() override;

    Q_PROPERTY(int state READ state NOTIFY stateChanged)

    QVariantList getAllAvailableEntities() override { return m_allAvailableEntities; }
    bool         addAvailableEntity(const QString& entityId, const QString& type, const QString& integration,
                                    const QString& friendlyName, const QStringList& supportedFeatures) override;
    void sendCommand(const QString& type, const QString& entityId, int command, const QVariant& param) override = 0;

    // get the state
    int state() override { return m_state; }

    // set the state
    void setState(int state);

    // get the id of the integration
    QString integrationId() override { return m_integrationId; }

    // set the id of the integration
    void setIntegrationId(QString value) { m_integrationId = value; }

    // get the friendly name of the integration
    QString friendlyName() override { return m_friendlyName; }

    // set the friendly name of the integration
    void setFriendlyName(QString value) { m_friendlyName = value; }

 signals:
    void connected();
    void connecting();
    void disconnected();
    void stateChanged();

 public slots:                       // NOLINT open issue: https://github.com/cpplint/cpplint/pull/99
    void connect() override    = 0;  // Must be implemented by integration
    void disconnect() override = 0;  // Must be implemented by integration
    void enterStandby() override {}  // Can be overriden by integration
    void leaveStandby() override {}  // Can be overriden by integration

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
    QVariantList            m_allAvailableEntities;
};
