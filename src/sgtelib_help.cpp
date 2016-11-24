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

#include "sgtelib_help.hpp"


//================================
//  Get dimension of HELP_DATA
//================================
int SGTELIB::dim_help_data (void){
  return 14;
}//

//================================
//  Construct the help data
//================================
std::string ** SGTELIB::get_help_data (void){
  int i;
  const int NL = 14;
  const int NC = 3;
  std::string ** HELP_DATA = new std::string * [NL];
  for (i = 0 ; i<NL ; i++) HELP_DATA[i] = new std::string [NC];
  //================================
  //      GENERAL
  //================================
  i = 0;
  HELP_DATA[i][0] = "GENERAL";
  HELP_DATA[i][1] = "GENERAL SGTELIB SERVER PREDICTION HELP";
  HELP_DATA[i][2] = "sgtelib is a dynamic surrogate modeling library. Given a set of data points [X,z(X)], it allowsto estimate the value of z(x) for any x.\n"
"sgtelib can be called in 4 modes:\n"
"  *  -predit: build a model on a set of data points and perform a prediction on a set of prediction points.See refPREDICT for more information.This requires the definition of a model with the option -model, see refMODEL.examplesgtelib.exe -model <model description> -predict <input/output files>\n"
"  *  -server: starts a server that can be interrogated to perform predictions or compute the error metric of a model.The server should be used via the matlab interface (see refSERVER).This requires the definition of a model with the option -model, see refMODEL.examplesgtelib.exe -server -model <mode description>\n"
"  *  -help: allows to ask for some information about some keyword.examplesgtelib.exe -help keyword\n"
"  *  -test: runs a test of the sgtelib library.examplesgtelib.exe -test";
  //================================
  //      MODEL
  //================================
  i = 1;
  HELP_DATA[i][0] = "MODEL";
  HELP_DATA[i][1] = "MODEL DESCRIPTION MODEL_DESCRIPTION DEFINITION MODEL_DEFINITION";
  HELP_DATA[i][2] = "Models in sgtelib should be defined by using a succession of field names (see refFIELD for the list of possible fields) and field value. Each field name is made of one single word. Each field value is made of one single word or numerical value. It is good pratice to start by the field name \"TYPE\", followed by the model type. See refTYPE for the list of available model types.";
  //================================
  //      FIELD
  //================================
  i = 2;
  HELP_DATA[i][0] = "FIELD";
  HELP_DATA[i][1] = "FIELD NAME FIELD_NAME";
  HELP_DATA[i][2] = "";
  //================================
  //      SERVER
  //================================
  i = 3;
  HELP_DATA[i][0] = "SERVER";
  HELP_DATA[i][1] = "SERVER MATLAB";
  HELP_DATA[i][2] = "";
  //================================
  //      TYPE
  //================================
  i = 4;
  HELP_DATA[i][0] = "TYPE";
  HELP_DATA[i][1] = "PRS KS RBF LOWESS ENSEMBLE KRIGING CN";
  HELP_DATA[i][2] = "The keyword TYPE defines which type of model is used.Possible values:\n"
"  *  PRS : Polynomial Response Surface\n"
"  *  KS : Kernel Smoothing\n"
"  *  PRS_EDGE  : PRS EDGE model\n"
"  *  PRS_CAT  : PRS CAT model\n"
"  *  RBF : Radial Basis Function Model\n"
"  *  RBFI : RBF model with incomplete basis\n"
"  *  LWR : Locally Weighted Regression\n"
"  *  ENSEMBLE : Ensemble of surrogates hline\n"
"  *  DYNATREE : dynaTree model (not supported yet)\n"
"  *  TGP : TGP model (not supported yet)\n"
"  *  KRIGING : Kriging model (not supported yet)\n"
"Default value This parameter does not have a default value. It must always be defined.Example\n"
"TYPE PRS defines a PRS model.\n"
"\n"
"quoteTYPE ENSEMBLE defines an ensemble of models.";
  //================================
  //      DEGREE
  //================================
  i = 5;
  HELP_DATA[i][0] = "DEGREE";
  HELP_DATA[i][1] = "PRS LOWESS";
  HELP_DATA[i][2] = "The keyword DEGREE defines the degree of a polynomial response surface.Allowed for models of type PRS, PRS_EDGE, PRS_CAT, LWR, RBFI.Possible valuesThe value must be an integer ge 1.Default values DEGREE = 1 for models of type RBFI. DEGREE = 2 for models of type PRS, PRS_EDGE, PRS_CAT and LWR.Example\n"
"TYPE PRS DEGREE 3 defines a PRS model of degree 3.\n"
"\n"
"quoteTYPE PRS_EDGE DEGREE 2 defines a PRS_EDGE model of degree 2.";
  //================================
  //      RIDGE
  //================================
  i = 6;
  HELP_DATA[i][0] = "RIDGE";
  HELP_DATA[i][1] = "PRS RBF LOWESS";
  HELP_DATA[i][2] = "The keyword RIDGE defines the regularization parameter of the model.Allowed for models of type PRS, PRS_EDGE, PRS_CAT, LWR, RBFI.Possible values Real value ge 0. Recommended values are 0 and 0.001.Default values Default value is 0.01.Example\n"
"TYPE PRS DEGREE 3 RIDGE 0 defines a PRS model of degree 3 with no regularization.";
  //================================
  //      KERNEL_TYPE
  //================================
  i = 7;
  HELP_DATA[i][0] = "KERNEL_TYPE";
  HELP_DATA[i][1] = "KS RBF LOWESS";
  HELP_DATA[i][2] = "The keyword KERNEL_TYPE defines the type of kernel used in the model. The keywordKERNEL is equivalent.Allowed for models of type RBF, RBFI, KS.Possible values\n"
"  *  D1 : Gaussian kernel phi(d) = expleft( fracr_phi^2 d^2d_mean^2right) \n"
" hline\n"
"  *  D2 : Inverse Quadratic Kernel, phi(d) = left( 1+fracr_phi^2 d^2d_mean^2right) ^-1\n"
"  *  D3 : Inverse Multiquadratic Kernel, phi(d) = left( 1+fracr_phi^2 d^2d_mean^2right) ^-1/2\n"
"  *  I0 : Multiquadratic Kernel, phi(d) = sqrt 1+fracr_phi^2 d^2d_mean^2 \n"
"  *  I1 : Polyharmonic splines, k=1, phi(d) = d\n"
"  *  I2 : Polyharmonic splines, k=2, phi(d) = d^2 log(d)\n"
"  *  I3 : Polyharmonic splines, k=3, phi(d) = d^3\n"
"  *  I4 : Polyharmonic splines, k=4, phi(d) = d^4 log(d)\n"
"Default valuesDefault value is D1.Example\n"
"TYPE KS KERNEL_TYPE D1 defines a KS model with Inverse Quadratic Kernel.";
  //================================
  //      KERNEL_COEF
  //================================
  i = 8;
  HELP_DATA[i][0] = "KERNEL_COEF";
  HELP_DATA[i][1] = "KS RBF LOWESS";
  HELP_DATA[i][2] = "The keyword KERNEL_COEF defines the shape coefficient r_phi of the kernel function. Note that this keyword has no impact for KERNEL_TYPES I1, I2, I3 and I4 because this kernels do not depend on r_phi.Alternative keyword name SHAPE_COEFAllowed for models of type RBF, RBFI, KS.Possible values Real value ge 0. Recommended range is [0.1 , 10]. Small values lead to smoother models.Default values Default value is 5.Example\n"
"TYPE RBF KERNEL_COEF 10 defines a RBF model with r_phi=10.";
  //================================
  //      DISTANCE_TYPE
  //================================
  i = 9;
  HELP_DATA[i][0] = "DISTANCE_TYPE";
  HELP_DATA[i][1] = "KS RBF";
  HELP_DATA[i][2] = "The keyword DISTANCE_TYPE defines the distance function used in the model. The keywordSHAPE_COEF is equivalent.Allowed for models of type RBF, RBFI, KS.Possible values\n"
"  *  NORM1 : Euclidian distance\n"
"  *  NORM2 : Distance based on norm 1\n"
"  *  NORMINF : Distance based on norm infty\n"
"  *  NORM2_IS0 : Tailored distance for discontinuity in 0.\n"
"  *  NORM2_CAT : Tailored distance for categorical models.\n"
"Default values Default value is NORM2.Example\n"
"TYPE KS DISTANCE NORM2_IS0 defines a KS model tailored for VAN optimization.";
  //================================
  //      WEIGHT
  //================================
  i = 10;
  HELP_DATA[i][0] = "WEIGHT";
  HELP_DATA[i][1] = "ENSEMBLE SELECTION WTA1 WTA2 WTA3 WTA4 WTA";
  HELP_DATA[i][2] = "The keyword WEIGHT defines the method used to compute the weights w of the ensemble of models. The keywordWEIGHT_TYPE is equivalent.Allowed for models of type ENSEMBLE.Possible values\n"
"  *  WTA1 : w_k propto metric_sum - metric_k\n"
"  *  WTA3 : w_k propto (metric_k + alpha metric_mean)^beta\n"
"  *  SELECT : w_k propto ind_metric_k = metric_min\n"
"  *  OPTIM : w minimizes metric(w)/(1+var(w)\n"
"  *  NORM2_IS0 : Tailored distance for discontinuity in 0.\n"
"Default values Default value is WTA1.Example\n"
"TYPE ENSEMBLE WEIGHT SELECT METRIC RMSECV defines an ensemble of models which selects the model that has the best RMSECV.\n"
"\n"
"quoteTYPE ENSEMBLE WEIGHT OPTIM METRIC RMSECV defines an ensemble of models where the weights w are computed by minimizing RMSECV/(1-var(w)).";
  //================================
  //      METRIC
  //================================
  i = 11;
  HELP_DATA[i][0] = "METRIC";
  HELP_DATA[i][1] = "PARAMETER OPTIMIZATION CHOICE SELECTION OPTIM";
  HELP_DATA[i][2] = "The keyword METRIC defines the metric used to compute the weights w of the ensemble of models. The keywordMETRIC_TYPE is equivalent.Allowed for models of type ENSEMBLE.Possible values\n"
"  *  EMAX : Error Max.\n"
"  *  EMAXCV: Error Max with Cross-Validation.\n"
"  *  RMSE : Root Mean Square Error.\n"
"  *  RMSECV: RMSE with Cross-Validation.\n"
"  *  OE : Order Error.\n"
"  *  OECV: Order Error with Cross-Validation.\n"
"  *  LINV : Inverte of the Likelihood.\n"
"Default values Default value is RMSE.Example\n"
"TYPE ENSEMBLE WEIGHT SELECT METRIC RMSECV defines an ensemble of models which selects the model that has the best RMSECV.";
  //================================
  //      PRESET
  //================================
  i = 12;
  HELP_DATA[i][0] = "PRESET";
  HELP_DATA[i][1] = "RBF ENSEMBLE LOWESS";
  HELP_DATA[i][2] = "The keyword PRESET defines the set of simplemodels used to build the ensemble of models.Allowed for models of type ENSEMBLE.Possible values\n"
"  *  DEFAULT: Set of 17 models (PRS, KS and RBFI).\n"
"  *  KS: Set of 7 KS models with Gaussian kernels.\n"
"  *  PRS: Set of 6 PRS models (degree 1 to 6).\n"
"  *  SMALL: Set of 3 models (PRS, KS and RBFI) with default parameters.\n"
"  *  IS0: Set of 30 models that handles the discontinuity in 0.\n"
"  *  CAT: Set of 30 models that handles categorical data.\n"
"The preset IS0 is recommended for VAN problems. The preset DEFAULT is recommended for other problems.Default values Default value is DEFAULT.Example\n"
"TYPE ENSEMBLE PRESET DEFAULT defines the default ensemble of models.\n"
"\n"
"quoteTYPE ENSEMBLE PRESET IS0 defines an ensemble of models tailored for VAN optimization.\n"
"\n"
"quoteTYPE ENSEMBLE PRESET CAT defines an ensemble of models tailored the 2D problem.";
  //================================
  //      OUTPUT
  //================================
  i = 13;
  HELP_DATA[i][0] = "OUTPUT";
  HELP_DATA[i][1] = "OUT";
  HELP_DATA[i][2] = "Define a text file in which informations will be recorded.";
  //================================
  return HELP_DATA;
}//
