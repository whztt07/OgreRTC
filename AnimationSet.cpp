﻿#include "AnimationSet.h"


#include "MyQtMacro.h"

//#include <QtWidgets/QPainter>
#include <QtWidgets>


#include "MyAnimation.h"



AnimationSetWidget::AnimationSetWidget( QWidget *parent) : 
QWidget(parent,Qt::WindowFlags (Qt::MSWindowsOwnDC))
{
	up_flag = true;
	
	QTextCodec* tc = QTextCodec::codecForLocale();

	QVBoxLayout *layout = new QVBoxLayout;

	NameEdit = new QComboBox();
	NameEdit->setLineEdit(new QLineEdit());
	connect(NameEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(NameSlot(int)));

	layout->addWidget(NameEdit);


	SetButton = new QPushButton(tc->toUnicode("作成"));
	connect(SetButton, SIGNAL(clicked()), this, SLOT(SetSlot()));
	layout->addWidget(SetButton);

	DestroyButton = new QPushButton(tc->toUnicode("削除"));
	connect(DestroyButton, SIGNAL(clicked()), this, SLOT(DestroySlot()));
	layout->addWidget(DestroyButton);


	KeyButton = new QPushButton(tc->toUnicode("キーフレーム追加"));
	connect(KeyButton, SIGNAL(clicked()), this, SLOT(KeySlot()));
	layout->addWidget(KeyButton);

	RemoveKeyButton = new QPushButton(tc->toUnicode("キーフレーム削除"));
	connect(RemoveKeyButton, SIGNAL(clicked()), this, SLOT(RemoveKeySlot()));
	layout->addWidget(RemoveKeyButton);

	TimespinBox = SetDoubleSpinBox(tc->toUnicode("終了時間"), 1000.0, 0.0, layout);
	connect(TimespinBox, SIGNAL(valueChanged(double)), this, SLOT(TimeSlot(double)));


	KeyNumspinBox = SetSpinBox(tc->toUnicode("キーフレームの番号"), 0, 0, layout);
	connect(KeyNumspinBox, SIGNAL(valueChanged(int)), this, SLOT(KeyNumSlot(int)));


	KeyTimespinBox = SetDoubleSpinBox(tc->toUnicode("キーフレームの時間"), 0, 0, layout);
	

	StatespinBox = SetDoubleSpinBox(tc->toUnicode("時間"), 0, 0, layout);
	connect(StatespinBox, SIGNAL(valueChanged(double)), this, SLOT(StateSlot(double)));


	QVBoxLayout *posLayout =  new QVBoxLayout();
	PosXspinBox = SetDoubleSpinBox(tc->toUnicode("X"), 1000.0, -1000.0, posLayout);
	connect(PosXspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosXSlot(double)));
	PosYspinBox = SetDoubleSpinBox(tc->toUnicode("Y"), 1000.0, -1000.0, posLayout);
	connect(PosYspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosYSlot(double)));
	PosZspinBox = SetDoubleSpinBox(tc->toUnicode("Z"), 1000.0, -1000.0, posLayout);
	connect(PosZspinBox, SIGNAL(valueChanged(double)), this, SLOT(PosZSlot(double)));
	TransButton = new QPushButton(tc->toUnicode("設定"));
	connect(TransButton, SIGNAL(clicked()), this, SLOT(TransSlot()));
	posLayout->addWidget(TransButton);
	QGroupBox *posGroup = new QGroupBox(tc->toUnicode("位置"));
	posGroup->setLayout(posLayout);
	layout->addWidget(posGroup);

	QVBoxLayout *angleLayout =  new QVBoxLayout();
	RollspinBox = SetDoubleSpinBox(tc->toUnicode("Roll"), 360.0, 0.0, angleLayout);
	connect(RollspinBox, SIGNAL(valueChanged(double)), this, SLOT(RollSlot(double)));
	PitchspinBox = SetDoubleSpinBox(tc->toUnicode("Pitch"), 360.0, 0.0, angleLayout);
	connect(PitchspinBox, SIGNAL(valueChanged(double)), this, SLOT(PitchSlot(double)));
	YawspinBox = SetDoubleSpinBox(tc->toUnicode("Yaw"), 360.0, 0.0, angleLayout);
	connect(YawspinBox, SIGNAL(valueChanged(double)), this, SLOT(YawSlot(double)));
	RotButton = new QPushButton(tc->toUnicode("設定"));
	connect(RotButton, SIGNAL(clicked()), this, SLOT(RotSlot()));
	angleLayout->addWidget(RotButton);
	QGroupBox *angleGroup = new QGroupBox(tc->toUnicode("姿勢"));
	angleGroup->setLayout(angleLayout);
	layout->addWidget(angleGroup);


	

	ResetButton = new QPushButton(tc->toUnicode("初期化"));
	connect(ResetButton, SIGNAL(clicked()), this, SLOT(ResetSlot()));
	layout->addWidget(ResetButton);


	layout->addStretch();
	
	

	setLayout(layout);
	
}

//----------------------------------------------------------------------------------------

AnimationSetWidget::~AnimationSetWidget(void)
{

}

void AnimationSetWidget::UpdatePos()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	int kn = KeyNumspinBox->value();
	float px = PosXspinBox->value();
	float py = PosYspinBox->value();
	float pz = PosZspinBox->value();

	if(up_flag)
	{
		if(EC)
		{
			MyAnimation *man = EC->getAnimationByName(n.c_str());
			if(man)
			{
				
				
				if(kn < man->animList.size())
				{
					if(man->animList[kn]->trans_flag)
					{
						man->animList[kn]->setTranslate(px,py,pz);
					}
				}




			}
			
		}
	}
}
void AnimationSetWidget::UpdateRot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	int kn = KeyNumspinBox->value();
	float roll = RollspinBox->value();
	float pitch = PitchspinBox->value();
	float yaw = YawspinBox->value();

	if(up_flag)
	{
		if(EC)
		{
			MyAnimation *man = EC->getAnimationByName(n.c_str());
			if(man)
			{
				
				
				if(kn < man->animList.size())
				{
					if(man->animList[kn]->rot_flag)
					{
						man->animList[kn]->setRotation(roll,pitch,yaw);
					}
				}




			}
			
		}
	}
}

void AnimationSetWidget::UpdateList()
{
	if(EC)
	{
		NameEdit->clear();
		for(int i=0;i < EC->QtAnimations.size();i++)
		{
			
			NameEdit->addItem(EC->QtAnimations[i]->name.c_str());
		}
		
	}
}


void AnimationSetWidget::SetSlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	

	if(EC)
	{
		if(n == "")
		{
			return;
		}
		else if(EC->getAnimationByName(n.c_str()))
		{
			return;
		}
		else
		{
			MyAnimation *man = EC->CreateQtAnimation(n.c_str(), TimespinBox->value());
			
			

			
			UpdateList();
			NameEdit->setCurrentIndex(NameEdit->count()-1);

			emit UpdateAnimation();
			
		}
	}

	
}

void AnimationSetWidget::NameSlot(int value)
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	if(EC)
	{
		MyAnimation *man = EC->getAnimationByName(n.c_str());
		if(man)
		{
			up_flag = false;
			TimespinBox->setValue(man->Time);
			int msize = man->animList.size()-1;
			if(msize < 0)msize = 0;
			KeyNumspinBox->setMaximum(msize);
			KeyTimespinBox->setMaximum(man->Time);
			StatespinBox->setMaximum(man->Time);
			if(man->animList.size() > 0)
			{
				KeyTimespinBox->setValue(man->animList[0]->mtime);
				if(man->animList[0]->trans_flag)
				{
					PosXspinBox->setValue(man->animList[0]->px);
					PosYspinBox->setValue(man->animList[0]->py);
					PosZspinBox->setValue(man->animList[0]->pz);
				}
				if(man->animList[0]->rot_flag)
				{
					RollspinBox->setValue(man->animList[0]->roll);
					PitchspinBox->setValue(man->animList[0]->pitch);
					YawspinBox->setValue(man->animList[0]->yaw);
				}
			}



			up_flag = true;

		}
		
	}
}

void AnimationSetWidget::TransSlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	int kn = KeyNumspinBox->value();
	float px = PosXspinBox->value();
	float py = PosYspinBox->value();
	float pz = PosZspinBox->value();

	if(up_flag)
	{
		if(EC)
		{
			MyAnimation *man = EC->getAnimationByName(n.c_str());
			if(man)
			{
				
				
				if(kn < man->animList.size())
				{
					
					man->animList[kn]->setTranslate(px,py,pz);
					
				}


			}
			
		}
	}
}

void AnimationSetWidget::RotSlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	int kn = KeyNumspinBox->value();
	float roll = RollspinBox->value();
	float pitch = PitchspinBox->value();
	float yaw = YawspinBox->value();

	if(up_flag)
	{
		if(EC)
		{
			MyAnimation *man = EC->getAnimationByName(n.c_str());
			if(man)
			{
				
				
				if(kn < man->animList.size())
				{
					man->animList[kn]->setRotation(roll,pitch,yaw);

				}


			}
			
		}
	}
}

void AnimationSetWidget::ResetSlot()
{

}

void AnimationSetWidget::DestroySlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();

	if(EC)
	{
		MyAnimation *man = EC->getAnimationByName(n.c_str());
		if(man)
		{
			EC->DestroyQtAnimation(man);
			UpdateList();
			emit UpdateAnimation();
		}
		
	}
}


void AnimationSetWidget::PosXSlot(double value)
{
	UpdatePos();
}
void AnimationSetWidget::PosYSlot(double value)
{
	UpdatePos();
}
void AnimationSetWidget::PosZSlot(double value)
{
	UpdatePos();
}
void AnimationSetWidget::RollSlot(double value)
{
	UpdateRot();
}
void AnimationSetWidget::PitchSlot(double value)
{
	UpdateRot();
}
void AnimationSetWidget::YawSlot(double value)
{
	UpdateRot();
}

void AnimationSetWidget::KeySlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	float t = KeyTimespinBox->value();

	if(EC)
	{
		MyAnimation *man = EC->getAnimationByName(n.c_str());
		if(man)
		{
			man->AddKeyFrame(t);
			int msize = man->animList.size()-1;
			if(msize < 0)msize = 0;
			KeyNumspinBox->setMaximum(msize);
			KeyNumspinBox->setValue(KeyNumspinBox->maximum());
		}
		
	}
}
void AnimationSetWidget::KeyNumSlot(int value)
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	int kn = KeyNumspinBox->value();
	if(EC)
	{
		MyAnimation *man = EC->getAnimationByName(n.c_str());
		if(man)
		{
			up_flag = false;
			if(kn < man->animList.size())
			{
				KeyTimespinBox->setValue(man->animList[kn]->mtime);
				if(man->animList[kn]->trans_flag)
				{
					PosXspinBox->setValue(man->animList[kn]->px);
					PosYspinBox->setValue(man->animList[kn]->py);
					PosZspinBox->setValue(man->animList[kn]->pz);
				}
				if(man->animList[kn]->rot_flag)
				{
					RollspinBox->setValue(man->animList[kn]->roll);
					PitchspinBox->setValue(man->animList[kn]->pitch);
					YawspinBox->setValue(man->animList[kn]->yaw);
				}
			}



			up_flag = true;

		}
		
	}
}
void AnimationSetWidget::RemoveKeySlot()
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	int kn = KeyNumspinBox->value();
	if(EC)
	{
		MyAnimation *man = EC->getAnimationByName(n.c_str());
		if(man)
		{
			if(kn < man->animList.size())
			{
				man->RemoveKeyFrame(man->animList[kn]);
				int msize = man->animList.size()-1;
				if(msize < 0)msize = 0;
				KeyNumspinBox->setMaximum(msize);
			}

		}
		
	}
}
void AnimationSetWidget::StateSlot(double value)
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	float st = StatespinBox->value();
	if(EC)
	{
		MyAnimation *man = EC->getAnimationByName(n.c_str());
		if(man)
		{
			man->SetAnimationState(st);

		}
		
	}
}

void AnimationSetWidget::TimeSlot(double value)
{
	std::string n = (const char*)NameEdit->currentText().toLocal8Bit();
	double t = TimespinBox->value();
	
	if(EC)
	{
		MyAnimation *man = EC->getAnimationByName(n.c_str());
		if(man)
		{
			man->SetLength(t);
			KeyTimespinBox->setMaximum(man->Time);
			StatespinBox->setMaximum(man->Time);
		}
		
	}
}