#ifndef FastSimulation_TrackingRecHitProducer_SiClusterTranslator_h
#define FastSimulation_TrackingRecHitProducer_SiClusterTranslator_h

//---------------------------------------------------------------------------
//! \class SiClusterTranslator
//! \author: Douglas Orbaker 
//! \email: Douglas.Orbaker@cern.ch
//! \Takes Clusters Produced by the FastSim and converts them to the standard
//! cluster type.
//!
//---------------------------------------------------------------------------

// Framework
#include "FWCore/Framework/interface/EDProducer.h"

// Data Formats
#include "FastSimDataFormats/External/interface/FastTrackerClusterCollection.h"
//Strip and Pixel Cluster Collection
#include "DataFormats/SiStripCluster/interface/SiStripClusterCollection.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "SimDataFormats/TrackerDigiSimLink/interface/StripDigiSimLink.h"
#include "SimDataFormats/TrackerDigiSimLink/interface/PixelDigiSimLink.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "DataFormats/Common/interface/DetSet.h"

class TrackerGeometry;
class DetId;

namespace edm { 
  class ParameterSet;
  class Event;
  class EventSetup;
}

class SiClusterTranslator : public edm::EDProducer
{
 public:
  //--- Constructor, virtual destructor (just in case)
  explicit SiClusterTranslator(const edm::ParameterSet& conf);
  virtual ~SiClusterTranslator();
  
  //--- The top-level event method.
  virtual void produce(edm::Event& e, const edm::EventSetup& c);
  
  // Begin Job
  virtual void beginRun(edm::Run & run, const edm::EventSetup & es);
  
 private:
  std::vector<edm::DetSet<StripDigiSimLink> > theStripDigiLinkVector;
  std::vector<edm::DetSet<PixelDigiSimLink> > thePixelDigiLinkVector;
  std::vector<std::pair<PSimHit, int > > theNewSimHitList;
  void loadPixelClusters(std::map<DetId,std::vector<SiPixelCluster> >& theClusters,
			 SiPixelClusterCollectionNew& theClusterCollection) const;
  void loadStripClusters(std::map<DetId,std::vector<SiStripCluster> >& theClusters,
			 edmNew::DetSetVector<SiStripCluster>& theClusterCollection) const; 
  
  
  const TrackerGeometry* geometry;
};


#endif
