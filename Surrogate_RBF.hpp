#ifndef __SGTELIB_SURROGATE_RBF__
#define __SGTELIB_SURROGATE_RBF__

#include "Surrogate.hpp"

namespace SGTELIB {

  /*--------------------------------------*/
  /*         Surrogate_RBF class        */
  /*--------------------------------------*/
  class Surrogate_RBF : public SGTELIB::Surrogate {

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
    int _q; // Nb of basis function
    int _qrbf; // Nb of RBF basis function
    int _qprs; // Nb of PRS basis function
    SGTELIB::Matrix _H; // Design matrix
    SGTELIB::Matrix _HtH; // H'*H
    SGTELIB::Matrix _HtZ; // H'*Z
    SGTELIB::Matrix _Ai; // inverse of H or Ht*H+r*J
    SGTELIB::Matrix _ALPHA; // Coefficients

    std::list<int> _selected_kernel;


    /*--------------------------------------*/
    /*          Building methods            */
    /*--------------------------------------*/
    const SGTELIB::Matrix compute_design_matrix ( const SGTELIB::Matrix & XXs , const bool constraints ); 

    /*--------------------------------------*/
    /*          Build model                 */
    /*--------------------------------------*/
    bool select_kernels ( void ); 
    virtual bool build_private (void);
    virtual bool init_private  (void);
    //SGTELIB::Matrix get_bumpiness (void);

    /*--------------------------------------*/
    /*          predict                     */
    /*--------------------------------------*/ 
    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZs); 

    /*--------------------------------------*/
    /*          Compute matrices            */
    /*--------------------------------------*/
    virtual const SGTELIB::Matrix * get_matrix_Zvs (void);

  public:

    /*--------------------------------------*/
    /*          Constructor                 */
    /*--------------------------------------*/
    Surrogate_RBF ( SGTELIB::TrainingSet & trainingset ,   
                     SGTELIB::Surrogate_Parameters param) ;

    /*--------------------------------------*/
    /*          Destructor                  */
    /*--------------------------------------*/
    virtual ~Surrogate_RBF ( void );

    /*--------------------------------------*/
    /*          Misc                        */
    /*--------------------------------------*/
    virtual void display_private ( std::ostream & out ) const;

  };
}

#endif
