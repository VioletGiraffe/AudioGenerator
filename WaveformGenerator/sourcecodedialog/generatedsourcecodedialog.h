#pragma once

#include <QDialog>

namespace Ui {
class GeneratedSourceCodeDialog;
}

class GeneratedSourceCodeDialog : public QDialog
{
public:
	explicit GeneratedSourceCodeDialog(QWidget *parent = 0);
	~GeneratedSourceCodeDialog();

	void setCode(const QString& sourceCode);

private:
	Ui::GeneratedSourceCodeDialog *ui;
};
