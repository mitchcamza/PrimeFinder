/**
 * @file primefinderexception.h
 * @author Mitch Campbell
 * @brief This file contains the declaration for the PrimeFinderException class.
 * @date 2024-09-08
 * @copyright Copyright (c) 2024
 */


#ifndef PRIMEFINDEREXCEPTION_H
#define PRIMEFINDEREXCEPTION_H

#include <QException>

/**
 * @class PrimeFinderException
 * @brief A class responsible for handling exceptions in the PrimeFinder class.
 */
class PrimeFinderException : public QException
{
public:
    /**
     * @brief Constructor for PrimeFinderException.
     * @param message The exception message.
     */
    PrimeFinderException(const QString &message);

    /**
     * @brief Destructor for PrimeFinderException.
     */
    PrimeFinderException *clone() const override;

    /**
     * @brief Returns the exception message.
     * @return The exception message.
     */
    const QString &message() const;

    /**
     * @brief Raises the exception.
     */
    void raise() const override;

private:
    QString m_message;  /**< The exception message. */
};

#endif // PRIMEFINDEREXCEPTION_H
