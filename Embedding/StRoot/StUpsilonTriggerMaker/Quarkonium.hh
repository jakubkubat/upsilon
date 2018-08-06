//
// Pibero Djawwotho <pibero@iucf.indiana.edu>
// Indiana University
// March 19, 2006
//
// Revised 3 June 2008
//

#ifndef Quarkonium_hh
#define Quarkonium_hh

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;

#include "trgStructures.h"
#include "bemcTower.h"

class Histogram;

struct BemcCluster {
  float x;
  float y;
  float z;
  float E;
};

class Timer {
public:
  void start();
  time_t time() const;

private:
  time_t startTime;
};

class Quarkonium {
public:
  Quarkonium(const string& name = "quarkonium");
  ~Quarkonium();

  string name() const;

  void init(int runNumber, int userInt[], float userFloat[]);
  bool run(TrgDataType* trgData, unsigned short* bemcData);
  void finish();
  void print();

  vector< pair<int, int> > candidates;
  float mEnergyDaughter1;
  float mEnergyDaughter2;
  float mCosTheta;
  float mInvMass;
  vector<int> L0candidates;

private:
  void  findSeedTowers(vector<int>& L0Seeds, vector<int>& L2Seeds);
  void  calcCluster(int daqId);
  bool  checkClusterCtbHit(int daqId) const;
  float bbcVertexZ() const;
  void  readBemcTower();
  void  readBemcStatus();
  void  readBemcCtbMap();
  void  makeBemcTables();
  void  makeBemcGainTable();
  void  makeBemcHwPedestalTable();
  void  makeBemcPedestalTable();
  void  makeBemcKillTable();
  void  makeBemcPositionTable();
  void  makeBemcNeighborTable();

  void  createHistograms();
  void  writeHistograms();
  void  resetHistograms();
  void  deleteHistograms();

  void setBaseFileName(int runNumber);
  string timeString() const;

  void readBtowDbFile();
  void readTowerMaskFile();
  void readBemcKillTable();
  void readCtbKillTable();

  static BemcTower bemcTower[4800];
  static BemcCluster bemcCluster[4800];
  static int daqIdFromSoftId[4801];
  static int bemcCtbMap[4800];
  static TrgDataType* trgData;
  static unsigned short* bemcData;
  static int ctbKill[256];

  string fName;
  string fBaseFileName;
  ofstream fLogfile;

  int fEventsSeen;
  int fEventsAccepted;
  int fRunNumber;

  // float parameters
  float fMinL0ClusterEnergy;
  float fMinL2ClusterEnergy;
  float fMinInvMass;
  float fMaxInvMass;
  float fMaxCosTheta;

  // int parameters
  int fL0SeedThreshold;
  int fL2SeedThreshold;
  int fUseCtb;
  int fUseVertexZ;
  int fNumberOfTowersPerCluster;

  // Histograms
  vector<Histogram*> fHistograms;
  Histogram* hL0SeedTowers;
  Histogram* hL2SeedTowers;
  Histogram* hNumberOfL0Seeds;
  Histogram* hNumberOfL2Seeds;
  Histogram* hInvMass;
  Histogram* hTime;
  Histogram* hEnergyOfL0Cluster;
  Histogram* hEnergyOfL2Cluster;
  Histogram* hCosTheta;
  Histogram* hVertexZ;
  Histogram* hCtbIndex;
  Histogram* hHighTowers;
  Histogram* hL0rate;
  Histogram* hL2rate;

  // Timer
  Timer timer;
};

inline void Timer::start() { startTime = std::time(0); }
inline time_t Timer::time() const { return std::time(0) - startTime; }

inline Quarkonium::Quarkonium(const string& name) : fName(name) { createHistograms(); }

inline Quarkonium::~Quarkonium()
{
  if (fLogfile.is_open()) finish();
  deleteHistograms();
}

inline string Quarkonium::name() const { return fName; }

extern Quarkonium jpsi;
extern Quarkonium ups;

#endif
