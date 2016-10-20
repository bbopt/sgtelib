#ifndef __SGTELIB_SURROGATE_PRS__
#define __SGTELIB_SURROGATE_PRS__

#include "Surrogate.hpp"

namespace SGTELIB {

  /*--------------------------------------*/
  /*         Surrogate_PRS class        */
  /*--------------------------------------*/
  class Surrogate_PRS : public SGTELIB::Surrogate {

    /*--------------------------------------------------------*/
    /*  these members are defined in the Surrogate superclass */
    /*--------------------------------------------------------*/
    // int _p; // number of data points in X and Z
    // int _n; // dimension -- number of variables
    // int _m; // number of outputs (includes the objective)

  protected:

    int _q; // Nb of basis function
    SGTELIB::Matrix _M; // Monomes
    SGTELIB::Matrix _H; // Design matrix
    SGTELIB::Matrix _Ai; // Inverse of Ht*H
    SGTELIB::Matrix _alpha; // Coefficients

    virtual const SGTELIB::Matrix compute_design_matrix ( const SGTELIB::Matrix Monomes, 
                                                          const SGTELIB::Matrix & Xs );

    // build model (private):
    virtual bool build_private (void);

    void predict_private ( const SGTELIB::Matrix & XXs,
                                 SGTELIB::Matrix * ZZs); 


    // Compute metrics
    const SGTELIB::Matrix * get_matrix_Zvs (void);

    bool compute_alpha ( void );

  public:

    // Constructor
    Surrogate_PRS ( SGTELIB::TrainingSet & trainingset ,   
                    SGTELIB::Surrogate_Parameters param) ;

    // destructor:
    virtual ~Surrogate_PRS ( void );

    // Build the monome exponents
    static int get_nb_PRS_monomes(const int nvar, const int degree);
    static SGTELIB::Matrix get_PRS_monomes(const int nvar, const int degree);
    virtual void display_private ( std::ostream & out ) const;

  };
}

#endif
