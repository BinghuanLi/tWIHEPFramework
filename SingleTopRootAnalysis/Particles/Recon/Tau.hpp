/******************************************************************************
 * Tau.hpp                                                                    *
 *                                                                            *
 * Store information about final state Taus                                   *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Tau class                                       *
 *    Tau()                              -- Default Constructor               *
 *    Tau()                              -- Parameterized Constructor         *
 *    Tau()                              -- Constructor with Particle         *
 *    ~Tau()                             -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill tau from event tree          *
 *    FillFastSim                        -- Fill tau from FastSim tree        *
 *    SetSetNumTracks                    -- Set Num Tracks                    *
 *    GetSetNumTracks                    -- Set Num Tracks                    *
 *    NumTracks                          -- Set Num Tracks                    *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Tau              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of Tau class                                          *
 *    Double_t _NumTracks                -- CAL Energy in cone around Tau     *
 *                                                                            *
 *****************************************************************************/

#ifndef tau_h
#define tau_h

#include "SingleTopRootAnalysis/Particles/Recon/Particle.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Trees/EventTree.hpp"
#include "SingleTopRootAnalysis/Trees/FastSimTree.hpp"

class Lepton;

class Tau: public Particle
{
public:
  // Default Constructor
  Tau();

  // Copy constructor  - Tau
  Tau(const Tau& other);

  // Copy Constructor - Particle
  Tau(const Particle& other);

  // Destructor
  ~Tau();

  // Set all contents to their defaults
  inline void Clear() { 
      Particle::Clear(); _NumTracks = 0.0; 
        _charge =0.0;
        _dz =0.0;
        _dxy =0.0;
        _isVLoose =0.0;
        _isLoose =0.0;
        _isMedium =0.0;
        _isTight =0.0;
        _isVTight =0.0;
        _rawMVA =0.0;
        _rawDNNVSjet = 0.0 ;
        _isVVVLooseVSjet = 0.0 ;
        _isVVLooseVSjet = 0.0 ;
        _isVLooseVSjet = 0.0 ;
        _isLooseVSjet = 0.0 ;
        _isMediumVSjet = 0.0 ;
        _isTightVSjet = 0.0 ;
        _isVTightVSjet = 0.0 ;
        _isVVTightVSjet = 0.0 ;
        _rawDNNVSmu = 0.0 ;
        _isVLooseVSmu = 0.0 ;
        _isLooseVSmu = 0.0 ;
        _isMediumVSmu = 0.0 ;
        _isTightVSmu = 0.0 ;
        _rawDNNVSe = 0.0 ;
        _isVVVLooseVSe = 0.0 ;
        _isVVLooseVSe = 0.0 ;
        _isVLooseVSe = 0.0 ;
        _isLooseVSe = 0.0 ;
        _isMediumVSe = 0.0 ;
        _isTightVSe = 0.0 ;
        _isVTightVSe = 0.0 ;
        _isVVTightVSe = 0.0 ;
        _decayModeFinding =0.0;
        _index =0.0; // this is the index in Ntuple
      };

  // Fill the tau from an EventTree
  Bool_t Fill(std::vector<Lepton>& selectedLeptons, EventTree *evtr, Int_t iE, TString tauType);
  // also fill from a fastsim tree
  Bool_t FillFastSim(FastSimTree *tr, Int_t iE, TEnv* config);

  // Get and Set Number of tracks for this tau
  void SetNumTracks(const Double_t& eop) { _NumTracks = eop; };
  Double_t GetNumTracks() const { return _NumTracks; };
  Double_t NumTracks() const { return _NumTracks; };

  // Overloaded operators:
  // +=
  Tau& operator+=(const Tau& other);
  // +
  Tau operator+(const Tau& other);
  // = const Particle
  Tau& operator=(const Particle& other);
  // = const Tau
  Tau& operator=(const Tau& other);
  // = non-const Tau
  Tau& operator=(Tau& other);

  void SetCuts(TEnv *config);

//Inline functions
  inline void Setcharge(Double_t charge){_charge = charge;};
  inline Double_t Getcharge() const {return _charge;};
  inline Double_t charge() const {return _charge;};

  inline void Setdz(Double_t dz){_dz = dz;};
  inline Double_t Getdz() const {return _dz;};
  inline Double_t dz() const {return _dz;};

  inline void Setdxy(Double_t dxy){_dxy = dxy;};
  inline Double_t Getdxy() const {return _dxy;};
  inline Double_t dxy() const {return _dxy;};

  inline void SetisVLoose(Double_t isVLoose){_isVLoose = isVLoose;};
  inline Double_t GetisVLoose() const {return _isVLoose;};
  inline Double_t isVLoose() const {return _isVLoose;};

  inline void SetisLoose(Double_t isLoose){_isLoose = isLoose;};
  inline Double_t GetisLoose() const {return _isLoose;};
  inline Double_t isLoose() const {return _isLoose;};

  inline void SetisMedium(Double_t isMedium){_isMedium = isMedium;};
  inline Double_t GetisMedium() const {return _isMedium;};
  inline Double_t isMedium() const {return _isMedium;};

  inline void SetisTight(Double_t isTight){_isTight = isTight;};
  inline Double_t GetisTight() const {return _isTight;};
  inline Double_t isTight() const {return _isTight;};

  inline void SetisVTight(Double_t isVTight){_isVTight = isVTight;};
  inline Double_t GetisVTight() const {return _isVTight;};
  inline Double_t isVTight() const {return _isVTight;};

  inline void SetrawMVA(Double_t rawMVA){_rawMVA = rawMVA;};
  inline Double_t GetrawMVA() const {return _rawMVA;};
  inline Double_t rawMVA() const {return _rawMVA;};

  inline void SetrawDNNVSjet(Double_t rawDNNVSjet){_rawDNNVSjet = rawDNNVSjet;};
  inline Double_t GetrawDNNVSjet() const {return _rawDNNVSjet;};
  inline Double_t rawDNNVSjet() const {return _rawDNNVSjet;};

  inline void SetisVVVLooseVSjet(Double_t isVVVLooseVSjet){_isVVVLooseVSjet = isVVVLooseVSjet;};
  inline Double_t GetisVVVLooseVSjet() const {return _isVVVLooseVSjet;};
  inline Double_t isVVVLooseVSjet() const {return _isVVVLooseVSjet;};

  inline void SetisVVLooseVSjet(Double_t isVVLooseVSjet){_isVVLooseVSjet = isVVLooseVSjet;};
  inline Double_t GetisVVLooseVSjet() const {return _isVVLooseVSjet;};
  inline Double_t isVVLooseVSjet() const {return _isVVLooseVSjet;};

  inline void SetisVLooseVSjet(Double_t isVLooseVSjet){_isVLooseVSjet = isVLooseVSjet;};
  inline Double_t GetisVLooseVSjet() const {return _isVLooseVSjet;};
  inline Double_t isVLooseVSjet() const {return _isVLooseVSjet;};

  inline void SetisLooseVSjet(Double_t isLooseVSjet){_isLooseVSjet = isLooseVSjet;};
  inline Double_t GetisLooseVSjet() const {return _isLooseVSjet;};
  inline Double_t isLooseVSjet() const {return _isLooseVSjet;};

  inline void SetisMediumVSjet(Double_t isMediumVSjet){_isMediumVSjet = isMediumVSjet;};
  inline Double_t GetisMediumVSjet() const {return _isMediumVSjet;};
  inline Double_t isMediumVSjet() const {return _isMediumVSjet;};

  inline void SetisTightVSjet(Double_t isTightVSjet){_isTightVSjet = isTightVSjet;};
  inline Double_t GetisTightVSjet() const {return _isTightVSjet;};
  inline Double_t isTightVSjet() const {return _isTightVSjet;};

  inline void SetisVTightVSjet(Double_t isVTightVSjet){_isVTightVSjet = isVTightVSjet;};
  inline Double_t GetisVTightVSjet() const {return _isVTightVSjet;};
  inline Double_t isVTightVSjet() const {return _isVTightVSjet;};

  inline void SetisVVTightVSjet(Double_t isVVTightVSjet){_isVVTightVSjet = isVVTightVSjet;};
  inline Double_t GetisVVTightVSjet() const {return _isVVTightVSjet;};
  inline Double_t isVVTightVSjet() const {return _isVVTightVSjet;};

  inline void SetrawDNNVSmu(Double_t rawDNNVSmu){_rawDNNVSmu = rawDNNVSmu;};
  inline Double_t GetrawDNNVSmu() const {return _rawDNNVSmu;};
  inline Double_t rawDNNVSmu() const {return _rawDNNVSmu;};

  inline void SetisVLooseVSmu(Double_t isVLooseVSmu){_isVLooseVSmu = isVLooseVSmu;};
  inline Double_t GetisVLooseVSmu() const {return _isVLooseVSmu;};
  inline Double_t isVLooseVSmu() const {return _isVLooseVSmu;};

  inline void SetisLooseVSmu(Double_t isLooseVSmu){_isLooseVSmu = isLooseVSmu;};
  inline Double_t GetisLooseVSmu() const {return _isLooseVSmu;};
  inline Double_t isLooseVSmu() const {return _isLooseVSmu;};

  inline void SetisMediumVSmu(Double_t isMediumVSmu){_isMediumVSmu = isMediumVSmu;};
  inline Double_t GetisMediumVSmu() const {return _isMediumVSmu;};
  inline Double_t isMediumVSmu() const {return _isMediumVSmu;};

  inline void SetisTightVSmu(Double_t isTightVSmu){_isTightVSmu = isTightVSmu;};
  inline Double_t GetisTightVSmu() const {return _isTightVSmu;};
  inline Double_t isTightVSmu() const {return _isTightVSmu;};

  inline void SetrawDNNVSe(Double_t rawDNNVSe){_rawDNNVSe = rawDNNVSe;};
  inline Double_t GetrawDNNVSe() const {return _rawDNNVSe;};
  inline Double_t rawDNNVSe() const {return _rawDNNVSe;};

  inline void SetisVVVLooseVSe(Double_t isVVVLooseVSe){_isVVVLooseVSe = isVVVLooseVSe;};
  inline Double_t GetisVVVLooseVSe() const {return _isVVVLooseVSe;};
  inline Double_t isVVVLooseVSe() const {return _isVVVLooseVSe;};

  inline void SetisVVLooseVSe(Double_t isVVLooseVSe){_isVVLooseVSe = isVVLooseVSe;};
  inline Double_t GetisVVLooseVSe() const {return _isVVLooseVSe;};
  inline Double_t isVVLooseVSe() const {return _isVVLooseVSe;};

  inline void SetisVLooseVSe(Double_t isVLooseVSe){_isVLooseVSe = isVLooseVSe;};
  inline Double_t GetisVLooseVSe() const {return _isVLooseVSe;};
  inline Double_t isVLooseVSe() const {return _isVLooseVSe;};

  inline void SetisLooseVSe(Double_t isLooseVSe){_isLooseVSe = isLooseVSe;};
  inline Double_t GetisLooseVSe() const {return _isLooseVSe;};
  inline Double_t isLooseVSe() const {return _isLooseVSe;};

  inline void SetisMediumVSe(Double_t isMediumVSe){_isMediumVSe = isMediumVSe;};
  inline Double_t GetisMediumVSe() const {return _isMediumVSe;};
  inline Double_t isMediumVSe() const {return _isMediumVSe;};

  inline void SetisTightVSe(Double_t isTightVSe){_isTightVSe = isTightVSe;};
  inline Double_t GetisTightVSe() const {return _isTightVSe;};
  inline Double_t isTightVSe() const {return _isTightVSe;};

  inline void SetisVTightVSe(Double_t isVTightVSe){_isVTightVSe = isVTightVSe;};
  inline Double_t GetisVTightVSe() const {return _isVTightVSe;};
  inline Double_t isVTightVSe() const {return _isVTightVSe;};

  inline void SetisVVTightVSe(Double_t isVVTightVSe){_isVVTightVSe = isVVTightVSe;};
  inline Double_t GetisVVTightVSe() const {return _isVVTightVSe;};
  inline Double_t isVVTightVSe() const {return _isVVTightVSe;};

  inline void SetdecayModeFinding(Double_t decayModeFinding){_decayModeFinding = decayModeFinding;};
  inline Double_t GetdecayModeFinding() const {return _decayModeFinding;};
  inline Double_t decayModeFinding() const {return _decayModeFinding;};

  inline void Setindex(Int_t index){_index = index;};
  inline Int_t Getindex() const {return _index;};
  inline Int_t index() const {return _index;};


private:
  Double_t _NumTracks;   // number of tracks
  Double_t _charge;
  Double_t _dz;
  Double_t _dxy;
  Double_t _isVLoose;
  Double_t _isLoose;
  Double_t _isMedium;
  Double_t _isTight;
  Double_t _isVTight;
  Double_t _rawMVA;
  Double_t _rawDNNVSjet;
  Double_t _isVVVLooseVSjet;
  Double_t _isVVLooseVSjet;
  Double_t _isVLooseVSjet;
  Double_t _isLooseVSjet;
  Double_t _isMediumVSjet;
  Double_t _isTightVSjet;
  Double_t _isVTightVSjet;
  Double_t _isVVTightVSjet;
  Double_t _rawDNNVSmu;
  Double_t _isVLooseVSmu;
  Double_t _isLooseVSmu;
  Double_t _isMediumVSmu;
  Double_t _isTightVSmu;
  Double_t _rawDNNVSe;
  Double_t _isVVVLooseVSe;
  Double_t _isVVLooseVSe;
  Double_t _isVLooseVSe;
  Double_t _isLooseVSe;
  Double_t _isMediumVSe;
  Double_t _isTightVSe;
  Double_t _isVTightVSe;
  Double_t _isVVTightVSe;
  Double_t _decayModeFinding;
  Int_t _index;
  
  /// cuts reading from config
  Double_t _closestLeptonCut;
  Double_t _minPtCut;
  Double_t _maxEtaCut;
  Double_t _maxDxyCut;
  Double_t _maxDzCut;

  ////////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(Tau,0)
  ////////////////////////////////////////////////////////////////////////////////    

};


#endif
