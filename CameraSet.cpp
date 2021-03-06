﻿#include "CameraSet.h"
#include <QtWidgets/QApplication>
//#include <QtWidgets/QPainter>
#include <QtWidgets>
#include "MyQtMacro.h"




CameraSetWidget::CameraSetWidget( QWidget *parent) : 
QWidget(parent,Qt::WindowFlags(Qt::MSWindowsOwnDC))
{

	up_flag = true;
	
	QTextCodec* tc = QTextCodec::codecForLocale();

	QVBoxLayout *layout = new QVBoxLayout;

	QVBoxLayout *lightposLayout =  new QVBoxLayout();
	LightXspinBox = SetDoubleSpinBox(tc->toUnicode("X"), 10000.0, -10000.0, lightposLayout);
	LightXspinBox->setValue(0);
	connect(LightXspinBox, SIGNAL(valueChanged(double)), this, SLOT(LightXSlot(double)));
	LightYspinBox = SetDoubleSpinBox(tc->toUnicode("Y"), 10000.0, -10000.0, lightposLayout);
	LightYspinBox->setValue(-10000);
	connect(LightYspinBox, SIGNAL(valueChanged(double)), this, SLOT(LightYSlot(double)));
	LightZspinBox = SetDoubleSpinBox(tc->toUnicode("Z"), 10000.0, -10000.0, lightposLayout);
	LightZspinBox->setValue(10000);
	connect(LightZspinBox, SIGNAL(valueChanged(double)), this, SLOT(LightZSlot(double)));
	QGroupBox *lightposGroup = new QGroupBox(tc->toUnicode("光源の位置"));
	lightposGroup->setLayout(lightposLayout);
	layout->addWidget(lightposGroup);

	QVBoxLayout *shadowcolorLayout =  new QVBoxLayout();
	ShadowRspinBox = SetDoubleSpinBox(tc->toUnicode("赤"), 1, 0, shadowcolorLayout);
	ShadowRspinBox->setValue(0.5);
	ShadowRspinBox->setSingleStep(0.1);
	connect(ShadowRspinBox, SIGNAL(valueChanged(double)), this, SLOT(ShadowRSlot(double)));
	ShadowGspinBox = SetDoubleSpinBox(tc->toUnicode("緑"), 1, 0, shadowcolorLayout);
	ShadowGspinBox->setValue(0.5);
	ShadowGspinBox->setSingleStep(0.1);
	connect(ShadowGspinBox, SIGNAL(valueChanged(double)), this, SLOT(ShadowGSlot(double)));
	ShadowBspinBox = SetDoubleSpinBox(tc->toUnicode("青"), 1, 0, shadowcolorLayout);
	ShadowBspinBox->setValue(0.5);
	ShadowBspinBox->setSingleStep(0.1);
	connect(ShadowBspinBox, SIGNAL(valueChanged(double)), this, SLOT(ShadowBSlot(double)));
	QGroupBox *shadowcolorGroup = new QGroupBox(tc->toUnicode("影の色"));
	shadowcolorGroup->setLayout(shadowcolorLayout);
	layout->addWidget(shadowcolorGroup);

	QVBoxLayout *posLayout =  new QVBoxLayout();
	PosXspinBox = SetDoubleSpinBox(tc->toUnicode("X"), 10000.0, -10000.0, posLayout);
	connect(PosXspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosXSlot(double)));
	PosYspinBox = SetDoubleSpinBox(tc->toUnicode("Y"), 10000.0, -10000.0, posLayout);
	connect(PosYspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosYSlot(double)));
	PosZspinBox = SetDoubleSpinBox(tc->toUnicode("Z"), 10000.0, -10000.0, posLayout);
	connect(PosZspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosZSlot(double)));
	QGroupBox *posGroup = new QGroupBox(tc->toUnicode("カメラの位置"));
	posGroup->setLayout(posLayout);
	layout->addWidget(posGroup);

	QVBoxLayout *angleLayout =  new QVBoxLayout();
	RollspinBox = SetDoubleSpinBox(tc->toUnicode("Roll"), 360.0, 0.0, angleLayout);
	RollspinBox->setValue(45);
	connect(RollspinBox, SIGNAL(valueChanged(double)), this, SLOT(RollSlot(double)));
	PitchspinBox = SetDoubleSpinBox(tc->toUnicode("Pitch"), 360.0, 0.0, angleLayout);
	PitchspinBox->setValue(0);
	connect(PitchspinBox, SIGNAL(valueChanged(double)), this, SLOT(PitchSlot(double)));
	YawspinBox = SetDoubleSpinBox(tc->toUnicode("Yaw"), 360.0, 0.0, angleLayout);
	YawspinBox->setValue(0);
	connect(YawspinBox, SIGNAL(valueChanged(double)), this, SLOT(YawSlot(double)));
	QGroupBox *angleGroup = new QGroupBox(tc->toUnicode("カメラの姿勢"));
	angleGroup->setLayout(angleLayout);
	layout->addWidget(angleGroup);

	LenspinBox = SetDoubleSpinBox(tc->toUnicode("距離"), 10000.0, 0.0, layout);
	LenspinBox->setValue(1500.0);
	connect(LenspinBox, SIGNAL(valueChanged(double)), this, SLOT(LenSlot(double)));


	layout->addStretch();


	

	


	




	setLayout(layout);
}

//----------------------------------------------------------------------------------------

CameraSetWidget::~CameraSetWidget(void)
{

}


void CameraSetWidget::UpdatePos()
{
	if(up_flag)
	{
		float px = PosXspinBox->value();
		float py = PosYspinBox->value();
		float pz = PosZspinBox->value();


		if(EC)
		{
			EC->SetCameraPosition(px, py, pz);

		}
	}
}

void CameraSetWidget::UpdatePQ()
{
	if(up_flag)
	{
		float px = PosXspinBox->value();
		float py = PosYspinBox->value();
		float pz = PosZspinBox->value();

		float roll = RollspinBox->value();
		float pitch = PitchspinBox->value();
		float yaw = YawspinBox->value();

		float len = LenspinBox->value();



		if(EC)
		{
			

			//std::cout << px << "\t" << py << "\t" << pz << "\t" << roll << "\t" << pitch << "\t" << yaw << "\t" << len << std::endl;
			EC->UpdateCameraPQ(px,py,pz,roll,pitch,yaw,len);
		}
	}


}

void CameraSetWidget::UpdateRot()
{
	if(up_flag)
	{
		float roll = RollspinBox->value();
		float pitch = PitchspinBox->value();
		float yaw = YawspinBox->value();


		if(EC)
		{
			EC->SetCameraRotation(roll,pitch,yaw);
			

		}
	}
}

void CameraSetWidget::UpdateColor()
{
	if(up_flag)
	{
		float red = ShadowRspinBox->value();
		float green = ShadowGspinBox->value();
		float blue = ShadowBspinBox->value();


		if(EC)
		{
			EC->SetShadowColour(red, green, blue);

		}
	}
}


void CameraSetWidget::UpdateLightPos()
{
	if(up_flag)
	{
		float lx = LightXspinBox->value();
		float ly = LightYspinBox->value();
		float lz = LightZspinBox->value();


		if(EC)
		{
			EC->SetLightPosition(lx, ly, lz);

		}
	}
}

void CameraSetWidget::LightXSlot(double value)
{
	UpdateLightPos();
}
void CameraSetWidget::LightYSlot(double value)
{
	UpdateLightPos();
}
void CameraSetWidget::LightZSlot(double value)
{
	UpdateLightPos();
}

void CameraSetWidget::ShadowRSlot(double value)
{
	UpdateColor();
}
void CameraSetWidget::ShadowGSlot(double value)
{
	UpdateColor();
}
void CameraSetWidget::ShadowBSlot(double value)
{
	UpdateColor();
}

void CameraSetWidget::PosXSlot(double value)
{
	UpdatePQ();
}
void CameraSetWidget::PosYSlot(double value)
{
	UpdatePQ();
}
void CameraSetWidget::PosZSlot(double value)
{
	UpdatePQ();
}

void CameraSetWidget::RollSlot(double value)
{
	UpdatePQ();
}
void CameraSetWidget::PitchSlot(double value)
{
	UpdatePQ();
}
void CameraSetWidget::YawSlot(double value)
{
	UpdatePQ();
}

void CameraSetWidget::LenSlot(double value)
{
	UpdatePQ();
}


void CameraSetWidget::UpdateList()
{
	if(EC)
	{
		up_flag = false;
		PosXspinBox->setValue(EC->CamX);
		PosYspinBox->setValue(EC->CamY);
		PosZspinBox->setValue(EC->CamZ);

		RollspinBox->setValue(EC->CamRoll);
		PitchspinBox->setValue(EC->CamPitch);
		YawspinBox->setValue(EC->CamYaw);

		
		LenspinBox->setValue(EC->CamLen);

		LightXspinBox->setValue(EC->LightX);
		LightYspinBox->setValue(EC->LightY);
		LightZspinBox->setValue(EC->LightZ);

		ShadowRspinBox->setValue(EC->ShadowR);
		ShadowGspinBox->setValue(EC->ShadowG);
		ShadowBspinBox->setValue(EC->ShadowB);
		up_flag = true;
	}
}

void CameraSetWidget::mouseMoveSlot(QMouseEvent*  evt, int dx, int dy)
{
	if(EC)
	{
		if(EC->CameraFlag && EC->JudgeMouseOnGUI(evt->pos().x(), evt->pos().y()) == false)
		{
			for(int i=0;i < EC->QtLinks.size();i++)
			{
				if(EC->QtLinks[i]->mNode->bound_visi)
				{
					return;
				}
			}
			
			if((evt->buttons() & Qt::LeftButton) && (evt->buttons() & Qt::RightButton))
			{
				if(EC->CamLen > 0)
				{
					EC->CamLen = EC->CamLen + EC->CamLen * dy/200.;
					LenspinBox->setValue(EC->CamLen);
				}
				
			}
			else if(evt->buttons() & Qt::LeftButton)
			{
				up_flag = false;
				float px = EC->CamLen * (float)dx / 2000.;
				float py = -EC->CamLen * (float)dy / 2000.;
				EC->MoveCameraPos(px, py);
				up_flag = true;
			}
			else if(evt->buttons() & Qt::RightButton)
			{
				up_flag = false;
				float px = (float)dx/4;
				float py = (float)dy/4;
				EC->MoveCameraRot(px, py);
				up_flag = true;
				
			}
			
			
			UpdateList();
		}
	}
}

void CameraSetWidget::mousePressSlot(QMouseEvent*  evt)
{
	if(EC)
	{
		up_flag = false;
		
		up_flag = true;
	}
}

void CameraSetWidget::mouseReleaseSlot(QMouseEvent*  evt)
{
	if(EC)
	{
		up_flag = false;

		up_flag = true;
	}
}


