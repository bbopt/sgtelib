#ifndef __SGTELIB_SURROGATE_KS__
#define __SGTELIB_SURROGATE_KS__

#include "Surrogate.hpp"

namespace SGTELIB {

  /*--------------------------------------*/
  /*         Surrogate_KS class        */
  /*--------------------------------------*/
  class Surrogate_KS : public SGTELIB::Surrogate {

  private:
  
    virtual bool build_private (void);
 
    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZs); 

    // Compute metrics
    virtual const SGTELIB::Matrix * get_matrix_Zvs (void);
    virtual const SGTELIB::Matrix * get_matrix_Zhs (void);

  public:

    // Constructor
    Surrogate_KS ( SGTELIB::TrainingSet & trainingset ,   
                   SGTELIB::Surrogate_Parameters param) ;

    // destructor:
    virtual ~Surrogate_KS ( void );

    virtual void display_private ( std::ostream & out ) const;

  };
}

#endif

