/******************************************************************************
 * Jet.cpp                                                                    *
 *                                                                            *
 * Store information about final state jets                                   *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Jet class                                       *
 *    Jet()                              -- Default Constructor               *
 *    Jet()                              -- Parameterized Constructor         *
 *    ~Jet()                             -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill jet from event tree          *
 *    FillFastSim                        -- Fill jet from FastSim tree        *
 *    SetEtM0                            -- Set ET for EM layer 0             *
 *    GetEtM0                            -- Set ET for EM layer 0             *
 *    EtEM0                              -- Set ET for EM layer 0             *
 *    ApplyJESCorrection                 -- Shift jet energy by some amount   *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Jet              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of Jet class                                          *
 *    Double_t _EtEm0                     -- Et for ME layer 0                *
 *                                                                            *
 * History                                                                    *
 *      16 Nov 2006 - Created by R. Schwienhorst                              *
 *      17 Nov 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *      20 Mar 2007 - RS: Add filling from fastsim tree                       *
 *      29 Nov 2007 - RS: Add b-tagging choice when filling                   *
 *      11 Jan 2008 - RS: Fill only if object passes ID cuts                  *
 *      14 Jan 2008 - RS: For TRFIP2D, add systematics                        *
 *      08 May 2009 - J. Holzbauer: added quarkFlavorLabel tag                *
 *****************************************************************************/
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Electron.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <TRandom3.h>
#include<TString.h>


using namespace std;
//using namespace Analysis;

//
// give me a random number generator.
// put it here and make it static so that I don't create multiple copies
static TRandom3 jet_myran;
static TRandom3 jet_jer_myran;

// Integrate classes into the Root system
ClassImp(Jet)

/******************************************************************************
 * Jet::Jet()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  Jet::Jet() : Particle::Particle(),
  _numberOfConstituents(0), _chargedMultiplicity(0),  _bDiscriminator ( -999.0), _pileupId ( 0.0), _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), _photonEnergy(0.0), _jesUp(false), _jesDown(false), _jerUp(false), _jerDown(false),
  _isNormalJet       (0.0),
  _isForwardJet       (0.0),
  _isLooseBdisc       (0.0),
  _isMediumBdisc       (0.0),
  _isTightBdisc       (0.0),
  _qg       (0.0),
  _axis2       (0.0),
  _axis1       (0.0),
  _ptD       (0.0),
  _mult       (0.0),
  _ele_number       (0),
  _mu_number       (0),
  _tau_number       (0),
  _pfCombinedCvsLJetTags       (0.0),
  _pfCombinedCvsBJetTags       (0.0),
  _pfCombinedInclusiveSecondaryVertexV2BJetTags       (0.0),
  _pfCombinedMVAV2BJetTags       (0.0),
  _pfJetProbabilityBJetTags       (0.0),
  _pfDeepCSVCvsLJetTags       (0.0),
  _pfDeepCSVCvsBJetTags       (0.0),
  _pfDeepCSVBJetTags       (0.0),
  _pfDeepFlavourBJetTags       (0.0),
  _lepdrmax       (0.0),
  _lepdrmin       (0.0),
  _isToptag       (0.0),
  _isResToptag       (0.0),
  _index       (0.0),
  _L1corrPt       (0.0),
  _uncorrE       (0.0),
  _JerSF       (1.0),
  _JerSFup       (1.0),
  _JerSFdown       (1.0),
  _partonFlavour       (0.0),
  _hadronFlavour       (0.0),
  _genMother_pdgId       (0.0),
  _genGrandMother_pdgId       (0.0),
  _matchId       (0.0),
  _isFromTop       (0.0),
  _isFromH       (0.0),
  _matchMother_Id       (0.0),
  _matchGrandMother_Id       (0.0),
  _HjDisc       (0.0)
{
} //Jet()

/******************************************************************************
 * Jet::~Jet()                                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Jet::~Jet()
{
} //~Jet()

/******************************************************************************
 * Jet::Jet(const Jet& other)                                                 *
 *                                                                            *
 * Copy Constructor Jet const                                                 *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: None                                                               *
 ******************************************************************************/
Jet::Jet(const Jet& other): Particle(other),
_numberOfConstituents		(other.GetnumberOfConstituents()), 
_chargedMultiplicity		(other.GetchargedMultiplicity()),  
_bDiscriminator 		(other.GetbDiscriminator()), 
_pileupId 			(other.GetpileupId()), 
_mass 				(other.Getmass()), 
_uncorrPt 			(other.GetuncorrPt()), 
_L1corrPt 			(other.GetL1corrPt()), 
_uncorrE 			(other.GetuncorrE()), 
_JerSF 			(other.GetJerSF()), 
_JerSFup 			(other.GetJerSFup()), 
_JerSFdown 			(other.GetJerSFdown()), 
_neutralHadEnergyFraction	(other.GetneutralHadEnergyFraction()), 
_neutralEmEmEnergyFraction 	(other.GetneutralEmEmEnergyFraction()),
 _chargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction()), 
_chargedEmEnergyFraction	(other.GetchargedEmEnergyFraction()), 
_muonEnergyFraction		(other.GetmuonEnergyFraction()), 
_electronEnergy			(other.GetelectronEnergy()), 
  _isForwardJet(other.GetisForwardJet()),
  _isNormalJet(other.GetisNormalJet()),
  _isLooseBdisc(other.GetisLooseBdisc()),
  _isMediumBdisc(other.GetisMediumBdisc()),
  _isTightBdisc(other.GetisTightBdisc()),
  _qg(other.Getqg()),
  _axis2(other.Getaxis2()),
  _axis1(other.Getaxis1()),
  _ptD(other.GetptD()),
  _mult(other.Getmult()),
  _ele_number(other.Getele_number()),
  _mu_number(other.Getmu_number()),
  _tau_number(other.Gettau_number()),
  _pfCombinedCvsLJetTags(other.GetpfCombinedCvsLJetTags()),
  _pfCombinedCvsBJetTags(other.GetpfCombinedCvsBJetTags()),
  _pfCombinedInclusiveSecondaryVertexV2BJetTags(other.GetpfCombinedInclusiveSecondaryVertexV2BJetTags()),
  _pfCombinedMVAV2BJetTags(other.GetpfCombinedMVAV2BJetTags()),
  _pfJetProbabilityBJetTags(other.GetpfJetProbabilityBJetTags()),
  _pfDeepCSVCvsLJetTags(other.GetpfDeepCSVCvsLJetTags()),
  _pfDeepCSVCvsBJetTags(other.GetpfDeepCSVCvsBJetTags()),
  _pfDeepFlavourBJetTags(other.GetpfDeepFlavourBJetTags()),
  _pfDeepCSVBJetTags(other.GetpfDeepCSVBJetTags()),
  _lepdrmax(other.Getlepdrmax()),
  _lepdrmin(other.Getlepdrmin()),
  _partonFlavour(other.GetpartonFlavour()),
  _hadronFlavour(other.GethadronFlavour()),
  _isToptag(other.GetisToptag()),
  _isResToptag(other.GetisResToptag()),
  _index(other.Getindex()),
  _HjDisc(other.GetHjDisc()),
  _genMother_pdgId(other.GetgenMother_pdgId()),
  _genGrandMother_pdgId(other.GetgenGrandMother_pdgId()),
  _matchId(other.GetmatchId()),
  _isFromTop(other.GetisFromTop()),
  _isFromH(other.GetisFromH()),
  _matchMother_Id(other.GetmatchMother_Id()),
  _matchGrandMother_Id(other.GetmatchGrandMother_Id()),
_photonEnergy			(other.GetphotonEnergy())
{
} //Jet()

/******************************************************************************
 * Jet::Jet(const Particle& other)                                            *
 *                                                                            *
 * Copy Constructor Particle const                                            *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: None                                                               *
 ******************************************************************************/
Jet::Jet(const Particle& other): Particle(other),
_numberOfConstituents(0), _chargedMultiplicity(0),  _bDiscriminator ( -999.0), _pileupId ( 0.0), _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), 
  _isForwardJet       (0.0),
  _isNormalJet       (0.0),
  _isLooseBdisc       (0.0),
  _isMediumBdisc       (0.0),
  _isTightBdisc       (0.0),
  _qg       (0.0),
  _axis2       (0.0),
  _axis1       (0.0),
  _ptD       (0.0),
  _mult       (0.0),
  _ele_number       (0),
  _mu_number       (0),
  _tau_number       (0),
  _pfCombinedCvsLJetTags       (0.0),
  _pfCombinedCvsBJetTags       (0.0),
  _pfCombinedInclusiveSecondaryVertexV2BJetTags       (0.0),
  _pfCombinedMVAV2BJetTags       (0.0),
  _pfJetProbabilityBJetTags       (0.0),
  _pfDeepCSVCvsLJetTags       (0.0),
  _pfDeepCSVCvsBJetTags       (0.0),
  _pfDeepFlavourBJetTags       (0.0),
  _pfDeepCSVBJetTags       (0.0),
  _L1corrPt  (0.0),
  _uncorrE  (0.0),
  _JerSF  (1.0),
  _JerSFup  (1.0),
  _JerSFdown  (1.0),
  _lepdrmax       (0.0),
  _lepdrmin       (0.0),
  _partonFlavour       (0.0),
  _hadronFlavour       (0.0),
  _isToptag       (0.0),
  _isResToptag       (0.0),
  _index       (0.0),
  _HjDisc       (0.0),
  _genMother_pdgId       (0.0),
  _genGrandMother_pdgId       (0.0),
  _matchId       (0.0),
  _isFromTop       (0.0),
  _isFromH       (0.0),
  _matchMother_Id       (0.0),
  _matchGrandMother_Id       (0.0),
_photonEnergy(0.0)
{
 
} //Jet()


/******************************************************************************
 * Jet& Jet::operator+=(const Jet& other)                                     *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator+=(const Jet& other)
{
  
  Particle::operator+=(other);
  return *this;
} //+=

/******************************************************************************
 * Jet& Jet::operator+(const Jet& other)                                      *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet Jet::operator+(const Jet& other)
{
  Particle particleTemp = Particle::operator+(other);
  Jet jetTemp = particleTemp;
  return jetTemp;

} //+

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = Particle                                                        *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(const Particle& other)
{
  
  Particle::operator=(other);
  SetnumberOfConstituents(0); 
  SetchargedMultiplicity(0); 
  SetbDiscriminator ( -999.0); 
  SetpileupId ( 0.0); 
  Setmass ( 0.0); 
  SetuncorrPt ( 0.0); 
  SetL1corrPt ( 0.0); 
  SetuncorrE ( 0.0); 
  SetJerSF ( 1.0); 
  SetJerSFup ( 1.0); 
  SetJerSFdown ( 1.0); 
  SetneutralHadEnergyFraction(0.0); 
  SetneutralEmEmEnergyFraction ( 0.0); 
  SetchargedHadronEnergyFraction (0.0); 
  SetchargedEmEnergyFraction(0.0); 
  SetmuonEnergyFraction(0.0); 
  SetelectronEnergy(0.0); 
  SetisNormalJet       (0.0);
  SetisForwardJet       (0.0);
  SetisLooseBdisc       (0.0);
  SetisMediumBdisc       (0.0);
  SetisTightBdisc       (0.0);
  Setqg       (0.0);
  Setaxis2       (0.0);
  Setaxis1       (0.0);
  SetptD       (0.0);
  Setmult       (0.0);
  Setele_number       (0);
  Setmu_number       (0);
  Settau_number       (0);
  SetpfCombinedCvsLJetTags       (0.0);
  SetpfCombinedCvsBJetTags       (0.0);
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags       (0.0);
  SetpfCombinedMVAV2BJetTags       (0.0);
  SetpfJetProbabilityBJetTags       (0.0);
  SetpfDeepCSVCvsLJetTags       (0.0);
  SetpfDeepCSVCvsBJetTags       (0.0);
  SetpfDeepFlavourBJetTags       (0.0);
  SetpfDeepCSVBJetTags       (0.0);
  Setlepdrmax       (0.0);
  Setlepdrmin       (0.0);
  SetpartonFlavour       (0.0);
  SethadronFlavour       (0.0);
  SetisToptag       (0.0);
  SetisResToptag       (0.0);
  Setindex       (0.0);
  SetHjDisc       (0.0);
  SetgenMother_pdgId       (0.0);
  SetgenGrandMother_pdgId       (0.0);
  SetmatchId       (0.0);
  SetisFromTop       (0.0);
  SetisFromH       (0.0);
  SetmatchMother_Id       (0.0);
  SetmatchGrandMother_Id       (0.0);
  SetphotonEnergy(0.0);

  return *this;
} //= Particle

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = const Jet                                                       *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(const Jet& other)
{
  
  Particle::operator=(other);
  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  SetpileupId 				(other.GetpileupId());
  Setmass 				(other.Getmass());
  SetuncorrPt 				(other.GetuncorrPt());
  SetL1corrPt 				(other.GetL1corrPt());
  SetuncorrE 				(other.GetuncorrE());
  SetJerSF 				(other.GetJerSF());
  SetJerSFup 				(other.GetJerSFup());
  SetJerSFdown 				(other.GetJerSFdown());
  SetneutralHadEnergyFraction		(other.GetneutralHadEnergyFraction());
  SetneutralEmEmEnergyFraction 		(other.GetneutralEmEmEnergyFraction());
  SetchargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction());
  SetchargedEmEnergyFraction		(other.GetchargedEmEnergyFraction());
  SetmuonEnergyFraction			(other.GetmuonEnergyFraction());
  SetelectronEnergy			(other.GetelectronEnergy());
  SetisNormalJet(other.GetisNormalJet());
  SetisForwardJet(other.GetisForwardJet());
  SetisLooseBdisc(other.GetisLooseBdisc());
  SetisMediumBdisc(other.GetisMediumBdisc());
  SetisTightBdisc(other.GetisTightBdisc());
  Setqg(other.Getqg());
  Setaxis2(other.Getaxis2());
  Setaxis1(other.Getaxis1());
  SetptD(other.GetptD());
  Setmult(other.Getmult());
  Setele_number(other.Getele_number());
  Setmu_number(other.Getmu_number());
  Settau_number(other.Gettau_number());
  SetpfCombinedCvsLJetTags(other.GetpfCombinedCvsLJetTags());
  SetpfCombinedCvsBJetTags(other.GetpfCombinedCvsBJetTags());
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags(other.GetpfCombinedInclusiveSecondaryVertexV2BJetTags());
  SetpfCombinedMVAV2BJetTags(other.GetpfCombinedMVAV2BJetTags());
  SetpfJetProbabilityBJetTags(other.GetpfJetProbabilityBJetTags());
  SetpfDeepCSVCvsLJetTags(other.GetpfDeepCSVCvsLJetTags());
  SetpfDeepCSVCvsBJetTags(other.GetpfDeepCSVCvsBJetTags());
  SetpfDeepFlavourBJetTags(other.GetpfDeepFlavourBJetTags());
  SetpfDeepCSVBJetTags(other.GetpfDeepCSVBJetTags());
  Setlepdrmax(other.Getlepdrmax());
  Setlepdrmin(other.Getlepdrmin());
  SetpartonFlavour(other.GetpartonFlavour());
  SethadronFlavour(other.GethadronFlavour());
  SetisToptag(other.GetisToptag());
  SetisResToptag(other.GetisResToptag());
  Setindex(other.Getindex());
  SetHjDisc(other.GetHjDisc());
  SetgenMother_pdgId(other.GetgenMother_pdgId());
  SetgenGrandMother_pdgId(other.GetgenGrandMother_pdgId());
  SetmatchId(other.GetmatchId());
  SetisFromTop(other.GetisFromTop());
  SetisFromH(other.GetisFromH());
  SetmatchMother_Id(other.GetmatchMother_Id());
  SetmatchGrandMother_Id(other.GetmatchGrandMother_Id());
  SetphotonEnergy			(other.GetphotonEnergy());
  return *this;
} //= const

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = non-const Jet                                                   *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(Jet& other)
{
  Particle::operator=(other);
  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  SetpileupId 				(other.GetpileupId());
  Setmass 				(other.Getmass());
  SetuncorrPt 				(other.GetuncorrPt());
  SetL1corrPt 				(other.GetL1corrPt());
  SetuncorrE 				(other.GetuncorrE());
  SetJerSF 				(other.GetJerSF());
  SetJerSFup 				(other.GetJerSFup());
  SetJerSFdown 				(other.GetJerSFdown());
  SetneutralHadEnergyFraction		(other.GetneutralHadEnergyFraction());
  SetneutralEmEmEnergyFraction 		(other.GetneutralEmEmEnergyFraction());
  SetchargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction());
  SetchargedEmEnergyFraction		(other.GetchargedEmEnergyFraction());
  SetmuonEnergyFraction			(other.GetmuonEnergyFraction());
  SetelectronEnergy			(other.GetelectronEnergy());
  SetisNormalJet(other.GetisNormalJet());
  SetisForwardJet(other.GetisForwardJet());
  SetisLooseBdisc(other.GetisLooseBdisc());
  SetisMediumBdisc(other.GetisMediumBdisc());
  SetisTightBdisc(other.GetisTightBdisc());
  Setqg(other.Getqg());
  Setaxis2(other.Getaxis2());
  Setaxis1(other.Getaxis1());
  SetptD(other.GetptD());
  Setmult(other.Getmult());
  Setele_number(other.Getele_number());
  Setmu_number(other.Getmu_number());
  Settau_number(other.Gettau_number());
  SetpfCombinedCvsLJetTags(other.GetpfCombinedCvsLJetTags());
  SetpfCombinedCvsBJetTags(other.GetpfCombinedCvsBJetTags());
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags(other.GetpfCombinedInclusiveSecondaryVertexV2BJetTags());
  SetpfCombinedMVAV2BJetTags(other.GetpfCombinedMVAV2BJetTags());
  SetpfJetProbabilityBJetTags(other.GetpfJetProbabilityBJetTags());
  SetpfDeepCSVCvsLJetTags(other.GetpfDeepCSVCvsLJetTags());
  SetpfDeepCSVCvsBJetTags(other.GetpfDeepCSVCvsBJetTags());
  SetpfDeepFlavourBJetTags(other.GetpfDeepFlavourBJetTags());
  SetpfDeepCSVBJetTags(other.GetpfDeepCSVBJetTags());
  Setlepdrmax(other.Getlepdrmax());
  Setlepdrmin(other.Getlepdrmin());
  SetpartonFlavour(other.GetpartonFlavour());
  SethadronFlavour(other.GethadronFlavour());
  SetisToptag(other.GetisToptag());
  SetisResToptag(other.GetisResToptag());
  Setindex(other.Getindex());
  SetHjDisc(other.GetHjDisc());
  SetgenMother_pdgId(other.GetgenMother_pdgId());
  SetgenGrandMother_pdgId(other.GetgenGrandMother_pdgId());
  SetmatchId(other.GetmatchId());
  SetisFromTop(other.GetisFromTop());
  SetisFromH(other.GetisFromH());
  SetmatchMother_Id(other.GetmatchMother_Id());
  SetmatchGrandMother_Id(other.GetmatchGrandMother_Id());
  SetphotonEnergy			(other.GetphotonEnergy());
  return *this;
} //= non-const

/******************************************************************************         
 * void Jet::SetCuts(TEnv* config)                                            *
 *                                                                            *         
 * Set the cuts to be used on the jet objects                                 *
 *                                                                            *         
 * Input:  TEnv* config                                                       * 
 *         - Contains the cuts to be applied to each jet                      *
 * Output: None                                                               *
 ******************************************************************************/

void Jet::SetCuts(TEnv * config)
{
  _dataEra = config -> GetValue("DataEra",2017);
  _maxEtaCut = 		config -> GetValue("ObjectID.Jet.MaxEta",100.);
  _minPtCut = 		config -> GetValue("ObjectID.Jet.MinPt",0.);
  _FWJetEtaCut = 		config -> GetValue("ObjectID.FWJet.EtaCut",100.);
  _FWJetHighPtCut = 		config -> GetValue("ObjectID.FWJet.HighPtCut",9999.);
  _FWJetHighPtMinEta = 		config -> GetValue("ObjectID.FWJet.HighPt.MinEta",0.);
  _FWJetHighPtMaxEta = 		config -> GetValue("ObjectID.FWJet.HighPt.MaxEta",10.);
  _bMaxEtaCut = 	config -> GetValue("ObjectID.BJet.MaxEta",100.);
  _bMinPtCut = 		config -> GetValue("ObjectID.BJet.MinPt",0.);
  _LWPbTagCut = 		config -> GetValue("ObjectID.BJet.LWPBTagCut",0.0);
  _MWPbTagCut = 		config -> GetValue("ObjectID.BJet.MWPBTagCut",0.0);
  _TWPbTagCut = 		config -> GetValue("ObjectID.BJet.TWPBTagCut",0.0);
  _closestLeptonCut = 	config -> GetValue("ObjectID.Jet.LepCleanR",0.0);
  _jesUp = 		config -> GetValue("Systs.doJESUp",0);
  _jesDown = 		config -> GetValue("Systs.doJESDown",0);
  _jerUp = 		config -> GetValue("Systs.doJERUp",0);
  _jerDown = 		config -> GetValue("Systs.doJERDown",0);
  
}

/***************************************************************
 * void Jet Jet::set_HjMVAreader()                       *
 *                                                              * 
 * Set up the MVA xml file                                      *
 *                                                              *
 * Input: TEnv* config                                          *
 * Output: None                                                 *
 * **************************************************************/
 
void Jet::set_HjMVAreader(TEnv* config)
{
    readerjet = new TMVA::Reader("!Color:!Silent");
    readerjet->AddVariable("Jet25_bDiscriminator",&jetvarpfCombinedInclusiveSecondaryVertexV2BJetTags);
    readerjet->AddVariable("Jet25_pt",&jetvarpt);
    readerjet->AddVariable("Jet25_lepdrmin",&jetvarlepdrmin);
    readerjet->AddVariable("Jet25_lepdrmax",&jetvarlepdrmax);
    readerjet->AddVariable("Jet25_qg",&jetvarqg);
    readerjet->BookMVA("BDTG method", config -> GetValue("Include.HjTaggerMVAFile","null")); 
    _weightname = config->GetValue("Include.HjTaggerMVAFile","null");
}

/***************************************************************
 * double Jet Jet::get_JetMVA()                *
 *                                                              * 
 * Read the Hj Tagger MVA value                                      *
 *                                                              *
 * Input: None                                          *
 * Output: Hj Tagger MVA value                                     *
 * **************************************************************/
 
double Jet::get_JetMVA()
{
    jetvarqg = max(qg(),0.);
    jetvarlepdrmax = lepdrmax();
    jetvarpt = Pt();
    jetvarlepdrmin = lepdrmin();
    jetvarpfCombinedInclusiveSecondaryVertexV2BJetTags = max(bDiscriminator(),0.);
    //jetvarpfCombinedInclusiveSecondaryVertexV2BJetTags = pfCombinedInclusiveSecondaryVertexV2BJetTags();
    float hj_score = readerjet->EvaluateMVA("BDTG method");
    if (_weightname.Contains("xgboost")){
        float xgb_score = 1/(1+sqrt((1-hj_score)/(1+hj_score)));
        return xgb_score;
    }else{
        return hj_score;
    }
}

/******************************************************************************         
 * void Jet::Fill(EventTree *evtr, Int_t iE,const TString& tagName)           *         
 *                                                                            *         
 * Fill jet vector from tree                                                  *         
 *                                                                            *         
 * Input:  Event Tree pointer                                                 *         
 *         - which jet                                                        *
 * Output: True if this jet passes jet ID cuts                                *         
 ******************************************************************************/

Bool_t Jet::Fill( double myJESCorr, double myJERCorr,  int& mu_start_index, int& ele_start_index, int& tau_start_index, std::vector<Lepton>& selectedLeptons, std::vector<Tau>& selectedTaus, EventTree *evtr, Int_t iE, TLorentzVector * met, Bool_t useLepAwareJets, Bool_t isSimulation, int whichtrig)
{

  int eventNumber = evtr -> EVENT_event; 
  Double_t jetPt, jetEta,jetPhi,jetE, jetCharge, jetM;
  Double_t jetUncorrPt, jetUncorrE, jesSF, jerSF;
  jetUncorrPt = evtr->Jet_Uncorr_pt -> operator[](iE);
  jetUncorrE = (evtr -> Jet_energy -> operator[](iE))/(evtr -> Jet_pt -> operator[](iE))*jetUncorrPt;
  jesSF = evtr->Jet_JesSF -> operator[](iE);
  jerSF = evtr->Jet_JerSF -> operator[](iE);
  //jerSF = 1.0;
  SetJerSF 				(jerSF);
  SetJerSFup(evtr->Jet_JerSFup->operator[](iE));
  SetJerSFdown(evtr->Jet_JerSFdown->operator[](iE));
    
  jetPt     = evtr -> Jet_pt -> operator[](iE);
  jetE      = evtr -> Jet_energy -> operator[](iE);
  jetEta    = evtr -> Jet_eta    -> operator[](iE);
  jetPhi    = evtr -> Jet_phi    -> operator[](iE);
  
  if(jetE > 0){
    SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  }else{
    SetPtEtaPhiE(1,1,1,3);
  }
  
  if(jerSF > 1.1 && !useLepAwareJets){
    //>99% of jerSF > 1.1 is due to the bug in stochastic method , recalculation here
    float rho = evtr->EVENT_rhopog;
    TLorentzVector genJet={0,0,0,0}; 
    float JerScaleFactor(1.), JerScaleFactorUP(1.), JerScaleFactorDOWN(1.);
    Getjer(rho, false, genJet, JerScaleFactor, JerScaleFactorUP, JerScaleFactorDOWN, eventNumber);
    SetJerSF(JerScaleFactor);
    SetJerSFup(JerScaleFactorUP);
    SetJerSFdown(JerScaleFactorDOWN);
  }
  // jer SF is not applied to lepAware jets 
  if(!useLepAwareJets){
    jetPt     = evtr -> Jet_pt -> operator[](iE) * JerSF();
    jetE      = evtr -> Jet_energy -> operator[](iE) * JerSF();
  }else{
    jetPt     = evtr -> Jet_pt -> operator[](iE);
    jetE      = evtr -> Jet_energy -> operator[](iE);
  }
  jetEta    = evtr -> Jet_eta    -> operator[](iE);
  jetPhi    = evtr -> Jet_phi    -> operator[](iE);

  if(jetE > 0){
    SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  }else{
    SetPtEtaPhiE(1,1,1,3);
  }

  SetnumberOfConstituents		(evtr -> Jet_numberOfConstituents     	-> operator[](iE));
  SetchargedMultiplicity		(evtr -> Jet_chargedMultiplicity     	-> operator[](iE)); 
  //SetbDiscriminator 			(evtr -> Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags     	-> operator[](iE));
  SetbDiscriminator 			(evtr -> Jet_pfDeepFlavourBJetTags     	-> operator[](iE));
  SetpileupId 				(evtr -> Jet_pileupId     		-> operator[](iE));
  Setmass 				(evtr -> Jet_mass     			-> operator[](iE));
  SetuncorrPt 				(evtr -> Jet_Uncorr_pt     		-> operator[](iE));
  SetL1corrPt 				(evtr -> Jet_L1corr_pt     		-> operator[](iE));
  SetuncorrE 				(jetUncorrE);
  SetneutralHadEnergyFraction		(evtr -> Jet_neutralHadEnergyFraction	-> operator[](iE));
  SetneutralEmEmEnergyFraction 		(evtr -> Jet_neutralEmEnergyFraction  -> operator[](iE));
  SetchargedHadronEnergyFraction 	(evtr -> Jet_chargedHadronEnergyFraction-> operator[](iE));
  SetchargedEmEnergyFraction		(evtr -> Jet_chargedEmEnergyFraction    -> operator[](iE));
  SetmuonEnergyFraction			(evtr -> Jet_muonEnergyFraction     	-> operator[](iE));
  SetelectronEnergy			(evtr -> Jet_electronEnergy     	-> operator[](iE));
  SetphotonEnergy			(evtr -> Jet_photonEnergy     		-> operator[](iE));
  Setqg       (evtr -> Jet_qg      -> operator[](iE));
  Setaxis2       (evtr -> Jet_axis2      -> operator[](iE));
  Setaxis1       (evtr -> Jet_axis1      -> operator[](iE));
  SetptD       (evtr -> Jet_ptD      -> operator[](iE));
  Setmult       (evtr -> Jet_mult      -> operator[](iE));
  Setele_number       (evtr -> Jet_ele_number      -> operator[](iE));
  Setmu_number       (evtr -> Jet_mu_number      -> operator[](iE));
  Settau_number       (evtr -> Jet_tau_number      -> operator[](iE));
  SetpfCombinedCvsLJetTags       (evtr -> Jet_pfCombinedCvsLJetTags      -> operator[](iE));
  SetpfCombinedCvsBJetTags       (evtr -> Jet_pfCombinedCvsBJetTags      -> operator[](iE));
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags       (evtr -> Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags      -> operator[](iE));
  SetpfCombinedMVAV2BJetTags       (evtr -> Jet_pfCombinedMVAV2BJetTags      -> operator[](iE));
  SetpfJetProbabilityBJetTags       (evtr -> Jet_pfJetProbabilityBJetTags      -> operator[](iE));
  SetpfDeepCSVCvsLJetTags       (evtr -> Jet_pfDeepCSVProbc      -> operator[](iE)/(evtr -> Jet_pfDeepCSVProbc      -> operator[](iE) + evtr -> Jet_pfDeepCSVProbudsg -> operator[](iE)));
  SetpfDeepCSVCvsBJetTags       (evtr -> Jet_pfDeepCSVProbc      -> operator[](iE)/(evtr -> Jet_pfDeepCSVProbc      -> operator[](iE)+ evtr -> Jet_pfDeepCSVProbb      -> operator[](iE) + evtr -> Jet_pfDeepCSVProbbb      -> operator[](iE)) );
  SetpfDeepFlavourBJetTags       (evtr -> Jet_pfDeepFlavourBJetTags      -> operator[](iE));
  SetpfDeepCSVBJetTags       (evtr -> Jet_pfDeepCSVBJetTags      -> operator[](iE));
  if(isSimulation){
    SetpartonFlavour       (evtr -> Jet_partonFlavour      -> operator[](iE));
    SethadronFlavour       (evtr -> Jet_hadronFlavour      -> operator[](iE));
  }else{
    SetpartonFlavour       (-999.);
    SethadronFlavour       (-999.);
  }
  //SetgenMother_pdgId       (evtr -> Jet_genMother_pdgId      -> operator[](iE));
  //SetgenGrandMother_pdgId       (evtr -> Jet_genGrandMother_pdgId      -> operator[](iE));
  SetgenMother_pdgId       (-999.);
  SetgenGrandMother_pdgId       (-999.);

  SetisLooseBdisc      ( bDiscriminator() > _LWPbTagCut ); 
  SetisMediumBdisc       ( bDiscriminator() > _MWPbTagCut );
  SetisTightBdisc       ( bDiscriminator() > _TWPbTagCut );
 
  // Now we want to do the JER and JES systematic adjustments to the jet. This also requires correcting the MET.
  if (_jesUp || _jesDown || _jerUp || _jerDown) SystematicPtShift(evtr, iE, met, useLepAwareJets);  

  if (useLepAwareJets) return kTRUE;

/*
  SetPdgId      ( evtr -> Jet_flavor_truth_trueflav -> operator[](iE));
  SetIsBadLoose ( evtr -> Jet_isBadLoose            -> operator[](iE));
  ///////////////////////////////////////////////////////////////////////////////
  //
  // b-tagging choices
  /////////////////////////////////////////////////////////////////////////////////
  // Upated for version 14
  //currently no TRF b-taggers, so using a cut on weights
  
  std::vector<Double_t> bweight;
  bweight.clear();
  //cout<<evtr -> Jet_flavor_weight -> operator[](iE)<<endl;
  bweight.push_back(evtr -> Jet_flavor_weight -> operator[](iE));//0
  bweight.push_back(evtr -> Jet_flavor_weight_IP1D -> operator[](iE));//1
  bweight.push_back(evtr -> Jet_flavor_weight_IP2D -> operator[](iE));//2
  bweight.push_back(evtr -> Jet_flavor_weight_IP3D -> operator[](iE));//3
  bweight.push_back(evtr -> Jet_flavor_weight_SV1 -> operator[](iE));//4
  bweight.push_back(evtr -> Jet_flavor_weight_SV2 -> operator[](iE));//5
  //for JetProb, we actually use -ln(JetProb)
  bweight.push_back(-TMath::Log10(evtr -> Jet_flavor_weight_JetProb -> operator[](iE)));//6
  bweight.push_back(evtr -> Jet_flavor_weight_TrackCounting2D -> operator[](iE));//7
  bweight.push_back(evtr -> Jet_flavor_weight_SV0 -> operator[](iE));//8 
  bweight.push_back(evtr -> Jet_flavor_weight_JetFitterCOMBNN-> operator[](iE));//9
  SetBWeight(bweight);
  //cout<<bweight.size()<<endl;
  
  double tagCut = 0;

  tagCut = btagCut;

  if(tagName=="default" || tagName=="bTagged" || tagName=="IP3DSV1") {
    if(evtr -> Jet_flavor_weight -> operator[](iE) > tagCut) SetTagged(kTRUE);
    else SetTagged(kFALSE);
  } // if
  else if(tagName=="SV0") {
    if(evtr->Jet_flavor_weight_SV0->operator[](iE) > tagCut) SetTagged(kTRUE);
    else SetTagged(kFALSE);
  } 
  else {
    cout<<"<ERROR>: Error in jet.cpp: invalid tagger, "<<tagName<<endl;
    exit(8);
  }
*/
  /////////////////////////////////////////////////////////////////////////////
  // Jet Pt and Eta Cuts
  /////////////////////////////////////////////////////////////////////////////

  Bool_t passPt = Pt() > _minPtCut;
  Bool_t passEta = TMath::Abs(Eta()) < _maxEtaCut;

  /////////////////////////////////////////////////////////
  /////// Normal Jet Cut 
  ////////////////////////////////////////////////////
  Bool_t passNormalJet = TMath::Abs(Eta()) < _FWJetEtaCut;

  /////////////////////////////////////////////////////////
  /////// Forward Jet Cut 
  ////////////////////////////////////////////////////
  Bool_t passForwardJet = (TMath::Abs(Eta()) >= _FWJetEtaCut && ((TMath::Abs(Eta()) <_FWJetHighPtMinEta || TMath::Abs(Eta()) >_FWJetHighPtMaxEta) || (Pt()>= _FWJetHighPtCut && TMath::Abs(Eta()) >=_FWJetHighPtMinEta && TMath::Abs(Eta()) <= _FWJetHighPtMaxEta ))) ;
  
  if( eventNumber==18841459 ){
    std::cout<< Pt() << " " << Eta() << " " << TMath::Abs(Eta())<<"  _FWJetEtaCut "<< _FWJetEtaCut << " _FWJetHighPtCut " << _FWJetHighPtCut << "  _FWJetHighPtMinEta " << _FWJetHighPtMinEta << " _FWJetHighPtMaxEta " <<  _FWJetHighPtMaxEta << std::endl;
  }
  
  
  /////////////////////////////////////////////////////////////////////////
  // Jet ID
  /////////////////////////////////////////////////////////////////////////
  


  Bool_t LowEtaID =kTRUE;
  Bool_t MediumEtaID= kTRUE;
  Bool_t HighEtaID = kTRUE;

  if(_dataEra==2016){
    LowEtaID = (neutralHadEnergyFraction()<0.99 && neutralEmEmEnergyFraction()<0.99 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0 && chargedEmEnergyFraction() < 0.99) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
    MediumEtaID = (neutralEmEmEnergyFraction()>0.01 && neutralHadEnergyFraction()<0.98 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 ); 
    HighEtaID = (neutralEmEmEnergyFraction()<0.90 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 ); 
  }else if(_dataEra==2017){
    LowEtaID = (neutralHadEnergyFraction()<0.90 && neutralEmEmEnergyFraction()<0.90 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
    MediumEtaID = (neutralEmEmEnergyFraction()<0.99 && neutralEmEmEnergyFraction()>0.02 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 ); 
    HighEtaID = (neutralEmEmEnergyFraction()<0.90 && neutralHadEnergyFraction()>0.02 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 ); 
  }else if(_dataEra==2018){
    LowEtaID = (neutralHadEnergyFraction()<0.90 && chargedMultiplicity()>0 ) && ((TMath::Abs(Eta())<=2.6 && neutralEmEmEnergyFraction()<0.90 && numberOfConstituents()>1 && chargedHadronEnergyFraction()>0 ) || (TMath::Abs(Eta())>2.6 && neutralEmEmEnergyFraction()<0.99)) && TMath::Abs(Eta())<=2.7;
    MediumEtaID = (neutralEmEmEnergyFraction()<0.99 && neutralEmEmEnergyFraction()>0.02 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 ); 
    HighEtaID = (neutralEmEmEnergyFraction()<0.90 && neutralHadEnergyFraction()>0.2 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 ); 
  }else{
    std::cout<<"ERROR in Jet dataEra must be 2016/2017/2018 " << std::endl;
  }
  //Bool_t passesJetID = neutralID && chargedID && neutralHighEtaID;
  Bool_t passesJetID = LowEtaID || MediumEtaID || HighEtaID;

  

  /////////////////////////////////////////////////////////////////////////
  // Jet Cleaning
  /////////////////////////////////////////////////////////////////////////

  Bool_t passesCleaning = kTRUE;
 
  Double_t closestLepton = 999.;
  Double_t minlepdr = -1.;
  Double_t maxlepdr = -1.;
  
  int lep_num =selectedLeptons.size();
  
  if (lep_num == 1){
    minlepdr = selectedLeptons.at(0).DeltaR(*this);
    maxlepdr = minlepdr;
  }
 
  if (lep_num >= 2){
    minlepdr = TMath::Min(selectedLeptons.at(0).DeltaR(*this),selectedLeptons.at(1).DeltaR(*this));
    maxlepdr = TMath::Max(selectedLeptons.at(0).DeltaR(*this),selectedLeptons.at(1).DeltaR(*this));
  }
  
  /* 
  lepton and tau clean using dr
  for (auto const & lep : selectedLeptons){
    if (lep.DeltaR(*this) < closestLepton){
        closestLepton = lep.DeltaR(*this);
    }
  }
  for (auto const & tau : selectedTaus){
    if (tau.DeltaR(*this) < closestLepton) closestLepton = tau.DeltaR(*this);
  }

  if (closestLepton < _closestLeptonCut) passesCleaning = kFALSE;
  */
 
  // lepton and tau clean using common daughters  
  int ele_end_index = ele_start_index + ele_number();
  int mu_end_index = mu_start_index + mu_number();
  int tau_end_index = tau_start_index + tau_number();
  TLorentzVector MatchedLep = {0,0,0,0};
  if(ele_end_index > evtr->Jet_ele_indices->size()){
      std::cout << "ERROR in Jet matching Jet_ele_indices must >= ele_start_index + ele_number() "<<std::endl;
      exit(0);
  }
  if(mu_end_index > evtr->Jet_mu_indices->size()){
      std::cout << "ERROR in Jet matching Jet_mu_indices must >= mu_start_index + mu_number() "<<std::endl;
      exit(0);
  }
  if(tau_end_index> evtr->Jet_tau_indices->size()){
      std::cout << "ERROR in Jet matching Jet_tau_indices must >= tau_start_index + tau_number() "<<std::endl;
      exit(0);
  }
  for (auto const & lep : selectedLeptons){
    if(!passesCleaning) continue;
    if(fabs(lep.pdgId())==11){
        for(Int_t io = ele_start_index;io < ele_end_index ; io++) {
            if(lep.index() == evtr->Jet_ele_indices -> operator[](io)){ 
                closestLepton = lep.DeltaR(*this);
                passesCleaning = kFALSE;
                MatchedLep.SetPtEtaPhiE(lep.Pt(),lep.Eta(),lep.Phi(),lep.E());
                continue;
            }
        }
    }
    else if(fabs(lep.pdgId())==13){
        for(Int_t io = mu_start_index;io < mu_end_index ; io++) {
            if(lep.index() == evtr->Jet_mu_indices -> operator[](io)){ 
                closestLepton = lep.DeltaR(*this);
                passesCleaning = kFALSE;
                MatchedLep.SetPtEtaPhiE(lep.Pt(),lep.Eta(),lep.Phi(),lep.E());
                continue;
            }
        }
    }
  }
  for (auto const & tau : selectedTaus){
    if(!passesCleaning) continue;
    for(Int_t io = tau_start_index;io < tau_end_index ; io++) {
        if(tau.index() == evtr->Jet_tau_indices -> operator[](io)){ 
            closestLepton = tau.DeltaR(*this);
            passesCleaning = kFALSE;
            MatchedLep.SetPtEtaPhiE(tau.Pt(),tau.Eta(),tau.Phi(),tau.E());
            continue;
        }
    }
  }

  // set start_index for next jet
  ele_start_index = ele_end_index;
  mu_start_index = mu_end_index;
  tau_start_index = tau_end_index;

  SetClosestLep(closestLepton);
  Setlepdrmax       (maxlepdr);
  Setlepdrmin       (minlepdr);
  SetHjDisc       (get_JetMVA());
  SetmatchId       (-999);
  SetisFromTop       (-999);
  SetisFromH       (-999);
  SetmatchMother_Id       (-999);
  SetmatchGrandMother_Id       (-999);

  /////////////////////////////////////////////////////////////////////////
  // B-tag related cuts
  /////////////////////////////////////////////////////////////////////////

  Bool_t passbPt = Pt() > _bMinPtCut;
  Bool_t passbEta = TMath::Abs(Eta()) < _bMaxEtaCut;
  Bool_t passTagCut = bDiscriminator() > _LWPbTagCut;

  if (passbPt && passbEta && passTagCut) SetTagged(kTRUE);
  else SetTagged(kFALSE);
  //if( eventNumber== 861319 || eventNumber == 166533 || eventNumber == 263322 || eventNumber == 62175 || eventNumber == 1665166){
  if( eventNumber == 262316 || eventNumber == 173674){
      std::cout<< eventNumber << " jet pt eta phi "<< Pt()<<" "<< Eta()<<" "<<Phi()<< " passesJetID " << passesJetID<< " passesCleaning "<< passesCleaning<< " passForwardJet "<< passForwardJet <<" passLowEta "<< LowEtaID<<" passMediumEta "<< MediumEtaID<< " passHighEta "<< HighEtaID <<" JetID details : neutralHadEnergyFraction() " << neutralHadEnergyFraction() << " neutralEmEmEnergyFraction() " << neutralEmEmEnergyFraction() << " numberOfConstituents() " << numberOfConstituents() << " chargedHadronEnergyFraction() " << chargedHadronEnergyFraction() << " chargedMultiplicity() "<< chargedMultiplicity() <<" matched lepton Pt/Eta/Phi "<< MatchedLep.Pt()<<"/"<<MatchedLep.Eta()<<"/"<<MatchedLep.Phi() <<std::endl;
  } 
  SetisNormalJet(passPt && passEta && passesJetID && passesCleaning && passNormalJet);
  SetisForwardJet(passPt && passEta && passesJetID && passesCleaning && passForwardJet);
  

  if (passPt && passEta && passesJetID && passesCleaning) return kTRUE;
  
  return kFALSE;

} //Fill()

/******************************************************************************         
 * void Jet::FillFastSim(FastSimTree *tr, Int_t iE,const TString& tagName )   *         
 *                                                                            *         
 * Fill jet vector from fastsim tree                                          *         
 *                                                                            *         
 * Input:  - FastSim tree pointer                                             *         
 *         - which jet                                                        *
 *         - tagName, either default or IP2D                                  *
 * Output: True if this jet passes jet ID cuts                                *         
 ******************************************************************************/
Bool_t Jet::FillFastSim( std::vector<MCJet>& MCBJets, std::vector<MCJet>& MCCJets, std::vector<MCTau>& MCTaus, std::vector<Electron>& electrons, FastSimTree *tr,Int_t iE,TEnv* config,const TString& tagName, Double_t btagCut, Double_t mistagCut, Double_t eshift)
{  
  Double_t jetPt, jetEta,jetPhi,jetE, jetCharge;
  jetPt     = tr -> PJet_p_T    -> operator[](iE);
  jetEta    = tr -> PJet_eta    -> operator[](iE);
  jetPhi    = tr -> PJet_phi    -> operator[](iE);
  jetE      = tr -> PJet_E      -> operator[](iE);
  jetCharge = tr -> PJet_charge -> operator[](iE); 
  
  SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  SetCharge(jetCharge);

  if(eshift != 0){
    
    Double_t diffx,diffy,diffz,diffe;
    
    //  cout<<"OLD "<<Px()<<"  "<<Py()<<"  "<<Pz()<<"  "<<E()<<endl;
    //  cout<<"OLD "<<Pt()<<"  "<<Eta()<<"  "<<Phi()<<endl;
    
    diffx = eshift * Px();
    diffy = eshift * Py();
    diffz = eshift * Pz();
    diffe = eshift * E();
    SetPxPyPzE(diffx + Px(),
	       diffy + Py(),
	       diffz + Pz(),
	       diffe + E());
    
    //cout<<diffx<<"  "<<diffy<<"  "<<diffz<<"  "<<diffe<<"  "<<eshift<<endl;
    //cout<<"NEW "<<Px()<<"  "<<Py()<<"  "<<Pz()<<"  "<<E()<<endl;
    //cout<<"NEW "<<Pt()<<"  "<<Eta()<<"  "<<Phi()<<endl;
    
    // if met pointers have been provided, update those also
    //cout<<"OLDMET "<<metx<<"  "<<mety<<endl;
    
    // cout<<"NEWMET "<<*metx<<"  "<<*mety<<endl;
   
  }
  //##########################################################################
  //b-tagging.  Insert info when available, based on reco tree.
  //##########################################################################



  //##########################################################################
  //PdgId()
  //
  //identifies jet with a MC quark.  5=bquark, 4=cquark, 15=tau(mc), 0=lightquark or gluon, etc
  //
  //This section identifies the MC particle (b, c, tau, or other (light quark)
  //that the jet is closest to and labels it as that, by pdgid, where light quark
  //is 0.  Jets are labeled starting with b, then c, then tau, and then, if none
  //of these match, as light quark.  This follows proceedure in b-tagging csc note.
  //Jet must be within deltaR of 0.3 of particle to be matched, and mc particle
  //must have Pt > 5 GeV, also per the csc note.
  //
  //Currently modified to use the Jet_Truth_Label variable from tree
  //Currently no charge information carried in this label
  //
  //NOTE: This PDGId() method returns the flavor of the MC particle associated
  //with the jet (wrt position).  It is NOT nessesarily the jet's flavor, but
  //a reasonable assumption BASED ON MC AND RECO INFORMATION
  //##########################################################################

  Double_t DeltaRCurrent = 0;
  Double_t EtaCurrent  = 0;
  Double_t PhiCurrent  = 0;
  Double_t PtCurrent   = 0;
  //SetPdgId(999);//not set yet
  
  //SetPdgId(tr -> Jet_Truth_Label -> operator[](iE));//not set yet
  
  
  //////////////////////////////////////////////////
  // Overlap with Electron
  //////////////////////////////////////////////////
  // Get Minimum separation between the electron and jet from the config file
  Double_t electronDeltaRMin = config -> GetValue("ObjectID.Jet.ElectronDeltaRMin", 0.0);
  Double_t electronDeltaR = 0.0;
  std::vector<Electron>::iterator electronIterator;
  for(electronIterator = electrons.begin(); electronIterator != electrons.end(); electronIterator++){
    electronDeltaR = electronIterator->DeltaR(*this);
    // If jet is too close to any electron set overlap to 1 and break
    if(electronDeltaR < electronDeltaRMin ){
      //SetOverlapWithElectron(1);
      break;
    } //if
  } //for
  
  //
  // now check jet object ID cuts
  double maxEta=config->GetValue("ObjectID.Jet.MaxEta",100.);
  double minPt=config->GetValue("ObjectID.Jet.MinPt",0.);
  
  
  //if(jetPt<minPt) return kFALSE;
  //if(TMath::Abs(jetEta)>maxEta) return kFALSE;

  // Set to false if jet fails pT requirement, eta reqiurement, is overlapped with electron
  //if( jetPt <= minPt || TMath::Abs(jetEta) >= maxEta  || GetOverlapWithElectron() ) return kFALSE;
  //else return kTRUE;
  return kTRUE;
  
} //FillFastSim()

/******************************************************************************         
 * void Jet::CalculateUncSource(TString JECfile, TString SourceName, Bool_t SystUp)*
 *                                                                            *         
 * Calculate JEC uncertainty source                                           *
 *                                                                            *         
 * Input:  - SourceName, SystUp, txtfilenmame                                 # 
 * Output: -                                                                  *
 ******************************************************************************/
float Jet::CalculateUncSource(Double_t jesSF, bool jesup, int eventNumber ){
    /*
    if(eventNumber == 16125347 || eventNumber == 16124780 ){
        std::cout<< " eventNumber " << eventNumber << " JetEta " << Eta() << " JetPt " << Pt() << " jesSF " << jesSF << std::endl;
    } 
    */
    //std::cout << " calculate unc source "<< _jecsourceName << " set pt eta " << std::endl;
    float jecvar = 1.;
    if(jesSF == 1 )return jecvar;
    jecAK4PFchsMCUncSource_->setJetEta( Eta() );
    jecAK4PFchsMCUncSource_->setJetPt( Pt() );
    float corrUpAK4PFchs_up = jesSF * (1 + fabs(jecAK4PFchsMCUncSource_->getUncertainty(1)));
    jecAK4PFchsMCUncSource_->setJetEta( Eta() );
    jecAK4PFchsMCUncSource_->setJetPt( Pt() );
    float corrUpAK4PFchs_down = jesSF * (1 - fabs(jecAK4PFchsMCUncSource_->getUncertainty(-1)));
    //std::cout << "_jecsource "<< _jecsourceName <<" jet Pt  " << Pt() << " jet eta "  << Eta() << " jesSF " << jesSF << " jesFlavorQCDup " << corrUpAK4PFchs_up << " jesFlavorQCDdown " << corrUpAK4PFchs_down << std::endl;
    if(jesup)jecvar = corrUpAK4PFchs_up;
    else jecvar = corrUpAK4PFchs_down;
    return jecvar;
};

void Jet::SetJECUncSource(TEnv * config, TString jecsourceName, TString jersourceName){
   _sourcefilename = config->GetValue("Systs.JecSourceFile","config/weights/ttH2018/Regrouped_Autumn18_V19_MC_UncertaintySources_AK4PFchs.txt");
  resolution = JME::JetResolution(config->GetValue("Systs.JerResFile","config/weights/ttH2018/Autumn18_V7_MC_PtResolution_AK4PFchs.txt"));
  res_sf = JME::JetResolutionScaleFactor(config->GetValue("Systs.JerSFFile","config/weights/ttH2018/Autumn18_V7_MC_SF_AK4PFchs.txt"));
   _jecsourceName = jecsourceName;
   _jersourceName = jersourceName;

   std::cout<< " set jecsource " << jecsourceName << " _jecsource " << _jecsourceName << std::endl;
   std::cout<< " set jersource " << jersourceName << " _jersource " << _jersourceName << std::endl;
   std::cout<< " set jerresfile " << config->GetValue("Systs.JerResFile","config/weights/ttH2018/Autumn18_V7_MC_PtResolution_AK4PFchs.txt") << " _jerSFFile " << config->GetValue("Systs.JerSFFile","config/weights/ttH2018/Autumn18_V7_MC_SF_AK4PFchs.txt") << std::endl;
   //_sourcename = config->GetValue("FlavorQCD");
   if(_jecsourceName != "NONE"){
    jecAK4PFchsMCUncSource_   =  new JetCorrectionUncertainty(*(new JetCorrectorParameters(_sourcefilename.Data(), _jecsourceName.Data())));
   }
};

/******************************************************************************         
 * void Jet::CalculateUncSource(TString JECfile, TString SourceName, Bool_t SystUp)*
 *                                                                            *         
 * Calculate JEC uncertainty source                                           *
 *                                                                            *         
 * Input:  - SourceName, SystUp, txtfilenmame                                 # 
 * Output: -                                                                  *
 ******************************************************************************/
void Jet::Getjer(float rhoJER, bool isgenmatch, TLorentzVector genjet, float &JERScaleFactor, float &JERScaleFactorUP, float &JERScaleFactorDOWN, int nEvent){
  double cFactorJER = 1.0; 
  double cFactorJERdown = 1.0;
  double cFactorJERup = 1.0;
  //https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#JER_Scaling_factors_and_Unce_AN1
  
  double recoJetPt = Pt();
  //std::cout<< " recoJetPt " << recoJetPt << std::endl;
  JME::JetParameters parameters;
  parameters.setJetPt(Pt());
  parameters.setJetEta(Eta());
  parameters.setRho(rhoJER);
  float relpterr = resolution.getResolution(parameters);
  cFactorJER = res_sf.getScaleFactor(parameters);
  cFactorJERup = res_sf.getScaleFactor(parameters, Variation::UP);
  cFactorJERdown = res_sf.getScaleFactor(parameters, Variation::DOWN);
  if(isgenmatch){
    // scale method
    double genJetPt = genjet.Pt();
    double diffPt    = recoJetPt - genJetPt;
    // cone size 
    double conesize = 0.4;
    if(genJetPt>0. && genjet.DeltaR(*this)<conesize/2
     && (abs(recoJetPt-genjet.Pt())<3*relpterr*recoJetPt)) {
        JERScaleFactor     = (std::max(0., genJetPt + cFactorJER*diffPt))/recoJetPt;
        JERScaleFactorUP   = (std::max(0., genJetPt + cFactorJERup*diffPt))/recoJetPt;
        JERScaleFactorDOWN = (std::max(0., genJetPt + cFactorJERdown*diffPt))/recoJetPt;
    } else {
        JERScaleFactor     = 1.;
        JERScaleFactorUP   = 1.;
        JERScaleFactorDOWN = 1.;
    }
  }else{
    // stochastic method
    // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h#L239-L247
    if(cFactorJER>1){
        double sigma = relpterr * std::sqrt(cFactorJER*cFactorJER-1);
        //sigma = 1.0; // set to 1 for debugging
        //std::normal_distribution<> d(0, sigma);
        JERScaleFactor = (std::max(0., 1. + jet_jer_myran.Gaus(0,sigma)));
        //std::cout<<" Event " << nEvent << " Get jer stochastic method : setting sigma to "<< sigma << " jet pt "<< Pt() << " jet eta " << Eta() << " jerSF " << JERScaleFactor  <<std::endl;
    }else{
        JERScaleFactor = 1.;
    }
    if(cFactorJERup>1){
        double sigma = relpterr * std::sqrt(cFactorJERup*cFactorJERup-1);
        //std::normal_distribution<> d(0, sigma);
        JERScaleFactorUP = (std::max(0., 1. + jet_jer_myran.Gaus(0,sigma)));
    }else{
        JERScaleFactorUP = 1.;
    }
    if(cFactorJERdown>1){
        double sigma = relpterr * std::sqrt(cFactorJERdown*cFactorJERdown-1);
        //std::normal_distribution<> d(0, sigma);
        JERScaleFactorDOWN = (std::max(0., 1. + jet_jer_myran.Gaus(0,sigma)));
    }else{
        JERScaleFactorDOWN = 1.;
    }
  }
};

/******************************************************************************         
 * void Jet::SystematicPtShift(EventTree * evtr)                         *
 *                                                                            *         
 * Apply systematic shifts in jet pt                                          *
 *                                                                            *         
 * Input:  - the event tree (to access systematic SFs and MET info)      *
 * Output: -                                                                  *
 ******************************************************************************/
void Jet::SystematicPtShift(EventTree * evtr, Int_t iE, TLorentzVector * met, Bool_t useLepAware){

  
  float ptSF = 1.0;
  float jecvar = 1.0;
  float jesSF = evtr->Jet_JesSF -> operator[](iE);
  int evtNumber = evtr -> EVENT_event; 
  /*
  if( evtNumber== 16125347 || evtNumber == 16124780){
    std::cout << " syst useLepAware " << useLepAware << std::endl;
  }
  */
  if (_jesUp){
    if(_jecsourceName != "NONE"){
        jecvar = CalculateUncSource(jesSF, true, evtNumber);
        ptSF = jecvar/jesSF;
    }else{
        ptSF = evtr->Jet_JesSFup->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
    }
  }
  if (_jesDown){
    if(_jecsourceName != "NONE"){
        jecvar = CalculateUncSource(jesSF, false, evtNumber);
        ptSF = jecvar/jesSF;
    }else{
        ptSF = evtr->Jet_JesSFdown->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
    }
  }
  if (_jerUp && !useLepAware){
    //ptSF = evtr->Jet_JerSFup->operator[](iE)/evtr->Jet_JerSF->operator[](iE);
    if(_jersourceName =="NONE"){
        ptSF = JerSFup()/JerSF();
    }else if(_jersourceName =="HEM"){
        //https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/2000.html
        //20 % for jets with -1.57 <phi< -0.87 and -2.5<eta<-1.3
        //35 % for jets with -1.57 <phi< -0.87 and -3.0<eta<-2.5
        if (Phi() < -0.87 && Phi() > -1.57 && Eta() < -1.3 && Eta()>-2.5)ptSF=1.2;
        else if(Phi() < -0.87 && Phi() > -1.57 && Eta() < -2.5 && Eta()>-3.0)ptSF=1.35;
        else ptSF= 1.0;
    }
    //https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#Run2_JER_uncertainty_correlation
    //- in region |eta| < 1.93 use one pT bin: (0,Inf)
    //- in region 1.93 < |eta| < 2.5 use one pT bin: (0,Inf)
    //- in region 2.5 < |eta| < 3 use two pT bins: (0,50) and (50,Inf)
    //- in region 3 < |eta| < 5 use two pT bins: (0,50) and (50,Inf)
    else if(_jersourceName == "eta1p9" && abs(Eta())<1.93){
        ptSF = JerSFup()/JerSF();
    }
    else if(_jersourceName == "eta2p5" && 1.93 < abs(Eta()) && abs(Eta()) < 2.5){
        ptSF = JerSFup()/JerSF();
    }
    else if(_jersourceName == "eta3lowpt" && 2.5 < abs(Eta()) && abs(Eta()) < 3.0 && Pt() < 50){
        ptSF = JerSFup()/JerSF();
    }
    else if(_jersourceName == "eta3highpt"&& 2.5 < abs(Eta()) && abs(Eta()) < 3.0 && Pt() > 50   ){
        ptSF = JerSFup()/JerSF();
    }
    else if(_jersourceName == "eta5lowpt" && 3.0 < abs(Eta()) && abs(Eta()) < 5.0 && Pt() < 50 ){
        ptSF = JerSFup()/JerSF();
    }
    else if(_jersourceName == "eta5highpt" && 3.0 < abs(Eta()) && abs(Eta()) < 5.0 && Pt() > 50  ){
        ptSF = JerSFup()/JerSF();
    }else{
        ptSF=1.0;
    }
  }
  if (_jerDown && !useLepAware){
    //ptSF = evtr->Jet_JerSFdown->operator[](iE)/evtr->Jet_JerSF->operator[](iE);
    if(_jersourceName =="NONE"){
        ptSF = JerSFdown()/JerSF();
    }else if(_jersourceName =="HEM"){
        if (Phi() < -0.87 && Phi() > -1.57 && Eta() < -1.3 && Eta()>-2.5)ptSF=0.8;
        else if(Phi() < -0.87 && Phi() > -1.57 && Eta() < -2.5 && Eta()>-3.0)ptSF=0.65;
        else ptSF= 1.0;
    }
    else if(_jersourceName == "eta1p9" && abs(Eta())<1.93){
        ptSF = JerSFdown()/JerSF();
    }
    else if(_jersourceName == "eta2p5" && 1.93 < abs(Eta()) && abs(Eta()) < 2.5){
        ptSF = JerSFdown()/JerSF();
    }
    else if(_jersourceName == "eta3lowpt" && 2.5 < abs(Eta()) && abs(Eta()) < 3.0 && Pt() < 50){
        ptSF = JerSFdown()/JerSF();
    }
    else if(_jersourceName == "eta3highpt"&& 2.5 < abs(Eta()) && abs(Eta()) < 3.0 && Pt() > 50   ){
        ptSF = JerSFdown()/JerSF();
    }
    else if(_jersourceName == "eta5lowpt" && 3.0 < abs(Eta()) && abs(Eta()) < 5.0 && Pt() < 50 ){
        ptSF = JerSFdown()/JerSF();
    }
    else if(_jersourceName == "eta5highpt" && 3.0 < abs(Eta()) && abs(Eta()) < 5.0 && Pt() > 50  ){
        ptSF = JerSFdown()/JerSF();
    }else{
        ptSF=1.0;
    }
  }
  //  float ptBefore = Pt();
  if(!useLepAware){
  //Remove jet from MET
    met->SetPx(met->Px() + Px());
    met->SetPy(met->Py() + Py());
  //Apply the correction
  //  std::cout << Px() << " " << Py() << " " << Pt() << std::endl;
    SetPx(Px()*ptSF);
    SetPy(Py()*ptSF);
    SetPz(Pz()*ptSF);
    SetE(E()*ptSF);
  //std::cout << Px() << " " << Py() << " " << Pt() << std::endl << std::endl;
  
  //Propagate to MET
    met->SetPx(met->Px() - Px());
    met->SetPy(met->Py() - Py());
  }
  //  float ptAfter = Pt();
  //  if (ptBefore < 30 && ptAfter > 30) {
  //  std::cout << "Now selected: Jet #" << iE << "Jet Pt: " << ptBefore << " JER SF: " << evtr->Jet_JerSF->operator[](iE) << " up: " << evtr->Jet_JerSFup->operator[](iE) << " down: " << evtr->Jet_JerSFdown->operator[](iE) << " JES SF: " << evtr->Jet_JesSF->operator[](iE) << " up: " << evtr->Jet_JesSFup->operator[](iE) << " down: " << evtr->Jet_JesSFdown->operator[](iE);
  //  std::cout << " Pt SF: " << ptSF << " Jet pt after: " << Pt() << std::endl;
  //}
  //if (ptBefore > 30 && ptAfter < 30) {
  //  std::cout << "No longer selected: Jet #" << iE << "Jet Pt: " << ptBefore << " JER SF: " << evtr->Jet_JerSF->operator[](iE) << " up: " << evtr->Jet_JerSFup->operator[](iE) << " down: " << evtr->Jet_JerSFdown->operator[](iE) << " JES SF: " << evtr->Jet_JesSF->operator[](iE) << " up: " << evtr->Jet_JesSFup->operator[](iE) << " down: " << evtr->Jet_JesSFdown->operator[](iE);
  //  std::cout << " Pt SF: " << ptSF << " Jet pt after: " << Pt() << std::endl;
  //}



}
