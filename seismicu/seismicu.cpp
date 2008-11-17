#include <QtGui>
#include "seismicu.h"

SeismicU::SeismicU(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QPushButton *convertButton =
            buttonBox->button(QDialogButtonBox::Ok);
    convertButton->setText(tr("&Run"));
    convertButton->setEnabled(true);
    outputTextEdit->append("Lol" );

    connect(convertButton, SIGNAL(clicked()),
            this, SLOT(runScript()));
//  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(&process, SIGNAL(readyReadStandardError()),
            this, SLOT(updateOutputTextEdit()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(&process, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(processError(QProcess::ProcessError)));
}

void SeismicU::runScript()
{
    outputTextEdit->clear();
	
	QFile file("script.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	// I just added this line to test some things 
	QTextStream out(&file);
	out << "#!/bin/bash\n";
	out << "/opt/SU/src/demos/Synthetic/Finite_Difference/Sufdmod2/XDemo3" << endl;

    QStringList args;
	args << "script.txt";

//  if (enhanceCheckBox->isChecked())
//      args << "-enhance";
//  if (monochromeCheckBox->isChecked())
//      args << "-monochrome";
	
    outputTextEdit->append(args.at(0));
    outputTextEdit->append(process.workingDirectory());
	QStringList env = QProcess::systemEnvironment();
	process.setEnvironment(env);
	env << "CWPROOT=/opt/SU"; 
	env << "PATH=$PATH:/opt/SU/bin"; 
//	process.start("sh", args);
	process.start("sh", args);
//	process.start("/opt/SU/src/demos/Synthetic/Finite_Difference/Sufdmod2/XDemo3");
}

void SeismicU::processFinished(int exitCode,
                                    QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit) {
        outputTextEdit->append(tr("Conversion program crashed"));
    } else if (exitCode != 0) {
        outputTextEdit->append(QString("Conversion failed, code=%1").arg(exitCode));
    } else {
        outputTextEdit->append(tr("File %1 created").arg(targetFile));
    }
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void SeismicU::processError(QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        outputTextEdit->append(tr("Conversion program not found"));
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void SeismicU::updateOutputTextEdit()
{
    QByteArray newData = process.readAllStandardError();
    QString text = outputTextEdit->toPlainText()
                   + QString::fromLocal8Bit(newData);
    outputTextEdit->setPlainText(text);
}
