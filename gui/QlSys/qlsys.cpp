#include "qlsys.h"
#include "ui_qlsys.h"

#include "lswidget.h"
#include <QFileDialog>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QTime>
#include <QInputDialog>
#include "../../src/fileinput.h"

QlSys::QlSys(QWidget *parent)
	:QMainWindow(parent), ui(new Ui::QlSysClass), lsys(0), opengl(0), povsettings("+W800 +H600 +Q11 +A0.1")
{
	ui->setupUi(this);
	ui->centralWidget->setEnabled(false);
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openClicked()));
	connect(ui->spinIteration, SIGNAL(valueChanged(int)), this, SLOT(iterationsChanged(int)));
	connect(ui->btnRender, SIGNAL(clicked()), this, SLOT(renderClicked()));
	connect(ui->btnRendClose, SIGNAL(clicked()), this, SLOT(renderCloseClicked()));
	connect(ui->chkLineMode, SIGNAL(stateChanged(int)), this, SLOT(testRerender()));
	connect(ui->chkRound, SIGNAL(stateChanged(int)), this, SLOT(testRerender()));
	connect(ui->btnRendPov, SIGNAL(clicked()), this, SLOT(povRenClicked()));
	connect(ui->btnPovSet, SIGNAL(clicked()), this, SLOT(povSetClicked()));
	connect(ui->btnPov, SIGNAL(clicked()), this, SLOT(expPovClicked()));
	connect(ui->sldRot, SIGNAL(valueChanged(int)), this, SLOT(testRerender()));
}

QlSys::~QlSys(){
	delete ui;
}

void QlSys::openClicked(){
	if (!lsys){
		delete lsys;
	}
	lsys = new LSystem();

	QString filename = QFileDialog::getOpenFileName(this, "Open", ui->txtFilename->text(), "XML L-System (*.xml)");
	if (!filename.isNull()){
		if (read_file(filename.toStdString(), *lsys)==0){
			ui->txtFilename->setText(filename);
			ui->centralWidget->setEnabled(true);
			ui->spinIteration->setValue(0);
		}else{
			QMessageBox::critical(this, "Error", "Unable to parse file");
		}
	}
}

void QlSys::iterationsChanged(int i){
	this->doiterate(i);
	QString len;
	len.setNum(lsys->it->length(), 10);
	ui->txtStrlen->setText(len);
	this->testRerender();
}

void QlSys::renderClicked(){
	this->docalculate();
	if (!opengl){
		opengl = new Engine();
		opengl->init(800, 600);
	}
	this->dorender();
}

void QlSys::renderCloseClicked(){
	ui->chkAutorender->setChecked(false);
	delete opengl;
	opengl=0;
	ui->chkAutorender->setChecked(false);
}

void QlSys::expPovClicked(){
	QString filename = QFileDialog::getSaveFileName(this, "Export", ui->txtFilename->text()+".pov", "POVRay file (*.pov)");
	if (!filename.isNull()){
		lsys->c->draw2(filename.toStdString().c_str(), lsys->cm);
	}
}

void QlSys::povRenClicked(){
	this->docalculate();
	QString filename = QDir::tempPath().append("/tmppov.pov");
	lsys->c->draw2(filename.toStdString().c_str(), lsys->cm);
	QProcess pr;
	QStringList args = povsettings.split(" ");
	args << filename;
	pr.start("povray", args);
	if (!pr.waitForStarted()){
		QMessageBox::critical(this, "Error", "Unable to start povray");
		return;
	}

	if (!pr.waitForFinished(-1)){
		QMessageBox::critical(this, "Error", "povray returned with error");
		return;
	}

	QProcess view;
	QStringList args2;
	args2 << "tmppov.png";
	view.start("xdg-open", args2);
	view.waitForStarted();
	view.waitForFinished(5000);
}

void QlSys::povSetClicked(){
	bool ok;
	QString set=QInputDialog::getText(this, "Input", "POVRay command line options:", QLineEdit::Normal, povsettings, &ok);
	if (ok){
		povsettings = set;
	}
}

void QlSys::testRerender(){
	if (ui->chkAutorender->isChecked()){
		this->renderClicked();
	}
}

void QlSys::doiterate(int i){
	ui->statusBar->showMessage("Iterating...");
	qApp->processEvents();
	QTime t = QTime::currentTime();
	lsys->it->setIteration(i);
	int diff=t.msecsTo(QTime::currentTime());
	QString s;
	s.setNum(diff, 10);
	s.append(" ms");
	ui->txtIttime->setText(s);
	ui->statusBar->showMessage("Ready...", 5000);
}

void QlSys::docalculate(){
	ui->statusBar->showMessage("Calculating geometry...");
	qApp->processEvents();
	QTime t = QTime::currentTime();
	lsys->c->calculate(lsys);
	int diff=t.msecsTo(QTime::currentTime());
	QString s;
	s.setNum(diff, 10);
	s.append(" ms");
	ui->txtCalctime->setText(s);
	s.setNum(lsys->c->countLines(), 10);
	ui->txtCyl->setText(s);
	s.setNum(lsys->c->countTriangles(), 10);
	ui->txtTria->setText(s);
	ui->statusBar->showMessage("Ready...", 5000);
}

void QlSys::dorender(){
	ui->statusBar->showMessage("Rendering...");
	qApp->processEvents();
	QTime t = QTime::currentTime();
	opengl->clear();
	opengl->setRoundCylinder(ui->chkRound->isChecked());
	opengl->setLinePlain(ui->chkLineMode->isChecked());
	lsys->c->draw(opengl, ui->sldRot->value(), lsys->cm);
	int diff=t.msecsTo(QTime::currentTime());
	QString s;
	s.setNum(diff, 10);
	s.append(" ms");
	ui->txtRendertime->setText(s);
	ui->statusBar->showMessage("Ready", 5000);
}
