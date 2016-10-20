#include "Surrogate_dynaTree.hpp"


#ifdef USE_DYNATREE

/*----------------------------*/
/*         constructor        */
/*----------------------------*/
SGTELIB::Surrogate_dynaTree::Surrogate_dynaTree ( SGTELIB::TrainingSet & trainingset,
                                                  SGTELIB::Surrogate_Parameters param) :
  SGTELIB::Surrogate ( trainingset , param                 ),
  _model_handles     ( new int [_m]             ){

  // TODO : take external seed into account
  std::cout << "constructor dynaTree\n";

  for ( int j = 0 ; j < _m ; ++j ){
    _model_handles[j] = 0;
  }
  
}//


/*----------------------------*/
/*          destructor        */
/*----------------------------*/
SGTELIB::Surrogate_dynaTree::~Surrogate_dynaTree ( void ) {
  // clean dynaTree clouds:
  delete_clouds_R();
  if (_model_handles)
    delete [] _model_handles;
}//

/*----------------------------*/
/*          display           */
/*----------------------------*/
void SGTELIB::Surrogate_dynaTree::display_private ( std::ostream & out ) const {
  out << "(No special members)\n";
}//

/*--------------------------------------*/
/*               build                  */
/*--------------------------------------*/
bool SGTELIB::Surrogate_dynaTree::build_private ( void ) {
  
  #ifdef SGTELIB_DEBUG
    std::cout << "DYNATREE CONSTRUCT (BEGIN)\n" << std::endl;
  #endif

  int      i , j , k;
  double * scaled_X = new double [_p*_n];

  k = 0;
  for ( i = 0 ; i < _p ; ++i ) {
    for ( j = 0 ; j < _n ; ++j )
      scaled_X[k++] = _trainingset.get_Xs(i,j);
  }

  int N = _param.get_nb_particles(); // number of particles to be used
  int n_copy = _n;
  double * scaled_Z = new double [_p];
  double * lpred    = new double [_p];

  // loop on the outputs:
  for ( j = 0 ; j < _m ; ++j ) {

    // fixed output:
    if ( _trainingset.get_Z_nbdiff(j) == 0 ) {
      _model_handles[j] = -1;
    }
    // binary or normal output:
    else {

      for ( i = 0 ; i < _p ; ++i )
      	scaled_Z[i] = _trainingset.get_Zs(i,j);
 
      int imodel , minp;
      // classification model:
      if ( _trainingset.get_Z_nbdiff(j) == 2 ) {
	      imodel = 3;
	      minp   = 1;
      }
      else {
	      // constant model:
	      if ( _param.get_degree() == 0 ) {
	        imodel = 1; 
	        minp   = 4;
	      }
	      // linear model:
	      else {
	        imodel = 2;
	        minp   = 2*_n+4;
	      }
      }

      double params[9];
      params[0] = params[1] = 0.0;       // nu0s20
      params[2] = 0.95; params[3] = 2.0; // ab
      params[4] = minp;
      params[5] = 1; params[6] = _n;     // sb
      params[7] = 1;                     // icepti --> icept="implicit"
      params[8] = 2;                     // irprop
        
      int nstart = 2*minp;
      int verb   = 0;
      int bna    = 0;

      my_set_seed ( ( _param.get_seed() != 0 ) ? _param.get_seed() : 1 , 77911 ); // seed=0 makes this function bug
  
      #ifdef SGTELIB_DEBUG
        std::cout << "dynaTree_R() ..." << std::flush;
      #endif

      dynaTree_R ( &n_copy              ,
		               &_p                  ,
		               &N                   ,
		               scaled_X             ,
		               &bna                 ,
		               NULL                 , // Xna_in
		               NULL                 , // XNA_IN
		               scaled_Z             ,
		               &imodel              ,
		               params               ,
		               &nstart              ,
		               &verb                ,
		               lpred                ,
		               &(_model_handles[j]) );


      
      #ifdef SGTELIB_DEBUG
        std::cout << "... OK\n\n" << "models[" << j << "]=" << _model_handles[j] << "\n\n";
      #endif
    }
  } 
  delete [] scaled_X;
  delete [] lpred;
  delete [] scaled_Z;

  #ifdef SGTELIB_DEBUG
    std::cout << "DYNATREE CONSTRUCT (END)\n" << std::endl;
  #endif

  return true;    
}//

/*--------------------------------------*/
/*       predict (ZZs only)              */
/*--------------------------------------*/
void SGTELIB::Surrogate_dynaTree::predict_private ( const SGTELIB::Matrix & XXs,
                                                    SGTELIB::Matrix       * ZZs ) {
  check_ready(__FILE__,__FUNCTION__,__LINE__);

  int pxx = XXs.get_nb_rows();
  SGTELIB::Matrix * std = new SGTELIB::Matrix("std",pxx,_m);
  SGTELIB::Matrix * ei  = new SGTELIB::Matrix("ei" ,pxx,_m);
  SGTELIB::Matrix * cdf = new SGTELIB::Matrix("cdf",pxx,_m);

  predict_private(XXs,ZZs,std,ei,cdf);

  delete std;
  delete ei;
  delete cdf;

}//

/*--------------------------------------*/
/*       predict (ZZs,std,ei)            */
/*--------------------------------------*/
// Must be overloaded for statistical models like kriging, dynaTree or Musu
void SGTELIB::Surrogate_dynaTree::predict_private (const SGTELIB::Matrix & XXs,
                                                         SGTELIB::Matrix * ZZs ,
                                                         SGTELIB::Matrix * std, 
                                                         SGTELIB::Matrix * ei ,
                                                         SGTELIB::Matrix * cdf) {
  check_ready(__FILE__,__FUNCTION__,__LINE__);

  int i , j , k , verb = 0;
  bool error = false;  
  int pxx = XXs.get_nb_rows();

  std::cout << verb << " Surragate_dynaTree, line " << __LINE__ << "\n";

  // ============================= //
  //  BUILD MATRIX Y               //
  // ============================= //

  SGTELIB::Matrix * Y0 = new SGTELIB::Matrix ("Y0",1,_m);
  for ( j = 0 ; j < _m ; ++j ){
    if (_trainingset.get_bbo(j)==SGTELIB::BBO_OBJ)
      Y0->set(0,j,_trainingset.get_fs_min());
    else
      Y0->set(0,j,0.0);
  }

  // ============================= //
  //  Inputs/Outputs Verification  //
  // ============================= //

  // Verification du nombre de points 
  
  if ( ZZs->get_nb_rows() != pxx || std->get_nb_rows() != pxx || cdf->get_nb_rows() != pxx || ei->get_nb_rows() != pxx){
    error = true;
    std::cout << "Error on the number of points (ie: nb of lines): " << std::endl;
  }
  // Verification du nombre d'entrées
  if ( XXs.get_nb_cols() != _n ){
    error = true;
    std::cout << "Error on the number of inputs (ie: nb of columns of XXs): " << std::endl;
  }
  // Verification du nombre de sorties 
  if ( ZZs->get_nb_cols() != _m || std->get_nb_cols() != _m || cdf->get_nb_cols() != _m || ei->get_nb_cols() != _m  || Y0->get_nb_cols() != _m ){
    error = true;
    std::cout << "Error on the number of outputs (ie: nb of columns of ZZs, STD, DCF and EI): " << std::endl;
  }
  if ( error ) {
    std::cout << "SGTELIB::dynaTree_Model::predict_std : bad dimensions \n";
    std::cout.flush();
    throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
			       "dynaTree_Model::predict_std(): bad dimensions" );
  }

  // ============================= //
  //         Predictions           //
  // ============================= //


  double * scaled_XXs = new double [pxx*_n]; // matrix XXs ( pxx x n ) :

  k = 0;
  for ( i = 0 ; i < pxx ; ++i )
    for ( j = 0 ; j < _n ; ++j )
      scaled_XXs[k++] = XXs.get(i,j);


  double y0;


  // loop on the outputs:
  for ( j = 0 ; j < _m ; ++j ){

    y0 = Y0->get(0,j);

    // ==== fixed output ====:
    if ( _trainingset.get_Z_nbdiff(j)==1 )
    {
      
      double ei_i, cdf_i, z_i;
      z_i = _trainingset.get_Zs_mean(j);
      
      for ( i = 0 ; i < pxx ; ++i ){
        ei_i = y0 - z_i;
        ei_i = (ei_i>0)*ei_i;
        cdf_i = (z_i<=y0);

        ZZs->set  ( i , j , z_i   );
        std->set ( i , j , 0.0 );
        cdf->set ( i , j , cdf_i );
        ei->set  ( i , j , ei_i  );
      }
      
    }
    else if ( _trainingset.get_Z_nbdiff(j)==2 ) {

      
      // ==== binary output ====:

      double p0, p1, v0, v1, cdf_i, std_i, mean_i, ei_i;
      v0 = 0.0;
      v1 = 1.0;
      // TODO : set v0 & v1 in a clean way.

      // Outputs for continuous
      double * p       = new double [2*pxx];
      double * entropy = new double [pxx];
      int byy = 0;
      predclass_R ( &(_model_handles[j]) ,
	                  scaled_XXs            ,
	                  &byy                 , // = 0
	                  NULL                 , // yy_in
	                  &pxx                  ,
	                  &verb                ,
	                  p                    ,
	                  NULL                 , // yypred_out
	                  entropy                );

      // set ZZs and STD:

      for ( i = 0 ; i < pxx ; ++i ) {
        p0 = p[i];
        p1 = p[i+pxx];
        mean_i = p0*v0 + p1*v1;
        std_i = (v1-v0)*sqrt(p0*p1);
        cdf_i = (y0<=v0)*p0 + (y0<=v1)*p1;
        ei_i = (y0<=v0)*p0*(v0-y0) + (y0<=v0)*p1*(v1-y0);

        ZZs->set  ( i , j , mean_i);
        std->set ( i , j , std_i );
        cdf->set ( i , j , cdf_i );
        ei->set  ( i , j , ei_i  );
      }

      delete [] p;
      delete [] entropy;
      
    }
    else { 

      
      // ==== Continuous outputs ====
      double * mean_j    = new double [pxx];
      double * var_j     = new double [pxx];
      double * ei_j      = new double [pxx];
      double * cdf_j    = new double [pxx];
      predict_R_complete (  &(_model_handles[j]) ,
	                          scaled_XXs           ,
	                          &pxx                 ,
	                          &verb                ,
                            &y0                  ,
	                          mean_j               ,
	                          var_j                ,
	                          ei_j                 ,
                            cdf_j                );

      // set ZZs, STD, CDF and EI
      for ( i = 0 ; i < pxx ; ++i )
      {
        ZZs->set ( i , j , mean_j[i]      );
        std->set( i , j , sqrt(var_j[i]) );
        if ( isnan( std->get(i,j) ) ){
          std->set(i,j,0.0);
        }
        cdf->set( i , j , cdf_j[i] );
        ei->set( i , j , ei_j[i] );
  	  } 

      delete [] mean_j;
      delete [] var_j;
      delete [] ei_j;
      delete [] cdf_j;
      
    }
  }

  delete Y0;
  delete [] scaled_XXs;

}//



/*--------------------------------------*/
/*       get_matrix_Zvs                 */
/*--------------------------------------*/
const SGTELIB::Matrix SGTELIB::Surrogate_dynaTree::get_matrix_Zvs (void){
  check_ready(__FILE__,__FUNCTION__,__LINE__);
  if (not _Zvs){
    _Zvs = new SGTELIB::Matrix("Zvs",_p,_m);  
    _Zvs->fill(+INF);
    /// 
    _Zvs->replace_nan(+INF);
    _Zvs->set_name("Zvs");
  }
}//


#else // if not def USE_DYNATREE

// DUMMY constructor
SGTELIB::Surrogate_dynaTree::Surrogate_dynaTree ( SGTELIB::TrainingSet & trainingset,
                                                  SGTELIB::Surrogate_Parameters param) :
  SGTELIB::Surrogate ( trainingset , param ),
  _model_handles     ( NULL                     ) {
  std::cout << "DYNATREE NOT DEFINED !!\n";
}//

// destructor
SGTELIB::Surrogate_dynaTree::~Surrogate_dynaTree ( void ) {}//

// DUMMY build_private
bool SGTELIB::Surrogate_dynaTree::build_private ( void ) { 
  std::cout << "DYNATREE NOT DEFINED !!\n";
  return false; 
}//
  
// DUMMY predict
void SGTELIB::Surrogate_dynaTree::predict_private ( const SGTELIB::Matrix & XXs,
                                                    SGTELIB::Matrix       * ZZs ) {
  ZZs->fill(-SGTELIB::INF);
  std::cout << _model_handles << "\n";
  std::cout << &XXs << " " << ZZs << "\n";
  std::cout << "DYNATREE NOT DEFINED !!\n";
}//

// DUMMY predict
void SGTELIB::Surrogate_dynaTree::predict_private (const SGTELIB::Matrix & XXs,
                                                         SGTELIB::Matrix * ZZs ,
                                                         SGTELIB::Matrix * std, 
                                                         SGTELIB::Matrix * ei ,
                                                         SGTELIB::Matrix * cdf) {
  std::cout << _param.get_degree() << " " << _param.get_nb_particles() << " " << _param.get_seed() << "\n";
  ZZs->fill(-SGTELIB::INF);
  std->fill(-SGTELIB::INF);
  ei->fill(-SGTELIB::INF);
  cdf->fill(-SGTELIB::INF);
  std::cout << &XXs << "\n";
  std::cout << "DYNATREE NOT DEFINED !!\n";
}//

// DUMMY get_matrix_Zvs
const SGTELIB::Matrix * SGTELIB::Surrogate_dynaTree::get_matrix_Zvs (void){
  _Zvs = new SGTELIB::Matrix("Zvs",_p,_m); 
  std::cout << "DYNATREE NOT DEFINED !!\n";
  return _Zvs;
}//

// DUMMY display
void SGTELIB::Surrogate_dynaTree::display_private ( std::ostream & out ) const {
  out << "!! DYNATREE NOT DEFINED !!\n";
}//


#endif



























