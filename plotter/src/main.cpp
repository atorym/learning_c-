#include <QApplication>
#include <QStyleFactory>

#include <plotter/MainWindow.hpp>

#ifdef Q_OS_WIN
  #include <windows.h>
#endif


int main(int argc, char* argv[]) {
#if defined(Q_OS_WIN) && !defined(NDEBUG)
  ShowWindow(GetConsoleWindow(), 0);
#endif

  QApplication const app{argc, argv};

#ifdef Q_OS_WIN
  if (QString const f_style = "Fusion"; QStyleFactory::keys().contains(f_style)) {
    qApp->setStyle(QStyleFactory::create(f_style));
  }
#endif

  lc::MainWindow root;
  root.show();

  return QApplication::exec();
}
