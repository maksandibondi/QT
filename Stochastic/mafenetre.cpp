#include "mafenetre.h"


MaFenetre::MaFenetre() : QWidget()
{
    setFixedSize(500, 500);

    // Construction du bouton, slider, bar
    m_quit = new QPushButton("Quit!", this); // this we use as pointer that object belongs to this fenetre.
    m_slider = new QSlider(Qt::Horizontal,this);
    m_slider2 = new QSlider(Qt::Vertical,this);
   // m_bar = new QProgressBar(this);

    m_slider->setRange(500,800);
    m_slider2->setRange(500,800);
    m_slider->setGeometry(10,200,150,20);
    m_slider2->setGeometry(300,200,20,150);
    // m_bar->setGeometry(10,300,150,20);

    m_quit->setToolTip("faire une simulation");
    m_quit->setFont(QFont("Comic Sans MS", 14));
    m_quit->setCursor(Qt::PointingHandCursor);
    m_quit->setIcon(QIcon("smile.png"));
    m_quit->move(60, 50);

   // m_bar->setValue(50);

    QObject::connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeWidth(int)));
    QObject::connect(m_slider2, SIGNAL(valueChanged(int)), this, SLOT(changeHeight(int)));
    QObject::connect(this, SIGNAL(heightMax()), qApp, SLOT(quit()));


}

void MaFenetre::changeWidth(int _width){
    setFixedWidth(_width);
}

void MaFenetre::changeHeight(int _height){
    setFixedHeight(_height);
    if (_height == 800){
        emit heightMax();
    }
}

