#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "PrimaryGenerator.hh"
#include "G4Event.hh"
#include "HistoManager.hh"
#include "PrimaryGeneratorActionMessenger.hh"

#include "BeamParams.hh"

#include "G4ParticleGun.hh"


struct IsotopeParams
{
    G4String shape;
};


/**
 * \class PrimaryGeneratorAction
 * \brief heart of simulated physics
 */
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        PrimaryGeneratorAction(HistoManager* histo);
        ~PrimaryGeneratorAction();
        virtual void GeneratePrimaries(G4Event*);

     //   virtual void GeneratePrimaries1(G4Event*); //sks

        void SetSourceTypeInfo(G4String);
        BeamParams* GetBeamParams(){return fBeam;};

        G4String GetSourceTypeInfo(){return fGenerateSourceType;};

        const G4ParticleGun* GetParticleGun() const {return fParticleGun;} //sks

    private:

        G4String fGenerateSourceType;///< "run", "beam", "isotope"
        G4String fAllowedSourceTypes[3] = {"run", "beam", "isotope"};


        PrimaryGeneratorActionMessenger* fMessenger;

        PrimaryGenerator* fPrimaryGenerator;
        HistoManager* fHisto;

        BeamParams* fBeam;

        G4ParticleGun* fParticleGun;  //sks

};
#endif
