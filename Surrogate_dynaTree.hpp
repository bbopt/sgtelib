#ifndef __SGTELIB_DYNATREE__
#define __SGTELIB_DYNATREE__

#include "Surrogate.hpp"

#ifdef USE_DYNATREE

//#include <stdio.h>
extern "C" {
#include "matrix.h"
//#include "Rmath.h"
}
#include "cloud.h"
#include "assert.h"

extern "C" {

  void dynaTree_R ( int    * m_in      ,
		                int    * T_in      ,
		                int    * N_in      ,
		                double * X_in      ,
		                int    * bna       ,
		                int    * Xna_in    ,
		                int    * XNA_in    ,
		                double * y_in      ,
		                int    * model_in  ,
		                double * params_in ,
		                int    * nstart_in ,
		                int    * verb_in   ,
		                double * lpred_out ,
		                int    * c_out     );

  void predict_R ( int    * c_in       ,
		               double * XX_in      ,
		               int    * byy        ,
		               double * yy_in      ,
		               int    * nn_in      ,
		               int    * verb_in    ,
		               double * mean_out   ,
		               double * var_out    ,
		               int    * quants     ,
		               double * q1_out     ,
		               double * q2_out     ,
		               double * yypred_out ,
		               int    * bei        ,
		               double * ei_out       );

  void predict_R_complete( int    * c_in,
                           double * XX_in,
                           int    * nn_in,
                           int    * verb_in,
                           double * y0_in,
                           double * mean_out,// out
                           double * var_out, // out
                           double * ei_out,  // out
                           double * cdf_out); // out

  void predclass_R ( int    * c_in        ,
		                 double * XX_in       ,
		                 int    * byy         ,
		                 int    * yy_in       ,
		                 int    * nn_in       ,
		                 int    * verb_in     ,
		                 double * p_out       ,
		                 double * yypred_out  ,
		                 double * entropy_out   );

  void update_R ( int    * c_in      ,
		              int    * m_in      ,
		              int    * T_in      ,
		              double * X_in      ,
		              int    * bna       ,
		              int    * Xna_in    ,
		              int    * XNA_in    ,
		              double * y_in      ,
		              int    * verb_in   ,
		              double * lpred_out   );

  void delete_clouds_R ( void );

}
#endif // end USE_DYNATREE


namespace SGTELIB {


  /*--------------------------------------*/
  /*         Surrogate_dynaTree class        */
  /*--------------------------------------*/
  class Surrogate_dynaTree : public SGTELIB::Surrogate {

    /*--------------------------------------------------------*/
    /*  these members are defined in the Surrogate superclass */
    /*--------------------------------------------------------*/
    // int _p; // number of data points in X and Z
    // int _n; // dimension -- number of variables
    // int _m; // number of outputs (includes the objective)

  private:
    int        *      _model_handles;

    // build model (private):
    virtual bool build_private ( void );
 
    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZs ); 

    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZs,
                                         SGTELIB::Matrix * std, 
                                         SGTELIB::Matrix * ei ,
                                         SGTELIB::Matrix * cdf ); 

    // Compute metrics
    const SGTELIB::Matrix * get_matrix_Zvs (void);

  public:
    // Constructor
    Surrogate_dynaTree ( SGTELIB::TrainingSet & trainingset ,   
                         SGTELIB::Surrogate_Parameters param) ;

    // destructor:
    virtual ~Surrogate_dynaTree ( void );

    virtual void display_private ( std::ostream & out ) const;

  };
}
#endif // End if ifndef __SGTELIB_DYNATREE__
