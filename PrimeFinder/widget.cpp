#include "widget.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>


Widget::Widget(QWidget *parent)
    : QWidget(parent),
    labelStart(new QLabel("Start Number:")),
    spinBoxStart(new QSpinBox(this)),
    labelEnd(new QLabel("End Number:")),
    spinBoxEnd(new QSpinBox(this)),
    labelThreads(new QLabel("Number of Threads:")),
    spinBoxThreads(new QSpinBox(this)),
    buttonStart(new QPushButton("Start", this)),
    buttonStop(new QPushButton("Stop", this))
{
    setupUI();
    connect(buttonStart, &QPushButton::clicked, this, &Widget::startPrimeSearch);
}

Widget::~Widget() {}

void Widget::setupUI()
{
    // Window properties
    setWindowTitle("Multithreaded Prime Finder");
    resize(640, 480);

    // Configure widgets
    spinBoxStart->setRange(0, 1000);
    spinBoxEnd->setRange(1, 10000);
    spinBoxThreads->setRange(1, MAX_THREADS);
    buttonStop->setEnabled(false);

    // Create prime display areas (one for each thread)
    for (int i = 0; i < MAX_THREADS; i++)
    {
        primeDisplay[i] = new QPlainTextEdit(this);
        primeDisplay[i]->setReadOnly(true);
        primeDisplay[i]->setPlaceholderText(QString("Thread %1 output...").arg(i+1));
    }

    // Layouts
    QGridLayout *inputLayout = new QGridLayout();
    inputLayout->addWidget(labelStart, 0, 0);
    inputLayout->addWidget(spinBoxStart, 0, 1);
    inputLayout->addWidget(labelEnd, 1, 0);
    inputLayout->addWidget(spinBoxEnd, 1, 1);
    inputLayout->addWidget(labelThreads, 2, 0);
    inputLayout->addWidget(spinBoxThreads, 2, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(buttonStart);
    buttonLayout->addWidget(buttonStop);

    QVBoxLayout *primeDisplayLayout = new QVBoxLayout();
    for (int i = 0; i < MAX_THREADS; i++)
    {
        primeDisplayLayout->addWidget(primeDisplay[i]);
    }

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(primeDisplayLayout);

    setLayout(mainLayout);
}

void Widget::startPrimeSearch()
{
    buttonStart->setEnabled(false);
    buttonStop->setEnabled(true);

    // TODO: implement search for prime numbers
}
