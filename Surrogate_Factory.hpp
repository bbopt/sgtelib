#ifndef __SURROGATE_FACTORY__
#define __SURROGATE_FACTORY__

#include "Defines.hpp"
#include "Exception.hpp"
#include "Surrogate.hpp"
#include "Surrogate_KS.hpp"
#include "Surrogate_RBF.hpp"
#include "Surrogate_PRS.hpp"
#include "Surrogate_PRS_EDGE.hpp"
#include "Surrogate_PRS_CAT.hpp"
#include "Surrogate_dynaTree.hpp"
#include "Surrogate_Ensemble.hpp"
#include "Surrogate_LWR.hpp"
#include "Surrogate_Kriging.hpp"

namespace SGTELIB {

SGTELIB::Surrogate * Surrogate_Factory ( SGTELIB::TrainingSet    & C,
                                         const std::string & s );

SGTELIB::Surrogate * Surrogate_Factory ( SGTELIB::Matrix & X0,
                                         SGTELIB::Matrix & Z0,
                                         const std::string & s );

void surrogate_delete ( SGTELIB::Surrogate * S );

}

#endif
