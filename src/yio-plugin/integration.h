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
    // TODO(mze) default implementation
    // Integration(const QVariantMap& config, EntitiesInterface *entities, NotificationsInterface *notifications,
    //             YioAPIInterface* api, ConfigInterface *configObj, Plugin* plugin);
    // Integration(Plugin* plugin);
    Integration() {}

    // FIXME do we really need all Q_PROPERTY & Q_INVOKABLE function? E.g. why should QML be able to change the
    // integrationId?
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString integrationId READ integrationId WRITE setIntegrationId NOTIFY integrationIdChanged)
    Q_PROPERTY(QString friendlyName READ friendlyName WRITE setFriendlyName)

    Q_INVOKABLE void connect() = 0;     // Must be implemented by integration
    Q_INVOKABLE void disconnect() = 0;  // Must be implemented by integration
    Q_INVOKABLE void enterStandby() {}  // Can be overriden by integration
    Q_INVOKABLE void leaveStandby() {}  // Can be overriden by integration
    Q_INVOKABLE void sendCommand(const QString& type, const QString& entity_id, int command, const QVariant& param) = 0;

    void setup(const QVariantMap& config, EntitiesInterface* entities) {
        // FIXME remove QVariantMap indirection for friendlyName and integrationId:
        //       plugins MUST set them themself. Otherwise it's just very confusing without any benefits.
        for (QVariantMap::const_iterator iter = config.begin(); iter != config.end(); ++iter) {
            if (iter.key() == "friendly_name")
                m_friendlyName = iter.value().toString();
            else if (iter.key() == "id")
                m_integrationId = iter.value().toString();
        }
        m_entities = entities;
    }

    ~Integration() {}

    // get the state
    int state() { return m_state; }

    // set the state
    void setState(int state) {
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

    // get the id of the integration
    QString integrationId() { return m_integrationId; }

    // set the id of the integration
    void setIntegrationId(QString value) {
        m_integrationId = value;
        emit integrationIdChanged();
    }

    // get the friendly name of the integration
    QString friendlyName() { return m_friendlyName; }

    // set the friendly name of the integration
    void setFriendlyName(QString value) { m_friendlyName = value; }

 signals:
    void integrationIdChanged();
    void connected();
    void connecting();
    void disconnected();
    void stateChanged();

 protected:
    int                m_state = DISCONNECTED;
    QString            m_integrationId;
    QString            m_friendlyName;
    EntitiesInterface* m_entities;
    /*
    bool                    m_workerThread;
    NotificationsInterface* m_notifications;
    YioAPIInterface*        m_yioapi;
    ConfigInterface*        m_config;
    QLoggingCategory&       m_log;
    */
};
