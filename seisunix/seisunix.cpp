#include <QtGui>
#include "seisunix.h"

SeisUnix::SeisUnix(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QPushButton *convertButton =
            buttonBox->button(QDialogButtonBox::Ok);
    convertButton->setText(tr("&Run"));
    convertButton->setEnabled(true);
    outputTextEdit->append("Lol" );

    connect(convertButton, SIGNAL(clicked()),
            this, SLOT(convertImage()));
//  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(&process, SIGNAL(readyReadStandardOutput()),
            this, SLOT(updateOutputTextEdit()));

//  connect(&process, SIGNAL(readyReadStandardError()),
//          this, SLOT(updateOutputTextEdit()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(&process, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(processError(QProcess::ProcessError)));
}

void SeisUnix::convertImage()
{
    outputTextEdit->clear();
	
	QFile file("script.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	// I just added this line to test some things 
	QTextStream out(&file);
	out << "#!/bin/bash\n";
	out << "echo Thunder" << endl;

    QStringList args;
	args << "script.txt";

//  if (enhanceCheckBox->isChecked())
//      args << "-enhance";
//  if (monochromeCheckBox->isChecked())
//      args << "-monochrome";
	
    outputTextEdit->append(args.at(0));
	QStringList env = QProcess::systemEnvironment();
	process.setEnvironment(env);
	env << "CWPROOT=/opt/SU"; 
	env << "PATH=$PATH:/opt/SU/bin"; 
	process.start("sh", args);
	// process.start("/Users/Naix/Tmp/viper-sugui/script.sh");
//	process.start("/opt/SU/src/demos/Synthetic/Finite_Difference/Sufdmod2/XDemo3");
}

void SeisUnix::processFinished(int exitCode,
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

void SeisUnix::processError(QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        outputTextEdit->append(tr("Conversion program not found"));
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}
