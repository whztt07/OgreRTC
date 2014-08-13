#include <QtGui>
#include <QLabel>
#include <QTextEdit>
#include <qfont.h>
#include <QThread>

#include "mainwindow.h"
#include "OgreWidget.h"
















MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
	
	tc = QTextCodec::codecForLocale();
	
	
	

	QHBoxLayout *layout = new QHBoxLayout;
	


	mOgreWidget = new OgreWidget() ;
	
	

	
	
	layout->addWidget(mOgreWidget);

	tabWidget = new QTabWidget;


	mBodySetWidget = new BodySetWidget();
	tabWidget->addTab(mBodySetWidget, tc->toUnicode("�{�f�B"));
	mBornSetWidget = new BornSetWidget();
	tabWidget->addTab(mBornSetWidget, tc->toUnicode("�{�[��"));
	mCameraSetWidget = new CameraSetWidget();
	tabWidget->addTab(mCameraSetWidget, tc->toUnicode("�J����"));
	mGUISetWidget = new GUISetWidget();
	tabWidget->addTab(mGUISetWidget, tc->toUnicode("CEGUI"));
	mGUITextSetWidget = new GUITextSetWidget();
	tabWidget->addTab(mGUITextSetWidget, tc->toUnicode("CEGUI�̃e�L�X�g"));
	mImageSetWidget = new ImageSetWidget();
	tabWidget->addTab(mImageSetWidget, tc->toUnicode("CEGUI�̉摜"));
	mParticleSetWidget = new ParticleSetWidget();
	tabWidget->addTab(mParticleSetWidget, tc->toUnicode("�p�[�e�B�N��"));
	mSubWindowSetWidget = new SubWindowSetWidget();
	tabWidget->addTab(mSubWindowSetWidget, tc->toUnicode("��ʕ���"));
	mAnimationSetWidget = new AnimationSetWidget();
	tabWidget->addTab(mAnimationSetWidget, tc->toUnicode("�A�j���[�V����"));
	mLightSetWidget = new LightSetWidget();
	tabWidget->addTab(mLightSetWidget, tc->toUnicode("����"));
	mNodeSetWidget = new NodeSetWidget();
	tabWidget->addTab(mNodeSetWidget, tc->toUnicode("�m�[�h"));
	mSimulationSetWidget = new SimulationSetWidget();
	tabWidget->addTab(mSimulationSetWidget, tc->toUnicode("�����V�~�����[�V����(�ݒ�)"));
	mSimBodySetWidget = new SimBodySetWidget();
	tabWidget->addTab(mSimBodySetWidget, tc->toUnicode("�����V�~�����[�V����(�{�f�B)"));
	mSimJointSetWidget = new SimJointSetWidget();
	tabWidget->addTab(mSimJointSetWidget, tc->toUnicode("�����V�~�����[�V����(�W���C���g)"));
	mOtherSetWidget = new OtherSetWidget();
	tabWidget->addTab(mOtherSetWidget, tc->toUnicode("���̑�"));

	connect(mBodySetWidget, SIGNAL(UpdateBody()), mBornSetWidget, SLOT(UpdateBody()));
	connect(mGUISetWidget, SIGNAL(UpdateGUI()), mGUITextSetWidget, SLOT(UpdateGUI()));
	connect(mGUISetWidget, SIGNAL(UpdateGUI()), mImageSetWidget, SLOT(UpdateGUI()));


	connect(this, SIGNAL(UpdateList()), mBodySetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mCameraSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mGUISetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mGUITextSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mImageSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mParticleSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mSubWindowSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mAnimationSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mLightSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mNodeSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mSimulationSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mSimBodySetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mSimJointSetWidget, SLOT(UpdateList()));
	connect(this, SIGNAL(UpdateList()), mOtherSetWidget, SLOT(UpdateList()));

	connect(mBodySetWidget, SIGNAL(UpdateBody()), mNodeSetWidget, SLOT(UpdateList()));
	connect(mParticleSetWidget, SIGNAL(UpdateParticle()), mNodeSetWidget, SLOT(UpdateList()));
	connect(mAnimationSetWidget, SIGNAL(UpdateAnimation()), mNodeSetWidget, SLOT(UpdateList()));
	connect(mLightSetWidget, SIGNAL(UpdateLight()), mNodeSetWidget, SLOT(UpdateList()));
	connect(mSimBodySetWidget, SIGNAL(UpdateODEBody()), mNodeSetWidget, SLOT(UpdateList()));
	connect(mSimJointSetWidget, SIGNAL(UpdateODEJoint()), mNodeSetWidget, SLOT(UpdateList()));

	connect(mSimBodySetWidget, SIGNAL(UpdateODEBody()), mSimJointSetWidget, SLOT(UpdateList()));
	
	connect(mOgreWidget, SIGNAL(mouseMoveSignal(QMouseEvent*, int, int)), mCameraSetWidget, SLOT(mouseMoveSlot(QMouseEvent*, int, int)));
	connect(mOgreWidget, SIGNAL(mousePressSignal(QMouseEvent*)), mCameraSetWidget, SLOT(mousePressSlot(QMouseEvent*)));
	connect(mOgreWidget, SIGNAL(mouseReleaseSignal(QMouseEvent*)), mCameraSetWidget, SLOT(mouseReleaseSlot(QMouseEvent*)));

	connect(mOgreWidget, SIGNAL(mouseMoveSignal(QMouseEvent*, int, int)), mBodySetWidget, SLOT(mouseMoveSlot(QMouseEvent*, int, int)));
	connect(mOgreWidget, SIGNAL(mousePressSignal(QMouseEvent*)), mBodySetWidget, SLOT(mousePressSlot(QMouseEvent*)));
	connect(mOgreWidget, SIGNAL(mouseReleaseSignal(QMouseEvent*)), mBodySetWidget, SLOT(mouseReleaseSlot(QMouseEvent*)));


		
	QVBoxLayout *alayout = new QVBoxLayout;
	alayout->addWidget(tabWidget);
	QWidget *awidget = new QWidget;
	awidget->setLayout(alayout);

	tabWidget->setMinimumSize(250, 768);
	tabWidget->setMaximumWidth(250);

	QScrollArea *area = new QScrollArea();
	area->setWidget(awidget);
	area->setMaximumSize(300, 708);
	area->setMinimumSize(300, 708);
	
	layout->addWidget(area);
	

	

	
	QWidget *widget = new QWidget;
	
    widget->setLayout(layout);
	widget->setMinimumSize(1244, 708);

	setCentralWidget(widget);

	
	

	

	setWindowTitle(tr("OgreRTC"));
    setUnifiedTitleAndToolBarOnMac(true);

	mOgreWidget->initOgre();

	EC = mOgreWidget->mOgreRTCApplication;
	mBodySetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mBornSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mCameraSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mGUISetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mGUITextSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mImageSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mParticleSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mSubWindowSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mAnimationSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mLightSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mNodeSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mSimulationSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mSimBodySetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mSimJointSetWidget->EC = mOgreWidget->mOgreRTCApplication;
	mOtherSetWidget->EC = mOgreWidget->mOgreRTCApplication;


	

	createAction();
	createMenus();

	


}


void MainWindow::createAction()
{
	newAct = new QAction(tr("&New..."),this);
	newAct->setShortcuts(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));


	openAct = new QAction(tr("&Open..."),this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	pyAct = new QAction(tr("&Open Python..."),this);
    connect(pyAct, SIGNAL(triggered()), this, SLOT(pyOpen()));


    saveAct = new QAction(tr("&Save"),this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	addFileSystemAct = new QAction(tr("&Add FileSystem"),this);
    connect(addFileSystemAct, SIGNAL(triggered()), this, SLOT(addFileSystem()));
}


void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(pyAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
	fileMenu->addAction(addFileSystemAct);
	

}


void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
							tc->toUnicode("�J��"), "",
							tr("Text File (*.txt);;All Files (*)"));
	if (fileName.isEmpty())
        return;

	


	
	

	std::string ba = fileName.toLocal8Bit();
	
	if(EC)
	{
		EC->StopFile();
		EC->openb(ba);

		

		
		

		emit UpdateList();

	}


	

}

void MainWindow::pyOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this,
							tc->toUnicode("�X�N���v�g���J��"), "",
							tr("Python File (*.py);;All Files (*)"));

	if (fileName.isEmpty())
        return;

	
	

	std::string ba = fileName.toLocal8Bit();

	std::string tmp = Replace(ba,"\\","/");

	if(EC)
	{
		EC->reset();
		

		

		EC->OpenFile(tmp.c_str());


	}

	


	

}

bool MainWindow::save()
{
	QString fileName = QFileDialog::getSaveFileName(this,
							tc->toUnicode("�ۑ�"), "",
							tr("Text File (*.txt);;All Files (*)"));
	if (fileName.isEmpty())
        return false;

	std::string ba = fileName.toLocal8Bit();

	
	
	if(EC)
	{
		EC->save(ba);

		
		

		
		

		


	}

    return true;
}


void MainWindow::newFile()
{
	if(EC)
	{
		EC->newfile();

		

		


		emit UpdateList();
	}
}

void MainWindow::addFileSystem()
{
	QString fileName = QFileDialog::getExistingDirectory(this,
							tc->toUnicode("�t�@�C���V�X�e���̒ǉ�"));
	if (fileName.isEmpty())
        return;

	fileName = QFileInfo(fileName).canonicalFilePath();

	//std::cout << fileName.toStdString() << std::endl;

	std::string ba = fileName.toLocal8Bit();

	if(EC)
	{
		EC->AddFileSystem(ba.c_str());
	}
}