#ifndef __SGTELIB_SURROGATE_KRIGING__
#define __SGTELIB_SURROGATE_KRIGING__

#include "Surrogate.hpp"

namespace SGTELIB {

  /*--------------------------------------*/
  /*         Surrogate_Kriging class        */
  /*--------------------------------------*/
  class Surrogate_Kriging : public SGTELIB::Surrogate {

    /*--------------------------------------------------------*/
    /*  these members are defined in the Surrogate superclass */
    /*--------------------------------------------------------*/
    // int _p; // number of data points in X and Z
    // int _n; // dimension -- number of variables
    // int _m; // number of outputs (includes the objective)

  private:

    /*--------------------------------------*/
    /*          Attributes                  */
    /*--------------------------------------*/
    SGTELIB::Matrix _R; // Covariance Matrix
    SGTELIB::Matrix _Ri; // Inverte of _R
    SGTELIB::Matrix _H; // Polynomial terms
    SGTELIB::Matrix _alpha;
    SGTELIB::Matrix _beta;
    SGTELIB::Matrix _var;
    double _detR;

    /*--------------------------------------*/
    /*          Building methods            */
    /*--------------------------------------*/
    const SGTELIB::Matrix compute_covariance_matrix ( const SGTELIB::Matrix & XXs ); 

    /*--------------------------------------*/
    /*          Build model                 */
    /*--------------------------------------*/
    virtual bool build_private (void);
    virtual bool init_private  (void);
    //void init_covariance_coef (void);
    virtual void compute_metric_linv (void);
    bool compute_cv_values (void);

    /*--------------------------------------*/
    /*          predict                     */
    /*--------------------------------------*/ 
    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZs); 

    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZs,
                                         SGTELIB::Matrix * std, 
                                         SGTELIB::Matrix * ei ,
                                         SGTELIB::Matrix * cdf ); 

    /*--------------------------------------*/
    /*          Compute matrices            */
    /*--------------------------------------*/
    virtual const SGTELIB::Matrix * get_matrix_Zvs (void);
    virtual const SGTELIB::Matrix * get_matrix_Svs (void);

  public:

    /*--------------------------------------*/
    /*          Constructor                 */
    /*--------------------------------------*/
    Surrogate_Kriging ( SGTELIB::TrainingSet & trainingset ,   
                        SGTELIB::Surrogate_Parameters param) ;

    /*--------------------------------------*/
    /*          Destructor                  */
    /*--------------------------------------*/
    virtual ~Surrogate_Kriging ( void );

    /*--------------------------------------*/
    /*          Misc                        */
    /*--------------------------------------*/
    virtual void display_private ( std::ostream & out ) const;

  };
}

#endif
