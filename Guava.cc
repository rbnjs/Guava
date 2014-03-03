/*
 * =====================================================================================
 *
 *       Filename:  Guava.cc
 *
 *    Description:  Main
 *
 *        Version:  1.0
 *        Created:  03/03/14 14:24:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas , Michael Woo 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include <iostream>
#include "GuavaDriver.hh"


int main (int argc, char *argv[])
{
  GuavaDriver driver;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
        driver.trace_parsing = true;
    else if (argv[i] == std::string ("-s"))
        driver.trace_scanning = true;
    else if (!driver.parse (argv[i]))
        std::cout << driver.result << std::endl;
}
