#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sourcecodedialog/generatedsourcecodedialog.h"
#include "generators/sinegenerator.h"
#include "generators/squaregenerator.h"
#include "generators/trianglegenerator.h"

#include <QStringBuilder>
#include <QValueAxis>

#include <assert.h>
#include <math.h>
#include <iterator>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

// Graph setup
	ui->chartWidget->setChart(&_chart);
	ui->chartWidget->setRenderHint(QPainter::Antialiasing);

	_series = new QLineSeries;
	_chart.addSeries(_series);

	_chart.createDefaultAxes();
	_chart.axes(Qt::Vertical).at(0)->setTitleText("Value");
	_chart.legend()->hide();

// Live UI
	connect(ui->numSamples, (void (QSpinBox::*)(int))&QSpinBox::valueChanged, this, [this](int){
		setupGraphXAxis();
		generateWaveform();
	});
	connect(ui->waveform, (void (QComboBox::*)(int))&QComboBox::currentIndexChanged, this, [this](int waveformIndex){
		const auto& gen = _generators[waveformIndex];

		for (int i = 0; i < ui->extraParameterLayout->count(); ++i)
			ui->extraParameterLayout->itemAt(i)->widget()->setVisible(gen->hasExtraParameter());

		if (gen->hasExtraParameter())
		{
			ui->extraParameter->setValue(gen->extraParameter());
			ui->extraParameter->setMinimum(gen->extraParameterProperties().minValue);
			ui->extraParameter->setMaximum(gen->extraParameterProperties().maxValue);
			ui->extraParameter->setSingleStep(gen->extraParameterProperties().step);

			ui->extraParameterName->setText(gen->extraParameterProperties().name.c_str());
		}

		generateWaveform();
	});
	connect(ui->amplitude, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, [this](double){
		setupGraphYAxis();
		generateWaveform();
	});
	connect(ui->signedSamples, &QCheckBox::toggled, this, [this](bool){
		setupGraphYAxis();
		generateWaveform();
	});
	connect(ui->extraParameter, (void (QDoubleSpinBox::*)(double))&QDoubleSpinBox::valueChanged, this, [this](double value){
		currentWaveformGenerator()->setExtraParameter((float)value);
		generateWaveform();
	});

	connect(ui->generate, &QPushButton::clicked, this, &MainWindow::generateWaveformSourceCode);

// Generators
	_generators.emplace_back(std::make_unique<SineGenerator>());
	_generators.emplace_back(std::make_unique<SquareGenerator>());
	_generators.emplace_back(std::make_unique<TriangleGenerator>());

// Final UI initialization
	for (const auto& gen: _generators)
		ui->waveform->addItem(gen->name());

	setupGraphXAxis();
	setupGraphYAxis();

	generateWaveform();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::generateWaveformSourceCode()
{
	const QString type = ui->type->text();
	QString sourceCode = type + QStringLiteral(" wavetable[%1] = {\n").arg(_samples.size());
	for (const float sample: _samples)
	{
		QString sampleText = sampleValueToSourceCode(type, sample, true);
		sourceCode = sourceCode % '\t' % sampleText % ",\n";
	}

	if (!_samples.empty())
		sourceCode.chop(2); // Remove extra ",\n" after the last item

	sourceCode += "\n};";

	GeneratedSourceCodeDialog sourceCodeView;
	sourceCodeView.setCode(sourceCode);
	sourceCodeView.exec();
}

void MainWindow::generateWaveform()
{
	_samples = currentWaveformGenerator()->generate(numSamples(), amplitude(), signedSamples());
	updateWaveformGraph();
}

void MainWindow::updateWaveformGraph()
{
	QVector<QPointF> points;
	points.reserve((int)_samples.size());
	for (size_t i = 0; i < _samples.size(); ++i)
	{
		QPointF point((float)i, _samples[i]);
		points.push_back(point);
	}

	_series->replace(points);
}

uint32_t MainWindow::numSamples() const
{
	return (uint32_t)ui->numSamples->value();
}

float MainWindow::amplitude() const
{
	return (float)ui->amplitude->value();
}

bool MainWindow::signedSamples() const
{
	return ui->signedSamples->isChecked();
}

void MainWindow::setupGraphXAxis()
{
	_chart.axes(Qt::Horizontal).at(0)->setRange(0, numSamples());
}

void MainWindow::setupGraphYAxis()
{
	_chart.axes(Qt::Vertical).at(0)->setRange(signedSamples() ? -amplitude() : 0, signedSamples() ? amplitude() : 2.0 * amplitude());
}

WaveformGenerator*MainWindow::currentWaveformGenerator() const
{
	return _generators[(size_t)ui->waveform->currentIndex()].get();
}

QString MainWindow::sampleValueToSourceCode(const QString &type, float sample, bool dualChannel)
{
	const bool intType = type.contains("int", Qt::CaseInsensitive);

	if (intType)
	{
		uint32_t sampleInt = static_cast<uint32_t>(::round(sample));
		if (dualChannel)
		{
			assert(type == "uint32_t");
			sampleInt |= (sampleInt << 16 | (1u << 28));
		}

		auto text =	QString::number(sampleInt);
		if (type.startsWith('u'))
			text += 'U';
		return text;
	}
	else
	{
		assert(!dualChannel);
		QString sampleText = QString::number((double)sample, 'g', 20);
		if (!sampleText.contains('.') && !sampleText.contains('e'))
			sampleText += ".0";

		return sampleText + 'f';
	}



	QString sampleText = intType ? QString::number((int64_t)(sample + 0.5f)) : QString::number((double)sample, 'g', 20);
	if (!intType && !sampleText.contains('.') && !sampleText.contains('e'))
		sampleText += ".0";

	if (!intType)
		sampleText += 'f';

	return sampleText;
}
