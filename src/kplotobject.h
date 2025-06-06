/*  -*- C++ -*-
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2003 Jason Harris <kstars@30doradus.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KPLOTOBJECT_H
#define KPLOTOBJECT_H

#include <kplotting_export.h>

#include <QColor>
#include <QString>

#include <memory>

class QBrush;
class QPainter;
class QPen;
class QPointF;
class KPlotWidget;
class KPlotPoint;

/*!
 * \class KPlotObject
 * \inmodule KPlotting
 *
 * \brief Encapsulates a data set to be plotted in a KPlotWidget.
 *
 * Think of a KPlotObject as a set of data displayed as a group in the plot.
 * Each KPlotObject consists of a list of KPlotPoints, a "type" controlling
 * how the data points are displayed (some combination of Points, Lines, or
 * Bars), a color, and a size. There is also a parameter which controls the
 * shape of the points used to display the KPlotObject.
 *
 * \note KPlotObject will take care of the points added to it, so when clearing
 * the points list (eg with clearPoints()) any previous reference to a KPlotPoint
 * already added to a KPlotObject will be invalid.
 */
class KPLOTTING_EXPORT KPlotObject
{
public:
    /*!
     * The type classification of the KPlotObject.
     *
     * These are bitmask values that can be OR'd together, so that a set
     * of points can be represented in the plot in multiple ways.
     *
     * \note points should be added in order of increasing x-coordinate
     * when using Bars.
     *
     * \value UnknownType
     * \value Points Each KPlotPoint is represented with a drawn point
     * \value Lines Each KPlotPoint is connected with a line
     * \value Bars Each KPlotPoint is shown as a vertical bar
     */
    enum PlotType {
        UnknownType = 0,
        Points = 1,
        Lines = 2,
        Bars = 4,
    };
    Q_DECLARE_FLAGS(PlotTypes, PlotType)

    /*!
     * The available shape styles for plotted points.
     *
     * \value NoPoints
     * \value Circle
     * \value Letter
     * \value Triangle
     * \value Square
     * \value Pentagon
     * \value Hexagon
     * \value Asterisk
     * \value Star
     * \value UnknownPoint
     */
    enum PointStyle {
        NoPoints = 0,
        Circle = 1,
        Letter = 2,
        Triangle = 3,
        Square = 4,
        Pentagon = 5,
        Hexagon = 6,
        Asterisk = 7,
        Star = 8,
        UnknownPoint,
    };

    /*!
     * Constructor.
     *
     * \a color The color for plotting this object. By default this sets
     * the color for Points, Lines and Bars, but there are functions to
     * override any of these.
     *
     * \a otype the PlotType for this object (Points, Lines or Bars)
     *
     * \a size the size to use for plotted points, in pixels
     *
     * \a ps The PointStyle describing the shape for plotted points
     */
    explicit KPlotObject(const QColor &color = Qt::white, PlotType otype = Points, double size = 2.0, PointStyle ps = Circle);

    ~KPlotObject();

    /*!
     * Returns the plot flags of the object
     */
    PlotTypes plotTypes() const;

    /*!
     * Set whether points will be drawn for this object
     *
     * \a b if true, points will be drawn
     */
    void setShowPoints(bool b);

    /*!
     * Set whether lines will be drawn for this object
     *
     * \a b if true, lines will be drawn
     */
    void setShowLines(bool b);

    /*!
     * Set whether bars will be drawn for this object
     *
     * \a b if true, bars will be drawn
     */
    void setShowBars(bool b);

    /*!
     * Returns the size of the plotted points in this object, in pixels
     */
    double size() const;

    /*!
     * Set the size for plotted points in this object, in pixels
     *
     * \a s the new size
     */
    void setSize(double s);

    /*!
     * Returns the style used for drawing the points in this object
     */
    PointStyle pointStyle() const;

    /*!
     * Set a new style for drawing the points in this object
     *
     * \a p the new style
     */
    void setPointStyle(PointStyle p);

    /*!
     * Returns the default pen for this Object.
     *
     * If no other pens are set, this pen will be used for
     * points, lines, bars and labels (this pen is always used for points).
     */
    const QPen &pen() const;

    /*!
     * Set the default pen for this object
     *
     * \a p the pen to use
     */
    void setPen(const QPen &p);

    /*!
     * Returns the pen to use for drawing lines for this Object.
     */
    const QPen &linePen() const;

    /*!
     * Set the pen to use for drawing lines for this object
     *
     * \a p the pen to use
     */
    void setLinePen(const QPen &p);

    /*!
     * Returns the pen to use for drawing bars for this Object.
     */
    const QPen &barPen() const;

    /*!
     * Set the pen to use for drawing bars for this object
     *
     * \a p the pen to use
     */
    void setBarPen(const QPen &p);

    /*!
     * Returns the pen to use for drawing labels for this Object.
     */
    const QPen &labelPen() const;

    /*!
     * Set the pen to use for labels for this object
     *
     * \a p the pen to use
     */
    void setLabelPen(const QPen &p);

    /*!
     * Returns the default Brush to use for this Object.
     */
    const QBrush brush() const;

    /*!
     * Set the default brush to use for this object
     *
     * \a b the brush to use
     */
    void setBrush(const QBrush &b);

    /*!
     * Returns the brush to use for filling bars for this Object.
     */
    const QBrush barBrush() const;

    /*!
     * Set the brush to use for drawing bars for this object
     *
     * \a b the brush to use
     */
    void setBarBrush(const QBrush &b);

    /*!
     * Returns the list of KPlotPoints that make up this object
     */
    QList<KPlotPoint *> points() const;

    /*!
     * Add a point to the object's list of points, using input data to construct a KPlotPoint.
     *
     * \a p the QPointF to add.
     *
     * \a label the optional text label for this point
     *
     * \a barWidth the width of the bar, if this object is to be drawn with bars
     *
     * \note if \a barWidth is left at its default value of 0.0, then the width will be
     * automatically set to the distance between this point and the one to its right.
     */
    void addPoint(const QPointF &p, const QString &label = QString(), double barWidth = 0.0);

    /*!
     * Add a given KPlotPoint to the object's list of points.
     *
     * \overload
     *
     * \a p pointer to the KPlotPoint to add.
     */
    void addPoint(KPlotPoint *p);

    /*!
     * Add a point to the object's list of points, using input data to construct a KPlotPoint.
     *
     * \overload
     *
     * \a x the X-coordinate of the point to add.
     *
     * \a y the Y-coordinate of the point to add.
     *
     * \a label the optional text label
     *
     * \a barWidth the width of the bar, if this object is to be drawn with bars
     *
     * \note if \a barWidth is left at its default value of 0.0, then the width will be
     * automatically set to the distance between this point and the one to its right.
     */
    void addPoint(double x, double y, const QString &label = QString(), double barWidth = 0.0);

    /*!
     * Remove the QPointF at position index from the list of points
     *
     * \a index the index of the point to be removed.
     */
    void removePoint(int index);

    /*!
     * Remove and destroy the points of this object
     */
    void clearPoints();

    /*!
     * Draw this KPlotObject on the given QPainter
     *
     * \a p The QPainter to draw on
     *
     * \a pw the KPlotWidget to draw on (this is needed
     * for the KPlotWidget::mapToWidget() function)
     */
    void draw(QPainter *p, KPlotWidget *pw);

private:
    class Private;
    std::unique_ptr<Private> const d;

    Q_DISABLE_COPY(KPlotObject)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(KPlotObject::PlotTypes)

#endif
