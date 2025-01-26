/*  -*- C++ -*-
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2003 Jason Harris <kstars@30doradus.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KPLOTPOINT_H
#define KPLOTPOINT_H

#include <kplotting_export.h>

#include <QString>

#include <memory>

class QPointF;

/*!
 * \class KPlotPoint
 * \inmodule KPlotting
 *
 * \brief Encapsulates a point in the plot.
 *
 * A KPlotPoint consists of X and Y coordinates (in Data units),
 * an optional label string, and an optional bar-width,
 * The bar-width is only used for plots of type KPlotObject::Bars,
 * and it allows the width of each bar to be set manually.  If
 * bar-widths are omitted, then the widths will be set automatically,
 * based on the halfway-mark between adjacent points.
 */
class KPLOTTING_EXPORT KPlotPoint
{
public:
    /*!
     * Default constructor.
     */
    explicit KPlotPoint();

    /*!
     * Constructor.
     *
     * Sets the KPlotPoint according to the given arguments
     *
     * \a x the X-position for the point, in Data units
     *
     * \a y the Y-position for the point, in Data units
     *
     * \a label the label string for the point.  If the string
     * is defined, the point will be labeled in the plot.
     *
     * \a width the bar width to use for this point (only used for
     * plots of type KPlotObject::Bars)
     */
    KPlotPoint(double x, double y, const QString &label = QString(), double width = 0.0);

    /*!
     * Constructor.
     *
     * Sets the KPlotPoint according to the given arguments
     *
     * \a p the position for the point, in Data units
     *
     * \a label the label string for the point.  If the string
     * is defined, the point will be labeled in the plot.
     *
     * \a width the bar width to use for this point (only used for
     * plots of type KPlotObject::Bars)
     */
    explicit KPlotPoint(const QPointF &p, const QString &label = QString(), double width = 0.0);

    ~KPlotPoint();

    /*!
     * Returns the position of the point, in data units
     */
    QPointF position() const;

    /*!
     * Set the position of the point, in data units
     *
     * \a pos the new position for the point.
     */
    void setPosition(const QPointF &pos);

    /*!
     * Returns the X-position of the point, in data units
     */
    double x() const;

    /*!
     * Set the X-position of the point, in Data units
     */
    void setX(double x);

    /*!
     * Returns the Y-position of the point, in data units
     */
    double y() const;

    /*!
     * Set the Y-position of the point, in Data units
     */
    void setY(double y);

    /*!
     * Returns the label for the point
     */
    QString label() const;

    /*!
     * Set the label for the point
     */
    void setLabel(const QString &label);

    /*!
     * Returns the bar-width for the point
     */
    double barWidth() const;

    /*!
     * Set the bar-width for the point
     */
    void setBarWidth(double w);

private:
    class Private;
    std::unique_ptr<Private> const d;

    Q_DISABLE_COPY(KPlotPoint)
};

#endif
