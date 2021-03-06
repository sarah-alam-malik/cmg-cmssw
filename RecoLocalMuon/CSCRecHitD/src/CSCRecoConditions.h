#ifndef CSCRecRecHitD_CSCRecoConditions_h
#define CSCRecRecHitD_CSCRecoConditions_h

/**
 * \class CSCRecoConditions
 *
 * Wrap CSCConditions class for use in CSC local reconstruction, in analogy with wrapper classes
 * Rick uses in CSCDigitizer.
 *
 * CSCConditions encapsulates the conditions data (e.g. calibration data) from the database
 * and presents it as CSCRecHitD requires (and that is somewhat historical!)
 *
 * All functions in public interface accept CSCDetId for ME1A (i.e. ring 4) with channel
 * number 1-16 (and not the raw ME11 channel 65-80).
 *
 * \author Tim Cox - UC Davis
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CalibMuon/CSCCalibration/interface/CSCConditions.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"

class CSCRecoConditions 
{
 public:

  // Passed a PSet just in case we need to configure in some way
  explicit CSCRecoConditions(const edm::ParameterSet & pset);
  ~CSCRecoConditions();

  /// fetch the cond data from the database
  void initializeEvent(const edm::EventSetup & es);

  /// channels count from 1
  float gain(const CSCDetId & id, int channel) const;

  /// return average gain over entire CSC system
  float averageGain() const { 
     return theConditions.averageGain(); }

  ///  calculate gain weights for all strips in a CSC layer 
  /// - filled into C-array which caller must have allocated.
  void stripWeights( const CSCDetId& id, float* weights ) const;

  /// static pedestal in ADC counts
  float pedestal(const CSCDetId & id, int channel) const;

  /// sigma of static pedestal in ADC counts
  float pedestalSigma(const CSCDetId & id, int channel) const;

  /// fill expanded noise matrix for 3 neighbouring strips as linear vector (must be allocated by caller)
  /// Note that centralStrip is a 'geomStrip' and ranges 1-48 in ME1a.
  void noiseMatrix( const CSCDetId& id, int centralStrip, std::vector<float>& nme ) const;

  /// fill crosstalk information for 3 neighbouring strips as linear vector (must be allocated by caller)
  /// Note that centralStrip is a 'geomStrip' and ranges 1-48 in ME1a.
  void crossTalk( const CSCDetId& id, int centralStrip, std::vector<float>& xtalks) const;

   // returns chip speed correction in ns given detId (w/layer) and strip channel
  float chipCorrection( const CSCDetId & detId, int channel ) const;

   // returns chamber level timing correction (cable length and extra chamber correction) in ns 
  float chamberTimingCorrection( const CSCDetId & detId )const;

   // returns anode bx off for each chamber, used to correct anode times to 0 for collision muons
  float anodeBXoffset( const CSCDetId & detId )const;

  /// Is a neighbour bad?
  bool nearBadStrip( const CSCDetId& id, int geomStrip ) const;

  /// Is the strip bad?
  bool badStrip( const CSCDetId& id, int geomStrip ) const;

  /// Get bad wiregroup word
  const std::bitset<112>& badWireWord( const CSCDetId& id ) const;

  /// returns gas-gain correction given detId (w/layer), strip, channel.  This converts ME1/4 strips 1-16 to ME1/1 channels 65-80
  float gasGainCorrection( const CSCDetId & detId, int strip, int wire ) const;

 private:

  /// return gain weight for given strip channel
  ///
  /// WARNING - expects ME11 detId for both ME1b (channels 1-64) AND for ME1a (channels 65-80)
  /// so this requires 'raw' channel interface.
  float stripWeight( const CSCDetId& id, int channel ) const;


  CSCConditions theConditions;
};

#endif
