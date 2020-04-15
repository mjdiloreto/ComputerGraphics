#include "BasicWidget.h"
#include "Obj.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent, std::string objFilename) : QOpenGLWidget(parent), logger_(this)
{
  objFilename_ = objFilename;
  setFocusPolicy(Qt::StrongFocus);
  camera_.setPosition(QVector3D(0.5, 0.5, -2.0));
  camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
  world_.setToIdentity();
}

BasicWidget::~BasicWidget()
{
    for (auto renderable : renderables_) {
        delete renderable;
    }
    renderables_.clear();
}

//////////////////////////////////////////////////////////////////////
// Privates
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  // Handle key events here.
  if (keyEvent->key() == Qt::Key_Left) {
    qDebug() << "Left Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else if (keyEvent->key() == Qt::Key_Right) {
    qDebug() << "Right Arrow Pressed";
    update();  // We call update after we handle a key press to trigger a redraw when we are ready
  } else if (keyEvent->key() == Qt::Key_R) {
    camera_.setPosition(QVector3D(0.5, 0.5, -2.0));
    camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
  } else if (keyEvent->key() == Qt::Key_Q) {
    qDebug() << "q pressed. Exiting application";
    exit(0);
    update(); 
  } else if (keyEvent->key() == Qt::Key_W) {
    qDebug() << "w pressed. Toggling wireframe mode.";
    fillmode = !fillmode;
    update();
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
}

void BasicWidget::mousePressEvent(QMouseEvent* mouseEvent)
{
  if (mouseEvent->button() == Qt::LeftButton) {
    qDebug() << "Left mouse clicked";
    mouseAction_ = Rotate;
  } else if (mouseEvent->button() == Qt::RightButton) {
    qDebug() << "Right mouse clicked";
    mouseAction_ = Zoom;
  }
  lastMouseLoc_ = mouseEvent->pos();
}

void BasicWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
  if (mouseAction_ == NoAction) {
    return;
  }
  QPoint delta = mouseEvent->pos() - lastMouseLoc_;
  lastMouseLoc_ = mouseEvent->pos();
  if (mouseAction_ == Rotate) {
  	camera_.translateLookAt(QVector3D(delta.x()*0.01,delta.y()*0.01,0));
  } else if (mouseAction_ == Zoom) {
  	camera_.setPerspective(lastMouseLoc_.y(), ((float)width())/((float)height()), 0.1f, 20.0f);
  } 
  update();
}

void BasicWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    mouseAction_ = NoAction;
}

void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();

  qDebug() << QDir::currentPath();

  Obj houseObj = Obj(objFilename_);
  QString texFile = QString::fromStdString(houseObj.diffuseTextureFilename);
  QString normFile = QString::fromStdString(houseObj.normalTextureFilename);
  QVector<QVector3D> pos;
  QVector<QVector3D> norm;
  QVector<QVector2D> texCoord;
  QVector<unsigned int> idx;

  for(int i = 0; i < houseObj.combinedPositionData.size(); i+=3) {
      pos << QVector3D(houseObj.combinedPositionData[i], houseObj.combinedPositionData[i+1], houseObj.combinedPositionData[i+2]);
  	  norm << QVector3D(0.0,0.0,0.0); // TODO when we use normals they go here.
  }
  for(int i = 0; i < houseObj.combinedTextureData.size(); i+=2) {
      texCoord << QVector2D(houseObj.combinedTextureData[i], houseObj.combinedTextureData[i+1]);
  }
  for(int i = 0; i < houseObj.combinedIndexes.size(); i++) {
      idx << houseObj.combinedIndexes[i];
  }

  Renderable* ren1 = new Renderable();
  ren1->init(pos, norm, texCoord, idx, texFile, normFile);
  ren1->setRotationAxis(QVector3D(0,1,0));

  renderables_.push_back(ren1);
  emitters_.push_back(new FountainEmitter(&camera_, QVector3D(0,0,0), QVector3D(0,1,0), 10, ren1));

  glViewport(0, 0, width(), height());
  frameTimer_.start();
}

void BasicWidget::resizeGL(int w, int h)
{
    if (!logger_.isLogging()) {
        logger_.initialize();
        // Setup the logger for real-time messaging
        connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=]() {
            const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
            for (auto msg : messages) {
                qDebug() << msg;
            }
            });
        logger_.startLogging();
    }
  glViewport(0, 0, w, h);

  camera_.setPerspective(70.f, (float)w / (float)h, 0.001, 1000.0);
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  qint64 msSinceRestart = frameTimer_.restart();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, fillmode ? GL_FILL : GL_LINE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto emitter: emitters_)
      emitter->update(msSinceRestart);
  
  update();
}
