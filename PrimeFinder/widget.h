#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

private slots:
    void startPrimeSearch();

private:
    QLabel *labelStart;
    QLabel *labelEnd;
    QLabel *labelThreads;

    QSpinBox *spinBoxStart;
    QSpinBox *spinBoxEnd;
    QSpinBox *spinBoxThreads;

    QPushButton *buttonStart;
    QPushButton *buttonStop;

    QPlainTextEdit *primeDisplay[4]; // For displaying primes found by each thread
    void setupUI();
};

#endif // WIDGET_H
