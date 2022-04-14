/// @file
#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>

#include "wavfile_mono.h"
#include "pitch_analyzer.h"

#include "docopt.h"

#define FRAME_LEN   0.030 /* 30 ms. */
#define FRAME_SHIFT 0.015 /* 15 ms. */

using namespace std;
using namespace upc;

static const char USAGE[] = R"(
get_pitch - Pitch Estimator 

Usage:
    get_pitch [options] <input-wav> <output-txt>
    get_pitch (-h | --help)
    get_pitch --version

Options:
    -m FLOAT, --umaxnorm FLOAT  Umbral del maximo de la autocorrelacion normalizada [default: 0.5]
    -h, --help  Show this screen
    --version   Show the version of the project

Arguments:
    input-wav   Wave file with the audio signal
    output-txt  Output file: ASCII file with the result of the estimation:
                    - One line per frame with the estimated f0
                    - If considered unvoiced, f0 must be set to f0 = 0
)";

int main(int argc, const char *argv[]) {
	/// \TODO 
	///  Modify the program syntax and the call to **docopt()** in order to
	///  add options and arguments to the program.
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},	// array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string

  //docopt = mapeo
	std::string input_wav = args["<input-wav>"].asString();
	std::string output_txt = args["<output-txt>"].asString();
  float umaxnorm = std::stof(args["--umaxnorm"].asString());

  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }

  int n_len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT; //desplazamiento

  // Define analyzer
  PitchAnalyzer analyzer(n_len, rate, PitchAnalyzer::RECT, 50, 500, umaxnorm);
  /// \FET -> add the argument umaxronm

  /// \TODO
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.
  
  // Iterate for each frame and save values in f0 vector
  vector<float>::iterator iX;
  vector<float> f0;

  //center-clipping: DATA 
  for (iX = x.begin(); iX  < x.end(); iX++ ) {
    if (*iX < 0.008){ //0.008
      *iX = 0;
    }

  }
  /// \FET -> center-cliping done

  for (iX = x.begin(); iX + n_len < x.end(); iX = iX + n_shift) {
    float f = analyzer(iX, iX + n_len);
    f0.push_back(f);
  }

  /// \TODO
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.
<<<<<<< HEAD

  /*vector<float> med; 
  int cont = 0;
  int k = 3;

  for (iX = 0; iX < f0.end(); ++iX){
    if(k<3){
      med[k]=*iX;
    }else{
      for(int r=0; r<k; r+k){
        med[k]+=med[r];
=======
  /// \FET -> Non recursive median filter 

  float aux = 0;
  int k_wind = 3; ///window size
  for(int i = 0; i < (int)f0.size(); i=i+k_wind){
    for(int j = 0; j < k_wind; ++j){
      if(i <= ((int)f0.size()-k_wind)){
        aux += f0[i + j]; 
      }else{
        aux = f0[i];
>>>>>>> 4ed4ded518897445f5625f95040f22ea7d73d4ca
      }
    }
<<<<<<< HEAD
  k++;
  }
  cont = 0;
  for (iX = f0.begin(); iX < f0.end(); ++iX){
    *iX = med[cont];
    cont++;
  }*/
=======
    f0[i] = aux/k_wind;
    aux=0;
  }
>>>>>>> 4ed4ded518897445f5625f95040f22ea7d73d4ca

int k_wind = 3; ///tamany finestra (millor 3 q 5)
  for(int i = 0; i < f0.size(); i=i+k_wind){
    for(int j = 0; j < k_wind; ++j){
      //iX[i+j]=(iX[i]+iX[k_wind-1])/2;        //meva
      iX[i + j] = iX[i + (k_wind - 1) / 2];   //bona
    }
  }
  
  // Write f0 contour into the output file
  ofstream os(output_txt);
  if (!os.good()) {
    cerr << "Error reading output file " << output_txt << " (" << strerror(errno) << ")\n";
    return -3;
  }

  os << 0 << '\n'; //pitch at t=0
  for (iX = f0.begin(); iX != f0.end(); ++iX) 
    os << *iX << '\n';
  os << 0 << '\n';//pitch at t=Dur

  return 0;
  
}
