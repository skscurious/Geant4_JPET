#include "DetectorSD.hh"
#include "G4VProcess.hh"

DetectorSD::DetectorSD(G4String name)
    :G4VSensitiveDetector(name)
{
     G4String HCname;
     collectionName.insert(HCname="detectorCollection");
}

DetectorSD::~DetectorSD()
{}

void DetectorSD::Initialize(G4HCofThisEvent* HCE)
{
    static int HCID = -1;
    fDetectorCollection = new DetectorHitsCollection(SensitiveDetectorName,collectionName[0]);

    if(HCID<0)
    { HCID = GetCollectionID(0); }
    HCE->AddHitsCollection(HCID,fDetectorCollection);

    for (G4int i=0; i<totScinNum; i++)
    {
        previousHitHistory[i] = -1;
        previousHitTimeHistory[i] = 0;
    }
}


G4bool DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep==0.0) return false;

    G4TouchableHistory* theTouchable  = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable()); 
    G4VPhysicalVolume* physVol = theTouchable->GetVolume();
    G4int   currentScinCopy = physVol->GetCopyNo();
    G4double currentTime = aStep->GetPreStepPoint()->GetGlobalTime();


    if( (previousHitHistory[currentScinCopy] !=-1 )
          &&( abs(previousHitTimeHistory[currentScinCopy]-currentTime)<timeIntervals) ) 
    {
        // update track
        (*fDetectorCollection)[previousHitHistory[currentScinCopy]]->AddEdep(edep);
        (*fDetectorCollection)[previousHitHistory[currentScinCopy]]->AddInteraction();

    } else {
        // new hit
        DetectorHit* newHit = new DetectorHit();
        newHit->SetEdep( edep );
        newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
        newHit->SetTrackPDG(aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
        newHit->SetProcessName(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
        newHit->SetInteractionNumber();
        newHit->SetPosition(aStep->GetPostStepPoint()->GetPosition());
        newHit->SetTime(currentTime);

        newHit->SetScinID(physVol->GetCopyNo());

        newHit->SetPolarizationIn(aStep->GetPreStepPoint()->GetPolarization());
        newHit->SetPolarizationOut(aStep->GetPostStepPoint()->GetPolarization());
        newHit->SetMomentumIn(aStep->GetPreStepPoint()->GetMomentum());
        newHit->SetMomentumOut(aStep->GetPostStepPoint()->GetMomentum());

        G4int id = fDetectorCollection->insert(newHit);
        previousHitHistory[currentScinCopy] = id-1;
        previousHitTimeHistory[currentScinCopy]= currentTime;
    }


    return true;
}


