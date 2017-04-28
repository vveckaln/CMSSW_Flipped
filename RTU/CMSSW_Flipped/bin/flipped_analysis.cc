#include "TFile.h"
#include "TH1.h"
#include <stdio.h>
#include "RTU/CMSSW_Flipped/interface/CFAT_cmssw.hh"
#include "RTU/CMSSW_Flipped/interface/MiniEvent.h"
//#include "RTU/CMSSW_Flipped/interface/CFAT_Event.hh"
#include "RTU/CMSSW_Flipped/interface/CFAT_AssignHistograms.hh"
#include "RTU/CMSSW_Flipped/interface/CFAT_Core_cmssw.hh"
#include "RTU/CMSSW_Flipped/interface/Definitions_cmssw.hh"
//#include "TopQuarkAnalysis/TopTools/interface/MEzCalculator.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  MiniEvent_t event;
  const TString filename(argv[1]);
  printf("int main(): opening file %s", filename.Data());
  getchar();
  TFile * file = TFile::Open(filename);
  TTree * tree = (TTree*)file -> Get("analysis/data");
  attachToMiniEventTree(tree, event, true);
  const unsigned long nentries(tree -> GetEntriesFast());
  printf("number of entries %lu\n", nentries);
  getchar();
  tree -> GetEntry(0);

  map<TString, TH1 *> allPlots;
  CFAT_cmssw colour_flow_analysis_tool;
  AssignHistograms(allPlots);
  colour_flow_analysis_tool.plots_ptr_ = & allPlots;
  for (unsigned long iev = 0; iev < nentries; iev ++)                                                                                                                                                        {                                                                                                                                                                                                   
      tree->GetEntry(iev);                                                                                                                                                                                     if(iev % 10 == 0) printf ("\r [%3.0f%%] done", 100.*(float)iev/(float)nentries);           
    }
  file -> Close();
  printf("exiting\n");
}
