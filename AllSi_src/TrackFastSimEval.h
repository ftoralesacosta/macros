// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef TRACKFASTSIMEVAL_H
#define TRACKFASTSIMEVAL_H

#include <fun4all/SubsysReco.h>

#include <map>
#include <set>
#include <string>

//Forward declarations
class PHCompositeNode;
class PHG4TruthInfoContainer;
class SvtxTrackMap;
class SvtxVertexMap;
class TTree;
class TH2D;

//Brief: basic ntuple and histogram creation for sim evaluation
class TrackFastSimEval : public SubsysReco
{
 public:
  //Default constructor
  TrackFastSimEval(const std::string& name = "TrackFastSimEval",
                   const std::string& filename = "g4eval.root",
                   const std::string& trackmapname = "SvtxTrackMap");

  //Initialization, called for initialization
  int Init(PHCompositeNode*);

  //Process Event, called for each event
  int process_event(PHCompositeNode*);

  //End, write and close files
  int End(PHCompositeNode*);

  //Change output filename
  void set_filename(const char* file)
  {
    if (file) _outfile_name = file;
  }

  //Flags of different kinds of outputs
  enum Flag
  {
    //all disabled
    NONE = 0,
  };

  //Set the flag
  //Flags should be set like set_flag(TrackFastSimEval::TRUTH, true) from macro
  void set_flag(const Flag& flag, const bool& value)
  {
    if (value)
      _flags |= flag;
    else
      _flags &= (~flag);
  }

  //User modules
  void reset_variables();
  void AddProjection(const std::string& name);

 private:
  void fill_track_tree(PHCompositeNode*);
  void fill_vertex_tree(PHCompositeNode*);

  //output filename
  std::string _outfile_name;

  //name of SvtxTrackMap collection
  std::string _trackmapname;

  //Event counter
  int _event;

  //Get all the nodes
  int GetNodes(PHCompositeNode*);

  //flags
  unsigned int _flags;

  //TTrees
  TTree* _eval_tree_tracks;
  TTree* _eval_tree_vertex;
  int event;
  //-- truth
  int gtrackID;
  int gflavor;
  float gpx;
  float gpy;
  float gpz;
  float gvx;
  float gvy;
  float gvz;
  float gvt;

  //-- reco
  int trackID;
  int charge;
  int nhits;
  float px;
  float py;
  float pz;
  float pcax;
  float pcay;
  float pcaz;
  float dca2d;

  static const int nproj = 3;
  // projections hits/mom
  float proj[3][nproj];
  float proj_p[3][nproj];
  // hits/mom at reference
  float ref[3][nproj];
  float ref_p[3][nproj];

  //vertex
  float vx;
  float vy;
  float vz;
  float deltavx;
  float deltavy;
  float deltavz;
  int ntracks;
  int n_from_truth;

  //Histos
  TH2D* _h2d_Delta_mom_vs_truth_mom;
  TH2D* _h2d_Delta_mom_vs_truth_eta;

  //Node pointers
  PHG4TruthInfoContainer* _truth_container;
  SvtxTrackMap* _trackmap;
  SvtxVertexMap* _vertexmap;

  std::map<std::string, int> m_ProjectionNameMap;
};

#endif  //* TRACKFASTSIMEVAL_H *//
