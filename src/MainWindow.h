#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QWidget
{
    public:
        MainWindow();

    private:
        QVBoxLayout *m_vlayout;
        QHBoxLayout *m_hlayout;
};
