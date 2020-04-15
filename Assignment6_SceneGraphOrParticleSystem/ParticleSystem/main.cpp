/**
 * Support code written by Erik W. Anderson
 */

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
// Lab application
#include "App.h"
#include <iostream>
#include <cstdlib>

static bool enableGLDebug = true;

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage " << argv[0] << " <.obj file path> <particles per second>" << std::endl;
    return 1;
  }
  // Seed the random number generator for deterministic results
  std::srand(1111);

  QApplication a(argc, argv);
  QString appDir = a.applicationDirPath();
  QDir::setCurrent(appDir);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setStencilBufferSize(8);
  fmt.setVersion(3,3);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  if(enableGLDebug) {
    fmt.setOption(QSurfaceFormat::DebugContext);
  }
  QSurfaceFormat::setDefaultFormat(fmt);
 
 // std::cout << atoi(argv[2]);
  std::string objFilename(argv[1]);//, atoi(argv[2]));
  App app(0, objFilename);
  app.show();
  return QApplication::exec();
}
