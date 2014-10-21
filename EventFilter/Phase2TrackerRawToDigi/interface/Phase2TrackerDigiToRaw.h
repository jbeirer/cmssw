#include "EventFilter/Phase2TrackerRawToDigi/interface/Phase2TrackerFEDDAQHeader.h"
#include "EventFilter/Phase2TrackerRawToDigi/interface/Phase2TrackerFEDDAQTrailer.h"
#include "EventFilter/Phase2TrackerRawToDigi/interface/Phase2TrackerFEDHeader.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "CondFormats/SiStripObjects/interface/Phase2TrackerCabling.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"

namespace Phase2Tracker
{
  enum STACK_LAYER
  {
      LAYER_UNUSED = -1,
      LAYER_INNER  = 0,
      LAYER_OUTER  = 1
  };

  class Phase2TrackerDigiToRaw
  {
    public:
      Phase2TrackerDigiToRaw() {}
      Phase2TrackerDigiToRaw(const Phase2TrackerCabling *, std::map<int,int>, edm::Handle< edmNew::DetSetVector<SiPixelCluster> >, int);
      ~Phase2TrackerDigiToRaw() {}
      // loop on FEDs to create buffers
      void buildFEDBuffers(std::auto_ptr<FEDRawDataCollection>&);
      // builds a single FED buffer
      std::vector<uint64_t> makeBuffer(std::vector<edmNew::DetSet<SiPixelCluster>>);
      // write FE Header to buffer
      void writeFeHeaderSparsified(std::vector<uint64_t>&,uint64_t&,int,int,int);
      // determine if a P or S cluster should be written
      void writeCluster(std::vector<uint64_t>&,uint64_t&,const SiPixelCluster*,int,STACK_LAYER);
      // write S cluster to buffer
      void writeSCluster(std::vector<uint64_t>&,uint64_t&,const SiPixelCluster*,STACK_LAYER);
      // write P cluster to buffer
      void writePCluster(std::vector<uint64_t>&,uint64_t&,const SiPixelCluster*);
      // compute chip id and strip number from digi
      std::pair<int,int> calcChipId(const SiPixelCluster*,STACK_LAYER);
    private:
      // data you get from outside
      const Phase2TrackerCabling * cabling_; 
      std::map<int,int> stackMap_;
      edm::Handle< edmNew::DetSetVector<SiPixelCluster> > digishandle_;
      int mode_;
      // headers 
      FEDDAQHeader FedDaqHeader_;
      FEDDAQTrailer FedDaqTrailer_; 
      Phase2TrackerFEDHeader FedHeader_;
  };
}
