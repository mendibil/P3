/// @file

#include <iostream>
#include <math.h>
#include <fstream>
#include "pitch_analyzer.h"

using namespace std;

/// Name space of UPC
namespace upc {
  void PitchAnalyzer::autocorrelation(const vector<float> &x, vector<float> &r) const {
    /// \DONE Compute the autocorrelation r[k]
    for (unsigned int k = 0; k < r.size(); ++k) {
      for(unsigned int m = 0; m < x.size()-k-1; ++m) {
        r[k] += x[m]*x[m+k];
      }
      r[k] = r[k] / x.size();
    }

    if (r[0] == 0.0F) //to avoid log() and divide zero 
      r[0] = 1e-10; 

  }

  void PitchAnalyzer::set_window(Window win_type) {
    if (frameLen == 0)
      return;

    window.resize(frameLen);

    switch (win_type) {
    case HAMMING:
      /// \DONE Implement the Hamming window
      for (unsigned int n = 0; n < frameLen; ++n) {
        window[n] = 0.54 - 0.46 * cos( 2 * M_PI * n / (frameLen - 1) );
      }
      break;
    case RECT:
    default:
      window.assign(frameLen, 1);
    }
  }

  void PitchAnalyzer::set_f0_range(float min_F0, float max_F0) {
    npitch_min = (unsigned int) samplingFreq/max_F0;
    if (npitch_min < 2)
      npitch_min = 2;  // samplingFreq/2

    npitch_max = 1 + (unsigned int) samplingFreq/min_F0;

    //frameLen should include at least 2*T0
    if (npitch_max > frameLen/2)
      npitch_max = frameLen/2;
  }

  bool PitchAnalyzer::unvoiced(float pot, float r1norm, float rmaxnorm, int zeros) const {
    /// \DONE Implement a rule to decide whether the sound is voiced or not.
    /// * You can use the standard features (pot, r1norm, rmaxnorm),
    ///   or compute and use other ones.
    

    /*** Version probabilidades ***/
    float probveu = 0.0;

    //Power
    if(pot > -thpoth_)
      probveu = probpoth_;
    else if(pot < -thpotl_)
      probveu = probpotl_;
    else
      probveu = probpotl_ + (probpoth_ - probpotl_) * (pot + thpotl_) / (-thpoth_ + thpotl_);
    
    //ZCR
    if(zeros > thzeros_)
      probveu *= probzeros_;

    //r1norm
    if(r1norm > thr1h_)
      probveu *= probr1normh_;
    else if (r1norm < thr1l_)
      probveu *= probr1norml_;
    else
      probveu *= probr1norml_+ (probr1normh_ - probr1norml_) * (r1norm - thr1l_) / (thr1h_ - thr1l_);
  
    //rmaxnorm
    if(rmaxnorm > thrmaxh_)
      probveu *= probrmaxnormh_;
    else if(rmaxnorm <thrmaxl_)
      probveu *= probrmaxnorml_;
    else
      probveu *= probrmaxnorml_ + (probrmaxnormh_ - probrmaxnorml_) * (rmaxnorm - thrmaxl_) / (thrmaxh_- thrmaxl_);

    //Decision
    if(probveu >= probmin_) return false;
    else return true;

    //-----------------------------------------------//

    /*** Version solo parametros ***/
    /*
    //Totalment Unvoiced
    if(pot < -47.5 && zeros > 2700) return true;
    if(pot < -54 && r1norm < 0.32) return true;
    if(pot > -35 && zeros > 2500) return true;
    if(rmaxnorm < 0.13 && r1norm < 0.32) return true;
    if(pot < -50 && pot > -77 && rmaxnorm < 0.8 & zeros > 0) return true;

    //Totalment Voiced                                   
    if(pot > -24.74) return false;
    else if(rmaxnorm > 0.852) return false;
    else if(pot > -32.5 && rmaxnorm > 0.775) return false;
    else if(pot > -39.1 && r1norm > 0.988) return false;
    
    //Primera versión
    if(
        pot       < pot_                     || 
        r1norm    < r1norm_                  || 
        rmaxnorm  < rmaxnorm_                ||
        zeros     > zeros_                   ||
        (r1norm    < 0.94 && rmaxnorm < 0.42)) {
        return true;
    } else {
      return false;
    }
    */
  }

  int PitchAnalyzer::compute_zcr(std::vector<float> &x, unsigned int N, float fm) const{
    int zcr = 0;

    for(int i = 1; i < N; i++) {
        if(x[i-1] * x[i] < 0)
          zcr++;
    }
    zcr = fm/(2* (N-1)) * zcr;
    return zcr;
  }

  float PitchAnalyzer::compute_pitch(vector<float> & x) const {
    
    if (x.size() != frameLen)
      return -1.0F;

    //Window input frame
    for (unsigned int i = 0; i < x.size(); ++i)
      x[i] *= window[i];

    vector<float> r(npitch_max);

    /// \DONE
    /// Find the lag of the maximum value of the autocorrelation away from the origin.<br>
    /// Choices to set the minimum value of the lag are:

    //Compute correlation
    autocorrelation(x, r);

    //Limits reals que imposarem a l'hora de decidir el pitch
    float maxf0_real = 340; //Hi ha alguns de mes de 340 Hz pero dona millor resultat aixi
    float minf0_real = 60;
    unsigned int nmin_real = (unsigned int) samplingFreq / maxf0_real;
    unsigned int nmax_real = (unsigned int) samplingFreq / minf0_real;

    vector<float>::const_iterator iR = r.begin(), iRMax = iR;

    iR += npitch_min;
    iRMax = iR;

	  /// In either case, the lag should not exceed that of the minimum value of the pitch (trampa)
    while(iR != r.end() && (iR - r.begin()) < npitch_max) {
      if(*iR > *iRMax)
        iRMax = iR;
      ++iR;
    }
    unsigned int lag = iRMax - r.begin();

    //Ara, si el lag calculat es correspon amb un pitch no coherent (fora del rang f0_real)
    //retornarem f0 = 0 Hz, com si s'hagues interpretat com unvoiced.
    //Millora el resultat perquè és una forma de "trobar segments unvoiced",
    //que no ens aconsegueix detectar la funció unvoiced() a partir
    //dels paràmetres del frame.
    //Descriminem segons la detecció de pitch utilitzant l'autocorrelació
    if(lag < nmin_real || nmax_real < lag)
      return 0;

    float pot = 10 * log10(r[0]);
    int zeros = compute_zcr(x, x.size(), 20e3);

    //You can print these (and other) features, look at them using wavesurfer
    //Based on that, implement a rule for unvoiced
    //change to #if 1 and compile
    #if 0
        ofstream fitxer;
        fitxer.open("param.txt", std::ios_base::app);
        fitxer.clear();
        if (r[0] > 0.0F)
          //cout << pot << '\t' << r[1]/r[0] << '\t' << r[lag]/r[0] << '\t';
          fitxer << "Pot: " << round(pot) << '\t' << "r1norm: " << round(r[1]/r[0]) << '\t' << "rmaxnorm: " << round(r[lag]/r[0]) << '\t';
          fitxer << "ZCR: " << round(zeros) << '\t';
          float f0 = (float) samplingFreq / (float) lag;
          //cout << f0 << endl;
          fitxer << "f0: " << round(f0) << endl;
          fitxer.close();
    #endif
    if (unvoiced(pot, r[1]/r[0], r[lag]/r[0], zeros))
      return 0;
    else
      return (float) samplingFreq / (float) lag;
  }
}