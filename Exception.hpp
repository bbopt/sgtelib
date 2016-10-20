#ifndef __SGTELIB_EXCEPTION__
#define __SGTELIB_EXCEPTION__

#include <iostream>
#include <sstream>
#include <cstdlib>

namespace SGTELIB {

  class Exception : public std::exception {

  private:

    std::string _file;
    int         _line;
    std::string _err_msg;

    mutable std::string _tmp;

  public:

    virtual const char * what ( void ) const throw() {
      std::ostringstream oss;
      oss << _file << ":" << _line << " (" << _err_msg << ")";
      _tmp = oss.str();
      return _tmp.c_str();
    }

    Exception ( const std::string & file    ,
		int                 line    ,
		const std::string & err_msg   )
      : _file(file) , _line(line) , _err_msg(err_msg) {}
    
    virtual ~Exception ( void ) throw() {}
  };
}

// usage: throw SGTELIB::Exception ( "file.cpp" , __LINE__ , "error message" );

#endif
