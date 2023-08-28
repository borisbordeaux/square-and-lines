#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow():
	QMainWindow(nullptr), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_pen.setBrush(Qt::black);
	m_pen.setWidth(3);

	ui->graphicsView->setScene(&m_scene);
	ui->graphicsView->setBackgroundBrush(Qt::white);
	m_scene.setSceneRect(0.0, 0.0, 700.0, 700.0);

	connect(&m_timer, SIGNAL(timeout()), this, SLOT(animate()));

	this->reset();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
		this->close();

	if (event->key() == Qt::Key_Space)
		m_timer.start(20);

	if (event->key() == Qt::Key_R)
		this->reset();
}

void MainWindow::animate()
{
	if (m_lines.size() != 0)
	{
		m_scene.addLine(m_lines.first(), m_pen);
		m_lines.removeFirst();
		update();
	}
	else
		m_timer.stop();
}

void MainWindow::reset()
{
	m_timer.stop();
	m_scene.clear();
	m_lines.clear();
	this->drawSquare();
	this->drawTriangles();
	this->fillTriangles();
}

void MainWindow::drawSquare()
{
	m_scene.addRect(QRectF(0.0, 0.0, 700.0, 700.0), m_pen);
}

void MainWindow::drawTriangles()
{
	m_scene.addLine(0.0, 0.0, 350.0, 700.0, m_pen);
	m_scene.addLine(350.0, 700.0, 700.0, 0.0, m_pen);
	m_scene.addLine(0.0, 700.0, 350.0, 0.0, m_pen);
	m_scene.addLine(350.0, 0.0, 700.0, 700.0, m_pen);
	m_scene.addLine(0.0, 350.0, 700.0, 350.0, m_pen);
}

void MainWindow::fillTriangles()
{
	//parameters
	const int iterLittle = 30;
	const int iterBigger = 40;
	const double ratio = 1.0 / 8.0;
	const double ratioFactorLittle = 1.02;
	const double ratioFactorBig = 1.01;

	//10 triangles to fill
	//up from left to right
	this->fillTriangle({0.0, 0.0}, {175.0, 350.0}, {0.0, 350.0}, iterLittle, ratio, ratioFactorLittle);
	this->fillTriangle({0.0, 0.0}, {350.0, 0.0}, {175.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({350.0, 0.0}, {175.0, 350.0}, {525.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 0.0}, {350.0, 0.0}, {525.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 0.0}, {525.0, 350.0}, {700.0, 350.0}, iterLittle, ratio, ratioFactorLittle);

	//down from left to right
	this->fillTriangle({0.0, 700.0}, {175.0, 350.0}, {0.0, 350.0}, iterLittle, ratio, ratioFactorLittle);
	this->fillTriangle({350.0, 700.0}, {175.0, 350.0}, {0.0, 700.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({525.0, 350.0}, {175.0, 350.0}, {350.0, 700.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 700.0}, {350.0, 700.0}, {525.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 700.0}, {525.0, 350.0}, {700.0, 350.0}, iterLittle, ratio, ratioFactorLittle);
}

void MainWindow::fillTriangle(QPointF pointA, QPointF pointB, QPointF pointC, int iteration, qreal ratio, qreal ratioFactor)
{
	if (iteration > 0)
	{
		QPointF newPoint = (1.0 - ratio) * pointB + ratio * pointC;
		m_lines.emplaceBack(pointA, newPoint);
		fillTriangle(newPoint, pointC, pointA, iteration - 1, ratio * ratioFactor, ratioFactor);
	}
}

