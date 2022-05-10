/**
* @file demo_class.h
* @brief An example of how I might convert executables applications into c++ class objects
*
* Michael M. Rosenthal
*/

#ifndef DEMO_CLASS_H_
#define DEMO_CLASS_H_

#include <stdio.h>
#include "SpiceUsr.h"
#include <vector>




class demo_class{
  private:
    ////////////////////////////////////////////////////////////////////////////
    // dimension parameters
    int max_file_string_size; /**< \brief maximum length used to define the file path*/
    int max_word_size; /**< \brief maximum length used to define a word*/
    int room;/**< \brief todo describe variable*/
    ////////////////////////////////////////////////////////////////////////////
    // prompt inputs
    std::vector<SpiceChar> setupf;/**< \brief  todo describe variable

      length equal max_file_string_size
    */
    std::vector<SpiceChar> satnm;/**< \brief  todo describe variable

      length equal max_word_size
    */
    std::vector<SpiceChar> fixref;/**< \brief  todo describe variable

      length equal max_word_size
    */
    std::vector<SpiceChar> scnm;/**< \brief  todo describe variable

      length equal max_word_size
    */
    std::vector<SpiceChar> instnm;/**< \brief  todo describe variable

      length equal max_word_size
    */
    std::vector<SpiceChar> time;/**< \brief  todo describe variable

      length equal max_word_size
    */
    ////////////////////////////////////////////////////////////////////////////
    // outputs
    SpiceDouble pclat;/**< \brief  todo describe variable*/
    SpiceDouble pclon;/**< \brief  todo describe variable*/
    SpiceDouble pdlat;/**< \brief  todo describe variable*/
    SpiceDouble pdlon;/**< \brief  todo describe variable*/
    SpiceDouble srfvec[3];/**< \brief  todo describe variable*/
    SpiceDouble phase;/**< \brief  todo describe variable*/
    SpiceDouble solar;/**< \brief  todo describe variable*/
    SpiceDouble emissn;/**< \brief  todo describe variable*/
  public:
    demo_class(
      int max_file_string_size_0, /**< \brief the maximum length accepted for storing file paths*/
      int max_word_size_0, /**< \brief the maximum length accepted for storing words*/
      int room_0 /**< \brief  todo describe variable*/
    );
    ~demo_class();
    /** \brief Prompt for the user-supplied inputs for our program.*/
    void prompt();
    /** \brief Take the inputs from the prompt and attempt to gather requested information.*/
    void process_request();
    /* \brief Display results. Convert angles to degrees for output. */
    void display_results();
};

#endif  // DEMO_CLASS_H_