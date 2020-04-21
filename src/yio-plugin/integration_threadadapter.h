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

#pragma once

#include <QObject>
#include <QThread>

#include "plugin.h"
#include "yio-interface/integrationinterface.h"
#include "yio-plugin/integration.h"

/**
 * @brief The IntegrationThreadAdapter class is a convenient adapter to run an integration plugin within it's own
 * thread. It takes care of proxying all signals between the integration interface and the plugin implementation.
 */
class IntegrationThreadAdapter : public Integration {
    Q_OBJECT

 public:
    explicit IntegrationThreadAdapter(Integration& integration,  // NOLINT we need a non-const reference
                                      Plugin*      parent);
    ~IntegrationThreadAdapter() override;

 public slots:  // NOLINT open issue: https://github.com/cpplint/cpplint/pull/99
    void connect() override;
    void disconnect() override;
    void enterStandby() override;
    void leaveStandby() override;

    // set the state
    void onStateChanged();

    // IntegrationInterface
 public:
    QVariantList getAllAvailableEntities() override;
    void         sendCommand(const QString& type, const QString& entityId, int command, const QVariant& param) override;

 signals:
    void connectSignal();
    void disconnectSignal();
    void enterStandbySignal();
    void leaveStandbySignal();
    void sendCommandSignal(const QString& type, const QString& entityId, int command, const QVariant& param);

 private:
    Integration& m_integration;
    QThread      m_thread;
};
