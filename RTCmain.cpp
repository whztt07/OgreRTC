﻿// -*- C++ -*-
/*!
 * @file Test1Comp.cpp
 * @brief Standalone component
 * @date $Date$
 *
 * $Id$
 */


#include <iostream>
#include <string>
#include <stdlib.h>

#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>





int main (int argc, char** argv)
{
  
  int _argc = 1;
  QApplication app(_argc, argv);
  MainWindow mainWindow(argc, argv);
  mainWindow.show();
  app.exec();


  // If you want to run the manager in non-blocking mode, do like this
  // manager->runManager(true);

  return 0;
}
