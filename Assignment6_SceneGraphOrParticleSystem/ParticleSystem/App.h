/**
 * The primary application code.
 */

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class App : public QMainWindow
{
  Q_OBJECT

public:
  App(QWidget* parent=0, std::string objFilename="", int particlesRate=15);
  virtual ~App();
  
signals:

public slots:

private:
  void buildGui(std::string objFilename, int particlesRate);
};
