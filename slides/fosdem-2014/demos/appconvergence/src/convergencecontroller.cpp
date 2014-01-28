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

#include <QtCore/QDebug>
#include <QtCore/QSignalMapper>
#include <QtCore/QCoreApplication>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>

#include "qtquickcontrolsapplication.h"
#include "convergencecontroller.h"

ConvergenceController::ConvergenceController()
    : QObject()
{
    m_interceptor = new ConvergenceInterceptor(this);
    m_interceptor->setBasePath(QCoreApplication::applicationDirPath() + "/content");
    connect(m_interceptor, &ConvergenceInterceptor::reload,
            this, &ConvergenceController::load);

    m_engine = new QQmlApplicationEngine(this);
    m_engine->setUrlInterceptor(m_interceptor);
}

void ConvergenceController::setPlatformHints(const QStringList &hints)
{
    m_interceptor->setPlatformHints(hints);
}

void ConvergenceController::run()
{
    m_engine->load(QUrl::fromLocalFile(m_interceptor->filePath("main.qml")));
}

void ConvergenceController::load(const QString &path)
{
    if (!m_engine)
        return;

    m_engine->deleteLater();

    while (QCoreApplication::hasPendingEvents())
        QCoreApplication::processEvents();

    QQmlApplicationEngine *engine = new QQmlApplicationEngine(this);
    engine->setUrlInterceptor(m_interceptor);
    m_engine = engine;
    run();
}
