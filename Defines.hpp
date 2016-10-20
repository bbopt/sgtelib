#ifndef __SGTELIB_DEFINES__
#define __SGTELIB_DEFINES__

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string.h>


#include <limits>
#include <limits.h>

// choose tgp or dynaTree:
//#define USE_TGP
//#define USE_DYNATREE
// --> these options are defined in the makefile

// debug flag:
//#define SGTELIB_DEBUG
//#define ENSEMBLE_DEBUG

namespace SGTELIB {
  
  const double EPSILON = 1E-13;
  const double PI = 3.141592654;
  const double INF = std::numeric_limits<double>::max(); ///< Infinity

  const bool APPROX_CDF = true;
  // If true, then the lower bound of standard deviation is EPSILON. 
  // This allows to avoid flat EI and P functions. 

  enum scaling_t {
    SCALING_NONE ,
    SCALING_MEANSTD ,
    SCALING_BOUNDS
  };

  const scaling_t scaling_method = SCALING_MEANSTD;
  //const scaling_t scaling_method = SCALING_NONE;


  // model output type:
  enum model_output_t {
    NORMAL_OUTPUT ,
    FIXED_OUTPUT  ,
    BINARY_OUTPUT
  };

  // model output type:
  enum bbo_t {
    BBO_OBJ , // Objective
    BBO_CON , // Constraint
    BBO_DUM   // Dummy
  };

  enum param_domain_t {
    PARAM_DOMAIN_CONTINUOUS,
    PARAM_DOMAIN_INTEGER,
    PARAM_DOMAIN_BOOL,
    PARAM_DOMAIN_CAT,
    PARAM_DOMAIN_MISC
  };

  // FIXED => Parameter is set once and for all
  // OPTIM => Parameter is optimized so as to minimize a metric
  // MODEL_DEFINED => The surrogate model is able to define/chose the parameter
  enum param_status_t {
    STATUS_FIXED,
    STATUS_OPTIM,
    STATUS_MODEL_DEFINED
  };
    


}

#endif
