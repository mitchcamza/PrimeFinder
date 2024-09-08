/**
 * @file primefinderexception.cpp
 * @author Mitch Campbell
 * @brief This file contains the implementation for the PrimeFinderException class.
 * @date 2024-09-08
 * @copyright Copyright (c) 2024
 */


#include "primefinderexception.h"



PrimeFinderException::PrimeFinderException(const QString &message)
    : m_message(message)
{

}

PrimeFinderException *PrimeFinderException::clone() const
{
    return new PrimeFinderException(*this);
}

const QString &PrimeFinderException::message() const
{
    return m_message;
}

void PrimeFinderException::raise() const
{
    throw *this;
}
