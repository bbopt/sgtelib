// last update: 2014-08-28

#include <unistd.h>
#include "sgtelib.hpp"
#include "Surrogate_Factory.hpp"
#include "Surrogate_Utils.hpp"
#include <fstream>
#include <string>




/*--------------------------------------*/
/*           main function              */
/*--------------------------------------*/
int main ( int argc , char ** argv ) {


  std::string str_model;
  if (argc==1){
    str_model = "TYPE PRS_CAT DEGREE 2";
  }
  else{
    str_model = "";
    for (int i=1 ; i<argc ; i++){
      str_model += std::string(argv[i])+" ";
    }
  }
  std::cout << "str_model : " << str_model << "\n";

  SGTELIB::TrainingSet * C = NULL;
  SGTELIB::Surrogate * S = NULL;
  SGTELIB::Matrix X, Z, std, ei, cdf;
  std::string dummy_str;

  std::cout << "========== SERVER ==========================\n";  


  std::cout << "Start server\n";
  std::cout << "Remove all flag files...\n";
  dummy_str = system("rm flag_* 2>/dev/null");
  std::cout << "Ok.\n";

  int dummy_k = 0;
  int pxx = 0;
  int m = 0;
  const bool display = false;

  std::ofstream out;
  std::ifstream in;
  

  while (true){

    SGTELIB::wait(0.01);

    if (SGTELIB::exists("flag_new_data_transmit")){
      //------------------------------
      // NEW DATA
      //------------------------------
      std::cout << "============flag: new_data===================\n";
      dummy_k = 0;
      dummy_str = system("mv flag_new_data_transmit flag_new_data_received");
      if (display) std::cout << "Read matrices\n";
      X = SGTELIB::Matrix("new_data_x.txt");
      Z = SGTELIB::Matrix("new_data_z.txt");
      if (display) Z.display(std::cout);

      if (not S){
        if (display) std::cout << "FIRST DATA: Build C & S\n";
        C = new SGTELIB::TrainingSet(X,Z);
        S = Surrogate_Factory(*C,str_model);
        m = C->get_output_dim();
        dummy_str = system("rm -f flag_not_ready");
      }
      else{
        if (display) std::cout << "Add points to C\n";
        C->add_points(X,Z);
      }
      if (display) std::cout << "Back to waiting...\n";

    }
    else if (SGTELIB::exists("flag_predict_transmit")){
      //------------------------------
      // PREDICT
      //------------------------------
      std::cout << "============flag: predict==================" << dummy_k++ << "\n";
      dummy_str = system("mv flag_predict_transmit flag_predict_received");

      bool ready = false;
      if (S){
        if (display) std::cout << "Build Sgte (" << C->get_nb_points() << " pts)... ";
        ready = S->build();      
        if (dummy_k==1){
          S->display(std::cout);
          out.open ("model_info.txt");
          S->display(out);
          out.close();
        }
      }

      // Read input matrix
      if (display) std::cout << "Read matrix... ";
      X = SGTELIB::Matrix("flag_predict_received");
      pxx = X.get_nb_rows();
      Z = SGTELIB::Matrix("ZZ",pxx,m);
      std = SGTELIB::Matrix("std",pxx,m);
      ei = SGTELIB::Matrix("ei",pxx,m);
      cdf = SGTELIB::Matrix("cdf",pxx,m);
      if (ready){
        // Do prediction
        if (display) std::cout << "Predict... ";
        //S->predict(X,&Z,&std,&ei,&cdf);
        S->predict(X,&Z,NULL,NULL,NULL);
        if (display) X.display(std::cout);
        if (display) Z.display(std::cout);
      }
      else{
        if (display) std::cout << "Surrogate not ready\n";
        dummy_str = system("touch flag_not_ready");
        Z.fill(+SGTELIB::INF);
      }
      
      // Open stream and write matrices
      if (display) std::cout << "Write output.\n";    
      out.open ("flag_predict_received");
      {
        // Correct matrix names
        Z.set_name("Z");
        std.set_name("std");
        ei.set_name("ei");
        cdf.set_name("cdf");
        // Write matrices 
        Z.display(out);
        std.display(out);
        ei.display(out);
        cdf.display(out);
      }
      out.close(); 

      // Change flag
      dummy_str = system("mv flag_predict_received flag_predict_finished");
      if (display) std::cout << "Back to waiting.\n";

    }
    else if (SGTELIB::exists("flag_cv_transmit")){
      //------------------------------
      // CV values
      //------------------------------
      std::cout << "============flag: cv values==================" << dummy_k++ << "\n";
      dummy_str = system("mv flag_cv_transmit flag_cv_received");

      bool ready = false;
      if (S) ready = S->build();      
      if (not ready){
        if (display) std::cout << "Surrogate not ready\n";
        dummy_str = system("touch flag_not_ready");
      }

      SGTELIB::Matrix Zh, Sh, Zv, Sv;
      if (ready){
        Zh = S->get_matrix_Zh();
        Sh = S->get_matrix_Sh();
        Zv = S->get_matrix_Zv();
        Sv = S->get_matrix_Sv();
      }
      else{
        if (display) std::cout << "Surrogate not ready\n";
        dummy_str = system("touch flag_not_ready");
      }
      
      // Open stream and write matrices
      if (display) std::cout << "Write output.\n";    
      out.open ("flag_cv_received");
      {
        // Correct matrix names
        Zh.set_name("Zh");
        Sh.set_name("Sh");
        Zv.set_name("Zv");
        Sv.set_name("Sv");
        // Write matrices 
        Zh.display(out);
        Sh.display(out);
        Zv.display(out);
        Sv.display(out);
      }
      out.close(); 

      // Change flag
      dummy_str = system("mv flag_cv_received flag_cv_finished");
      if (display) std::cout << "Back to waiting.\n";

    }
    else if (SGTELIB::exists("flag_metric_transmit")){
      //------------------------------
      // METRIC
      //------------------------------

      std::cout << "============flag: metric===================" << dummy_k++ << "\n";
      dummy_str = system("mv flag_metric_transmit flag_metric_received");

      bool ready = false;
      if (S) ready = S->build();      
      if (not ready){
        if (display) std::cout << "Surrogate not ready\n";
        dummy_str = system("touch flag_not_ready");
      }


      std::string metric_string;
      SGTELIB::metric_t mt;
      double metric_value;

      // Read metric_string
      in.open("flag_metric_received");
      in >> metric_string;
      in.close();
      if (display) std::cout << "metric : " << metric_string << "\n";   
      mt = SGTELIB::str_to_metric_type(metric_string);

      // Open stream and write metric
      if (display) std::cout << "Write output.\n";    
      out.open ("flag_metric_received");
      if (ready){
        for (int j=0 ; j<C->get_output_dim() ; j++){
          metric_value = S->get_metric(mt,j);
          out << metric_value << " ";
          if (display){
            std::cout << "output[" << j << "]: " << metric_value << "\n";
          }
        }
      }
      else{
        out << -1;
      }
      out.close(); 

      // Change flag
      dummy_str = system("mv flag_metric_received flag_metric_finished");
      if (display) std::cout << "Back to waiting.\n";

    }
    else if (SGTELIB::exists("flag_info_transmit")){
      //------------------------------
      // INFO
      //------------------------------

      std::cout << "============flag: info===================" << dummy_k++ << "\n";
      dummy_str = system("mv flag_info_transmit flag_info_received");

      bool ready = false;
      if (S) ready = S->build();      
      if (not ready){
        if (display) std::cout << "Surrogate not ready\n";
        dummy_str = system("touch flag_not_ready");
      }

      // Open stream and write metric
      if (ready) S->display(std::cout);
      else std::cout << "Not ready.";
      // Change flag
      dummy_str = system("mv flag_info_received flag_info_finished");
      if (display) std::cout << "Back to waiting.\n";

    }
    else if (SGTELIB::exists("flag_reset_transmit")){
      //------------------------------
      // RESET
      //------------------------------

      std::cout << "============flag: reset======================" << "\n";
      dummy_str = system("mv flag_reset_transmit flag_reset_received");

      surrogate_delete(S);
      delete C;
      C = NULL;
      S = NULL;

      if (display) std::cout << "Pointers: S=" << S << ", C=" << C << "\n";

      // Change flag
      dummy_str = system("mv flag_reset_received flag_reset_finished");
      if (display) std::cout << "Back to waiting.\n";

    }
    else if (SGTELIB::exists("flag_ping")){
      //------------------------------
      // PING 
      //------------------------------
      if (display) std::cout << "ping ";
      // Write state in the ping file

      bool ready = false;
      if (S){
        if (display) std::cout << "Build Sgte (" << C->get_nb_points() << " pts)... ";
        ready = S->build();
      }
      if (ready){  
        std::cout << "(Ready)\n";
        dummy_str = system("echo 1 >> flag_ping");
      }
      else{
        std::cout << "(Not ready)\n";
        dummy_str = system("echo 0 >> flag_ping");
      }
      // Send an answer!
      dummy_str = system("mv flag_ping flag_pong");
    }
    else if (SGTELIB::exists("flag_quit")){
      //------------------------------
      // QUIT
      //------------------------------
      surrogate_delete(S);
      delete C;
      dummy_str = system("rm flag_quit");
      std::cout << "flag: quit\n";
      break;
    }

  }

  std::cout << "Remove all flag files...\n";
  dummy_str = system("rm    flag_* 2>/dev/null");
  std::cout << "Ok.\n";

  std::cout << "Quit server\n";

  return 0;
}




