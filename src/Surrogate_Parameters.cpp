/*-------------------------------------------------------------------------------------*/
/*  sgtelib - A surrogate model library for derivative-free optimization               */
/*  Version 1.0.0                                                                      */
/*                                                                                     */
/*  Copyright (C) 2012-2016  Bastien Talgorn - McGill University, Montreal             */
/*                                                                                     */
/*  Author: Bastien Talgorn                                                            */
/*  email: bastientalgorn@fastmail.com                                                 */
/*                                                                                     */
/*  This program is free software: you can redistribute it and/or modify it under the  */
/*  terms of the GNU Lesser General Public License as published by the Free Software   */
/*  Foundation, either version 3 of the License, or (at your option) any later         */
/*  version.                                                                           */
/*                                                                                     */
/*  This program is distributed in the hope that it will be useful, but WITHOUT ANY    */
/*  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A    */
/*  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.   */
/*                                                                                     */
/*  You should have received a copy of the GNU Lesser General Public License along     */
/*  with this program. If not, see <http://www.gnu.org/licenses/>.                     */
/*                                                                                     */
/*  You can find information on sgtelib at https://github.com/bastientalgorn/sgtelib   */
/*-------------------------------------------------------------------------------------*/

#include "Surrogate_Parameters.hpp"
#define SGTELIB_DEBUG
/*----------------------------*/
/*         constructor        */
/*----------------------------*/
SGTELIB::Surrogate_Parameters::Surrogate_Parameters ( const model_t mt ):
  _type  ( mt ){
  set_defaults();
  check();
}//


/*----------------------------*/
/*          constructor       */
/*----------------------------*/
SGTELIB::Surrogate_Parameters::Surrogate_Parameters ( const std::string & s ):
  _type  ( read_model_type(s) ){
  set_defaults();
  read_string(s);
  check();
}//

/*----------------------------*/
/*          Destructor        */
/*----------------------------*/
SGTELIB::Surrogate_Parameters::~Surrogate_Parameters ( void ) {

}//




/*----------------------------------------*/
/*   Extract the model type from a string */            
/*----------------------------------------*/
SGTELIB::model_t SGTELIB::Surrogate_Parameters::read_model_type ( const std::string & model_description){
  std::string s;
  std::istringstream in_line (model_description);	
  while ( in_line >> s ){
    s = SGTELIB::toupper(s);
    if (!strcmp(s,"TYPE")){
      in_line >> s;
      s = SGTELIB::toupper(s);
      return SGTELIB::str_to_model_type(s);
    }
  }
  // If nothing was found
  std::cout << "model_description: " << model_description << "\n";
  throw SGTELIB::Exception ( __FILE__ , __LINE__ , "No field \"TYPE\" found.");
}//

/*--------------------------------------------------------------------*/
/* Convert the param name provided by user into a standard param name */
/*--------------------------------------------------------------------*/
std::string SGTELIB::Surrogate_Parameters::to_standard_field_name (const std::string field){
  const std::string field_up = SGTELIB::toupper(field);
  
  if ( not strcmp(field_up,"TYPE") )           return "TYPE";
  if ( not strcmp(field_up,"TYPE_MODEL") )     return "TYPE";
  if ( not strcmp(field_up,"MODEL_TYPE") )     return "TYPE";

  if ( not strcmp(field_up,"DEGREE") )         return "DEGREE";

  if ( not strcmp(field_up,"WEIGHT") )         return "WEIGHT_TYPE";
  if ( not strcmp(field_up,"WEIGHT_TYPE") )    return "WEIGHT_TYPE";
  if ( not strcmp(field_up,"TYPE_WEIGHT") )    return "WEIGHT_TYPE";
  if ( not strcmp(field_up,"WEIGHT_CHOICE") )  return "WEIGHT_TYPE";
  if ( not strcmp(field_up,"CHOICE_WEIGHT") )  return "WEIGHT_TYPE";

  if ( not strcmp(field_up,"RIDGE") )          return "RIDGE";
  if ( not strcmp(field_up,"RIDGE_COEF") )     return "RIDGE";
  if ( not strcmp(field_up,"RIDGE_PARAM") )    return "RIDGE";

  if ( not strcmp(field_up,"KERNEL_TYPE") )    return "KERNEL_TYPE";
  if ( not strcmp(field_up,"TYPE_KERNEL") )    return "KERNEL_TYPE";
  if ( not strcmp(field_up,"KERNEL") )         return "KERNEL_TYPE";

  if ( not strcmp(field_up,"KERNEL_COEF") )    return "KERNEL_COEF";
  if ( not strcmp(field_up,"COEF_KERNEL") )    return "KERNEL_COEF";
  if ( not strcmp(field_up,"KERNEL_SHAPE") )   return "KERNEL_COEF";
  if ( not strcmp(field_up,"COEF_SHAPE") )     return "KERNEL_COEF";
  if ( not strcmp(field_up,"SHAPE") )          return "KERNEL_COEF";
  if ( not strcmp(field_up,"SHAPE_COEF") )     return "KERNEL_COEF";

  if ( not strcmp(field_up,"METRIC_TYPE") )    return "METRIC_TYPE";
  if ( not strcmp(field_up,"METRIC") )         return "METRIC_TYPE";

  if ( not strcmp(field_up,"PRESET") )         return "PRESET";

  if ( not strcmp(field_up,"OUTPUT") )         return "OUTPUT";
  if ( not strcmp(field_up,"OUTPUT_FILE") )    return "OUTPUT";

  if ( not strcmp(field_up,"DISTANCE") )       return "DISTANCE_TYPE";
  if ( not strcmp(field_up,"DISTANCE_TYPE") )  return "DISTANCE_TYPE";

  if ( not strcmp(field_up,"METRIC") )         return "METRIC_TYPE";
  if ( not strcmp(field_up,"METRIC_TYPE") )    return "METRIC_TYPE";
  if ( not strcmp(field_up,"TYPE_METRIC") )    return "DISTANCE_TYPE";

  if ( not strcmp(field_up,"PARTICLE") )       return "NB_PARTICLE";
  if ( not strcmp(field_up,"PARTICLE_NB") )    return "NB_PARTICLE";
  if ( not strcmp(field_up,"NB_PARTICLE") )    return "NB_PARTICLE";


  std::cout << "Field: " << field << " ( " << field_up << " )\n";
  throw SGTELIB::Exception ( __FILE__ , __LINE__ , "Field not recognized: \""+field+"\"not " );
  return "ERROR";
}

/*----------------------------*/
/*   Read model definition    */            
/*----------------------------*/
void SGTELIB::Surrogate_Parameters::read_string (const std::string & model_description){

  std::string field;
  std::string content_up;
  std::string content;
  bool content_is_optim;
  std::istringstream in_line (model_description);	

  while ( in_line >> field ){

    // Convert the field name into a std field name
    field = to_standard_field_name(field);

    // Check if this field is authorized for this type of model.
    if (not authorized_field(field)){
      std::cout << "model_description: " << model_description << "\n";
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Unauthorized field \""+field+"\" in a model of type "+model_type_to_str(_type) );
    }

    // Read the content_up 
    if (not (in_line >> content))
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Missing content_up for field \""+field+"\"" );

    // Pass the content_up to upper case
    content_up = SGTELIB::toupper(content);


    // Detect if the content is "OPTIM".
    content_is_optim = ( (!strcmp(content_up,"OPTIM")) or (!strcmp(content_up,"OPT")) or (!strcmp(content_up,"OPTIMIZE")) or (!strcmp(content_up,"OPTIMIZATION")) );

    // Check if optimization is allowed for this field.
    if ((content_is_optim) and (not authorized_optim(field))) {
      std::cout << "model_description: " << model_description << "\n";
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Field \""+field+"\" cannot be optimized." );
    }

    if (not strcmp(field,"TYPE")){
      if ( str_to_model_type(content_up) != _type ){
        std::cout << "model_description: " << model_description << "\n";
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Unconsistent model type!" );
      }
    }
    else if (not strcmp(field,"DEGREE")){
      if (content_is_optim)
        _degree_status = SGTELIB::STATUS_OPTIM;
      else{
        _degree = SGTELIB::stoi(content_up);
        _degree_status = SGTELIB::STATUS_FIXED;
      }
    }
    else if (not strcmp(field,"KERNEL_TYPE")){
      if (content_is_optim)
         _kernel_type_status = SGTELIB::STATUS_OPTIM;
      else{
        _kernel_type = SGTELIB::str_to_kernel_type(content_up);
        _kernel_type_status = SGTELIB::STATUS_FIXED;
      }
    }
    else if ( not strcmp(field,"KERNEL_COEF") ){
      if (content_is_optim)
        _kernel_coef_status = SGTELIB::STATUS_OPTIM;
      else{
        _kernel_coef = SGTELIB::stod(content_up);
        _kernel_coef_status = SGTELIB::STATUS_FIXED;
      }
    }
    else if (not strcmp(field,"RIDGE")){
      if (content_is_optim)
         _ridge_status = SGTELIB::STATUS_OPTIM;
      else{
        _ridge = SGTELIB::stod(content_up);
        _ridge_status = SGTELIB::STATUS_FIXED;
      }
    }
    else if ( not strcmp(field,"DISTANCE_TYPE") ){
      if (content_is_optim)
        _distance_type_status = SGTELIB::STATUS_OPTIM;
      else{
        _distance_type = str_to_distance_type(content_up);
        _distance_type_status = SGTELIB::STATUS_FIXED;
      }
    }
    else if ( not strcmp(field,"WEIGHT_TYPE") ){
      _weight_type = str_to_weight_type(content_up);
      if (content_is_optim) 
        _weight_status = SGTELIB::STATUS_OPTIM;
    }
    else if ( not strcmp(field,"METRIC_TYPE") ){
      _metric_type = str_to_metric_type(content_up);
    }
    else if ( not strcmp(field,"PRESET") ){
      _preset = content_up;
    }
    else if ( not strcmp(field,"OUTPUT") ){
      _output = content;
    }
    else if ( not strcmp(field,"NB_PARTICLES") ){
      _nb_particles = SGTELIB::stoi(content_up);
    }
    else if (not strcmp(field,"SEED")){
      _seed = SGTELIB::stoi(content_up);
    }
    else{
      std::cout << "model_description: " << model_description << "\n";
      throw SGTELIB::Exception ( __FILE__ , __LINE__ , "Field not recognized: \""+field+"\"" );
    }
  }// end while read
}//



bool SGTELIB::Surrogate_Parameters::authorized_field ( const std::string & field ) const{

  if (not strcmp(field,"TYPE")) return true;
  if (not strcmp(field,"OUTPUT")) return true;
  if (not strcmp(field,"METRIC_TYPE")) return true;

  switch (_type) {
    case SGTELIB::LINEAR:
    case SGTELIB::TGP: 
    case SGTELIB::SVN: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ , "Not implemented yetnot " );

    case SGTELIB::KRIGING: 
      if (not strcmp(field,"KERNEL_TYPE")) return true;
      if (not strcmp(field,"DISTANCE_TYPE")) return true;
      if (not strcmp(field,"COVARIANCE_COEF")) return true;

    case SGTELIB::DYNATREE: 
      if (not strcmp(field,"NB_PARTICLES")) return true;
      if (not strcmp(field,"DEGREE")) return true;
      if (not strcmp(field,"SEED")) return true;
      break;

    case SGTELIB::PRS: 
    case SGTELIB::PRS_EDGE: 
    case SGTELIB::PRS_CAT: 
      if (not strcmp(field,"DEGREE")) return true;
      if (not strcmp(field,"RIDGE")) return true;
      break;

    case SGTELIB::KS: 
      if (not strcmp(field,"KERNEL_TYPE")) return true;
      if (not strcmp(field,"KERNEL_COEF")) return true;
      if (not strcmp(field,"DISTANCE_TYPE")) return true;
      break;

    case SGTELIB::RBF: 
      if (not strcmp(field,"KERNEL_TYPE")) return true;
      if (not strcmp(field,"KERNEL_COEF")) return true;
      if (not strcmp(field,"DISTANCE_TYPE")) return true;
      if (not strcmp(field,"RIDGE")) return true;
      if (not strcmp(field,"PRESET")) return true;

      break;

    case SGTELIB::LOWESS:
      if (not strcmp(field,"DEGREE")) return true;
      if (not strcmp(field,"RIDGE")) return true;
      if (not strcmp(field,"KERNEL_TYPE")) return true;
      if (not strcmp(field,"KERNEL_COEF")) return true;
      if (not strcmp(field,"PRESET")) return true;
      break; 

    case SGTELIB::ENSEMBLE: 
      if (not strcmp(field,"WEIGHT_TYPE")) return true;
      if (not strcmp(field,"PRESET")) return true;
      break;

    default:
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Undefined model type" );
      break;
  }

  return false;
}//

bool SGTELIB::Surrogate_Parameters::authorized_optim ( const std::string & field ) {

  if (not strcmp(field,"DEGREE"))        return true;
  if (not strcmp(field,"RIDGE"))         return true;
  if (not strcmp(field,"KERNEL_TYPE"))   return true;
  if (not strcmp(field,"KERNEL_COEF"))   return true;
  if (not strcmp(field,"DISTANCE_TYPE")) return true;
  if (not strcmp(field,"WEIGHT_TYPE"))   return true;

  if (not strcmp(field,"TYPE"))          return false;
  if (not strcmp(field,"OUTPUT"))        return false;
  if (not strcmp(field,"NB_PARTICLES"))  return false;
  if (not strcmp(field,"SEED"))          return false;
  if (not strcmp(field,"METRIC_TYPE"))   return false;
  if (not strcmp(field,"PRESET"))        return false;
  if (not strcmp(field,"METRIC_TYPE"))   return false;

  std::cout << "Field : " << field << "\n";
  throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Undefined field" );

  return false;
}//



/*----------------------------*/
/*          Check             */
/*----------------------------*/
void SGTELIB::Surrogate_Parameters::check ( void ) {
  switch (_type) {
    case SGTELIB::LINEAR:
    case SGTELIB::TGP: 
    case SGTELIB::SVN: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Not implemented yet!" );



    case SGTELIB::DYNATREE: 
      if (_nb_particles <= 0 )
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"nb_particles must be > 0" );
      if ( (_degree < 0) or (_degree > 1) )
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"degree for DYNATREE model must be 0 or 1" );
      break;

    case SGTELIB::PRS: 
    case SGTELIB::PRS_EDGE: 
    case SGTELIB::PRS_CAT: 
      if (_degree < 0 )
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"degree must be >= 0" );
      if (_ridge<0)
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"ridge must be >= 0" );
      break;

    case SGTELIB::KRIGING: 
      if (!SGTELIB::kernel_is_decreasing(_kernel_type))
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"kernel_type must be decreasing" );
      break;


    case SGTELIB::KS: 
      if (_kernel_coef <= 0)
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"kernel_coef must be > 0" );
      if (!SGTELIB::kernel_is_decreasing(_kernel_type))
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"kernel_type must be decreasing" );
      break;

    case SGTELIB::RBF: 
      if (_kernel_coef <= 0) 
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"kernel_coef must be > 0" );
      if (_ridge<0)
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"ridge must be >= 0" );
      if ( (not kernel_has_parameter(_kernel_type)) and (_kernel_type_status==SGTELIB::STATUS_FIXED) ){
        // If the kernel coef is not used in this type of kernel, then it should be fixed. 
        _kernel_coef = 1;
        _kernel_coef_status = SGTELIB::STATUS_FIXED;
      }
      break;

    case SGTELIB::LOWESS: 
      if ( (_degree < 0) or (_degree > 2) )
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"degree for DYNATREE model must be 0, 1 or 2" );
      if (_ridge<0)
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"ridge must be >= 0" );
      //if (_kernel_coef <= 0)
      //  throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"kernel_coef must be > 0" );
      if ( (_preset!="D"  ) &&
           (_preset!="DEN") &&
           (_preset!="DGN") &&
           (_preset!="RE" ) &&
           (_preset!="RG" ) &&
           (_preset!="REN") &&
           (_preset!="RGN") ){
        std::cout << "LOWESS preset : " << _preset << "\n";
        std::cout << "Possible values: D, DEN, DGN, RE, RG, REN, RGN.\n";
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"preset not recognized" );
      if (!SGTELIB::kernel_is_decreasing(_kernel_type))
        throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"kernel_type must be decreasing" );
      }
      break;

    case SGTELIB::ENSEMBLE: 
      break;

    default: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Undefined type" );
  }




  // Count the number of parameters to optimize
  _nb_parameter_optimization = 0;
  if (_degree_status==SGTELIB::STATUS_OPTIM)           _nb_parameter_optimization++;
  if (_kernel_type_status==SGTELIB::STATUS_OPTIM)      _nb_parameter_optimization++;
  if (_kernel_coef_status==SGTELIB::STATUS_OPTIM)      _nb_parameter_optimization++;
  if (_ridge_status==SGTELIB::STATUS_OPTIM)            _nb_parameter_optimization++;
  if (_distance_type_status==SGTELIB::STATUS_OPTIM)    _nb_parameter_optimization++;
  if (_covariance_coef_status==SGTELIB::STATUS_OPTIM)  _nb_parameter_optimization += _covariance_coef.get_numel();
  if (_weight_status==SGTELIB::STATUS_OPTIM)           _nb_parameter_optimization += _weight.get_numel();

}//

/*----------------------------*/
/*          Display           */
/*----------------------------*/
void SGTELIB::Surrogate_Parameters::display ( std::ostream & out ) const {

  out << "Type: " << SGTELIB::model_type_to_str(_type) << std::endl;

  switch (_type) {
    case SGTELIB::LINEAR:
    case SGTELIB::TGP: 

    case SGTELIB::SVN: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,
        "Not implemented yet!" );

    case SGTELIB::KRIGING: 
      out << "Covariance coefs: " << "\n";
      _covariance_coef.display(out);
      break;

    case SGTELIB::DYNATREE: 
      out << "degree (leaf_type): " << _degree << std::endl;
      out << "nb_particles:" << _nb_particles << std::endl;
      out << "seed: " << _seed << std::endl;
      break;


    case SGTELIB::PRS: 
    case SGTELIB::PRS_EDGE: 
    case SGTELIB::PRS_CAT: 
      out << "degree: " << _degree << std::endl;
      out << "ridge: " << _ridge << std::endl;
      break;

    case SGTELIB::KS: 
      out << "Kernel type: " << _kernel_type << std::endl;
      out << "Kernel coef: " << _kernel_coef << std::endl;
      out << "Distance_type: " << distance_type_to_str(_distance_type) << std::endl;
      break;

    case SGTELIB::RBF: 
      out << "Kernel type: " << _kernel_type << std::endl;
      out << "Kernel coef: " << _kernel_coef << std::endl;
      out << "Distance_type: " << distance_type_to_str(_distance_type) << std::endl;
      out << "ridge: " << _ridge << std::endl;
      break;

    case SGTELIB::LOWESS: 
      out << "Kernel coef: " << _kernel_coef << std::endl;
      out << "Distance_type: " << distance_type_to_str(_distance_type) << std::endl;
      out << "degree: " << _degree << std::endl;
      out << "ridge: " << _ridge << std::endl;
      out << "Preset: " << _preset << std::endl;
      break;

    case SGTELIB::ENSEMBLE: 
      out << "Metric type: " << metric_type_to_str(_metric_type) << std::endl;
      out << "Weight type: " << weight_type_to_str(_weight_type) << std::endl;
      out << "Preset: " << _preset << std::endl;
      break;

    default: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Undefined type" );
  }
}//

/*----------------------------*/
/*          Set defaults           */
/*----------------------------*/
void SGTELIB::Surrogate_Parameters::set_defaults ( void ) {
  
  _metric_type = SGTELIB::METRIC_AOECV;
  _distance_type = SGTELIB::DISTANCE_NORM2;
  _distance_type_status = SGTELIB::STATUS_FIXED;
  _covariance_coef = SGTELIB::Matrix("COVARIANCE_COEF",0,0);
  _covariance_coef_status = SGTELIB::STATUS_FIXED;
  _weight = SGTELIB::Matrix("WEIGHT",0,0);
  _weight_status = SGTELIB::STATUS_MODEL_DEFINED;

  switch (_type) {
    case SGTELIB::LINEAR:
    case SGTELIB::TGP: 
    case SGTELIB::SVN: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Not implemented yet!" );

    case SGTELIB::KRIGING: 
      _kernel_type = SGTELIB::KERNEL_D1; 
      _kernel_type_status = SGTELIB::STATUS_FIXED;
      _distance_type = SGTELIB::DISTANCE_NORM2;
      _distance_type_status = SGTELIB::STATUS_FIXED;
      _covariance_coef = SGTELIB::Matrix("COVARIANCE_COEF",1,3);
      {
        const double default_noise  = 1e-6;
        const double default_exponent = 2;
        const double default_factor  = 1;
        _covariance_coef.set(0,0,default_noise);
        _covariance_coef.set(0,1,default_exponent);
        _covariance_coef.set(0,2,default_factor);
      }
      _covariance_coef_status = SGTELIB::STATUS_OPTIM;
      break;

    case SGTELIB::DYNATREE: 
      _degree = 1;
      _degree_status = SGTELIB::STATUS_FIXED;
      _nb_particles = 1000;
      _seed = 0;
      break;

    case SGTELIB::PRS: 
    case SGTELIB::PRS_EDGE: 
    case SGTELIB::PRS_CAT: 
      _degree = 2;
      _degree_status = SGTELIB::STATUS_FIXED;
      _ridge = 0.001;
      _ridge_status = SGTELIB::STATUS_FIXED;
      break;

    case SGTELIB::KS: 
      _kernel_type = SGTELIB::KERNEL_D1; 
      _kernel_type_status = SGTELIB::STATUS_FIXED;
      _kernel_coef = 5;
      _kernel_coef_status = SGTELIB::STATUS_OPTIM;
      _distance_type = SGTELIB::DISTANCE_NORM2;
      _distance_type_status = SGTELIB::STATUS_FIXED;
      break;

    case SGTELIB::RBF: 
      _kernel_type = SGTELIB::KERNEL_I2;
      _kernel_type_status = SGTELIB::STATUS_FIXED;
      _kernel_coef = 1;
      _kernel_coef_status = SGTELIB::STATUS_OPTIM;
      _distance_type = SGTELIB::DISTANCE_NORM2;
      _distance_type_status = SGTELIB::STATUS_FIXED;
      _ridge = 0.001;
      _ridge_status = SGTELIB::STATUS_FIXED;
      _preset = "I";
      _metric_type = SGTELIB::METRIC_AOECV;
      break;

    case SGTELIB::LOWESS: 
      _kernel_coef = 1.0;
      _kernel_coef_status = SGTELIB::STATUS_OPTIM;
      _kernel_type = SGTELIB::KERNEL_D1;
      _kernel_type_status = SGTELIB::STATUS_FIXED;
      _distance_type = SGTELIB::DISTANCE_NORM2;
      _distance_type_status = SGTELIB::STATUS_FIXED;
      _degree = 2;
      _degree_status = SGTELIB::STATUS_FIXED;
      _ridge = 0.001;
      _ridge_status = SGTELIB::STATUS_FIXED;
      _preset = "DGN";
      break;

    case SGTELIB::ENSEMBLE: 
      _metric_type = SGTELIB::METRIC_OECV;
      _weight_type = WEIGHT_WTA1; 
      _weight_status = SGTELIB::STATUS_MODEL_DEFINED;
      _preset = "DEFAULT";
      break;

    default: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Undefined type" );
  }

  // Default output file
  _output = "NULL";

}//

/*----------------------------*/
/*          Display           */
/*----------------------------*/
std::string SGTELIB::Surrogate_Parameters::get_string ( void ) const {

  std::string s = "TYPE "+model_type_to_str(_type);

  switch (_type) {
    case SGTELIB::LINEAR:
    case SGTELIB::TGP: 

    case SGTELIB::SVN: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ , "Not implemented yet!" );

    case SGTELIB::DYNATREE: 
      s += " Degree " + itos(_degree);
      s += " Particles " + itos(_nb_particles);
      s += " Seed " + itos(_seed);
      break;

    case SGTELIB::KRIGING: 
      s += " Kernel_Type " + kernel_type_to_str(_kernel_type);
      s += " Distance_Type " + distance_type_to_str(_distance_type);
      break;

    case SGTELIB::PRS: 
    case SGTELIB::PRS_EDGE: 
    case SGTELIB::PRS_CAT: 
      s += " Degree " + itos(_degree);
      s += " Ridge " + dtos(_ridge);
      break;

    case SGTELIB::KS: 
      s += " Kernel_Type " + kernel_type_to_str(_kernel_type);
      s += " Kernel_coef " + dtos(_kernel_coef);
      s += " Distance_Type " + distance_type_to_str(_distance_type);
      break;

    case SGTELIB::RBF: 
      s += " Kernel_Type " + kernel_type_to_str(_kernel_type);
      s += " Kernel_coef " + dtos(_kernel_coef);
      s += " Distance_Type " + distance_type_to_str(_distance_type);
      s += " Ridge " + dtos(_ridge);
      s += " Preset " + _preset;
      s += " Metric_Type " + metric_type_to_str(_metric_type);
      break;

    case SGTELIB::LOWESS: 
      s += " Kernel_coef " + dtos(_kernel_coef);
      s += " Kernel_Type " + kernel_type_to_str(_kernel_type);
      s += " Distance_Type " + distance_type_to_str(_distance_type);
      s += " Degree " + itos(_degree);
      s += " Ridge " + dtos(_ridge);
      s += " Preset " + _preset;
      break;

    case SGTELIB::ENSEMBLE: 
      s += " Metric_Type " + metric_type_to_str(_metric_type);
      s += " Weight_Type " + weight_type_to_str(_weight_type);
      s += " Preset " + _preset;
      break;

    default: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Undefined type" );
  }
  return s;

}//

/*----------------------------*/
/*          Display           */
/*----------------------------*/
std::string SGTELIB::Surrogate_Parameters::get_short_string ( void ) const {

  std::string s = model_type_to_str(_type);

  switch (_type) {
    case SGTELIB::LINEAR:
    case SGTELIB::TGP: 
    case SGTELIB::SVN: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ , "Not implemented yet!" );

    case SGTELIB::DYNATREE: 
      s += " " + itos(_degree) + " " + itos(_nb_particles) + " " + itos(_seed);
      break;

    case SGTELIB::KRIGING: 
      if (_kernel_type != SGTELIB::KERNEL_D1){
        s += " " + kernel_type_to_str(_kernel_type);
      }
      if (_distance_type != SGTELIB::DISTANCE_NORM2){
        s += " " + distance_type_to_str(_distance_type);
      }
      break;

    case SGTELIB::PRS: 
    case SGTELIB::PRS_EDGE: 
    case SGTELIB::PRS_CAT: 
      s += " " + itos(_degree);
      if (_ridge>0) s+= " R "+dtos(_ridge);
      break;

    case SGTELIB::KS: 
      s += " " + dtos(_kernel_coef);
      if (_kernel_type != SGTELIB::KERNEL_D1){
        s += " " + kernel_type_to_str(_kernel_type);
      }
      if (_distance_type != SGTELIB::DISTANCE_NORM2){
        s += " " + distance_type_to_str(_distance_type);
      }
      break;

    case SGTELIB::RBF: 
      s += " " + dtos(_kernel_coef);
      if (_kernel_type != SGTELIB::KERNEL_D1){
        s += " " + kernel_type_to_str(_kernel_type);
      }
      if (_distance_type != SGTELIB::DISTANCE_NORM2){
        s += " " + distance_type_to_str(_distance_type);
      }
      s += " " + dtos(_ridge);
      s += " "+_preset;
      if (_metric_type != SGTELIB::METRIC_AOECV){
        s += " " + metric_type_to_str(_metric_type);
      }
      break;


    case SGTELIB::LOWESS: 
      s += " " + dtos(_kernel_coef);
      if (_distance_type != SGTELIB::DISTANCE_NORM2){
        s += " " + distance_type_to_str(_distance_type);
      }
      if (_kernel_type != SGTELIB::KERNEL_D1){
        s += " " + kernel_type_to_str(_kernel_type);
      }
      if (_degree!=2) s += " Degree " + itos(_degree);
      if (_ridge>0) s+= " R "+dtos(_ridge);
      s += " "+_preset;
      break;

    case SGTELIB::ENSEMBLE: 
      s += " " + metric_type_to_str(_metric_type) + " " + weight_type_to_str(_weight_type);
      if (strcmp(_preset,"DEFAULT")) s += " "+_preset;
      break;

    default: 
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Undefined type" );
  }
  return s;

}//





/*------------------------------------*/
/*  Parameter domains and definitions */
/*------------------------------------*/
SGTELIB::Matrix SGTELIB::Surrogate_Parameters::get_x ( void ){

    SGTELIB::Matrix X ("X",1,_nb_parameter_optimization);
    int k=0;
    if (_degree_status        == SGTELIB::STATUS_OPTIM) X.set(0,k++,double(_degree));
    if (_ridge_status         == SGTELIB::STATUS_OPTIM) X.set(0,k++,double(_ridge));
    if (_kernel_coef_status   == SGTELIB::STATUS_OPTIM) X.set(0,k++,double(_kernel_coef));
    if (_kernel_type_status   == SGTELIB::STATUS_OPTIM) X.set(0,k++,double(_kernel_type));
    if (_distance_type_status == SGTELIB::STATUS_OPTIM) X.set(0,k++,double(_distance_type));

    if (_covariance_coef_status == SGTELIB::STATUS_OPTIM){
      for (int j=0 ; j<_covariance_coef.get_nb_cols() ; j++){
        X.set(0,k++,_covariance_coef[j]);
      }
    }

    if (_weight_status == SGTELIB::STATUS_OPTIM){
      for (int i=0 ; i<_weight.get_nb_rows() ; i++){
        for (int j=0 ; j<_weight.get_nb_cols() ; j++){
          X.set(0,k++,_weight.get(i,j));
        }
      }
    }

    if ( k != _nb_parameter_optimization){
      std::cout << "k=" << k << "\n";
      std::cout << "_nb_parameter_optimization=" << _nb_parameter_optimization << "\n";
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Unconcistency in the value of k." );
    }

    return X;

}//

/*-------------------------------------------------*/
/*  Set the parameters from an external value of x */
/*-------------------------------------------------*/
void SGTELIB::Surrogate_Parameters::set_x ( const SGTELIB::Matrix X ){

    int k=0;
    if (_degree_status        == SGTELIB::STATUS_OPTIM) _degree      = int(X.get(k++));
    if (_ridge_status         == SGTELIB::STATUS_OPTIM) _ridge       = double(X.get(k++));
    if (_kernel_coef_status   == SGTELIB::STATUS_OPTIM) _kernel_coef = double(X.get(k++));
    if (_kernel_type_status   == SGTELIB::STATUS_OPTIM) _kernel_type = SGTELIB::int_to_kernel_type(int(X.get(k++)));
    if (_distance_type_status == SGTELIB::STATUS_OPTIM) _distance_type=SGTELIB::int_to_distance_type(int(X.get(k++)));

    if (_covariance_coef_status == SGTELIB::STATUS_OPTIM){
      for (int j=0 ; j<_covariance_coef.get_nb_cols() ; j++){
        _covariance_coef.set(0,j,X.get(k++));
      }
    } 

    if (_weight_status == SGTELIB::STATUS_OPTIM){
      // For each BBO
      for (int i=0 ; i<_weight.get_nb_rows() ; i++){
        for (int j=0 ; j<_weight.get_nb_cols() ; j++){
        // For each model
          _weight.set(i,j,X.get(k++));
        }
      }
      _weight.normalize_cols();
    } 

    if ( k != _nb_parameter_optimization ){
      std::cout << "k=" << k << "\n";
      std::cout << "_nb_parameter_optimization=" << _nb_parameter_optimization << "\n";
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Unconcistency in the value of k." );
    }

}//

/*------------------------------------*/
/*  Parameter domains and definitions */
/*------------------------------------*/
void SGTELIB::Surrogate_Parameters::get_x_bounds ( SGTELIB::Matrix * LB ,
                                                   SGTELIB::Matrix * UB ,
                                                   SGTELIB::param_domain_t * domain,
                                                   bool * logscale ){

    if ( (not LB) or (not UB) or (not domain) or (not logscale) ){
      std::cout << LB << " " << UB << " " << domain << " " << logscale << "\n";
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Pointers are NULL." );
    }


    int i,j;
    const int N = _nb_parameter_optimization;
    for (i=0 ; i<N ; i++) logscale[i] = false;

    int k=0;
    // --------- DEGREE --------------------
    if (_degree_status == SGTELIB::STATUS_OPTIM){
      LB->set(0,k,0);
      if (_type==SGTELIB::LOWESS) {
        UB->set(0,k,2);
        domain[k] = SGTELIB::PARAM_DOMAIN_INTEGER;
      }
      else if (_type==SGTELIB::DYNATREE) {
        UB->set(0,k,1);
        domain[k] = SGTELIB::PARAM_DOMAIN_CAT;
      }
      else {
        UB->set(0,k,6);
        domain[k] = SGTELIB::PARAM_DOMAIN_INTEGER;
      }
      k++;
    }
    // --------- RIDGE --------------------
    if (_ridge_status == SGTELIB::STATUS_OPTIM){
      LB->set(0,k,0);
      UB->set(0,k,1);
      domain[k] = SGTELIB::PARAM_DOMAIN_CONTINUOUS;
      logscale[k] = true;
      k++;
    }
    // --------- KERNEL_COEF --------------------
    if (_kernel_coef_status == SGTELIB::STATUS_OPTIM){
      LB->set(0,k,0.01);
      UB->set(0,k,100);
      domain[k] = SGTELIB::PARAM_DOMAIN_CONTINUOUS;
      logscale[k] = true;
      k++;
    }
    // --------- KERNEL_TYPE --------------------
    if (_kernel_type_status == SGTELIB::STATUS_OPTIM){
      LB->set(0,k,0);
      if (_type==SGTELIB::RBF) {
        UB->set(0,k,double(NB_KERNEL_TYPES-1));
      }
      else{
        UB->set(0,k,double(NB_DECREASING_KERNEL_TYPES-1));
      }
      domain[k] = SGTELIB::PARAM_DOMAIN_CAT;
      k++;
    }
    // --------- DISTANCE_TYPE --------------------
    if (_distance_type_status == SGTELIB::STATUS_OPTIM){
      LB->set(0,k,0);
      UB->set(0,k,double(NB_DISTANCE_TYPES-1));
      domain[k] = SGTELIB::PARAM_DOMAIN_CAT;
      k++;
    }
    // --------- COVARIANCE COEF --------------------
    if (_covariance_coef_status == SGTELIB::STATUS_OPTIM){
      // Noise parameter
      LB->set(0,k,1e-9);
      UB->set(0,k,1e-3);
      domain[k] = SGTELIB::PARAM_DOMAIN_CONTINUOUS;
      logscale[k] = true;
      k++;
      const int v = (_covariance_coef.get_nb_cols()-1)/2;
      for (j=0 ; j<v ; j++){
        // Exponent parameter
        LB->set(0,k,0.5);
        UB->set(0,k,3.0);
        domain[k] = SGTELIB::PARAM_DOMAIN_CONTINUOUS;
        logscale[k] = false;
        k++;
        // Factor parameter
        LB->set(0,k,1e-3);
        UB->set(0,k,1e+3);
        domain[k] = SGTELIB::PARAM_DOMAIN_CONTINUOUS;
        logscale[k] = true;
        k++;
      }

    }
    // --------- WEIGHT --------------------
    if (_weight_status == SGTELIB::STATUS_OPTIM){
      for (i=0 ; i<_weight.get_nb_rows() ; i++){
        for (j=0 ; j<_weight.get_nb_cols() ; j++){
          LB->set(0,k,0);
          UB->set(0,k,1);
          domain[k] = SGTELIB::PARAM_DOMAIN_CONTINUOUS;
          logscale[k] = false;
          k++;
        }
      }
    }

    if ( k != N){
      std::cout << "k=" << k << "\n";
      std::cout << "N=" << N << "\n";
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Unconcistency in the value of k." );
    }
    // ----- CHECK CONSISTENCY -------
    bool error = false;
    for (j=0 ; j<N ; j++){
      // Check bounds order
      if (LB->get(j)>=UB->get(j)){
        error=true;
        std::cout << "Variable " << j << "\n";
        std::cout << "LB (=" << LB->get(j) << ") >= UB (=" << UB->get(j) << ")\n";
      }
      // Check that only continuous variables are using a log scale
      if ( (logscale[j]) and (domain[j]!=SGTELIB::PARAM_DOMAIN_CONTINUOUS) ){
        error=true;
        std::cout << "Variable " << j << "\n";
        std::cout << "Uses logscale and is not continuous.\n";
      }
      // Check that variables with log scale have bounds of the same sign.
      if (logscale[j]){
        if (LB->get(j)*UB->get(j)<=0){
          //error=true;
          std::cout << "Variable " << j << "\n";
          std::cout << "LB =" << LB->get(j) << "\nUB =" << UB->get(j) << "\n";
          std::cout << "The bounds are not appropriate for logscale optimization.\n";
        }
      }

      // Check fo reach domain type
      switch (domain[j]){
        case SGTELIB::PARAM_DOMAIN_CONTINUOUS:
          break;
        case SGTELIB::PARAM_DOMAIN_INTEGER:
        case SGTELIB::PARAM_DOMAIN_CAT:
          if (double(round(LB->get(j)))!=LB->get(j)){
            error=true;
            std::cout << "Variable " << j << " (Integer or Categorical)\n";
            std::cout << "LB (=" << LB->get(j) << ") is not an integer\n";
          }
          if (double(round(UB->get(j)))!=UB->get(j)){
            error=true;
            std::cout << "Variable " << j << " (Integer or Categorical)\n";
            std::cout << "UB (=" << UB->get(j) << ") is not an integer\n";
          }
          break;
        case SGTELIB::PARAM_DOMAIN_BOOL:
          if (LB->get(j)==0){
            error=true;
            std::cout << "Variable " << j << " (Boolean)\n";
            std::cout << "LB (=" << LB->get(j) << ") is not 0\n";
          }
          if (UB->get(j)==1){
            error=true;
            std::cout << "Variable " << j << " (Boolean)\n";
            std::cout << "UB (=" << UB->get(j) << ") is not 1\n";
          }
          break;
        case SGTELIB::PARAM_DOMAIN_MISC:
          error=true;
          std::cout << "Variable " << j << " is MISC\n";
          break;
      }
    }
    
    if (error){
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Error in definition of LB, UB or domain!" );
    }

}//

/*------------------------------------*/
/*  Check parameter X                 */
/*------------------------------------*/
bool SGTELIB::Surrogate_Parameters::check_x ( void ){

    SGTELIB::Matrix X = get_x();
    bool error = false;
    // Check dimension of X
    if (X.get_nb_rows()!=1){
      error = true;
      std::cout << "Number of rows is not 1\n";
    }
    // Check dimension of X
    const int N = _nb_parameter_optimization;
    if (X.get_nb_cols()!=N){
      error = true;
      std::cout << "Number of cols is not consistent with _nb_parameter_optimization\n";
    }

    // Get bound info.
    SGTELIB::Matrix * LB = new SGTELIB::Matrix("LB",1,N);
    SGTELIB::Matrix * UB = new SGTELIB::Matrix("UB",1,N);
    param_domain_t * domain = new param_domain_t[N];
    bool * logscale = new bool[N];
    get_x_bounds ( LB , UB , domain , logscale);

    for (int j=0 ; j<_nb_parameter_optimization ; j++){
      // Check bounds
      if (X[j]<LB->get(j)){
        error=true;
        std::cout << "X[" << j << "] < lower bound\n";
      }
      if (X[j]>UB->get(j)){
        error=true;
        std::cout << "X[" << j << "] > upper bound\n";
      }
      // Check types
      switch (domain[j]){
        case SGTELIB::PARAM_DOMAIN_CONTINUOUS:
          break;
        case SGTELIB::PARAM_DOMAIN_INTEGER:
        case SGTELIB::PARAM_DOMAIN_CAT:
          if (double(round(X[j]))!=X[j]){
            error=true;
            std::cout << "Variable " << j << " (Integer or Categorical)\n";
            std::cout << "X[" << j << "]=" << X[j] << " is not an integer\n";
          }
          break;
        case SGTELIB::PARAM_DOMAIN_BOOL:
          if ((X[j]!=0) and (X[j]!=1)){
            error=true;
            std::cout << "Variable " << j << " (Boolean)\n";
            std::cout << "X[" << j << "]=" << X[j] << " is not a boolean\n";
          }
          break;
        case SGTELIB::PARAM_DOMAIN_MISC:
          error=true;
          std::cout << "Variable " << j << " is MISC\n";
          break;
      }
    }// End loop on j

    // Check dimension of _covariance_coef
    if (_covariance_coef.get_nb_rows()>1){
      error = true;
      std::cout << "Covariance_coef should have only one row.\n";
    }
    
    if (error){
      throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"Invalid X!" );
    }

    delete LB;
    delete UB;
    delete [] domain; 

    return (not error);
}//



/*------------------------------------*/
/*  Parameter domains and definitions */
/*------------------------------------*/
void SGTELIB::Surrogate_Parameters::display_x ( std::ostream & out ){
    out << "Parameter set {\n";
    out << "    Dimension(X) " << _nb_parameter_optimization << "\n";
    if (_degree_status        == SGTELIB::STATUS_OPTIM)
      out << "    Degree " << _degree << " ";
    if (_ridge_status         == SGTELIB::STATUS_OPTIM)
      out << "    Ridge " << _ridge << " ";
    if (_kernel_coef_status   == SGTELIB::STATUS_OPTIM)
      out << "    Kernel_coef " << _kernel_coef << " ";
    if (_kernel_type_status   == SGTELIB::STATUS_OPTIM)
      out << "    Kernel_type " << SGTELIB::kernel_type_to_str(_kernel_type) << " (" << _kernel_type << ") ";
    if (_distance_type_status == SGTELIB::STATUS_OPTIM)
      out << "    Distance_type " << SGTELIB::distance_type_to_str(_distance_type) << " (" << _distance_type << ") ";
    if (_covariance_coef_status == SGTELIB::STATUS_OPTIM){
      out << "    Covariance_coef [ ";
      for (int j=0 ; j<_covariance_coef.get_nb_cols() ; j++){
        out << _covariance_coef.get(0,j) << " ";
      }
      out << "]\n";
    }
    if (_weight_status == SGTELIB::STATUS_OPTIM){
      out << "    Weight [ ";
      for (int i=0 ; i<_weight.get_nb_rows() ; i++){
        if (i>0) out << "                 ";
        for (int j=0 ; j<_weight.get_nb_cols() ; j++){
          out << _weight.get(i,j) << " ";
        }
        if (i==_weight.get_nb_rows()) out << " ]";
        out << "\n";
      }
    }

    out << "}\n";
  
}//


/*----------------------------------------------*/
/*  smoothness penalty for a set of parameters  */
/*----------------------------------------------*/
double SGTELIB::Surrogate_Parameters::get_x_penalty ( void ){
  double pen = 0;
  
  if (_degree_status        == SGTELIB::STATUS_OPTIM) pen += _degree;
  if (_ridge_status         == SGTELIB::STATUS_OPTIM) pen += log(_ridge+1e-9)+9; // Can be 0.
  if (_kernel_coef_status   == SGTELIB::STATUS_OPTIM) pen += log(_kernel_coef);
  if (_distance_type_status == SGTELIB::STATUS_OPTIM){
    switch (_distance_type){
      case DISTANCE_NORM2:
        pen += 0;
        break;
      case DISTANCE_NORM1:
      case DISTANCE_NORMINF:
        pen += 1;
        break;
      case DISTANCE_NORM2_IS0:
      case DISTANCE_NORM2_CAT:
        pen += 10;
        break;
    }
  }
  if (_covariance_coef_status == SGTELIB::STATUS_OPTIM){
    int v = (_covariance_coef.get_nb_cols()-1)/2;
    double c;
    int ip=0;
    // Noise (the smaller, the smoother)
    c = _covariance_coef.get(ip++);
    pen += log(c);
    for (int i=0 ; i<v ; i++){ 
      // Exponent (the larger, the smoother) 
      c = _covariance_coef.get(ip++);
      pen -= c;
      // Factor (the smaller, the smoother)
      c = _covariance_coef.get(ip++);
      pen += log(c);
    }
  }
  if (_weight_status == SGTELIB::STATUS_OPTIM){
    double wij;
    for (int i=0 ; i<_weight.get_nb_rows() ; i++){
      for (int j=0 ; j<_weight.get_nb_cols() ; j++){
        wij = _weight.get(i,j);
        pen += wij*wij;
      }
    }
  }

  if (std::isinf(pen)) pen=+INF;
  if (std::isnan(pen)) pen=+INF;
  return pen;
}





/*-------------------------------------------------*/
/*  update the dimension of _covariance_parameter  */
/*  for Kriging models                             */
/*-------------------------------------------------*/
void SGTELIB::Surrogate_Parameters::update_covariance_coef ( const int v ){

  const int v0 = (_covariance_coef.get_nb_cols()-1)/2;
  if (v<v0) throw SGTELIB::Exception ( __FILE__ , __LINE__ ,"v < v0" );
  if (v0 == v) return;

  double factor_mean = 0;
  double exponent_mean = 0;

  // First component is the noise. Then the exponent and factor for each dimension.
  int k = 1;
  for (int i=0 ; i<v0 ; i++){
    exponent_mean += _covariance_coef[k++];
    factor_mean   += _covariance_coef[k++];
  }
  exponent_mean /= v0;
  factor_mean /= v0;

  // Create additional columns
  SGTELIB::Matrix Add("Add",1,2);
  Add.set(0,0,exponent_mean);
  Add.set(0,1,factor_mean);

  // Add columns to _covariance_coef
  for (int i=0 ; i<v-v0 ; i++) _covariance_coef.add_cols(Add);

}//

























