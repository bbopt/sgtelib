// last update: 2014-08-28

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
  //( int argc , char ** argv ) {


  SGTELIB::sand_box();


  SGTELIB::Matrix X0;
  SGTELIB::Matrix Z0;

  std::cout << "========== TEST MANY MODELS ==========================\n";  



  //SGTELIB::build_test_data("hartman6",X0,Z0);
  //SGTELIB::test_many_models("model_list_test.data","output_hartman6.txt",X0,Z0);

/*
  SGTELIB::build_test_data("hartman3",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_hartman3.txt",X0,Z0);

  SGTELIB::build_test_data("braninhoo",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_braninhoo.txt",X0,Z0);

  SGTELIB::build_test_data("camelback",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_camelback.txt",X0,Z0);

  SGTELIB::build_test_data("rosenbrock",X0,Z0);
  SGTELIB::test_many_models("model_list_test.data","output_rosenbrock.txt",X0,Z0);
*/

/*
  X0 = SGTELIB::Matrix("./data_spe_X.txt");
  Z0 = SGTELIB::Matrix("./data_spe_Z.txt");
  SGTELIB::test_many_models("model_list_test.data","output_spe.txt",X0,Z0);
*/



/*
  X0 = SGTELIB::Matrix("./SW_X.txt");
  Z0 = SGTELIB::Matrix("./SW_Z.txt");
  SGTELIB::test_many_models("model_list_test.data","output_SW.txt",X0,Z0);
*/
  std::cout << "========== NORMAL END ================================\n"; 

  return 0;
}




