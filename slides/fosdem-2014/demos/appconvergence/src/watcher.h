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

#ifndef WATCHER_H
#define WATCHER_H

#include <QtCore/QObject>
#include <QtCore/QFileSystemWatcher>

class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = 0);

signals:
    void hintsChanged(const QStringList &hints);

private:
    QFileSystemWatcher *m_watcher;

private slots:
    void fileChanged(const QString &fileName);
};

#endif // WATCHER_H
