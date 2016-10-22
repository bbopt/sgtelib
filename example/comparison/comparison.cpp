#include <unistd.h>
#include <fstream>
#include <string>
#include "sgtelib.hpp"




/*--------------------------------------*/
/*           main function              */
/*--------------------------------------*/
int main (void) { 

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
