/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

#include <QtWaylandCompositor/qwaylandquickextension.h>
#include "qwaylandqtshell.h"
#include "qwaylandqtshellchrome.h"

QT_BEGIN_NAMESPACE

Q_COMPOSITOR_DECLARE_QUICK_EXTENSION_CLASS(QWaylandQtShell)

/*!
    \qmlmodule QtWayland.Compositor.QtShell
    \title Qt Wayland Qt Shell Extension
    \ingroup qmlmodules
    \since 6.3
    \brief Provides a shell extension for Qt applications running on a Qt Wayland Compositor.

    \section2 Summary
    The QtShell extension provides a way to associate an QtShellSurface with a regular Wayland
    surface. The QtShell extension is written to support the window management features which are
    supported by Qt. It may be suitable on a platform where both the compositor and client
    applications are written with Qt, and where applications are trusted not to abuse features such
    as manual window positioning and "bring-to-front".

    For other use cases, consider using IviApplication or XdgShell instead.

    \section2 Usage
    To use this module, import it like this:
    \qml
    import QtWayland.Compositor.IviApplication
    \endqml
*/

class QQtWaylandShellPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri) override
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtWayland.Compositor.QtShell"));
        defineModule(uri);
    }

    static void defineModule(const char *uri)
    {
        qmlRegisterModule(uri, QT_VERSION_MAJOR, QT_VERSION_MINOR);
        qmlRegisterType<QWaylandQtShellQuickExtension>(uri, 1, 0, "QtShell");
        qmlRegisterType<QWaylandQtShellSurface>(uri, 1, 0, "QtShellSurface");
        qmlRegisterType<QWaylandQtShellChrome>(uri, 1, 0, "QtShellChrome");
    }
};

QT_END_NAMESPACE

#include "qwaylandqtshellplugin.moc"
