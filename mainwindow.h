#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * @brief initialize the list of the lines to draw
	 */
	MainWindow();
	~MainWindow();

	// QWidget interface
protected:
	/**
	 * @brief the function called when a key is pressed.
	 * Press escape to quit the application.
	 * Press spacebar to start the animation.
	 * Press R to reset the drawing
	 * @param event the event received
	 */
	void keyPressEvent(QKeyEvent* event) override;

public slots:
	/**
	 * @brief function called each step of animation.
	 * It removes the first line of the list and draws it.
	 */
	void animate();

private:

	/**
	 * @brief Resets the drawing and fills the list of lines to draw
	 */
	void reset();

	/**
	 * @brief Draws the initial square
	 */
	void drawSquare();

	/**
	 * @brief Draws the initial triangles
	 */
	void drawTriangles();

	/**
	 * @brief fills all triangles calling the fillTriangle() function
	 */
	void fillTriangles();

	/**
	 * @brief recursive function that add a line to draw from A to a new point D
	 * defined as (1.0 - ratio) * B + ratio * C. Then if the iteration
	 * is not 0, it calls itself with the triangle (D, C, A), decreasing the iteration
	 * and multiplying the ratio with the ratio factor
	 * @param pointA the first point of the triangle
	 * @param pointB the second point of the triangle
	 * @param pointC the third point of the triangle
	 * @param iteration the iteration level, when 0 the recursivity stops
	 * @param ratio the ratio to use todecrease the length of one side of the triangle
	 * @param ratioFactor the factor by which the ratio is multiplied
	 */
	void fillTriangle(QPointF pointA, QPointF pointB, QPointF pointC, int iteration, qreal ratio, qreal ratioFactor);

private:
	Ui::MainWindow* ui;

	// the scene of the ui QGraphicsView
	QGraphicsScene m_scene;

	// the pen used to draw the lines
	QPen m_pen;

	// the timer for animation
	QTimer m_timer;

	// the list of lines to draw
	QList<QLineF> m_lines;
};
#endif // MAINWINDOW_H
