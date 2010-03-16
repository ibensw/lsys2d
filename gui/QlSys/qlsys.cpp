#include "qlsys.h"
#include "ui_qlsys.h"

#include <QFileDialog>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QTime>
#include <QInputDialog>
#include "../../src/fileinput.h"
#include "../../src/engine/povengine.h"

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
	connect(ui->btnPov, SIGNAL(clicked()), this, SLOT(expPovClicked()));
	connect(ui->sldRotY, SIGNAL(valueChanged(int)), this, SLOT(testRerender()));
	connect(ui->sldRotZ, SIGNAL(valueChanged(int)), this, SLOT(testRerender()));
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
		try{
			lsys->openfile(filename.toStdString().c_str());
			ui->txtFilename->setText(filename);
			ui->centralWidget->setEnabled(true);
		}catch(const char* err){
			QMessageBox::critical(this, "Error", err);
		}
	}
}

void QlSys::iterationsChanged(int i){
	this->doiterate(i);
	QString len;
	len.setNum(lsys->StringSize(), 10);
	ui->txtStrlen->setText(len);
	this->testRerender();
}

void QlSys::renderClicked(){
	this->docalculate();
	if (!opengl){
		opengl = new OGLEngine(800, 600, "QlSys OpenGL render");
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
		POVEngine pov(filename.toStdString().c_str(), lsys->getColors());
		lsys->render((Engine*)&pov);
	}
}

void QlSys::povRenClicked(){
	//this->docalculate();
	QString filename = QDir::tempPath().append("/tmppov.pov");
	POVEngine pov(filename.toStdString().c_str(), lsys->getColors());
	lsys->render((Engine*)&pov);
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
	lsys->absoluteiterate(i);
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
	lsys->calculate();
	int diff=t.msecsTo(QTime::currentTime());
	QString s;
	s.setNum(diff, 10);
	s.append(" ms");
	ui->txtCalctime->setText(s);
	s.setNum(lsys->CountLines(), 10);
	ui->txtCyl->setText(s);
	s.setNum(lsys->CountTriangles(), 10);
	ui->txtTria->setText(s);
	ui->statusBar->showMessage("Ready...", 5000);
}

void QlSys::dorender(){
	ui->statusBar->showMessage("Rendering...");
	qApp->processEvents();
	opengl->setRoundCylinder(ui->chkRound->isChecked());
	opengl->setLinePlain(ui->chkLineMode->isChecked());
	opengl->rotateY(ui->sldRotY->value());
	opengl->rotateZ(ui->sldRotZ->value());
	QTime t = QTime::currentTime();
	opengl->clear();
	lsys->render(opengl);
	int diff=t.msecsTo(QTime::currentTime());
	QString s;
	s.setNum(diff, 10);
	s.append(" ms");
	ui->txtRendertime->setText(s);
	ui->statusBar->showMessage("Ready", 5000);
}
