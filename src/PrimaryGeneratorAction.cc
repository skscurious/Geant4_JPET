#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4PrimaryVertex.hh"

//sks
#include "G4ParticleGun.hh"
#include "Randomize.hh"



PrimaryGeneratorAction::PrimaryGeneratorAction(HistoManager* histo)
    :G4VUserPrimaryGeneratorAction(),
    fPrimaryGenerator(0), fHisto(histo)
{
    fPrimaryGenerator = new PrimaryGenerator();
    fBeam = new BeamParams();
    fMessenger = new PrimaryGeneratorActionMessenger(this);
    fParticleGun = new G4ParticleGun();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fBeam;
    delete fPrimaryGenerator;
    delete fMessenger;
    delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{


    // if setup for dedicated run is set then ignore its modifications made by user
    if( DetectorConstruction::GetInstance()->GetRunNumber() != 0){
        if( GetSourceTypeInfo() != "run"){
          G4Exception("PrimaryGeneratorAction","PG03",JustWarning,
                 "User can not modify the predefined run geometry");
        }
        SetSourceTypeInfo("run");
    }
/*
    if( GetSourceTypeInfo() == ("run")) {
    } else if (GetSourceTypeInfo() == ("beam")) {
        fPrimaryGenerator->GenerateBeam(fBeam,event);
    } else if (GetSourceTypeInfo() == ("isotope")) {
    } else {
          G4Exception("PrimaryGeneratorAction","PG04",FatalException,
                 "Required source type is not allowed");

    }
    */

    if( GetSourceTypeInfo() == ("run")) {
    } else if (GetSourceTypeInfo() == ("beam")) {





        fPrimaryGenerator->GenerateBeam(fBeam,event);
    } else if (GetSourceTypeInfo() == ("isotope")) {
    } else {
          G4Exception("PrimaryGeneratorAction","PG04",FatalException,
                 "Required source type is not allowed");


    }

   // fPrimaryGenerator->GeneratePrimaryVertex(event);


}

//++++++++++++++++++++++++++ SKS
/*
void PrimaryGeneratorAction::GeneratePrimaries1(G4Event* event)
{



    G4double cosAlpha = 1. - 2. * G4UniformRand();
       G4double sinAlpha = std::sqrt(1. - cosAlpha *cosAlpha);
       G4double psi = twopi*G4UniformRand();
       G4ThreeVector dir(sinAlpha*std::cos(psi),sinAlpha*std::sin(psi),cosAlpha);

       fParticleGun->SetParticleMomentumDirection(dir);

       G4double energy;

     //  fParticleGun->SetParticleEnergy(energy);

       fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
       fParticleGun->SetParticleEnergy(511.*keV);

       // Intentiate first event

       fParticleGun->GeneratePrimaryVertex(event);


}*/





//--------------------------

void PrimaryGeneratorAction::SetSourceTypeInfo(G4String newSourceType)
{
    if (std::find(std::begin(fAllowedSourceTypes), std::end(fAllowedSourceTypes), newSourceType) != std::end(fAllowedSourceTypes))
    {
        // setup found
        if( DetectorConstruction::GetInstance()->GetRunNumber() == 0){
            fGenerateSourceType = newSourceType;
        } else {
            G4Exception("PrimaryGeneratorAction","PG01",JustWarning,
                    "Chosen detector geometry corresponds to run number and it can not be changed");
        }
    } else {
        G4Exception("PrimaryGeneratorAction","PG02",JustWarning,
                "Please pick from avaliable setups: beam/isotope");
    }

}



