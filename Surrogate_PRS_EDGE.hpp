#ifndef __SGTELIB_SURROGATE_PRS_EDGE__
#define __SGTELIB_SURROGATE_PRS_EDGE__

#include "Surrogate_PRS.hpp"

namespace SGTELIB {

  /*--------------------------------------*/
  /*         Surrogate_PRS_EDGE class     */
  /*--------------------------------------*/
  class Surrogate_PRS_EDGE : public SGTELIB::Surrogate_PRS {

  protected:

    virtual const SGTELIB::Matrix compute_design_matrix ( const SGTELIB::Matrix Monomes, 
                                                  const SGTELIB::Matrix & Xs );

    // build model (private):
    virtual bool build_private (void);

  public:

    // Constructor
    Surrogate_PRS_EDGE ( SGTELIB::TrainingSet & trainingset ,   
                         SGTELIB::Surrogate_Parameters param) ;
    // destructor:
    virtual ~Surrogate_PRS_EDGE ( void );

    virtual void display_private ( std::ostream & out ) const;

  };
}

#endif
