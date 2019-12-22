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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QLoggingCategory>

#include "../remote-software/sources/integrations/plugininterface.h"

class Integration;
class Plugin : public PluginInterface
{
    friend class Integration;

    //Q_OBJECT
    Q_INTERFACES(PluginInterface)
public:
    explicit Plugin(const char* pluginName, bool useWorkerThread);

    virtual void            create            (const QVariantMap& config, QObject *entities, QObject *notifications, QObject* api, QObject *configObj) override;
    virtual void            setLogEnabled     (QtMsgType msgType, bool enable) override;

protected:
    virtual Integration*    createIntegration (const QVariantMap& config, QObject *entities, QObject *notifications, QObject* api, QObject *configObj);

    QLoggingCategory        m_log;
    bool                    m_useWorkerThread;
};

#endif // PLUGIN_H
