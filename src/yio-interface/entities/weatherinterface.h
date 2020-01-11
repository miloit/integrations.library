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

/// This class is a work arround to make the feature enum available in the interface and in the specifc entity class.
/// Qt cannot create metadata describing an enum contained in the interface
/// In the specific entity class it is only needed to generically convert the feature enum to a string and back
class WeatherDef : public QObject {
    Q_OBJECT

 public:
    enum Attributes { STATE, CURRENT, FORECAST };
    Q_ENUM(Attributes)

    enum States { OFFLINE, ONLINE };
    Q_ENUM(States)

    enum Features { F_DETAIL };
    Q_ENUM(Features)

    enum Commands { C_SETLOCATION };
    Q_ENUM(Commands)

    explicit WeatherDef(QObject* parent = nullptr) : QObject(parent) {}
};
class WeatherItem {
 public:
    QString date() const { return _date; }
    QString description() const { return _description; }
    QString imageurl() const { return _imageurl; }
    QString temp() const { return _temp; }
    QString rain() const { return _rain; }
    QString snow() const { return _snow; }
    QString wind() const { return _wind; }
    QString humidity() const { return _humidity; }

    void setDate(const QString& date) { _date = date; }
    void setDescription(const QString& description) { _description = description; }
    void setImageurl(const QString& imageurl) { _imageurl = imageurl; }
    void setTemp(const QString& temp) { _temp = temp; }
    void setRain(const QString& rain) { _rain = rain; }
    void setSnow(const QString& snow) { _snow = snow; }
    void setWind(const QString& wind) { _wind = wind; }
    void setHumidity(const QString& humidity) { _humidity = humidity; }

 private:
    QString _date;
    QString _description;
    QString _imageurl;
    QString _temp;
    QString _rain;
    QString _snow;
    QString _wind;
    QString _humidity;
};

class WeatherInterface {
 public:
    virtual ~WeatherInterface();
    virtual void setCurrent(const WeatherItem& current) = 0;
    virtual void setForecast(QObject* model) = 0;
};

QT_BEGIN_NAMESPACE
#define WeatherInterface_iid "YIO.WeatherInterface"
Q_DECLARE_INTERFACE(WeatherInterface, WeatherInterface_iid)
QT_END_NAMESPACE
