/****************************************************************************
 * This file is part of FOSDEM 2014 Demo.
 *
 * Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL3$
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef CONVERGENCECONTROLLER_H
#define CONVERGENCECONTROLLER_H

#include <QtCore/QObject>
#include <QtQml/QQmlApplicationEngine>

#include "convergenceinterceptor.h"

class ConvergenceController : public QObject
{
    Q_OBJECT
public:
    ConvergenceController();

    void setPlatformHints(const QStringList &hints);

    void run();

public slots:
    void load(const QString &path);

private:
    QQmlApplicationEngine *m_engine;
    ConvergenceInterceptor *m_interceptor;
};

#endif // CONVERGENCECONTROLLER_H
