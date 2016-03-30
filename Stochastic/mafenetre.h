#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QProgressBar>

class MaFenetre : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    MaFenetre();

public slots:
    void changeWidth(int _width);
    void changeHeight(int _height);

signals:
    void heightMax();

    private:
    QPushButton *m_quit;
    QProgressBar *m_bar;
    QSlider *m_slider;
    QSlider *m_slider2;
};
#endif // MAFENETRE_H
