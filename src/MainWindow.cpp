
#include "MainWindow.h"

MainWindow::MainWindow()
    : QWidget()
    , m_vlayout(new QVBoxLayout(this))
    , m_hlayout(new QHBoxLayout())
{
    this->setWindowTitle("Big Number Product");

    m_vlayout->addLayout(m_hlayout);
}
