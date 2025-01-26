/*  -*- C++ -*-
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2005 Andreas Nicolai <Andreas.Nicolai@gmx.net>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KPLOTAXIS_H
#define KPLOTAXIS_H

#include <kplotting_export.h>

#include <QList>
#include <QString>

#include <memory>

/*!
 * \class KPlotAxis
 * \inmodule KPlotting
 *
 * \brief Axis for KPlotWidget.
 *
 * Contains all data for drawing an axis including format specification axis labels.
 */
class KPLOTTING_EXPORT KPlotAxis
{
public:
    /*!
     * Constructor, constructs an axis with the label \a label.
     */
    explicit KPlotAxis(const QString &label = QString());

    ~KPlotAxis();

    /*!
     * Returns whether the axis is visible or not
     */
    bool isVisible() const;

    /*!
     * Sets the "visible" property of the axis.
     *
     * \a visible if true, this axis will be drawn on the KPlotWidget
     */
    void setVisible(bool visible);

    /*!
     * Returns whether tick labels will be drawn for this axis
     */
    bool areTickLabelsShown() const;

    /*!
     * Determine whether tick labels will be drawn for this axis.
     *
     * \a b if true, tick labels will be drawn.
     */
    void setTickLabelsShown(bool b);

    /*!
     * Sets the axis label.
     *
     * Set the label to an empty string to omit the axis label.
     *
     * \a label a string describing the data plotted on the axis.
     */
    void setLabel(const QString &label);

    /*!
     * Returns the label string for this axis
     */
    QString label() const;

    /*!
     * Returns the ticklabel string for the given value, rendered according
     * to the current format specification.
     *
     * \a value the value to be rendered as a tick label.
     *
     * \sa setTickLabelFormat()
     */
    QString tickLabel(double value) const;

    /*!
     * Set the display format for converting the double value of the
     * tick's position to the QString for the tick label.
     *
     * Normally, the format character is one of 'e', 'E', 'f', 'g', or 'G'
     * (see the documentation for QString::arg(double) for details).
     *
     * In addition, it is possible to set the format character to 't';
     * in this case the tickmark value is interpreted as a time in hours,
     * and the ticklabel string will be in "hh:mm" clock format.
     * Note that when the format character is 't', the fieldWidth and prec
     * values are ignored.
     *
     * \a format the format specification character
     *
     * \a fieldWidth the number of characters in the output string.
     *
     * If set to 0, the string will be as wide as it needs to be to fully
     * render the value.
     *
     * \a precision the number of characters following the decimal point.
     */
    void setTickLabelFormat(char format = 'g', int fieldWidth = 0, int precision = -1);

    /*!
     * Returns the field width of the tick labels
     */
    int tickLabelWidth() const;

    /*!
     * Returns the number format of the tick labels
     */
    char tickLabelFormat() const;

    /*!
     * Returns the number precision of the tick labels
     */
    int tickLabelPrecision() const;

    /*!
     * Determine the positions of major and minor tickmarks for this axis.
     *
     * \note this function is called by KPlotWidget whenever the plot's
     * limits are modified.
     *
     * \a x0 the minimum data coordinate of the axis.
     *
     * \a length the range covered by the axis, in data units.
     *
     * \sa majorTickMarks()
     * \sa minorTickMarks()
     */
    void setTickMarks(double x0, double length);

    /*!
     * Returns the list of coordinates of the major tickmarks for this axis
     *
     * \note the positions of tickmarks are automatically computed by setTickMarks().
     *
     * \sa setTickMarks()
     * \sa minorTickMarks()
     */
    QList<double> majorTickMarks() const;

    /*!
     * Returns the list with the minor tickmarks
     *
     * \note the positions of tickmarks are automatically computed by setTickMarks().
     *
     * \sa setTickMarks()
     * \sa majorTickMarks()
     */
    QList<double> minorTickMarks() const;

private:
    class Private;
    std::unique_ptr<Private> const d;

    Q_DISABLE_COPY(KPlotAxis)
};

#endif // KPLOTAXIS_H
