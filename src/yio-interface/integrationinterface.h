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

#include <QVariant>

// FIXME provide complete API documentation with all QML requirements of the implementation!
/**
 * @brief The IntegrationInterface must be implemented by the integration plugins.
 */
class IntegrationInterface {
 public:
    enum States { CONNECTED = 0, CONNECTING = 1, DISCONNECTED = 2 };

    virtual ~IntegrationInterface();

    /**
     * @brief connect Must be implemented by integration as Q_INVOKABLE
     */
    virtual void connect() = 0;

    /**
     * @brief disconnect Must be implemented by integration as Q_INVOKABLE
     */
    virtual void disconnect() = 0;

    /**
     * @brief enterStandby Can be implemented by integration as Q_INVOKABLE
     */
    virtual void enterStandby() = 0;

    /**
     * @brief leaveStandby Can be implemented by integration as Q_INVOKABLE
     */
    virtual void leaveStandby() = 0;

    /**
     * @brief getAllAvailableEntities Can be implemented by integration
     */
    virtual QStringList getAllAvailableEntities() = 0;

    /**
     * @brief sendCommand Must be implemented as Q_INVOKABLE
     * @param type
     * @param entity_id
     * @param command
     * @param param
     */
    virtual void sendCommand(const QString& type, const QString& entity_id, int command, const QVariant& param) = 0;

    /**
     * @brief state Returns the current state. See States enum definition.
     * @details A Q_PROPERTY must be implemented with this method as READ accessor.
     */
    virtual int     state() = 0;

    /**
     * @brief state Returns the integration identifier.
     * @details A Q_PROPERTY must be implemented with this method as READ accessor.
     */
    virtual QString integrationId() = 0;

    /**
     * @brief state Returns the friendly human readable name of the integration.
     * @details A Q_PROPERTY must be implemented with this method as READ accessor.
     */
    virtual QString friendlyName() = 0;
};

QT_BEGIN_NAMESPACE
#define IntegrationInterface_iid "YIO.IntegrationInterface"
Q_DECLARE_INTERFACE(IntegrationInterface, IntegrationInterface_iid)
QT_END_NAMESPACE
