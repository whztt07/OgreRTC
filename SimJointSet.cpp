﻿#include "SimJointSet.h"

#include "MyQtMacro.h"
#include <QtWidgets/QApplication>
//#include <QtWidgets/QPainter>
#include <QtWidgets>

#include "MyODEBody.h"
#include "MyODEJoint.h"


SimJointSetWidget::SimJointSetWidget( QWidget *parent) : 
QWidget(parent,Qt::WindowFlags(Qt::MSWindowsOwnDC))
{
	up_flag = true;
	QTextCodec* tc = QTextCodec::codecForLocale();

	QVBoxLayout *layout = new QVBoxLayout;

	NameEdit = new QComboBox();
	NameEdit->setLineEdit(new QLineEdit());
	connect(NameEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(NameSlot(int)));

	layout->addWidget(NameEdit);


	TypeEdit = new QComboBox();
	TypeEdit->addItem("Slider");
	TypeEdit->addItem("Fixed");
	TypeEdit->addItem("Hinge");
	layout->addWidget(TypeEdit);


	SetButton = new QPushButton(tc->toUnicode("作成"));
	connect(SetButton, SIGNAL(clicked()), this, SLOT(SetSlot()));
	layout->addWidget(SetButton);

	Body1Edit = new QComboBox();
	Body1Edit->addItem("Ground");
	layout->addWidget(Body1Edit);

	Body2Edit = new QComboBox();
	Body2Edit->addItem("Ground");
	layout->addWidget(Body2Edit);

	QVBoxLayout *posLayout =  new QVBoxLayout();
	PosXspinBox = SetDoubleSpinBox(tc->toUnicode("X"), 1000.0, -1000.0, posLayout);
	connect(PosXspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosXSlot(double)));
	PosYspinBox = SetDoubleSpinBox(tc->toUnicode("Y"), 1000.0, -1000.0, posLayout);
	connect(PosYspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosYSlot(double)));
	PosZspinBox = SetDoubleSpinBox(tc->toUnicode("Z"), 1000.0, -1000.0, posLayout);
	connect(PosZspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosZSlot(double)));
	QGroupBox *posGroup = new QGroupBox(tc->toUnicode("位置"));
	posGroup->setLayout(posLayout);
	layout->addWidget(posGroup);

	QVBoxLayout *scaleLayout =  new QVBoxLayout();
	ScaleXspinBox = SetDoubleSpinBox(tc->toUnicode("X"), 10000.0, 0.01, scaleLayout);
	ScaleXspinBox->setValue(1);
	connect(ScaleXspinBox, SIGNAL(valueChanged(double)), this, SLOT(ScaleXSlot(double)));
	ScaleYspinBox = SetDoubleSpinBox(tc->toUnicode("Y"), 10000.0, 0.01, scaleLayout);
	ScaleYspinBox->setValue(1);
	connect(ScaleYspinBox, SIGNAL(valueChanged(double)), this, SLOT(ScaleYSlot(double)));
	ScaleZspinBox = SetDoubleSpinBox(tc->toUnicode("Z"), 10000.0, 0.01, scaleLayout);
	ScaleZspinBox->setValue(1);
	connect(ScaleZspinBox, SIGNAL(valueChanged(double)), this, SLOT(ScaleZSlot(double)));
	QGroupBox *scaleGroup = new QGroupBox(tc->toUnicode("拡大率"));
	scaleGroup->setLayout(scaleLayout);
	layout->addWidget(scaleGroup);



	QVBoxLayout *angleLayout =  new QVBoxLayout();
	RollspinBox = SetDoubleSpinBox(tc->toUnicode("X"), 1.0, -1.0, angleLayout);
	RollspinBox->setValue(1.0);
	connect(RollspinBox, SIGNAL(valueChanged(double)), this, SLOT(RollSlot(double)));
	PitchspinBox = SetDoubleSpinBox(tc->toUnicode("Y"), 1.0, -1.0, angleLayout);
	connect(PitchspinBox, SIGNAL(valueChanged(double)), this, SLOT(PitchSlot(double)));
	YawspinBox = SetDoubleSpinBox(tc->toUnicode("Z"), 1.0, -1.0, angleLayout);
	connect(YawspinBox, SIGNAL(valueChanged(double)), this, SLOT(YawSlot(double)));
	QGroupBox *angleGroup = new QGroupBox(tc->toUnicode("軸"));
	angleGroup->setLayout(angleLayout);
	layout->addWidget(angleGroup);



	QVBoxLayout *offsetLayout =  new QVBoxLayout();
	OffsetXspinBox = SetDoubleSpinBox(tc->toUnicode("X"), 10000.0, 0.01, offsetLayout);
	OffsetXspinBox->setValue(1);
	connect(OffsetXspinBox, SIGNAL(valueChanged(double)), this, SLOT(OffsetXSlot(double)));
	OffsetYspinBox = SetDoubleSpinBox(tc->toUnicode("Y"), 10000.0, 0.01, offsetLayout);
	OffsetYspinBox->setValue(1);
	connect(OffsetYspinBox, SIGNAL(valueChanged(double)), this, SLOT(OffsetYSlot(double)));
	OffsetZspinBox = SetDoubleSpinBox(tc->toUnicode("Z"), 10000.0, 0.01, offsetLayout);
	OffsetZspinBox->setValue(1);
	connect(OffsetZspinBox, SIGNAL(valueChanged(double)), this, SLOT(OffsetZSlot(double)));
	QGroupBox *offsetGroup = new QGroupBox(tc->toUnicode("オフセット"));
	offsetGroup->setLayout(offsetLayout);
	layout->addWidget(offsetGroup);


	VisibleButton = new QPushButton(tc->toUnicode("表示"));
	connect(VisibleButton, SIGNAL(clicked()), this, SLOT(VisibleSlot()));
	layout->addWidget(VisibleButton);

	unVisibleButton = new QPushButton(tc->toUnicode("非表示"));
	connect(unVisibleButton, SIGNAL(clicked()), this, SLOT(unVisibleSlot()));
	layout->addWidget(unVisibleButton);
	
	DestroyButton = new QPushButton(tc->toUnicode("削除"));
	connect(DestroyButton, SIGNAL(clicked()), this, SLOT(DestroySlot()));
	layout->addWidget(DestroyButton);


	layout->addStretch();
	
	

	setLayout(layout);
	
}

//----------------------------------------------------------------------------------------

SimJointSetWidget::~SimJointSetWidget(void)
{

}

void SimJointSetWidget::UpdateList()
{
	if(EC)
	{
		NameEdit->clear();
		for(int i=0;i < EC->mSim->QtJoints.size();i++)
		{
			
			NameEdit->addItem(EC->mSim->QtJoints[i]->name.c_str());
		}

		Body1Edit->clear();
		Body1Edit->addItem("Ground");
		for(int i=0;i < EC->mSim->QtLinks.size();i++)
		{
			
			Body1Edit->addItem(EC->mSim->QtLinks[i]->name.c_str());
		}

		Body2Edit->clear();
		Body2Edit->addItem("Ground");
		for(int i=0;i < EC->mSim->QtLinks.size();i++)
		{
			
			Body2Edit->addItem(EC->mSim->QtLinks[i]->name.c_str());
		}
		
	}
}
void SimJointSetWidget::SetSlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	std::string b1n = (const char*)Body1Edit->currentText().toLocal8Bit();
	std::string b2n = (const char*)Body2Edit->currentText().toLocal8Bit();
	int type = TypeEdit->currentIndex();
	double px = PosXspinBox->value();
	double py = PosYspinBox->value();
	double pz = PosZspinBox->value();

	double sx = ScaleXspinBox->value();
	double sy = ScaleYspinBox->value();
	double sz = ScaleZspinBox->value();

	double ox = OffsetXspinBox->value();
	double oy = OffsetYspinBox->value();
	double oz = OffsetZspinBox->value();

	double roll = RollspinBox->value();
	double pitch = PitchspinBox->value();
	double yaw = YawspinBox->value();


	if(EC)
	{
		if(n == "")
		{
			return;
		}
		else if(EC->mSim->getJointByName(n.c_str()))
		{
			return;
		}
		else
		{
			MyODEJoint *ml;
			MyODEBody *b1 = EC->mSim->getBodyByName(b1n.c_str());
			MyODEBody *b2 = EC->mSim->getBodyByName(b2n.c_str());
			if(b1 == NULL && b2 == NULL)
			{
				return;
			}
			else if(b1 == b2)
			{
				return;
			}
			if(type == 0)
			{
				
				if(b1 == NULL)
				{
					ml = EC->mSim->SetQtSliderJoint(n.c_str(), b2, roll, pitch, yaw);
					
				}
				else if(b2 == NULL)
				{
					ml = EC->mSim->SetQtSliderJoint(n.c_str(), b1, roll, pitch, yaw);
					
				}
				else
				{
					ml = EC->mSim->SetQtSliderJoint(n.c_str(), b1, b2, roll, pitch, yaw);
				}
			}
			else if(type == 1)
			{
				if(b1 == NULL)
				{
					ml = EC->mSim->SetQtFixJoint(n.c_str(), b2);
					
				}
				else if(b2 == NULL)
				{
					ml = EC->mSim->SetQtFixJoint(n.c_str(), b1);
					
				}
				else
				{
					ml = EC->mSim->SetQtFixJoint(n.c_str(), b1, b2);
				}
				
			}
			else if(type == 2)
			{
				if(b1 == NULL)
				{
					ml = EC->mSim->SetQtHingeJoint(n.c_str(), b2, px, py, pz, roll, pitch, yaw);
				}
				else if(b2 == NULL)
				{
					ml = EC->mSim->SetQtHingeJoint(n.c_str(), b1, px, py, pz, roll, pitch, yaw);
				}
				else
				{
					ml = EC->mSim->SetQtHingeJoint(n.c_str(), b1, b2, px, py, pz, roll, pitch, yaw);
				}
				
			}
			
			
			if(ml)
			{
				ml->SetJointPosition(px, py, pz);
				ml->SetJointRotation(roll, pitch, yaw);
				ml->SetODEScale(sx, sy, sz);
				ml->SetODEOffset(ox, oy, oz);
			}
			

			
			UpdateList();
			emit UpdateODEJoint();
			NameEdit->setCurrentIndex(NameEdit->count()-1);
			
		}
	}


}
void SimJointSetWidget::NameSlot(int value)
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	if(EC)
	{
		MyODEJoint *ml = EC->mSim->getJointByName(n.c_str());
		if(ml)
		{
			up_flag = false;
			TypeEdit->setCurrentIndex(ml->JointType);
			
			Body1Edit->setCurrentIndex(Body1Edit->findText(ml->b1.c_str()));
			
			Body2Edit->setCurrentIndex(Body2Edit->findText(ml->b2.c_str()));
			
			
			PosXspinBox->setValue(ml->jx);
			PosYspinBox->setValue(ml->jy);
			PosZspinBox->setValue(ml->jz);

			ScaleXspinBox->setValue(ml->bscale_x);
			ScaleYspinBox->setValue(ml->bscale_x);
			ScaleZspinBox->setValue(ml->bscale_x);

			RollspinBox->setValue(ml->axisx);
			PitchspinBox->setValue(ml->axisy);
			YawspinBox->setValue(ml->axisz);


			OffsetXspinBox->setValue(ml->offx);
			OffsetYspinBox->setValue(ml->offy);
			OffsetZspinBox->setValue(ml->offz);


			

			

			up_flag = true;

		}
		
	}
}
void SimJointSetWidget::PosXSlot(double value)
{
	SetPos();
}
void SimJointSetWidget::PosYSlot(double value)
{
	SetPos();
}
void SimJointSetWidget::PosZSlot(double value)
{
	SetPos();
}
void SimJointSetWidget::ScaleXSlot(double value)
{
	SetScale();
}
void SimJointSetWidget::ScaleYSlot(double value)
{
	SetScale();
}
void SimJointSetWidget::ScaleZSlot(double value)
{
	SetScale();
}
void SimJointSetWidget::RollSlot(double value)
{
	SetRot();
}
void SimJointSetWidget::PitchSlot(double value)
{
	SetRot();
}
void SimJointSetWidget::YawSlot(double value)
{
	SetRot();
}
void SimJointSetWidget::VisibleSlot()
{
	SetVisi(true);
}
void SimJointSetWidget::unVisibleSlot()
{
	SetVisi(false);
}



void SimJointSetWidget::DestroySlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();

	

	if(EC)
	{
		MyODEJoint *ml = EC->mSim->getJointByName(n.c_str());
		if(ml)
		{
			EC->mSim->DestroyQtJoint(ml);
			UpdateList();
			emit UpdateODEJoint();


		}
		
	}
}

void SimJointSetWidget::OffsetXSlot(double value)
{
	SetOffset();
}
void SimJointSetWidget::OffsetYSlot(double value)
{
	SetOffset();
}
void SimJointSetWidget::OffsetZSlot(double value)
{
	SetOffset();
}

void SimJointSetWidget::SetPos()
{
	if(up_flag)
	{
		std::string n = (const char*)NameEdit->currentText().toLocal8Bit();

		double px = PosXspinBox->value();
		double py = PosYspinBox->value();
		double pz = PosZspinBox->value();

		if(EC)
		{
			MyODEJoint *ml = EC->mSim->getJointByName(n.c_str());
			if(ml)
			{
				ml->SetJointPosition(px, py, pz);
			}
			
		}
	}
}
void SimJointSetWidget::SetScale()
{
	if(up_flag)
	{
		std::string n = (const char*)NameEdit->currentText().toLocal8Bit();

		double sx = ScaleXspinBox->value();
		double sy = ScaleYspinBox->value();
		double sz = ScaleZspinBox->value();

		if(EC)
		{
			MyODEJoint *ml = EC->mSim->getJointByName(n.c_str());
			if(ml)
			{
				ml->SetODEScale(sx, sy, sz);
			}
			
		}
	}
}
void SimJointSetWidget::SetRot()
{
	if(up_flag)
	{
		std::string n = (const char*)NameEdit->currentText().toLocal8Bit();

		double roll = RollspinBox->value();
		double pitch = PitchspinBox->value();
		double yaw = YawspinBox->value();

		if(EC)
		{
			MyODEJoint *ml = EC->mSim->getJointByName(n.c_str());
			if(ml)
			{
				ml->SetJointRotation(roll, pitch, yaw);
			}
			
		}
	}
}
void SimJointSetWidget::SetOffset()
{
	if(up_flag)
	{
		std::string n = (const char*)NameEdit->currentText().toLocal8Bit();

		double ox = OffsetXspinBox->value();
		double oy = OffsetYspinBox->value();
		double oz = OffsetZspinBox->value();

		if(EC)
		{
			MyODEJoint *ml = EC->mSim->getJointByName(n.c_str());
			if(ml)
			{
				ml->SetODEOffset(ox, oy, oz);
			}
			
		}
	}
}
void SimJointSetWidget::SetVisi(bool visi)
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	if(EC)
	{
		MyODEJoint *ml = EC->mSim->getJointByName(n.c_str());
		if(ml)
		{
			ml->SetVisible(visi);
		}
		
	}
}