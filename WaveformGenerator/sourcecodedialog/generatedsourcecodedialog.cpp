#include "generatedsourcecodedialog.h"
#include "ui_generatedsourcecodedialog.h"

GeneratedSourceCodeDialog::GeneratedSourceCodeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::GeneratedSourceCodeDialog)
{
	ui->setupUi(this);
}

GeneratedSourceCodeDialog::~GeneratedSourceCodeDialog()
{
	delete ui;
}

void GeneratedSourceCodeDialog::setCode(const QString &sourceCode)
{
	ui->sourceCodeView->setPlainText(sourceCode);
}
