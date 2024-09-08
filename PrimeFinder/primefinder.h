/**
 * @file primefinder.h
 * @author Mitch Campbell
 * @brief This file contains the declaration for the PrimeFinder class.
 * @date 2024-09-08
 * @copyright Copyright (c) 2024
 */


#ifndef PRIMEFINDER_H
#define PRIMEFINDER_H

#include <QObject>


/**
 * @class PrimeFinder
 * @brief A class responsible for finding prime numbers in a given range, running in a separate thread.
 */
class PrimeFinder : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for PrimeFinder.
     * @param startNumber Start number for prime search.
     * @param endNumber End number for prime search.
     * @param threadNumber Thread number.
     */
    explicit PrimeFinder(int startNumber, int endNumber, int threadNumber, QObject *parent = nullptr);

    /**
     * @brief Signal the thread to stop
     */
    void stop();

signals:
    /**
     * @brief Signal emitted when a prime number is found.
     * @param thread The thread number that found the prime.
     * @param prime The prime number that was found.
     */
    void foundPrime(int thread, int prime);

    /**
     * @brief Signal emitted when the prime search has finished.
     */
    void finished();

    /**
     * @brief Signal emitted to update the search progress.
     * @param progress The percentage progress (0-100).
     */
    void progressUpdated(int progress);

public slots:
    /**
     * @brief Slot to start the prime number search in the specified range.
     */
    void findPrimes();

private:
    /**
     * @brief Utility function to check if a number is prime.
     * @param toCheck The number to check.
     * @return True if the number is prime, false otherwise.
     */
    bool isPrime(int toCheck);

    int m_startNumber;      /**< The starting number of the range. */
    int m_endNumber;        /**< The ending number of the range. */
    int m_threadNumber;     /**< The thread number to differentiate multiple threads. */
    bool m_shouldStop;      /**< Flag to stop the thread. */
};

#endif // PRIMEFINDER_H
