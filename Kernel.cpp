#include "Kernel.hpp"


const double PI = 3.14159265359;

/*----------------------------------------------------------*/
std::string SGTELIB::kernel_type_to_str ( SGTELIB::kernel_t kt ) {
/*----------------------------------------------------------*/
  switch ( kt ) {
  case SGTELIB::KERNEL_D1: return "D1"; //Gaussian
  case SGTELIB::KERNEL_D2: return "D2"; //Inverse Quadratic
  case SGTELIB::KERNEL_D3: return "D3"; //Inverse Multiquadratic
  case SGTELIB::KERNEL_D4: return "D4"; //Bi-quadratic
  case SGTELIB::KERNEL_D5: return "D5"; //Tri-Cubique
  case SGTELIB::KERNEL_D6: return "D6"; //Exp(-sqrt)
  case SGTELIB::KERNEL_I0: return "I0"; //Multiquadratic
  case SGTELIB::KERNEL_I1: return "I1"; //Polyharmonic Spline, k=1
  case SGTELIB::KERNEL_I2: return "I2"; //Polyharmonic Spline, k=2
  case SGTELIB::KERNEL_I3: return "I3"; //Polyharmonic Spline, k=3
  case SGTELIB::KERNEL_I4: return "I4"; //Polyharmonic Spline, k=4
  default                : 
    throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
             "kernel_type_to_str: undefined kernel type" );
    return "undefined";
  }
}




/*----------------------------------------------------------*/
bool SGTELIB::kernel_is_decreasing ( const SGTELIB::kernel_t kt ) {
/*----------------------------------------------------------*/
  // nb: "D" stands for decreasing, meaning that phi(r) tends toward 0
  // when r tends toward +infinity.
  switch ( kt ) {
  case SGTELIB::KERNEL_D1:
  case SGTELIB::KERNEL_D2:
  case SGTELIB::KERNEL_D3:
  case SGTELIB::KERNEL_D4:
  case SGTELIB::KERNEL_D5: 
  case SGTELIB::KERNEL_D6: 
    return true;
  case SGTELIB::KERNEL_I0: 
  case SGTELIB::KERNEL_I1: 
  case SGTELIB::KERNEL_I2: 
  case SGTELIB::KERNEL_I3: 
  case SGTELIB::KERNEL_I4: 
    return false;
  default                : 
    throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
             "kernel_is_decreasing: undefined kernel type" );
    return false;
  }
}//

/*----------------------------------------------------------*/
bool SGTELIB::kernel_has_parameter ( const SGTELIB::kernel_t kt ) {
/*----------------------------------------------------------*/
  switch ( kt ) {
  case SGTELIB::KERNEL_D1:
  case SGTELIB::KERNEL_D2:
  case SGTELIB::KERNEL_D3:
  case SGTELIB::KERNEL_D4:
  case SGTELIB::KERNEL_D5: 
  case SGTELIB::KERNEL_D6: 
  case SGTELIB::KERNEL_I0: 
    return true;
  case SGTELIB::KERNEL_I2: 
  case SGTELIB::KERNEL_I1: 
  case SGTELIB::KERNEL_I3: 
  case SGTELIB::KERNEL_I4: 
    return false;
  default: 
    throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
             "kernel_has_parameter: undefined kernel type" );
    return false;
  }
}//

/*----------------------------------------------------------*/
int SGTELIB::kernel_dmin ( const SGTELIB::kernel_t kt ) {
/*----------------------------------------------------------*/
  switch ( kt ) {
  case SGTELIB::KERNEL_D1:
  case SGTELIB::KERNEL_D2:
  case SGTELIB::KERNEL_D3:
  case SGTELIB::KERNEL_D4:
  case SGTELIB::KERNEL_D5: 
  case SGTELIB::KERNEL_D6: 
    return -1;
  case SGTELIB::KERNEL_I0: 
  case SGTELIB::KERNEL_I1: 
    return 0;
  case SGTELIB::KERNEL_I2: 
  case SGTELIB::KERNEL_I3: 
  case SGTELIB::KERNEL_I4: 
    return 1;
  default: 
    throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
             "kernel_dmin: undefined kernel type" );
    return false;
  }
}//


/*----------------------------------------------------------*/
SGTELIB::kernel_t SGTELIB::str_to_kernel_type ( const std::string & s ) {
/*----------------------------------------------------------*/
  if ( s=="D1" ){ return SGTELIB::KERNEL_D1; }
  if ( s=="D2" ){ return SGTELIB::KERNEL_D2; }
  if ( s=="D3" ){ return SGTELIB::KERNEL_D3; }
  if ( s=="D4" ){ return SGTELIB::KERNEL_D4; }
  if ( s=="D5" ){ return SGTELIB::KERNEL_D5; }
  if ( s=="D6" ){ return SGTELIB::KERNEL_D6; }
  if ( s=="I0" ){ return SGTELIB::KERNEL_I0; }
  if ( s=="I1" ){ return SGTELIB::KERNEL_I1; }
  if ( s=="I2" ){ return SGTELIB::KERNEL_I2; }
  if ( s=="I3" ){ return SGTELIB::KERNEL_I3; }
  if ( s=="I4" ){ return SGTELIB::KERNEL_I4; }
  throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
     "str_to_kernel_type: unrecognised string \""+s+"\"" );
}//

/*----------------------------------------------------------*/
SGTELIB::kernel_t SGTELIB::int_to_kernel_type ( const int i ) {
/*----------------------------------------------------------*/
  if ( (i<0) or (i>=SGTELIB::NB_KERNEL_TYPES) ){
    throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
      "int_to_kernel_type: invalid integer "+i );
  }
  switch ( i ){
    case 0:  return SGTELIB::KERNEL_D1; 
    case 1:  return SGTELIB::KERNEL_D2; 
    case 2:  return SGTELIB::KERNEL_D3; 
    case 3:  return SGTELIB::KERNEL_D4; 
    case 4:  return SGTELIB::KERNEL_D5; 
    case 5:  return SGTELIB::KERNEL_D6; 
    case 6:  return SGTELIB::KERNEL_I0; 
    case 7:  return SGTELIB::KERNEL_I1; 
    case 8:  return SGTELIB::KERNEL_I2; 
    case 9:  return SGTELIB::KERNEL_I3; 
    case 10: return SGTELIB::KERNEL_I4; 
    default:
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
        "int_to_kernel_type: invalid integer "+i );
  }
}//

/*----------------------------------------------*/
/*       Compute the value of the kernel        */
/*----------------------------------------------*/
double SGTELIB::kernel (  const SGTELIB::kernel_t kt , 
                          const double ks ,
                          const double r ){
  // kt : kernel type
  // ks : kernel shape
  // r : radius

  switch (kt){
    case SGTELIB::KERNEL_D1:
      // Gaussian
      return exp(-PI*ks*ks*r*r);
    case SGTELIB::KERNEL_D2:
      // Inverse Quadratic
      return 1.0/(1.0+ks*ks*r*r);
    case SGTELIB::KERNEL_D3:
      // Inverse Multiquadratic
      return 1.0/sqrt(1.0+ks*ks*r*r);
    case SGTELIB::KERNEL_D4:
      // Bi-quadratic 
      {
        double ksr = fabs(ks*r)*16.0/15.0;
        if (ksr<=1){
          double d = (1-ksr*ksr);
          return d*d;
        }
      }
      return 0.0;
    case SGTELIB::KERNEL_D5:
      // Tri-cubic
      {
        double ksr = fabs(ks*r)*162.0/140.0;
        if (ksr<=1.0){
          double d = (1-ksr*ksr*ksr);
          return d*d*d;
        }   
      }
      return 0.0;
    case SGTELIB::KERNEL_D6:
      // Gaussian
      return exp(-sqrt(ks*r));
    case SGTELIB::KERNEL_I0:
      // Multiquadratic
      return sqrt(1.0+ks*ks*r*r);
    case SGTELIB::KERNEL_I1:
      // Polyharmonique spline (k=1)
      return r;
    case SGTELIB::KERNEL_I2:
      // Polyharmonique spline (k=2) (Thin Plate Splin)
      if (r==0.0) return 0.0;
      return log(r)*r*r;
    case SGTELIB::KERNEL_I3:
      // Polyharmonique spline (k=3)
      return r*r*r;
    case SGTELIB::KERNEL_I4:
      // Polyharmonique spline (k=4)
      if (r==0.0) return 0.0;
      {
        double r2 = r*r;
        return r2*r2*log(r);
      }
    default:
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
               "kernel: undefined kernel type" );
      return 0.0;
  } // end switch
}//

/*----------------------------------------------*/
/*       Compute the value of the kernel        */
/*----------------------------------------------*/
SGTELIB::Matrix SGTELIB::kernel (  const SGTELIB::kernel_t kt , 
                                   const double ks ,
                                   SGTELIB::Matrix R ){

  const int nbRows = R.get_nb_rows();
  const int nbCols = R.get_nb_cols();
  int i,j;
  for (i=0 ; i<nbRows ; i++){
    for (j=0 ; j<nbCols ; j++){
      R.set(i,j,kernel(kt,ks,R.get(i,j)));
    }
  }
  return R;
}//




