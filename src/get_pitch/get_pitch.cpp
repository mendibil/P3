/// @file

#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "wavfile_mono.h"
#include "pitch_analyzer.h"
#include "docopt.h"

#define FRAME_LEN   0.030 /* 30 ms. */
#define FRAME_SHIFT 0.015 /* 15 ms. */

using namespace std;
using namespace upc;

static const char USAGE[] = R"(
get_pitch - Pitch Detector 
Usage:
    get_pitch [options] <input-wav> <output-txt> [<probpoth_>] [<probpotl_>] [<probzeros_>] [<probr1normh_>] [<probr1norml_>]
                                                 [<probrmaxnormh_>] [<probrmaxnorml_>] [<probmin_>] [<cthpos_>] [<cthneg_>]
                                                 [<thpoth_>] [<thpotl_>] [<thzeros_>] [<thr1h_>] [<thr1l_>]
                                                 [<thrmaxh_>] [<thrmaxl_>]
    get_pitch (-h | --help)
    get_pitch --version
Options:
    -h, --help  Show this screen
    --version   Show the version of the project
Arguments:
    input-wav       Wave file with the audio signal
    output-txt      Output file: ASCII file with the result of the detection:
                        - One line per frame with the estimated f0
                        - If considered unvoiced, f0 must be set to f0 = 0
    probpoth_       Enter probpoth_
    probpotl_       Enter probpotl_ 
    probzeros_      Enter probzeros_
    probr1normh_    Enter probr1normh_
    probr1norml_    Enter probr1norml_
    probrmaxnormh_  Enter probrmaxnormh_
    probrmaxnorml_  Enter probrmaxnorml_
    probmin_        Enter probmin_
    cthpos_         Enter cthpos_
    cthneg_         Enter cthneg_
    thpoth_         Enter thpoth_
    thpotl_         Enter thpotl_
    thzeros_        Enter thzeros_
    thr1h_          Enter thr1h_
    thr1l_          Enter thr1l_
    thrmaxh_        Enter thrmaxh_
    thrmaxl_        Enter thrmaxl_
)";

int main(int argc, const char *argv[]) {
	/// \DONE
	///  Modify the program syntax and the call to **docopt()** in order to
	///  add options and arguments to the program.

  //Version probabilidades
  #if 1
    float   probpoth_       = 9.86290953e+01,
            probpotl_       = 4.98587206e+00,
            probzeros_      = 7.27325098e-01,
            probr1normh_    = 1.40249288e+00,
            probr1norml_    = 4.50000000e-01,
            probrmaxnormh_  = 2.60698850e+00,
            probrmaxnorml_  = 4.94947053e-01,
            probmin_        = 7.08996317e+01,
            cthpos_         = 9.09672067e-01,
            cthneg_         = 5.30373467e-01,
            thpoth_         = 3.00586587e+01,
            thpotl_         = 5.71000000e+01,
            thzeros_        = 7.80579518e+02,
            thr1h_          = 9.79019880e-01,
            thr1l_          = 4.00000000e-01,
            thrmaxh_        = 5.04249668e-01,
            thrmaxl_        = 2.66764520e-01;          
  #endif

  //Version parametros
  #if 0
    float pot_ = 47.0F, r1norm_ = 80, rmaxnorm_ = 10;
    int zeros_ = 1448;
    float thcc1_ = 0.1;
    float thcc2_ = 0.1;
    float minf0_ = 60;
    float maxf0_ = 370;
  #endif


  std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},	// array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string

	std::string input_wav   = args["<input-wav>"].asString();
	std::string output_txt  = args["<output-txt>"].asString();

  //Si pasamos parametros como argumentos
  if(argc > 3) {
    #if 1
    std::string probpoth          = args["<probpoth_>"].asString();
    std::string probpotl          = args["<probpotl_>"].asString();
    std::string probzeros         = args["<probzeros_>"].asString();
    std::string probr1normh       = args["<probr1normh_>"].asString();
    std::string probr1norml       = args["<probr1norml_>"].asString();
    std::string probrmaxnormh     = args["<probrmaxnormh_>"].asString();
    std::string probrmaxnorml     = args["<probrmaxnorml_>"].asString();
    std::string probmin           = args["<probmin_>"].asString();
    std::string cthpos            = args["<cthpos_>"].asString();
    std::string cthneg            = args["<cthneg_>"].asString();
    std::string thpoth            = args["<thpoth_>"].asString();
    std::string thpotl            = args["<thpotl_>"].asString();
    std::string thzeros           = args["<thzeros_>"].asString();
    std::string thr1h             = args["<thr1h_>"].asString();
    std::string thr1l             = args["<thr1l_>"].asString();
    std::string thrmaxh           = args["<thrmaxh_>"].asString();
    std::string thrmaxl           = args["<thrmaxl_>"].asString();
    probpoth_       = (::atof(probpoth.c_str()))/10000;
    probpotl_       = (::atof(probpotl.c_str()))/10000;
    probzeros_      = (::atof(probzeros.c_str()))/10000;
    probr1normh_    = (::atof(probr1normh.c_str()))/10000;
    probr1norml_    = (::atof(probr1norml.c_str()))/10000;
    probrmaxnormh_  = (::atof(probrmaxnormh.c_str()))/10000;
    probrmaxnorml_  = (::atof(probrmaxnorml.c_str()))/10000;
    probmin_        = (::atof(probmin.c_str()))/10000;
    cthpos_         = (::atof(cthpos.c_str()))/10000;
    cthneg_         = (::atof(cthneg.c_str()))/10000;
    thpoth_         = (::atof(thpoth.c_str()))/10000;
    thpotl_         = (::atof(thpotl.c_str()))/10000;
    thzeros_        = (::atof(thzeros.c_str()));
    thr1h_          = (::atof(thr1h.c_str()))/10000;
    thr1l_          = (::atof(thr1l.c_str()))/10000;
    thrmaxh_        = (::atof(thrmaxh.c_str()))/10000;
    thrmaxl_        = (::atof(thrmaxl.c_str()))/10000;
    #endif

    //Version antigua
    /*
      std::string pot         = args["<pot_>"].asString();
      std::string r1norm      = args["<r1norm_>"].asString();
      std::string rmaxnorm    = args["<rmaxnorm_>"].asString();
      std::string zeros       = args["<zeros_>"].asString();
      std::string thcc1       = args["<thcc1_>"].asString();
      std::string thcc2       = args["<thcc2_>"].asString();
      std::string minf0       = args["<minf0_>"].asString();
      std::string maxf0       = args["<maxf0_>"].asString();
      pot_      = ::atof(pot.c_str());
      r1norm_   = ::atof(r1norm.c_str());
      rmaxnorm_ = ::atof(rmaxnorm.c_str());
      zeros_    = ::atoi(zeros.c_str());
      thcc1_    = ::atof(thcc1.c_str()) / 100;
      thcc2_    = ::atof(thcc2.c_str()) / 100;
      minf0_    = ::atof(minf0.c_str());
      maxf0_    = ::atof(maxf0.c_str());
    */
  }

  

  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }

  int n_len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT;

  // Define analyzer
  PitchAnalyzer analyzer(probpoth_, probpotl_, probzeros_, probr1normh_, probr1norml_, probrmaxnormh_, probrmaxnorml_, probmin_, 
  thpoth_, thpotl_, thzeros_, thr1h_, thr1l_, thrmaxh_, thrmaxl_, n_len, rate, PitchAnalyzer::HAMMING, 50, 405);

  /// \DONE
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.


  /******************* CENTRAL CLIPPING *******************/
  /****** Calcul del threshhold de veu a partir de la potencia mitja ******/
  float thpos, thneg = 0.0;
  float potmitja = 0.0;
  for (unsigned int i = 0; i < x.size(); i++)
  {
    potmitja += fabs(x[i]) * fabs(x[i]);
  }
  potmitja = (1.0F / x.size()) * potmitja;
  
  thpos = potmitja * cthpos_;
  thneg = potmitja * cthpos_;


  /****** Manera 1: sense offset: Descartat ******/ 
  //  for(int i=0; i<x.size(); i++){
  //    if(x[i]>-th && x[i]<th){
  //      
  //     x[i] = 0;
  //    } else {
  //      cout << "Valor fora de threshold: \t" << x[i] << '\n' ;
  //    }
  //  }

  /****** Manera 2: amb offset ******/
  for(int i=0; i<x.size(); i++){
    if(x[i]>thpos){
      x[i] = x[i] -thpos;
    } else if (x[i] < -thneg){
      x[i] = x[i] + thneg;
    } else {
      x[i] = 0;
    }
  }

  // Iterate for each frame and save values in f0 vector
  vector<float>::iterator iX;
  vector<float> f0;
  for (iX = x.begin(); iX + n_len < x.end(); iX = iX + n_shift) {
    float f = analyzer(iX, iX + n_len);
    f0.push_back(f);
  }

  /// \DONE
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.

  // ****************** MEDIAN FILTER ******************/
  unsigned int window = 3;
  for(int i=1; i<f0.size()-1; i++){ 
    // Recorrem tot el vector de aproximacions de pitch
    // excepte el primer i l'ultim valor perque el filtro
    // de mediana necessita els neighbours

    // Creem un vector de 3 elements i l'ordenem
    float sortedf0[] = {f0[i-1], f0[i], f0[i+1] };
    std::sort(sortedf0, sortedf0 + window);

    // Assignem al valor del element f0[i] el 
    // valor del mig dels elements ordenats
    f0[i] = sortedf0[1];
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