#include "primefinder.h"

#include <QThread>
#include <QDebug>

// #include <cmath>
// #include <stdexcept>


PrimeFinder::PrimeFinder(int startNumber, int endNumber, int threadNumber, QObject *parent)
    : QObject(parent), m_startNumber(startNumber), m_endNumber(endNumber), m_threadNumber(threadNumber)
{
    if (m_startNumber > m_endNumber)
    {
        throw std::invalid_argument("startNum cannot be greater than endNum");
        // TODO: use Qt's error handling mechanisms to throw exceptions instead of c std library
    }
}

bool PrimeFinder::isPrime(int numberToCheck)
{
    if (numberToCheck <= 1) return false;     // Prime numbers are greater than 1
    if (numberToCheck == 2) return true;      // 2 is the only even prime
    if (numberToCheck % 2 == 0) return false; // Skip even numbers greater than 2

    // Only check odd divisors from 3 up to sqrt(toCheck)
    int limit = sqrt(numberToCheck) + 1;
    for (int i = 3; i <= limit; i += 2)
    {
        if (numberToCheck % i == 0)
        {
            return false;
        }
    }
    return true;
}

void PrimeFinder::findPrimes()
{
    int totalNumbers = m_endNumber - m_startNumber + 1;  // Calculate the total number of numbers to check
    for (int count = m_startNumber; count <= m_endNumber; count++)
    {
        if (isPrime(count))
        {
            emit foundPrime(m_threadNumber, count);  // Emit signal when a prime is found
        }

        // Calculate and emit progress
        int progress = ((count - m_startNumber) * 100) / totalNumbers;
        emit progressUpdated(progress);

        // Optional: Slow down the process for testing
        QThread::msleep(50);
    }

    qDebug() << "Ending findPrimes() for thread " << m_threadNumber;
    emit finished();  // Emit signal when the thread completes
}
