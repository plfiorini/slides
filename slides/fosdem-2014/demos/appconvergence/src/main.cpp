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

#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtQml/QQmlAbstractUrlInterceptor>
#include <QtQml/QQmlApplicationEngine>

#include "qtquickcontrolsapplication.h"

Q_LOGGING_CATEGORY(APPCONVERGENCE, "appconvergence")

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

    // Rewrite app:// URLs
    if (url.scheme() == "app") {
        QUrl newUrl = QUrl::fromLocalFile(filePath(QString(".%1").arg(url.path())));
        qCDebug(APPCONVERGENCE) << "Rewrite" << url.toString() << "to" << newUrl.toString();
        return newUrl;
    }

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
                    qCDebug(APPCONVERGENCE) << "Rewrite" << url.toString() << "to" << newUrl.toString();
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
                qCDebug(APPCONVERGENCE) << "Rewrite" << url.toString() << "to" << newUrl.toString();
                return newUrl;
            }
        }
    }

    qCDebug(APPCONVERGENCE) << "Not rewritten:" << url.toString();

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

    QCommandLineOption verboseOption("verbose",
                                     app.translate("main", "Verbose output"));
    parser.addOption(verboseOption);

    parser.addPositionalArgument("hints",
                                 app.translate("main", "List of hints"));

    parser.process(app);

    if (parser.isSet(verboseOption))
        QLoggingCategory::setFilterRules("appconvergence.debug=true");
    else
        QLoggingCategory::setFilterRules("appconvergence.debug=false");

    const QStringList hints = parser.positionalArguments();

    ConvergenceInterceptor interceptor;
    interceptor.setBasePath(QCoreApplication::applicationDirPath() + "/content");
    interceptor.setPlatformHints(hints);

    QQmlApplicationEngine engine;
    engine.setUrlInterceptor(&interceptor);
    engine.load(QUrl::fromLocalFile(interceptor.filePath("main.qml")));

    return app.exec();
}
