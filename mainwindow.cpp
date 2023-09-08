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

	connect(&m_timer, &QTimer::timeout, this, &MainWindow::animate);
	connect(this->ui->comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::reset);
	connect(this->ui->pushButton, &QPushButton::clicked, this, &MainWindow::startAnimation);

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
}

void MainWindow::startAnimation()
{
	this->reset();

	switch (this->ui->comboBox->currentIndex())
	{
		case 0:
			m_timer.start(15);
			break;

		case 1:
			m_timer.start(15);
			break;
	}
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

	switch (this->ui->comboBox->currentIndex())
	{
		case 0:
			this->drawDrawingOne();
			break;

		case 1:
			this->drawDrawingTwo();
			break;
	}
}

void MainWindow::drawDrawingOne()
{
	// initial square
	m_scene.addRect(QRectF(0.0, 0.0, 700.0, 700.0), m_pen);

	// initial triangles
	m_scene.addLine(0.0, 0.0, 350.0, 700.0, m_pen);
	m_scene.addLine(350.0, 700.0, 700.0, 0.0, m_pen);
	m_scene.addLine(0.0, 700.0, 350.0, 0.0, m_pen);
	m_scene.addLine(350.0, 0.0, 700.0, 700.0, m_pen);
	m_scene.addLine(0.0, 350.0, 700.0, 350.0, m_pen);

	// triangles will be filled
	// with these parameters
	const int iterLittle = 30;
	const int iterBigger = 40;
	const double ratio = 1.0 / 8.0;
	const double ratioFactorLittle = 1.02;
	const double ratioFactorBig = 1.01;

	// 10 triangles to fill
	// up from left to right
	this->fillTriangle({0.0, 0.0}, {175.0, 350.0}, {0.0, 350.0}, iterLittle, ratio, ratioFactorLittle);
	this->fillTriangle({0.0, 0.0}, {350.0, 0.0}, {175.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({350.0, 0.0}, {175.0, 350.0}, {525.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 0.0}, {350.0, 0.0}, {525.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 0.0}, {525.0, 350.0}, {700.0, 350.0}, iterLittle, ratio, ratioFactorLittle);

	// down from left to right
	this->fillTriangle({0.0, 700.0}, {175.0, 350.0}, {0.0, 350.0}, iterLittle, ratio, ratioFactorLittle);
	this->fillTriangle({350.0, 700.0}, {175.0, 350.0}, {0.0, 700.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({525.0, 350.0}, {175.0, 350.0}, {350.0, 700.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 700.0}, {350.0, 700.0}, {525.0, 350.0}, iterBigger, ratio, ratioFactorBig);
	this->fillTriangle({700.0, 700.0}, {525.0, 350.0}, {700.0, 350.0}, iterLittle, ratio, ratioFactorLittle);
}

void MainWindow::drawDrawingTwo()
{
	// initial square
	m_scene.addRect(QRectF(0.0, 0.0, 700.0, 700.0), m_pen);

	//initial triangles and squares
	m_scene.addLine(350.0, 0.0, 350.0, 700.0, m_pen);
	m_scene.addLine(0.0, 350.0, 700.0, 350.0, m_pen);
	m_scene.addLine(0.0, 0.0, 350.0, 175.0, m_pen);
	m_scene.addLine(350.0, 175.0, 700.0, 0.0, m_pen);
	m_scene.addLine(0.0, 175.0, 700.0, 525.0, m_pen);
	m_scene.addLine(0.0, 525.0, 700.0, 175.0, m_pen);
	m_scene.addLine(0.0, 700.0, 350.0, 525.0, m_pen);
	m_scene.addLine(350.0, 525.0, 700.0, 700.0, m_pen);
	m_scene.addLine(175.0, 262.5, 175.0, 437.5, m_pen);
	m_scene.addLine(525.0, 262.5, 525.0, 437.5, m_pen);

	// triangles will be filled
	// with these parameters
	const int iterLittleTriangle = 20;
	const int iterBiggerTriangle = 30;
	const int iterLittleRectangle = 45;
	const int iterBiggerRectangle = 65;
	const double ratioLittle = 1.0 / 8.0;
	const double ratioBigger = 1.0 / 10.0;
	const double ratioFactorLittleTriangle = 1.05;
	const double ratioFactorBigTriangle = 1.04;
	const double ratioFactorLittleRectangle = 1.03;
	const double ratioFactorBigRectangle = 1.02;

	// big triangles
	this->fillTriangle({350.0, 175.0}, {0.0, 0.0}, {350.0, 0.0}, iterBiggerTriangle, ratioBigger, ratioFactorBigTriangle);
	this->fillTriangle({350.0, 175.0}, {700.0, 0.0}, {350.0, 0.0}, iterBiggerTriangle, ratioBigger, ratioFactorBigTriangle);
	this->fillTriangle({350.0, 525.0}, {0.0, 700.0}, {350.0, 700.0}, iterBiggerTriangle, ratioBigger, ratioFactorBigTriangle);
	this->fillTriangle({350.0, 525.0}, {700.0, 700.0}, {350.0, 700.0}, iterBiggerTriangle, ratioBigger, ratioFactorBigTriangle);

	// little triangles
	this->fillTriangle({350.0, 350.0}, {175.0, 262.5}, {175.0, 350.0}, iterLittleTriangle, ratioLittle, ratioFactorLittleTriangle);
	this->fillTriangle({350.0, 350.0}, {175.0, 437.5}, {175.0, 350.0}, iterLittleTriangle, ratioLittle, ratioFactorLittleTriangle);
	this->fillTriangle({350.0, 350.0}, {525.0, 262.5}, {525.0, 350.0}, iterLittleTriangle, ratioLittle, ratioFactorLittleTriangle);
	this->fillTriangle({350.0, 350.0}, {525.0, 437.5}, {525.0, 350.0}, iterLittleTriangle, ratioLittle, ratioFactorLittleTriangle);

	// big rectangles
	this->fillRectangle({0.0, 175.0}, {350.0, 350.0}, {350.0, 175.0}, {0.0, 0.0}, iterBiggerRectangle, ratioBigger, ratioFactorBigRectangle);
	this->fillRectangle({700.0, 175.0}, {350.0, 350.0}, {350.0, 175.0}, {700.0, 0.0}, iterBiggerRectangle, ratioBigger, ratioFactorBigRectangle);
	this->fillRectangle({0.0, 525.0}, {350.0, 350.0}, {350.0, 525.0}, {0.0, 700.0}, iterBiggerRectangle, ratioBigger, ratioFactorBigRectangle);
	this->fillRectangle({700.0, 525.0}, {350.0, 350.0}, {350.0, 525.0}, {700.0, 700.0}, iterBiggerRectangle, ratioBigger, ratioFactorBigRectangle);

	// little rectangles
	this->fillRectangle({175.0, 262.5}, {175.0, 350.0}, {0.0, 350.0}, {0.0, 175.0}, iterLittleRectangle, ratioLittle, ratioFactorLittleRectangle);
	this->fillRectangle({175.0, 437.5}, {175.0, 350.0}, {0.0, 350.0}, {0.0, 525.0}, iterLittleRectangle, ratioLittle, ratioFactorLittleRectangle);
	this->fillRectangle({525.0, 262.5}, {525, 350.0}, {700.0, 350.0}, {700.0, 175.0}, iterLittleRectangle, ratioLittle, ratioFactorLittleRectangle);
	this->fillRectangle({525.0, 437.5}, {525, 350.0}, {700.0, 350.0}, {700.0, 525.0}, iterLittleRectangle, ratioLittle, ratioFactorLittleRectangle);
}

void MainWindow::fillTriangle(QPointF pointA, QPointF pointB, QPointF pointC, int iteration, qreal ratio, qreal ratioFactor)
{
	if (iteration > 0)
	{
		QPointF newPoint = (1.0 - ratio) * pointB + ratio * pointC;
		m_lines.emplaceBack(pointA, newPoint);
		this->fillTriangle(newPoint, pointC, pointA, iteration - 1, ratio * ratioFactor, ratioFactor);
	}
}

void MainWindow::fillRectangle(QPointF pointA, QPointF pointB, QPointF pointC, QPointF pointD, int iteration, qreal ratio, qreal ratioFactor)
{
	if (iteration > 0)
	{
		QPointF newPoint = (1.0 - ratio) * pointB + ratio * pointC;
		m_lines.emplaceBack(pointA, newPoint);
		this->fillRectangle(newPoint, pointC, pointD, pointA, iteration - 1, ratio * ratioFactor, ratioFactor);
	}
}

