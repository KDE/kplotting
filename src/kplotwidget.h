/*  -*- C++ -*-
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2003 Jason Harris <kstars@30doradus.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KPLOTWIDGET_H
#define KPLOTWIDGET_H

#include <kplotting_export.h>

#include <QFrame>
#include <QList>

#include <memory>

class KPlotAxis;
class KPlotObject;
class KPlotPoint;

/*!
 * \class KPlotWidget
 * \inmodule KPlotting
 *
 * \brief Generic data plotting widget.
 *
 * Widget for drawing plots. The basic idea behind KPlotWidget is that
 * you don't have to worry about any transformation from your data's
 * natural units to screen pixel coordinates; this is handled internally
 * by the widget.
 *
 * Data to be plotted are represented by one or more instances of
 * KPlotObject.  KPlotObject contains a list of QPointFs to be plotted
 * (again, in the data's natural units), as well as information about how
 * the data are to be rendered in the plot (i.e., as separate points or
 * connected by lines?  With what color and point style? etc).  See
 * KPlotObject for more information.
 *
 * KPlotWidget automatically adds axis labels with tickmarks and tick
 * labels.  These are encapsulated in the KPlotAxis class.  All you have
 * to do is set the limits of the plotting area in data units, and
 * KPlotWidget will figure out the optimal positions and labels for the
 * tickmarks on the axes.
 *
 * Example of usage:
 *
 * \code
 * KPlotWidget *kpw = new KPlotWidget( parent );
 * // setting our limits for the plot
 * kpw->setLimits( 1.0, 5.0, 1.0, 25.0 );
 *
 * // creating a plot object whose points are connected by red lines ...
 * KPlotObject *kpo = new KPlotObject( Qt::red, KPlotObject::Lines );
 * // ... adding some points to it ...
 * for ( float x = 1.0; x <= 5.0; x += 0.1 )
 *     kpo->addPoint( x, x*x );
 *
 * // ... and adding the object to the plot widget
 * kpw->addPlotObject( kpo );
 * \endcode
 *
 * \note KPlotWidget will take ownership of the objects added to it, so when
 * clearing the objects list (eg with removeAllPlotObjects()) any previous
 * reference to a KPlotObject already added to a KPlotWidget will be invalid.
 * You can disable this behavior by using setAutoDelete(false).
 */
class KPLOTTING_EXPORT KPlotWidget : public QFrame
{
    Q_OBJECT

    /*!
     * \property KPlotWidget::leftPadding
     */
    Q_PROPERTY(int leftPadding READ leftPadding)

    /*!
     * \property KPlotWidget::rightPadding
     */
    Q_PROPERTY(int rightPadding READ rightPadding)

    /*!
     * \property KPlotWidget::topPadding
     */
    Q_PROPERTY(int topPadding READ topPadding)

    /*!
     * \property KPlotWidget::bottomPadding
     */
    Q_PROPERTY(int bottomPadding READ bottomPadding)

    /*!
     * \property KPlotWidget::backgroundColor
     */
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

    /*!
     * \property KPlotWidget::foregroundColor
     */
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)

    /*!
     * \property KPlotWidget::gridColor
     */
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor)

    /*!
     * \property KPlotWidget::grid
     */
    Q_PROPERTY(bool grid READ isGridShown WRITE setShowGrid)

    /*!
     * \property KPlotWidget::objectToolTip
     */
    Q_PROPERTY(bool objectToolTip READ isObjectToolTipShown WRITE setObjectToolTipShown)
public:
    /*!
     * Constructor.
     *
     * \a parent the parent widget
     */
    explicit KPlotWidget(QWidget *parent = nullptr);

    ~KPlotWidget() override;

    /*!
     * The four types of plot axes.
     *
     * \value LeftAxis the left axis
     * \value BottomAxis the bottom axis
     * \value RightAxis the right axis
     * \value TopAxis the top axis
     */
    enum Axis {
        LeftAxis = 0,
        BottomAxis,
        RightAxis,
        TopAxis,
    };

    /*!
     * Returns suggested minimum size for the plot widget
     */
    QSize minimumSizeHint() const override;

    /*!
     * Returns suggested size for the plot widget
     */
    QSize sizeHint() const override;

    /*!
     * Set new data limits for the plot.
     *
     * \a x1 the minimum X value in data units
     *
     * \a x2 the maximum X value in data units
     *
     * \a y1 the minimum Y value in data units
     *
     * \a y2 the maximum Y value in data units
     */
    void setLimits(double x1, double x2, double y1, double y2);

    /*!
     * Reset the secondary data limits, which control the
     * values displayed along the top and right axes.
     *
     * All data points are *plotted* using the coordinates
     * defined by setLimits(), so this function is only useful for
     * showing alternate tickmark labels along the top and right
     * edges.  For example, if you were plotting temperature on the
     * X-axis, you could use Centigrade units for the primary
     * (bottom) axis, using setLimits( 0.0, 100.0, 0.0, 1.0 ).  If
     * you also wanted to show Fahrenheit units along the secondary
     * (top) axis, you would additionally use
     * setSecondaryLimits( 32.0, 212.0, 0.0, 1.0 ).  The data
     * added to the plot would have x-coordinates in Centigrade degrees.
     *
     * \a x1 the minimum X value in secondary data units
     *
     * \a x2 the maximum X value in secondary data units
     *
     * \a y1 the minimum Y value in secondary data units
     *
     * \a y2 the maximum Y value in secondary data units
     *
     * \sa setLimits()
     */
    void setSecondaryLimits(double x1, double x2, double y1, double y2);

    /*!
     * Unset the secondary limits, so the top and right axes
     * show the same tickmarks as the bottom and left axes (no tickmark
     * labels will be drawn for the top and right axes in this case)
     */
    void clearSecondaryLimits();

    /*!
     * Returns the rectangle representing the boundaries of the current plot,
     * in natural data units.
     * \sa setLimits()
     */
    QRectF dataRect() const;

    /*!
     * Returns the rectangle representing the boundaries of the secondary
     * data limits, if they have been set.  Otherwise, this function
     * behaves the same as dataRect().
     * \sa setSecondaryLimits()
     */
    QRectF secondaryDataRect() const;

    /*!
     * Returns the rectangle representing the boundaries of the current plot,
     * in screen pixel units.
     */
    QRect pixRect() const;

    /*!
     * Add an item to the list of KPlotObjects to be plotted.
     *
     * The widget takes ownership of the plot object, unless auto-delete was disabled.
     *
     * \a object the KPlotObject to be added
     */
    void addPlotObject(KPlotObject *object);

    /*!
     * Add more than one KPlotObject at one time.
     *
     * The widget takes ownership of the plot object, unless auto-delete was disabled.
     *
     * \a objects the list of KPlotObjects to be added
     */
    void addPlotObjects(const QList<KPlotObject *> &objects);

    /*!
     * Returns the current list of plot objects
     */
    QList<KPlotObject *> plotObjects() const;

    /*!
     * Enables auto-deletion of plot objects if autoDelete is true; otherwise auto-deletion is disabled.
     *
     * Auto-deletion is enabled by default.
     *
     * \since 5.12
     */
    void setAutoDeletePlotObjects(bool autoDelete);

    /*!
     * Removes all plot objects that were added to the widget.
     *
     * If auto-delete was not disabled, the plot objects are deleted.
     */
    void removeAllPlotObjects();

    /*!
     * Reset the mask used for non-overlapping labels so that all
     * regions of the plot area are considered empty.
     */
    void resetPlotMask();

    /*!
     * Clear the object list, reset the data limits, and remove axis labels
     *
     * If auto-delete was not disabled, the plot objects are deleted.
     */
    void resetPlot();

    /*!
     * Replace an item in the KPlotObject list.
     *
     * \a i the index of the item to be replaced
     *
     * \a o pointer to the replacement KPlotObject
     *
     * Since 5.12, if auto-deletion is enabled, the previous plot object is deleted.
     * Call setAutoDeletePlotObjects(false) if you want to swap between available plot objects
     * and therefore you want to handle deletion externally.
     */
    void replacePlotObject(int i, KPlotObject *o);

    /*!
     * Returns the background color of the plot.
     *
     * The default color is black.
     */
    QColor backgroundColor() const;

    /*!
     * Returns the foreground color, used for axes, tickmarks and associated
     * labels.
     *
     * The default color is white.
     */
    QColor foregroundColor() const;

    /*!
     * Returns the grid color.
     *
     * The default color is gray.
     */
    QColor gridColor() const;

    /*!
     * Set the background color
     *
     * \a bg the new background color
     */
    void setBackgroundColor(const QColor &bg);

    /*!
     * Set the foreground color
     *
     * \a fg the new foreground color
     */
    void setForegroundColor(const QColor &fg);

    /*!
     * Set the grid color
     *
     * \a gc the new grid color
     */
    void setGridColor(const QColor &gc);

    /*!
     * Returns whether the grid lines are shown
     *
     * Grid lines are not shown by default.
     */
    bool isGridShown() const;

    /*!
     * Returns whether the tooltip for the point objects is shown.
     *
     * Tooltips are enabled by default.
     */
    bool isObjectToolTipShown() const;

    /*!
     * Returns whether the antialiasing is active
     *
     * Antialiasing is not active by default.
     */
    bool antialiasing() const;

    /*!
     * Toggle antialiased drawing.
     *
     * \a b if true, the plot graphics will be antialiased.
     */
    void setAntialiasing(bool b);

    /*!
     * Returns the number of pixels to the left of the plot area.
     *
     * Padding values are set to -1 by default; if unchanged, this
     * function will try to guess a good value, based on whether
     * ticklabels and/or axis labels need to be drawn.
     */
    int leftPadding() const;

    /*!
     * Returns the number of pixels to the right of the plot area.
     *
     * Padding values are set to -1 by default; if unchanged, this
     * function will try to guess a good value, based on whether
     * ticklabels and/or axis labels are to be drawn.
     */
    int rightPadding() const;

    /*!
     * Returns the number of pixels above the plot area.
     *
     * Padding values are set to -1 by default; if unchanged, this
     * function will try to guess a good value, based on whether
     * ticklabels and/or axis labels are to be drawn.
     */
    int topPadding() const;

    /*!
     * Returns the number of pixels below the plot area.
     *
     * Padding values are set to -1 by default; if unchanged, this
     * function will try to guess a good value, based on whether
     * ticklabels and/or axis labels are to be drawn.
     */
    int bottomPadding() const;

    /*!
     * Set the number of pixels to the left of the plot area.
     *
     * Set this to -1 to revert to automatic determination of padding values.
     */
    void setLeftPadding(int padding);

    /*!
     * Set the number of pixels to the right of the plot area.
     *
     * Set this to -1 to revert to automatic determination of padding values.
     */
    void setRightPadding(int padding);

    /*!
     * Set the number of pixels above the plot area.
     *
     * Set this to -1 to revert to automatic determination of padding values.
     */
    void setTopPadding(int padding);

    /*!
     * Set the number of pixels below the plot area.
     *
     * Set this to -1 to revert to automatic determination of padding values.
     */
    void setBottomPadding(int padding);

    /*!
     * Revert all four padding values to -1, so that they will be
     * automatically determined.
     */
    void setDefaultPaddings();

    /*!
     * Map a coordinate \a p from the data rect to the physical
     * pixel rect.
     *
     * Used mainly when drawing.
     *
     * \a p the point to be converted, in natural data units
     *
     * Returns the coordinate in the pixel coordinate system
     */
    QPointF mapToWidget(const QPointF &p) const;

    /*!
     * Indicate that object labels should try to avoid the given
     * rectangle in the plot.  The rectangle is in pixel coordinates.
     *
     * \note You should not normally call this function directly.
     * It is called by KPlotObject when points, bars and labels are drawn.
     *
     * \a r the rectangle defining the region in the plot that
     * text labels should avoid (in pixel coordinates)
     *
     * \a value Allows you to determine how strongly the rectangle
     * should be avoided.  Larger values are avoided more strongly.
     */
    void maskRect(const QRectF &r, float value = 1.0f);

    /*!
     * Indicate that object labels should try to avoid the line
     * joining the two given points (in pixel coordinates).
     *
     * \note You should not normally call this function directly.
     * It is called by KPlotObject when lines are drawn in the plot.
     *
     * \a p1 the starting point for the line
     *
     * \a p2 the ending point for the line
     *
     * \a value Allows you to determine how strongly the line
     * should be avoided.  Larger values are avoided more strongly.
     */
    void maskAlongLine(const QPointF &p1, const QPointF &p2, float value = 1.0f);

    /*!
     * Place an object label optimally in the plot.  This function will
     * attempt to place the label as close as it can to the point to which
     * the label belongs, while avoiding overlap with regions of the plot
     * that have been masked.
     *
     * \note You should not normally call this function directly.
     * It is called internally in KPlotObject::draw().
     *
     * \a painter Pointer to the painter on which to draw the label
     *
     * \a pp pointer to the KPlotPoint whose label is to be drawn.
     */
    void placeLabel(QPainter *painter, KPlotPoint *pp);

    /*!
     * Returns the axis of the specified \a type, or 0 if no axis has been set.
     * \sa Axis
     */
    KPlotAxis *axis(Axis type);

    /*!
     * Returns the axis of the specified \a type, or 0 if no axis has been set.
     * \sa Axis
     */
    const KPlotAxis *axis(Axis type) const;

public Q_SLOTS:
    /*!
     * Toggle whether grid lines are drawn at major tickmarks.
     *
     * \a show if true, grid lines will be drawn.
     *
     * \sa isGridShown()
     */
    void setShowGrid(bool show);

    /*!
     * Toggle the display of a tooltip for point objects.
     *
     * \a show whether show the tooltip.
     *
     * \sa isObjectToolTipShown()
     */
    void setObjectToolTipShown(bool show);

protected:
    bool event(QEvent *) override;

    void paintEvent(QPaintEvent *) override;

    void resizeEvent(QResizeEvent *) override;

    /*!
     * Draws the plot axes and axis labels.
     * \internal
     * Internal use only; one should simply call update()
     * to draw the widget with axes and all objects.
     *
     * \a p pointer to the painter on which we are drawing
     */
    virtual void drawAxes(QPainter *p);

    /*!
     * Synchronize the PixRect with the current widget size and
     * padding settings.
     */
    void setPixRect();

    /*!
     * Returns a list of points in the plot which are within 4 pixels
     * of the screen position given as an argument.
     *
     * \a p The screen position from which to check for plot points.
     */
    QList<KPlotPoint *> pointsUnderPoint(const QPoint &p) const;

private:
    class Private;
    std::unique_ptr<Private> const d;

    Q_DISABLE_COPY(KPlotWidget)
};

#endif
