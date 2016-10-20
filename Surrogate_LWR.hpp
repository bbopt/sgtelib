#ifndef __SGTELIB_SURROGATE_LWR__
#define __SGTELIB_SURROGATE_LWR__

#include "Surrogate.hpp"

#include <iostream>
#include <fstream>

namespace SGTELIB {

  /*--------------------------------------*/
  /*         Surrogate_LWR class        */
  /*--------------------------------------*/
  class Surrogate_LWR : public SGTELIB::Surrogate {

  protected:

    int _q; // Number of basis functions
    int _q_old; 
    int _degree; // Degree of local regression
    double ** _H; // Design matrix
    double *  _W; // Weights of each observation
    double ** _A; // Matrix of the linear system (and preconditionner)
    double ** _HWZ; // Second term
    double * _u; // First line of inverse of A
    double * _old_u; // Last value of gamma
    double * _old_x; // Last value of x

    SGTELIB::Matrix _ZZsi; // Outputs for one point (buffer)

    // build model (private):
    virtual bool build_private (void);

    void predict_private ( const SGTELIB::Matrix & XXs,
                                 SGTELIB::Matrix * ZZs); 

    void delete_matrices (void);

    void predict_private_single ( SGTELIB::Matrix XXs , int i_exclude = -1);

    // Compute metrics
    const SGTELIB::Matrix * get_matrix_Zvs (void);

  public:
    // Constructor
    Surrogate_LWR ( SGTELIB::TrainingSet & trainingset ,   
                    SGTELIB::Surrogate_Parameters param) ;

    // destructor:
    virtual ~Surrogate_LWR ( void );

    // Build the monome exponents
    virtual void display_private ( std::ostream & out ) const;

  };
}

#endif
