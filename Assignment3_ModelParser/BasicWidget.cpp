#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), logger_(this)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
	vbo_.release();
	vbo_.destroy();
	ibo_.release();
	ibo_.destroy();
	vao_.release();
	vao_.destroy();
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
  QString str =
    "#version 330\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec4 color;\n"
    
    "out vec4 vertColor;\n"

    "void main()\n"
    "{\n"
    "  gl_Position = vec4(position, 1.0);\n"
    "  vertColor = color;\n"
    "}\n";
  return str;
}

QString BasicWidget::fragmentShaderString() const
{
  QString str =
	"#version 330\n"
    "in vec4 vertColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"  color = vertColor;\n"
	"}\n";
  return str;
}

void BasicWidget::createShader()
{
  QOpenGLShader vert(QOpenGLShader::Vertex);
  vert.compileSourceCode(vertexShaderString());
  QOpenGLShader frag(QOpenGLShader::Fragment);
  frag.compileSourceCode(fragmentShaderString());
  bool ok = shaderProgram_.addShader(&vert);
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.addShader(&frag);
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.link();
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  if (keyEvent->key() == Qt::Key_W) {
    qDebug() << "w pressed. Wireframe mode started.";
    update();
  } else if (keyEvent->key() == Qt::Key_Q) {
    qDebug() << "q pressed. Exit application";
    update(); 
  } else if (keyEvent->key() == Qt::Key_1) {
    qDebug() << "1 pressed. Render Bunny";
    update(); 
  } else if (keyEvent->key() == Qt::Key_2) {
    qDebug() << "2 pressed. Render Monkey";
    update(); 
  } else {
    qDebug() << "You Pressed an unsupported Key!";
  }
}

void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();
  logger_.initialize();

  connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=](){
  	const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
  	for (auto msg: messages) {
  	  qDebug() << msg;
	}
  });
  logger_.startLogging();

  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  doRender();
}

void BasicWidget::doRender() {
  createShader();

  static const GLfloat verts[21] = {
    0.0f, 0.0f, 0.0f, /* Center vertex position */ 1.0f, 0.0f, 0.0f, 1.0f, // red
    1.0f, 1.0f, 0.0f,  /* Top right vertex position */ 0.0f, 1.0f, 0.0f, 1.0f, // green
    -1.0f,  1.0f, 0.0f,  /* Top left vertex position */ 0.0f, 0.0f, 1.0f, 1.0f // blue
  };

  static const GLuint idx[3] = {0, 1, 2};

  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_.bind();
  vbo_.allocate(verts, 21 * sizeof(GL_UNSIGNED_INT));

  ibo_.create();
  ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ibo_.bind();
  ibo_.allocate(idx, 3 * sizeof(GL_UNSIGNED_INT));

  vao_.create();
  vao_.bind();
  vbo_.bind();

  shaderProgram_.enableAttributeArray(0);
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3, 7*sizeof(GL_FLOAT));

  shaderProgram_.enableAttributeArray(1);
  shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GL_FLOAT), 4, 7*sizeof(GL_FLOAT));
  ibo_.bind();

  vao_.release();
  shaderProgram_.release();
  
  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaderProgram_.bind();
  vao_.bind();
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  vao_.release();
  shaderProgram_.release();
}
