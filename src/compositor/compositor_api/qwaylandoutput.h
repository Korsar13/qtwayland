/****************************************************************************
**
** Copyright (C) 2014-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
** Copyright (C) 2013 Klarälvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDOUTPUT_H
#define QWAYLANDOUTPUT_H

#include <QtCompositor/qwaylandextension.h>
#include <QtCore/QObject>

#include <QObject>
#include <QRect>
#include <QSize>

QT_BEGIN_NAMESPACE

struct wl_resource;

class QWaylandCompositor;
class QWindow;
class QWaylandSurface;
class QWaylandView;
class QWaylandClient;
class QWaylandOutputSpace;

namespace QtWayland {
    class Output;
}

class Q_COMPOSITOR_EXPORT QWaylandOutput : public QObject, public QWaylandExtensionContainer
{
    Q_OBJECT
    Q_PROPERTY(QString manufacturer READ manufacturer CONSTANT)
    Q_PROPERTY(QString model READ model CONSTANT)
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QWaylandOutput::Mode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QRect geometry READ geometry NOTIFY geometryChanged)
    Q_PROPERTY(QRect availableGeometry READ availableGeometry WRITE setAvailableGeometry NOTIFY availableGeometryChanged)
    Q_PROPERTY(QSize physicalSize READ physicalSize WRITE setPhysicalSize NOTIFY physicalSizeChanged)
    Q_PROPERTY(QWaylandOutput::Subpixel subpixel READ subpixel WRITE setSubpixel NOTIFY subpixelChanged)
    Q_PROPERTY(QWaylandOutput::Transform transform READ transform WRITE setTransform NOTIFY transformChanged)
    Q_PROPERTY(int scaleFactor READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)
    Q_PROPERTY(QWaylandCompositor *compositor READ compositor CONSTANT)
    Q_PROPERTY(QWindow *window READ window CONSTANT)
    Q_PROPERTY(bool sizeFollowsWindow READ sizeFollowsWindow WRITE setSizeFollowsWindow NOTIFY sizeFollowsWindowChanged)
    Q_PROPERTY(QWaylandOutputSpace *outputSpace READ outputSpace WRITE setOutputSpace NOTIFY outputSpaceChanged)
    Q_ENUMS(Subpixel Transform)

public:
    enum Subpixel {
      SubpixelUnknown = 0,
      SubpixelNone,
      SubpixelHorizontalRgb,
      SubpixelHorizontalBgr,
      SubpixelVerticalRgb,
      SubpixelVerticalBgr
    };

    enum Transform {
        TransformNormal = 0,
        Transform90,
        Transform180,
        Transform270,
        TransformFlipped,
        TransformFlipped90,
        TransformFlipped180,
        TransformFlipped270
    };

    struct Mode
    {
        QSize size;
        int refreshRate;
    };

    QWaylandOutput(QWaylandOutputSpace *outputSpace, QWindow *window,
                   const QString &manufacturer, const QString &model);
    ~QWaylandOutput();

    static QWaylandOutput *fromResource(wl_resource *resource);

    void setOutputSpace(QWaylandOutputSpace *outputSpace);
    QWaylandOutputSpace *outputSpace() const;

    virtual void update();

    QWaylandCompositor *compositor() const;

    QString manufacturer() const;

    QString model() const;

    QPoint position() const;
    void setPosition(const QPoint &pt);

    Mode mode() const;
    void setMode(const Mode &mode);

    QRect geometry() const;
    void setGeometry(const QRect &geometry);
    void setWidth(int newWidth);
    void setHeight(int newHeight);

    QRect availableGeometry() const;
    void setAvailableGeometry(const QRect &availableGeometry);

    QSize physicalSize() const;
    void setPhysicalSize(const QSize &size);

    Subpixel subpixel() const;
    void setSubpixel(const Subpixel &subpixel);

    Transform transform() const;
    void setTransform(const Transform &transform);

    int scaleFactor() const;
    void setScaleFactor(int scale);

    QWindow *window() const;

    bool sizeFollowsWindow() const;
    void setSizeFollowsWindow(bool follow);

    bool physicalSizeFollowsSize() const;
    void setPhysicalSizeFollowsSize(bool follow);

    void frameStarted();
    void sendFrameCallbacks();

    void surfaceEnter(QWaylandSurface *surface);
    void surfaceLeave(QWaylandSurface *surface);

    QtWayland::Output *handle() const;

    Q_INVOKABLE virtual QWaylandView *pickView(const QPointF &outputPosition) const;
    Q_INVOKABLE virtual QPointF mapToView(QWaylandView *view, const QPointF &surfacePosition) const;

    Q_INVOKABLE QPointF mapToOutputSpace(const QPointF &point);

Q_SIGNALS:
    void positionChanged();
    void geometryChanged();
    void modeChanged();
    void availableGeometryChanged();
    void physicalSizeChanged();
    void scaleFactorChanged();
    void subpixelChanged();
    void transformChanged();
    void sizeFollowsWindowChanged();
    void physicalSizeFollowsSizeChanged();
    void outputSpaceChanged();

protected:
    QScopedPointer<QtWayland::Output> d_ptr;

private Q_SLOTS:
    void windowDestroyed();

};

Q_DECLARE_METATYPE(QWaylandOutput::Mode)

QT_END_NAMESPACE

#endif // QWAYLANDOUTPUT_H
