#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    about = new About(this);
    connect(ui->spinbox_segment_nr,SIGNAL(valueChanged(int)),ui->slider_segment_nr,SLOT(setValue(int)));
    connect(ui->slider_segment_nr,SIGNAL(valueChanged(int)),ui->spinbox_segment_nr,SLOT(setValue(int)));
    connect(ui->spinbox_angle,SIGNAL(valueChanged(int)),ui->slider_angle,SLOT(setValue(int)));
    connect(ui->slider_angle,SIGNAL(valueChanged(int)),ui->spinbox_angle,SLOT(setValue(int)));

    connect(ui->spinbox_segment_nr,SIGNAL(valueChanged(int)),ui->canvas,SLOT(setSegmentNumber(int)));
    connect(ui->spinbox_angle,SIGNAL(valueChanged(int)),ui->canvas,SLOT(setAngle(int)));

    connect(ui->lineedit_reversals,SIGNAL(textChanged(QString)),ui->canvas,SLOT(setReverseTurns(QString)));

    connect(ui->pushbutton_random,SIGNAL(clicked()),this,SLOT(random()));

    connect(ui->button_line_color,SIGNAL(clicked()),ui->canvas,SLOT(setLineColor()));
    connect(ui->button_background_color,SIGNAL(clicked()),ui->canvas,SLOT(setBackgroundColor()));
    connect(ui->spinbox_line_width,SIGNAL(valueChanged(double)),ui->canvas,SLOT(setLineWidth(double)));
    connect(ui->button_fill_color,SIGNAL(clicked()),ui->canvas,SLOT(setFillColor()));
    connect(ui->checkbox_fill,SIGNAL(stateChanged(int)),this,SLOT(useFillToggle(int)));
    connect(ui->checkbox_fill,SIGNAL(stateChanged(int)),ui->canvas,SLOT(setUseFill(int)));

    connect(ui->canvas,SIGNAL(lineColorChanged(QColor)),this,SLOT(setLineColor(QColor)));
    connect(ui->canvas,SIGNAL(backgroundColorChanged(QColor)),this,SLOT(setBackgroundColor(QColor)));
    connect(ui->canvas,SIGNAL(fillColorChanged(QColor)),this,SLOT(setFillColor(QColor)));
    ui->canvas->setLineColor(QColor(50,50,50));
    ui->canvas->setBackgroundColor(Qt::white);
    ui->canvas->setFillColor(QColor(181,218,255));

    ui->button_fill_color->setVisible(false);
    ui->label_fill->setVisible(false);

    connect(ui->actionSaveSVG,SIGNAL(triggered()),this,SLOT(saveSVG()));
    connect(ui->actionSavePNG,SIGNAL(triggered()),this,SLOT(savePNG()));

    ui->canvas->setAngle(ui->spinbox_angle->value());
    ui->canvas->setSegmentNumber(ui->spinbox_segment_nr->value());

    QRegExp rx("^(\\d+(,\\d+)*)?$");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->lineedit_reversals->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveSVG()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
        path, tr("SVG files (*.svg)"));

    if (newPath.isEmpty())
        return;

    path = newPath;

    QSvgGenerator generator;
    generator.setFileName(path);
    generator.setSize(ui->canvas->size());
    generator.setViewBox(QRect(0, 0, ui->canvas->width(), ui->canvas->height()));
    QPainter painter;
    painter.begin(&generator);
    ui->canvas->paint(painter);
    painter.end();
}

void MainWindow::savePNG()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save PNG"),
        path, tr("PNG files (*.png)"));

    if (newPath.isEmpty())
        return;

    path = newPath;

    QImage image(ui->canvas->size(), QImage::Format_ARGB32);
    QPainter painter(&image);
    ui->canvas->render(&painter);

    image.save(path);
}

void MainWindow::setLineColor(QColor color)
{
    QString stylesheet("border: 1px solid black; background: " + color.name() + ";");
    ui->button_line_color->setStyleSheet(stylesheet);
}

void MainWindow::setBackgroundColor(QColor color)
{
    QString stylesheet("border: 1px solid black; background: " + color.name() + ";");
    ui->button_background_color->setStyleSheet(stylesheet);
}

void MainWindow::setFillColor(QColor color)
{
    QString stylesheet("border: 1px solid black; background: " + color.name() + ";");
    ui->button_fill_color->setStyleSheet(stylesheet);
}

void MainWindow::setReverseTurns()
{
    ui->canvas->setReverseTurns(ui->lineedit_reversals->text());
}

void MainWindow::random()
{
    QRandomGenerator generator;
    int segment_nr = generator.global()->bounded(ui->slider_segment_nr->minimum(),ui->slider_segment_nr->maximum()+1);
    int angle = generator.global()->bounded(ui->slider_angle->minimum(),ui->slider_angle->maximum()+1);

    ui->slider_angle->setValue(angle);
    ui->slider_segment_nr->setValue(segment_nr);
}

void MainWindow::useFillToggle(int state)
{
    bool checked = (state == Qt::Unchecked) ? false : true;
    ui->button_fill_color->setVisible(checked);
    ui->label_fill->setVisible(checked);
}

void MainWindow::on_actionAbout_triggered()
{
    about->show();
}
