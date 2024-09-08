#include "widget.h"
#include "primefinder.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
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
    pushButtonStart(new QPushButton("Start", this)),
    pushButtonStop(new QPushButton("Stop", this)),
    activeThreads(0),
    userInitiatedStop(false)
{
    setupUI();
    connect(pushButtonStart, &QPushButton::clicked, this, &Widget::startThreads);
    connect(pushButtonStop, &QPushButton::clicked, this, &Widget::stopThreads);
}

Widget::~Widget()
{
    stopThreads();
}

void Widget::closeEvent(QCloseEvent *event)
{
    stopThreads();
    event->accept();
}

void Widget::setupUI()
{
    // Window properties
    setWindowTitle("Multithreaded Prime Finder");
    resize(640, 480);

    // Configure widgets
    spinBoxStart->setRange(0, 1000);
    spinBoxEnd->setRange(1, 10000);
    spinBoxThreads->setRange(1, MAX_THREADS);
    pushButtonStop->setEnabled(false);

    // Create prime display areas (one for each thread)
    for (int i = 0; i < MAX_THREADS; i++)
    {
        primeDisplay[i] = new QPlainTextEdit(this);
        primeDisplay[i]->setReadOnly(true);
        primeDisplay[i]->setPlaceholderText(QString("Thread %1 output...").arg(i+1));
    }

    /// Layouts
    QGridLayout *inputLayout = new QGridLayout();
    inputLayout->addWidget(labelStart, 0, 0);
    inputLayout->addWidget(spinBoxStart, 0, 1);
    inputLayout->addWidget(labelEnd, 1, 0);
    inputLayout->addWidget(spinBoxEnd, 1, 1);
    inputLayout->addWidget(labelThreads, 2, 0);
    inputLayout->addWidget(spinBoxThreads, 2, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(pushButtonStart);
    buttonLayout->addWidget(pushButtonStop);

    QVBoxLayout *primeDisplayLayout = new QVBoxLayout();
    for (int i = 0; i < MAX_THREADS; i++)
    {
        // Add display areas to layout
        primeDisplayLayout->addWidget(primeDisplay[i]);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(primeDisplayLayout);

    setLayout(mainLayout);
}

void Widget::displayPrime(int threadNumber, int prime)
{
    switch (threadNumber)
    {
        case 0:
        {
            primeDisplay[0]->appendPlainText(QString::number(prime));
            break;
        }
        case 1:
        {
            primeDisplay[1]->appendPlainText(QString::number(prime));
            break;
        }
        case 2:
        {
            primeDisplay[2]->appendPlainText(QString::number(prime));
            break;
        }
        case 3:
        {
            primeDisplay[3]->appendPlainText(QString::number(prime));
            break;
        }
        default:
        {
            break;
        }
    }
}

void Widget::startThreads()
{
    // Set initial button status
    pushButtonStart->setEnabled(false);
    pushButtonStop->setEnabled(true);

    // Reset flags
    userInitiatedStop = false;

    // Clear the display widgets
    for (int i = 0; i < MAX_THREADS; i++)
    {
        primeDisplay[i]->clear();
    }

    // Initialize variables
    int numThreads = spinBoxThreads->value();
    activeThreads = numThreads;
    int startNumber = spinBoxStart->value();
    int endNumber = spinBoxEnd->value();
    int range = endNumber - startNumber + 1;
    int increment = range / numThreads;

    int currentStart = startNumber;
    int currentEnd = currentStart + increment;

    // Instantiate and start threads
    for (int i = 0; i < numThreads; i++)
    {
        QThread *thread = new QThread();
        PrimeFinder *finder;

        if (i == numThreads - 1)
        {
            finder = new PrimeFinder(currentStart, endNumber, i);
        }
        else
        {
            finder = new PrimeFinder(currentStart, currentEnd, i);
        }

        // Move the finder to the new thread
        finder->moveToThread(thread);

        // Connect signals and slots for thread communication
        connect(thread, &QThread::started, finder, &PrimeFinder::findPrimes);
        connect(finder, &PrimeFinder::foundPrime, this, &Widget::displayPrime);
        connect(finder, &PrimeFinder::finished, this, &Widget::threadFinished);
        connect(finder, &PrimeFinder::finished, finder, &PrimeFinder::deleteLater);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        // Start the thread
        threadList.append(thread);
        primeFinderList.append(finder);
        thread->start();

        // Update the range for the next thread
        currentStart = currentEnd + 1;
        currentEnd += increment;
    }
}

void Widget::stopThreads()
{
    // Set flags
    userInitiatedStop = true;

    // Signal all workers to stop their work
    for (PrimeFinder *finder : primeFinderList)
    {
        // Ensure that the finder exists before attempting to stop it
        if (finder)
        {
            finder->stop();
        }
    }

    // Stop all threads and wait for them to finish
    for (QThread *thread : threadList)
    {
        if (thread && thread->isRunning())
        {
            thread->quit();
            thread->wait();
        }
    }

    // Cleanup only if this stop was user-initiated
    if (userInitiatedStop)
    {
        cleanupThreads();
    }

    pushButtonStart->setEnabled(true);
    pushButtonStop->setEnabled(false);
}

void Widget::threadFinished()
{
    // Decrease the count of the active threads
    activeThreads--;

    // Only perform cleanup when all threads have finished
    if (activeThreads == 0 && !userInitiatedStop)
    {
        cleanupThreads();
    }

    // Enable the start button once all threads are done
    if (activeThreads == 0)
    {
        pushButtonStart->setEnabled(true);
        pushButtonStop->setEnabled(false);
    }
}

void Widget::cleanupThreads()
{
    // Cleanup threads
    threadList.clear();
    primeFinderList.clear();
}
