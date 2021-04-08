#ifndef TEST_E4H2L_H
#define TEST_E4H2L_H

#include <GaudiAlg/GaudiAlgorithm.h>

#include <string>

#include "k4FWCore/DataHandle.h"

// EDM4hep
#include "edm4hep/ParticleID.h"
#include "edm4hep/ParticleIDCollection.h"
// #include "edm4hep/ReconstructedParticle.h"
// #include "edm4hep/ReconstructedParticleCollection.h"
// #include "edm4hep/ReconstructedParticleData.h"
#include "edm4hep/Track.h"
#include "edm4hep/TrackCollection.h"
#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/CalorimeterHitCollection.h"
// #include "edm4hep/Cluster.h"
// #include "edm4hep/ClusterCollection.h"
// #include "edm4hep/Vertex.h"
// #include "edm4hep/VertexCollection.h"

// LCIO
#include "lcio.h"
#include "IMPL/LCEventImpl.h"
#include "IMPL/LCCollectionVec.h"
#include "IMPL/ReconstructedParticleImpl.h"
#include "IMPL/TrackImpl.h"
#include "IMPL/TrackStateImpl.h"
#include "IMPL/CalorimeterHitImpl.h"
#include "IMPL/TrackerHitImpl.h"
#include "IMPL/ClusterImpl.h"
#include "IMPL/VertexImpl.h"
#include "IMPL/ParticleIDImpl.h"

#include "LCIOSTLTypes.h"

// Interface
#include "converters/IEDMConverter.h"
#include "converters/EDM4hep2Lcio.h"
#include "converters/Lcio2EDM4hep.h"

// #include "util/k4MarlinWrapperUtil.h"


class TestE4H2L : public GaudiAlgorithm {
public:
  explicit TestE4H2L(const std::string& name, ISvcLocator* pSL);
  virtual ~TestE4H2L() = default;
  virtual StatusCode execute() override final;
  virtual StatusCode finalize() override final;
  virtual StatusCode initialize() override final;

private:

  ToolHandle<IEDMConverter> m_edm_conversionTool{"IEDMConverter/EDM4hep2Lcio", this};
  ToolHandle<IEDMConverter> m_lcio_conversionTool{"IEDMConverter/Lcio2EDM4hep", this};

  std::map<std::string, DataObjectHandleBase*> m_dataHandlesMap;

  const std::string m_e4h_callohit_name   = "E4H_CaloHitCollection";
  const std::string m_e4h_trackerhit_name = "E4H_TrackerHitCollection";
  const std::string m_e4h_track_name      = "E4H_TrackCollection";

  const std::string m_lcio_callohit_name   = "LCIO_CaloHitCollection";
  const std::string m_lcio_trackerhit_name = "LCIO_TrackerHitCollection";
  const std::string m_lcio_track_name      = "LCIO_TrackCollection";

  void createCalorimeterHits(const int num_elements, int& int_cnt, float& float_cnt);
  void createTrackerHits(const int num_elements, int& int_cnt, float& float_cnt);
  void createTracks(
    const int num_elements,
    const int subdetectorhitnumbers,
    const std::vector<uint>& link_trackerhits_idx,
    const int num_track_states,
    const std::vector<std::pair<uint, uint>>& track_link_tracks_idx,
    int& int_cnt,
    float& float_cnt);

  bool checkEDMTrackerHitLCIOTrackerHit(lcio::LCEventImpl* the_event);
  bool checkEDMTrackLCIOTrack(
    lcio::LCEventImpl* the_event,
    const std::vector<uint>& link_trackerhits_idx,
    const std::vector<std::pair<uint, uint>>& track_link_tracks_idx);

  bool checkEDMCaloHitEDMCaloHit();
  bool checkEDMTrackEDMTrack();

};


#endif