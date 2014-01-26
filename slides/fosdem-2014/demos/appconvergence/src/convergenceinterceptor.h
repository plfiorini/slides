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

#ifndef CONVERGENCEINTERCEPTOR_H
#define CONVERGENCEINTERCEPTOR_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtQml/QQmlAbstractUrlInterceptor>

#include "watcher.h"

class ConvergenceInterceptor : public QObject, public QQmlAbstractUrlInterceptor
{
    Q_OBJECT
public:
    ConvergenceInterceptor(QObject *parent = 0);

    void setBasePath(const QString &path);
    void setPlatformHints(const QStringList &hints);

    QString filePath(const QString &fileName) const;

    QUrl intercept(const QUrl &url, DataType type);

signals:
    void reload(const QString &filePath);

private:
    QDir m_basePath;
    QStringList m_hints;
    Watcher *m_watcher;

private slots:
    void hintsChanged(const QStringList &hints);
};

#endif // CONVERGENCEINTERCEPTOR_H
