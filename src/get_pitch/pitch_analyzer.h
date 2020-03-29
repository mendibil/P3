/// @file

#ifndef PITCH_ANALYZER_H
#define PITCH_ANALYZER_H

#include <vector>
#include <algorithm>

namespace upc {
  const float MIN_F0 = 60.0F;    ///< Minimum value of pitch in Hertzs
  const float MAX_F0 = 370.0F; ///< Maximum value of pitch in Hertzs

  ///
  /// PitchAnalyzer: class that computes the pitch (in Hz) from a signal frame.
  /// No pre-processing or post-processing has been included
  ///
  class PitchAnalyzer {
  public:
	/// Wndow type
    enum Window {
		RECT, 						///< Rectangular window
		HAMMING						///< Hamming window
	};

    void set_window(Window type); ///< pre-compute window

  private:
    std::vector<float> window; ///< precomputed window
    unsigned int frameLen, ///< length of frame (in samples). Has to be set in the constructor call
      samplingFreq, ///< sampling rate (in samples per second). Has to be set in the constructor call
      npitch_min, ///< minimum value of pitch period, in samples
      npitch_max; ///< maximum value of pitch period, in samples
      //zeros_;
    float probpoth_, probpotl_, probzeros_, probr1normh_, probr1norml_, probrmaxnormh_, probrmaxnorml_, probmin_, thpoth_, thpotl_, thzeros_, thr1h_, thr1l_, thrmaxh_, thrmaxl_;
 
	///
	/// Computes correlation from lag=0 to r.size()
	///
    void autocorrelation(const std::vector<float> &x, std::vector<float> &r) const;

	///
	/// Returns the pitch (in Hz) of input frame x
	///
    float compute_pitch(std::vector<float> & x) const;
	
	///
	/// Returns true if the frame is unvoiced
	///
    bool unvoiced(float pot, float r1norm, float rmaxnorm, int zeros) const;

    int compute_zcr(std::vector<float> &x, unsigned int N, float fm) const;


  public:
  /*
    PitchAnalyzer(unsigned int fLen,			///< Frame length in samples
					        unsigned int sFreq,			///< Sampling rate in Hertzs
					        Window w=PitchAnalyzer::HAMMING,	///< Window type
					        float min_F0 = MIN_F0,		///< Pitch range should be restricted to be above this value
					        float max_F0 = MAX_F0)		///< Pitch range should be restricted to be below this value			 
	  {
      frameLen = fLen;
      samplingFreq = sFreq;
      set_f0_range(min_F0, max_F0);
      set_window(w);
      pot_ = -47.0F;
      r1norm_ = 0.8F;
      rmaxnorm_ = 0.1F;
      zeros_ = 1448;
    }
    */
    PitchAnalyzer(float probpoth, float probpotl, float probzeros, float probr1normh, float probr1norml, float probrmaxnormh, float probrmaxnorml, float probmin, float thpoth, float thpotl, float thzeros, float thr1h, float thr1l, float thrmaxh, float thrmaxl,
                  unsigned int fLen,			///< Frame length in samples
					        unsigned int sFreq,			///< Sampling rate in Hertzs
					        Window w=PitchAnalyzer::HAMMING,	///< Window type
					        float min_F0 = MIN_F0,		///< Pitch range should be restricted to be above this value
					        float max_F0 = MAX_F0)		///< Pitch range should be restricted to be below this value			 
	  {
      frameLen = fLen;
      samplingFreq = sFreq;
      set_f0_range(min_F0, max_F0);
      set_window(w);
      probpoth_ = probpoth;
      probpotl_ = probpotl;
      probzeros_ = probzeros;
      probr1normh_ = probr1normh;
      probr1norml_ = probr1norml;
      probrmaxnormh_ = probrmaxnormh;
      probrmaxnorml_ = probrmaxnorml;
      probmin_ = probmin;
      thpoth_ = thpoth;
      thpotl_ = thpotl;
      thzeros_ = thzeros;
      thr1h_ = thr1h;
      thr1l_ = thr1l;
      thrmaxh_ = thrmaxh;
      thrmaxl_ = thrmaxl;
    }


	///
    /// Operator (): computes the pitch for the given vector x
	///
    float operator()(const std::vector<float> & _x) const {
      if (_x.size() != frameLen)
        return -1.0F;

      std::vector<float> x(_x); //local copy of input frame
      return compute_pitch(x);
    }

	///
    /// Operator (): computes the pitch for the given "C" vector (float *).
    /// N is the size of the vector pointer by pt.
	///
    float operator()(const float * pt, unsigned int N) const {
      if (N != frameLen)
        return -1.0F;

      std::vector<float> x(N); //local copy of input frame, size N
      std::copy(pt, pt+N, x.begin()); ///copy input values into local vector x
      return compute_pitch(x);
    }

	///
    /// Operator (): computes the pitch for the given vector, expressed by the begin and end iterators
	///
    float operator()(std::vector<float>::const_iterator begin, std::vector<float>::const_iterator end) const {

      if (end-begin != frameLen)
        return -1.0F;

      std::vector<float> x(end-begin); //local copy of input frame, size N
      std::copy(begin, end, x.begin()); //copy input values into local vector x
      return compute_pitch(x);
    }
    
	///
    /// Sets pitch range: takes min_F0 and max_F0 in Hz, sets npitch_min and npitch_max in samples
	///
    void set_f0_range(float min_F0, float max_F0);
  };
}
#endif
