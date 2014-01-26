/****************************************************************************
**
** Copyright (C) 2014 Pier Luigi Fiorini.
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#define USE_FILE_SELECTOR 0

#include "qtquickcontrolsapplication.h"
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtQml/QQmlAbstractUrlInterceptor>
#include <QtQml/QQmlApplicationEngine>

class ConvergenceInterceptor : public QQmlAbstractUrlInterceptor
{
public:
    ConvergenceInterceptor();

    void setBasePath(const QString &path);
    void setPlatformHints(const QStringList &hints);

    QString filePath(const QString &fileName) const;

    QUrl intercept(const QUrl &url, DataType type);

private:
    QDir m_basePath;
    QStringList m_hints;
};

ConvergenceInterceptor::ConvergenceInterceptor()
{
}

void ConvergenceInterceptor::setBasePath(const QString &path)
{
    m_basePath = path;
}

void ConvergenceInterceptor::setPlatformHints(const QStringList &hints)
{
    m_hints = hints;
}

QString ConvergenceInterceptor::filePath(const QString &fileName) const
{
    return m_basePath.filePath(fileName);
}

QUrl ConvergenceInterceptor::intercept(const QUrl &url, QQmlAbstractUrlInterceptor::DataType type)
{
    if (type == QQmlAbstractUrlInterceptor::QmldirFile)
        return url;

    if (type == QQmlAbstractUrlInterceptor::QmlFile || type == QQmlAbstractUrlInterceptor::JavaScriptFile) {
        // Rewrite only URLs relative to our base path
        if (url.path().startsWith(m_basePath.absolutePath())) {
            // Extract relative URL
            QString relativePath = url.path().mid(m_basePath.absolutePath().length());

            for (int i = 0; i < m_hints.size(); i++) {
                // Check whether this relative path exist in the hint domain
                QString newPath = m_basePath.absoluteFilePath("+" + m_hints.at(i) + relativePath);
                //qDebug() << "Trying" << newPath;
                if (QFile::exists(newPath)) {
                    QUrl newUrl = QUrl::fromLocalFile(newPath);
                    qDebug() << "Rewrite" << url.toString() << "to" << newUrl.toString();
                    return newUrl;
                }
            }
        }
    } else {
        // Rewrite local URLs relative to the base path
        if (url.path().startsWith(m_basePath.absolutePath()) && url.isLocalFile()) {
            QString relativePath = url.path().mid(m_basePath.absolutePath().length());
            QString newPath = m_basePath.absoluteFilePath(relativePath);
            if (QFile::exists(newPath)) {
                QUrl newUrl = QUrl::fromLocalFile(newPath);
                qDebug() << "Rewrite" << url.toString() << "to" << newUrl.toString();
                return newUrl;
            }
        }
    }

    qDebug() << url.toString();

    return url;
}

int main(int argc, char *argv[])
{
    QtQuickControlsApplication app(argc, argv);
    app.setApplicationName("appconvergence");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription(app.translate("main", "Demo for convergence"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    QStringList hints;
    hints << "touch" << "tablet";

    ConvergenceInterceptor interceptor;
    interceptor.setBasePath(QCoreApplication::applicationDirPath() + "/content");
    interceptor.setPlatformHints(hints);

    QQmlApplicationEngine engine;
    engine.setUrlInterceptor(&interceptor);
    engine.load(QUrl::fromLocalFile(interceptor.filePath("main.qml")));

    return app.exec();
}
