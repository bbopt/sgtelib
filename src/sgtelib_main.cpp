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

#include <unistd.h>
#include "sgtelib.hpp"
#include "Tests.hpp"
#include "Surrogate_Factory.hpp"
#include "Surrogate_Utils.hpp"
#include <fstream>
#include <string>




/*--------------------------------------*/
/*           main function              */
/*--------------------------------------*/
int main (void) { 

  SGTELIB::sand_box();

  SGTELIB::Matrix X0;
  SGTELIB::Matrix Z0;

  std::cout << "========== TEST MANY MODELS ==========================\n";  

  SGTELIB::build_test_data("hartman6",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_hartman6.txt",X0,Z0);

  SGTELIB::build_test_data("hartman3",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_hartman3.txt",X0,Z0);

  SGTELIB::build_test_data("braninhoo",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_braninhoo.txt",X0,Z0);

  SGTELIB::build_test_data("camelback",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_camelback.txt",X0,Z0);

  SGTELIB::build_test_data("rosenbrock",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_rosenbrock.txt",X0,Z0);


  std::cout << "========== END ================================\n"; 

  return 0;
}




