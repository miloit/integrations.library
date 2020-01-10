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

// This interface is implemented by the integration .so files, it is used by the entities to operate the integration
class PluginInterface : public QObject {
    Q_OBJECT

 public:
    virtual ~PluginInterface() {}

    // create an integration and return the object
    virtual void create(const QVariantMap &configurations, QObject *entities, QObject *notifications, QObject *api,
                        QObject *configObj) = 0;

    // enable log category
    virtual void setLogEnabled(QtMsgType msgType, bool enable) = 0;

 signals:
    void createDone(QMap<QObject *, QVariant> map);
};

QT_BEGIN_NAMESPACE
#define PluginInterface_iid "YIO.PluginInterfaceInterface"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE
