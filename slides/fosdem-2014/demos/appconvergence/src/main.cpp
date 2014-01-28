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

#include "qtquickcontrolsapplication.h"
#include "convergencecontroller.h"
#include "convergenceinterceptor.h"

Q_LOGGING_CATEGORY(APPCONVERGENCE, "appconvergence")

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

    ConvergenceController controller;
    controller.setPlatformHints(hints);

    return app.exec();
}
