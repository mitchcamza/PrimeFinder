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


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void startThreads();
    void stopThreads();
    void displayPrime(int threadNumber, int prime);
    void threadFinished();

private:
    void setupUI();
    void cleanupThreads();

    QLabel *labelStart;
    QLabel *labelEnd;
    QLabel *labelThreads;

    QSpinBox *spinBoxStart;
    QSpinBox *spinBoxEnd;
    QSpinBox *spinBoxThreads;

    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;

    QPlainTextEdit *primeDisplay[4]; // For displaying primes found by each thread

    QList<QThread*> threadList;
    QList<PrimeFinder*> primeFinderList;

    int activeThreads;
    bool userInitiatedStop; // Track if stop was initiated by the user
};

#endif // WIDGET_H
