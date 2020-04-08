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

#include <QLoggingCategory>
#include <QObject>

#include "yio-interface/plugininterface.h"

class Integration;

/**
 * @brief The Plugin class is the default skeleton implementation of an integration plugin.
 */
class Plugin : public PluginInterface {
    friend class Integration;

    Q_INTERFACES(PluginInterface)

 public:
    explicit Plugin(const char* pluginName, bool useWorkerThread);

    /**
     * @brief create Default implementation of PluginInterface::create: calls the internal createIntegration operation
     * and moves it to a worker thread based on the configuration.
     * @details If the integration requires special handling, e.g. uses auto discovery of possibly multiple instances
     * like the dock integration, then this method must be overriden.
     */
    void         create(const QVariantMap& config, EntitiesInterface* entities, NotificationsInterface* notifications,
                        YioAPIInterface* api, ConfigInterface* configObj) override;
    void         setLogEnabled(QtMsgType msgType, bool enable) override;
    QTranslator* installTranslator(QString language) override;
    QTranslator* pluginTranslator() override;

 protected:
    /**
     * @brief createIntegration Internal integration creation. Must be implemented by the integration plugin if the
     * default PluginInterface::create implementation is used and no custom implementation is provided.
     * @param config The integration plugin specific configuration map
     * @param entities The YIO entities interface
     * @param notifications The YIO notifications interface
     * @param api The YIO API interface
     * @param configObj The YIO configuration interface
     * @return The created integration or null if creation failed
     */
    virtual Integration* createIntegration(const QVariantMap& config, EntitiesInterface* entities,
                                           NotificationsInterface* notifications, YioAPIInterface* api,
                                           ConfigInterface* configObj);

    QLoggingCategory m_logCategory;

 private:
    bool         m_useWorkerThread;
    QTranslator* m_translator;
};
