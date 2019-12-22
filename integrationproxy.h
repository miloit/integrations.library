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

#ifndef INTEGRATIONPROXY_H
#define INTEGRATIONPROXY_H

#include <QObject>
#include <QThread>
#include "integration.h"
#include "../remote-software/sources/integrations/integrationinterface.h"

class IntegrationProxy : public Integration
{
    Q_OBJECT
public:
    explicit IntegrationProxy(Integration& integration, Plugin* parent);
    ~IntegrationProxy();

    Q_INVOKABLE void connect	    ();
    Q_INVOKABLE void disconnect	    ();
    Q_INVOKABLE void enterStandby   ();
    Q_INVOKABLE void leaveStandby   ();
    Q_INVOKABLE void sendCommand    (const QString& type, const QString& entity_id, int command, const QVariant& param);

    // set the state
    void onStateChanged             ();

signals:
    void connectSignal              ();
    void disconnectSignal           ();
    void enterStandbySignal         ();
    void leaveStandbySignal         ();
    void sendCommandSignal          (const QString& type, const QString& entity_id, int command, const QVariant& param);

private:
    Integration&                    m_integrationThread;
    QThread                         m_thread;
};

#endif // INTEGRATIONPROXY_H
