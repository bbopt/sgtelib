#ifndef __SGTELIB_SURROGATE_ENSEMBLE__
#define __SGTELIB_SURROGATE_ENSEMBLE__

#include "Surrogate.hpp"
#include "Surrogate_Factory.hpp"


//#include <time.h>


namespace SGTELIB {

  const double wta3_alpha = 0.05;
  const double wta3_beta  = -1;

  /*--------------------------------------*/
  /*         Surrogate_Ensemble class        */
  /*--------------------------------------*/
  class Surrogate_Ensemble : public SGTELIB::Surrogate {

    /*--------------------------------------------------------*/
    /*  these members are defined in the Surrogate superclass */
    /*--------------------------------------------------------*/
    // int _p; // number of data points in X and Z
    // int _n; // dimension -- number of variables
    // int _m; // number of outputs (includes the objective)

  protected:

    int _kmax; // Nb of surrogates in the ensemble
    int _kready; // Nb of surrogates READY in the ensemble
    //SGTELIB::Matrix _W; // Weight vector
    std::vector<SGTELIB::Surrogate *>  _surrogates; // List des surrogates
    bool * _active; // Array of boolean. Is _active[k] is true if surrogate k is ready
                    // AND if there is a j such that W(k,j)!=0 
                    // ie: the weight in k is non null for at least one output
    double * _metric; // Value of the metric for the Ensemble

    // build model (private):
    virtual bool build_private (void);
    virtual bool init_private  (void);

    // Compute metrics
    virtual const SGTELIB::Matrix * get_matrix_Zhs (void);
    virtual const SGTELIB::Matrix * get_matrix_Shs (void);
    virtual const SGTELIB::Matrix * get_matrix_Zvs (void);

    void compute_W_by_select(void);
    void compute_W_by_wta1  (void);
    void compute_W_by_wta3  (void);

    // predict model (private):
    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZ ,
                                         SGTELIB::Matrix * std, 
                                         SGTELIB::Matrix * ei ,
                                         SGTELIB::Matrix * cdf ); 
 
    virtual void predict_private ( const SGTELIB::Matrix & XXs,
                                         SGTELIB::Matrix * ZZ ); 


  public:

    // Constructor
    Surrogate_Ensemble ( SGTELIB::TrainingSet & trainingset ,   
                         SGTELIB::Surrogate_Parameters param) ;

    /*
    Surrogate_Ensemble ( SGTELIB::TrainingSet & trainingset ,   
                         const std::string & s) ;
    */

    // destructor:
    virtual ~Surrogate_Ensemble ( void );

    virtual void display_private ( std::ostream & out ) const;
    void display ( std::ostream & out , const int k ) const {_surrogates.at(k)->display(out);};

    // ==============================================//
    // Method for inspection of the basic surrogates //
    // ==============================================//

    // Test if basic model k is ready.
    bool is_ready (const int k) const;

/*
    int get_kmax(void){return _kmax;};
    // Set the weight method
    void set_weight_type (const SGTELIB::weight_t wt){
      _param.set_weight_type( wt );
    };
    void set_weight_type (const std::string & s){
      _param.set_weight_type( SGTELIB::str_to_weight_type(s) );
    };
    // Use model k for all outputs
    void set_weight_vector (const int k);
    // Use model k for output j 
    void set_weight_vector (const int k , const int j);
    // Provide the whole matrix    
    void set_weight_vector (const SGTELIB::Matrix & W);
*/

    // Compute the boolean array _active
    void compute_active_models ( void ) ;
    // Check the weight vector
    bool check_weight_vector ( void ) const;

/*
    // Display stats on the weight vector
    void stat_weight_vector ( void ) const;
    // Compute the variance of the weight vector for output j
    double get_weight_variance ( const int j ) const;
*/

    // ==============================================//
    // Method to define the model_list //
    // ==============================================//
    void model_list_display        ( std::ostream & out );
    void model_list_filter_by_type ( const std::string & s );
    void model_list_filter_by_type ( const SGTELIB::model_t type );
    void model_list_preset         ( const std::string & preset );
    void model_list_remove_all ( void );
    void model_list_add ( const std::string & definition );

  };
}

#endif
