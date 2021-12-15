/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "import_dlg.h"
//#include <QtGui/QWidget>
#include <QtWidgets/QMessageBox>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QToolTip>
#include "fileLoader.h"

ImportDLG::ImportDLG(QWidget *parent)
:QDialog(parent)
{
	m_ui.setupUi(this);

	connect(m_ui.closeButton,SIGNAL(clicked()),this,SLOT(close()));
	connect(m_ui.btn_ImportFileSelect,SIGNAL(clicked()),this,SLOT(GetVolumeFile()));
	connect(m_ui.btn_SinoOutputDir,SIGNAL(clicked()),this,SLOT(GetSinoOutDir()));
	connect(m_ui.btn_ImportConvert,SIGNAL(clicked()),this,SLOT(ImportConvert()));

	m_ui.lineEdit_VolumeFile->installEventFilter(this);
	m_ui.lineEdit_SinoOutDir->installEventFilter(this);
}

////////////////////
//-ju- Event filter
////////////////////////////////////////////////////////////////////////////////////
bool ImportDLG::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if(targetCtrl == m_ui.lineEdit_VolumeFile)
	{
		if(event->type() == QEvent::ToolTip)
		{
           QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
			if(m_ui.lineEdit_VolumeFile->text().isEmpty())
			{
				QToolTip::showText(helpEvent->globalPos(),tr("<empty>"));
			}
			else
			{
				QToolTip::showText(helpEvent->globalPos(),m_ui.lineEdit_VolumeFile->text());				
			}
		}
	}
	if(targetCtrl == m_ui.lineEdit_SinoOutDir)
	{
		if(event->type() == QEvent::ToolTip)
		{
           QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
			if(m_ui.lineEdit_SinoOutDir->text().isEmpty())
			{
				QToolTip::showText(helpEvent->globalPos(),tr("<empty>"));
			}
			else
			{
				QToolTip::showText(helpEvent->globalPos(),m_ui.lineEdit_SinoOutDir->text());				
			}
		}
	}
	return QDialog::eventFilter(targetCtrl,event);
}

// slots
/////////
void ImportDLG::GetVolumeFile()
{
	QString file =
		QFileDialog::getOpenFileName(this,
		tr("Select Import Volume File"),
		tr("C:\\"),
		tr("Volume File (*.pru)"));

	QFileInfo fInfo(file);

	if(!file.endsWith(tr(".pru"),Qt::CaseInsensitive))
	{
		QString msg(tr("Can not open file: "));
		msg += file;
		QMessageBox::warning(this,tr("Error Open File"),msg);
		return;
	}
	m_completeBaseInputName = file.remove(QRegExp("\\.pru$"));
	m_ui.lineEdit_VolumeFile->clear();
	m_ui.lineEdit_VolumeFile->setText(m_completeBaseInputName);
	m_temDir = fInfo.absolutePath();
}

void ImportDLG::GetSinoOutDir()
{
	QFileDialog::Options mode = QFileDialog::Directory;
	m_outputDir = 
		QFileDialog::getExistingDirectory(0, 
		tr("Select Directory for Output Sinograms"), 
		m_temDir,
		QFileDialog::ShowDirsOnly);
	if(m_outputDir.isEmpty())
	{
		return;
	}
	m_ui.lineEdit_SinoOutDir->clear();
	m_temDir = m_outputDir;
	m_ui.lineEdit_SinoOutDir->setText(m_outputDir);
}

void ImportDLG::ImportConvert()
{
	m_ui.progressBar->setValue(1);
	int w = m_ui.spinBox_imgWidth->value();
	int h = m_ui.spinBox_ImgHeight->value();
	float bhc = static_cast<float>(m_ui.doubleSpinBox_BHC->value());
	float flatCorrFac = m_ui.doubleSpinBox_FlatCorrFac->value();
	fileLoader importer(w,h,bhc,flatCorrFac,&m_ui);
	if(m_completeBaseInputName.isEmpty())
	{
		QMessageBox::warning(this,tr("Missing Parameter"),tr("Missing volume file"));
		m_ui.lineEdit_VolumeFile->setFocus();
		return;
	}
	if(m_outputDir.isEmpty())
	{
		QMessageBox::warning(this,tr("Missing Parameter"),tr("Missing output directory"));
		m_ui.lineEdit_SinoOutDir->setFocus();
		return;
	}
	QString sinoOut = m_ui.lineEdit__SinoBaseName->text();
	if(sinoOut.isEmpty())
	{
		QMessageBox::warning(this,tr("Missing Parameter"),tr("Missing sinogram base name"));
		m_ui.lineEdit__SinoBaseName->setFocus();
		return;
	}
	QString outFile = m_outputDir + "\\" + sinoOut;
	m_ui.closeButton->setEnabled(false);
	importer.loadAll(m_completeBaseInputName.toStdString(),outFile.toStdString());
	m_ui.closeButton->setEnabled(true);
}