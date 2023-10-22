#include <QApplication>
#include <QMainWindow>

#include <MainWindow.hpp>


int main(int argc, char* argv[]) {
  QApplication const app{argc, argv};

  pg::MainWindow root;
  root.show();

  return QApplication::exec();
}
