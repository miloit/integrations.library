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

#include <QString>
#include <QTranslator>
#include <QVariantMap>

#include "configinterface.h"
#include "entities/entitiesinterface.h"
#include "notificationsinterface.h"
#include "yioapiinterface.h"

// FIXME provide complete API documentation with all QML requirements of the implementation!
/**
 * @brief The PluginInterface must be implemented by the integration plugins, it is used by the entities to operate the
 * integration.
 */
class PluginInterface : public QObject {
    Q_OBJECT

 public:
    virtual ~PluginInterface() {}

    /**
     * @brief create Creates the integration and returns the object in the createDone signal.
     * @param config The integration plugin specific configuration map
     * @param entities The YIO entities interface
     * @param notifications The YIO notifications interface
     * @param api The YIO API interface
     * @param configObj The YIO configuration interface
     */
    virtual void create(const QVariantMap &config, EntitiesInterface *entities, NotificationsInterface *notifications,
                        YioAPIInterface *api, ConfigInterface *configObj) = 0;

    // enable log category
    /**
     * @brief setLogEnabled Enable or disable given log category.
     * @param msgType
     * @param enable
     */
    virtual void setLogEnabled(QtMsgType msgType, bool enable) = 0;

    virtual QTranslator *installTranslator(QString language) = 0;
    virtual QTranslator *pluginTranslator()                  = 0;

 signals:
    void createDone(QMap<QObject *, QVariant> map);
};

QT_BEGIN_NAMESPACE
#define PluginInterface_iid "YIO.PluginInterfaceInterface"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE
