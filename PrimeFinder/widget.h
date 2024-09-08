/**
 * @file widget.h
 * @author Mitch Campbell
 * @brief This file contains the declaration for the Widget class.
 * @date 2024-09-08
 * @copyright Copyright (c) 2024
 */


#ifndef WIDGET_H
#define WIDGET_H

#include <QList>
#include <QPlainTextEdit>
#include <QThread>
#include <QWidget>

class PrimeFinder;
class QLabel;
class QPlainTextEdit;
class QPushButton;
class QSpinBox;

const int MAX_THREADS = 4; // Maximum number of allowed threads


/**
 * @class Widget
 * @brief A class responsible for the main application window and thread management.
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Widget object
     * 
     * @param parent 
     */
    Widget(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Widget object
     */
    ~Widget();

protected:
    /**
     * @brief Event handler for the close event.
     * 
     * @param event The close event.
     */
    void closeEvent(QCloseEvent *event) override;

private slots:
    /**
     * @brief Slot to start the prime number search.
     */
    void startThreads();

    /**
     * @brief Slot to stop the prime number search.
     */
    void stopThreads();

    /**
     * @brief Slot to display a prime number found by a thread.
     * 
     * @param threadNumber The thread number that found the prime.
     * @param prime The prime number that was found.
     */
    void displayPrime(int threadNumber, int prime);

    /**
     * @brief Slot to handle thread completion.
     */
    void threadFinished();

private:
    /**
     * @brief Setup the user interface.
     */
    void setupUI();

    /**
     * @brief Cleanup threads and associated objects.
     */
    void cleanupThreads();

    QLabel *labelStart;         // Start number label
    QLabel *labelEnd;           // End number label
    QLabel *labelThreads;       // Number of threads label

    QSpinBox *spinBoxStart;     // Start number input
    QSpinBox *spinBoxEnd;       // End number input
    QSpinBox *spinBoxThreads;   // Number of threads input

    QPushButton *pushButtonStart;   // Start button
    QPushButton *pushButtonStop;    // Stop button

    QPlainTextEdit *primeDisplay[4]; // For displaying primes found by each thread

    QList<QThread*> threadList;             // List of threads
    QList<PrimeFinder*> primeFinderList;    // List of prime finders

    int activeThreads;      // Number of active threads
    bool userInitiatedStop; // Track if stop was initiated by the user
};

#endif // WIDGET_H
