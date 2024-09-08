#ifndef PRIMEFINDEREXCEPTION_H
#define PRIMEFINDEREXCEPTION_H

#include <QException>

class PrimeFinderException : public QException
{
public:
    PrimeFinderException(const QString &message);
    PrimeFinderException *clone() const override;
    const QString &message() const;
    void raise() const override;

private:
    QString m_message;
};

#endif // PRIMEFINDEREXCEPTION_H
