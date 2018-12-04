#include "MainWidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("CloudMusic");
  app.setOrganizationName("CloudMusic");
  app.setOrganizationDomain("github.com/bottod");
  app.setWindowIcon(QIcon(":/images/logoIcon.png"));

  MainWidget w;

  w.show();

  return app.exec();
}
