/**
 * @file main.cpp
 * @author Mitch Campbell
 * @brief This file contains the main entry point for the PrimeFinder application.
 * @date 2024-09-08
 * @copyright Copyright (c) 2024
 */


#include "widget.h"

#include <QApplication>


/**
 * @brief Main entry point for the PrimeFinder application.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Exit code.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
