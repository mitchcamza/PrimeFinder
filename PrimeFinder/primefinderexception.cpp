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
