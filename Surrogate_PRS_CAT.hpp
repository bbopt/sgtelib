#ifndef __SGTELIB_SURROGATE_PRS_CAT__
#define __SGTELIB_SURROGATE_PRS_CAT__

#include "Surrogate_PRS.hpp"

namespace SGTELIB {

  /*--------------------------------------*/
  /*         Surrogate_PRS_CAT class      */
  /*--------------------------------------*/
  class Surrogate_PRS_CAT : public SGTELIB::Surrogate_PRS {

  protected:
    std::set<double> _cat; // Categories
    int _nb_cat; // Number of categories

    virtual const SGTELIB::Matrix compute_design_matrix ( const SGTELIB::Matrix Monomes, 
                                                          const SGTELIB::Matrix & Xs );
    // build model (private):
    virtual bool build_private (void);
    virtual bool init_private  (void);
  public:

    // Constructor
    Surrogate_PRS_CAT ( SGTELIB::TrainingSet & trainingset ,   
                        SGTELIB::Surrogate_Parameters param) ;

    // destructor:
    virtual ~Surrogate_PRS_CAT ( void );

    virtual void display_private ( std::ostream & out ) const;

  };
}

#endif
