#ifndef __SGTELIB_DYNATREE__
#define __SGTELIB_DYNATREE__

#include "Surrogate.hpp"

#include "dynaTree/dynaTree.h"

namespace SGTELIB {

    
    /*--------------------------------------*/
    /*         Surrogate_dynaTree class        */
    /*--------------------------------------*/
    class Surrogate_dynaTree : public SGTELIB::Surrogate {
        
    private:
        int * _model_handles;
        
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
        
        // DynaTree module structure for accessing library functions
        void * lib_handle;
        dynaTree_module *dtm;
        
    public:
        
        // Constructor
        Surrogate_dynaTree ( SGTELIB::TrainingSet & trainingset ,
                            SGTELIB::Surrogate_Parameters & param) ;
        
        // destructor:
        virtual ~Surrogate_dynaTree ( void );
        
        virtual void display_private ( std::ostream & out ) const;
        
    };
}
#endif // End if ifndef __SGTELIB_DYNATREE__
