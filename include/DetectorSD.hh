#ifndef DetectorSD_h
#define DetectorSD_h 1

#include "G4VSensitiveDetector.hh"
#include "DetectorHit.hh"

class DetectorSD : public G4VSensitiveDetector
{
    public:
        DetectorSD(G4String name);
        virtual ~DetectorSD();

        virtual void Initialize(G4HCofThisEvent* HCE);

    private:
        const G4double timeIntervals = 0.08; // 80 ps
      //  const G4int totScinNum = 193; 
      //  G4int previousHitHistory[193];
      //  G4double previousHitTimeHistory[193];
	
	
	// changed for fourth layer sks+++++++++
	
	const G4int totScinNum = 505; 
        G4int previousHitHistory[505];
        G4double previousHitTimeHistory[505];
	
	//---------------------------------
	//
        DetectorHitsCollection *fDetectorCollection;
        //G4int lastHitID;
        //G4double previousTime;



    protected:
         virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);


};


#endif
