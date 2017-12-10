#pragma once

#include <QChart>
#include <QLineSeries>
#include <QMainWindow>

#include <cstdint>
#include <memory>
#include <vector>

namespace Ui {
class MainWindow;
}

class WaveformGenerator;

class MainWindow : public QMainWindow
{
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void generateWaveformSourceCode();

	void generateWaveform();
	void updateWaveformGraph();

	uint32_t numSamples() const;
	float amplitude() const;
	bool signedSamples() const;

	void setupGraphXAxis();
	void setupGraphYAxis();

	WaveformGenerator* currentWaveformGenerator() const;

	static QString sampleValueToSourceCode(const QString& type, float sample);

private:
	Ui::MainWindow *ui;

	std::vector<float> _samples;

	QtCharts::QChart _chart;
	QtCharts::QLineSeries* _series = nullptr;

	std::vector<std::unique_ptr<WaveformGenerator>> _generators;
};

