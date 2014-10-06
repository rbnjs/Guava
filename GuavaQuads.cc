/*
 * =====================================================================================
 *
 *       Filename:  GuavaQuads.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28/09/14 18:32:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GuavaQuads.hh"
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream

int secuencia_label_unico = 0;

/** 
  * Constructor de GuavaLabel que sirve como
  * un newlabel
  */
GuavaLabel::GuavaLabel(): GuavaQuads("label"){
    std::ostringstream convert;
    convert << secuencia_label_unico;
    secuencia_label_unico++;
    this->set_op("label"+convert.str());
}

