#include <iostream>
#include <vector>
#include <sstream>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

class Util {

  public:
    
// Output an arbitrary number of elements from a vector to std::cout
    template <typename T>
      void printVec(T& vec, int nval=0) {
        int cnt = 0;
        for (const auto& e : vec) {
          std::cout << e << " ";
          if (nval > 0 && ++cnt == nval) {break;}
        }; std::cout << std::endl;
      }

// Output an arbitrary number of Keys from a map to std::cout    
    template <typename T>
      void printMapKeys(T& pmap, int nval=25) {
        if (nval > 1) { 
          try {
            for (const auto& e : pmap) {
              std::cout << e.first << " ";
              --nval;
              if (nval == 0) {break;}
            }; std::cout << std::endl; 
          } catch (std::exception& e) {
            std::cerr << "Error printMapKeys may have been given something which is not a map" << std::endl;
            std::cerr << "Msg: " << e.what();
          }
        } 
      }

// Test if 'chkval' occurs in the vector 'invec'
    template<typename T>
      bool has(const std::vector<T>& invec, const T& chkval) {
        for (const auto& e : invec) {
          if (e == chkval) {
            return true;
          }
        }
        return false;
      }

// get index of chkval in vec 
    template<typename T>
      int getIndx(const std::vector<T>& vec, const T& chkval) {
        int ix = 0;
        for (const T& e : vec) {
          if (e == chkval) {
            return ix;
          }
          ++ix;
        }
        return -1; 
      }

// make string out of vector
    template<typename T>
      std::string vec2str(std::vector<T>& vec, std::string sep="\t") {
        std::stringstream s;
        for (int i = 0; i < vec.size()-1; ++i) {
          s << vec[i] << sep;
        }
        s << vec.back();
        return s.str();
      }

// make_unique for c++11 (following 6 templates)
// from https://stackoverflow.com/questions/17902405/how-to-implement-make-unique-function-in-c11
		template<class T> struct _Unique_if {
			typedef std::unique_ptr<T> _Single_object;
		};

		template<class T> struct _Unique_if<T[]> {
			typedef std::unique_ptr<T[]> _Unknown_bound;
		};

		template<class T, size_t N> struct _Unique_if<T[N]> {
			typedef void _Known_bound;
		};

		template<class T, class... Args>
			typename _Unique_if<T>::_Single_object
			make_unique(Args&&... args) {
				return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
			}

		template<class T>
			typename _Unique_if<T>::_Unknown_bound
			make_unique(size_t n) {
				typedef typename std::remove_extent<T>::type U;
				return std::unique_ptr<T>(new U[n]());
			}

		template<class T, class... Args>
			typename _Unique_if<T>::_Known_bound
			make_unique(Args&&...) = delete;
};


