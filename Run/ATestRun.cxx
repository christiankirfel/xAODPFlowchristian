void ATestRun (const std::string& submitDir)
{
  //===========================================
  // FOR ROOT6 WE DO NOT PUT THIS LINE 
  // (ROOT6 uses Cling instead of CINT)
  // Load the libraries for all packages
  // gROOT->Macro("$ROOTCOREDIR/scripts/load_packages.C");
  // Instead on command line do:
  // > root -l '$ROOTCOREDIR/scripts/load_packages.C' 'ATestRun.cxx ("submitDir")'
  // The above works for ROOT6 and ROOT5
  //==========================================


  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // create a new sample handler to describe the data files we use
  // scan for datasets in the given directory
  // this works if you are on lxplus, otherwise you'd want to copy over files
  // to your local machine and use a local path.  if you do so, make sure
  // that you copy all subdirectories and point this to the directory
  // containing all the files, not the subdirectories.


   // Construct the samples to run on:
  // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
  SH::SampleHandler sh;

  //SH::DiskListLocal list("./../../../../../workspace/MC/AOD/JZ3/user.moles.147913.Pythia8_AU2CT10_jetjet_JZ3W.recon.AOD.e3099_s2832_r7617_AOD.67276209/");
  //SH::scanFiles(sh, list);

  //export DataFiles=/afs/cern.ch/user/m/moles/workspace/MC/AOD/  
  const char* inputFilePath = gSystem->ExpandPathName ("$DataFiles/SinglePions/mc15c_piplus/user.moles.mc15_13TeV.428001.ParticleGun_single_piplus_logE0p2to2000.recon.AOD.e3501_s2832_r8014_AOD/");
  SH::ScanDir().filePattern("user.moles.8671065.AOD._000411.pool.root").scan(sh,inputFilePath); //One indiviudual file
  //SH::ScanDir().scan(sh,inputFilePath); //All files in the directory

  
  // set the name of the tree in our files
  // in the xAOD the TTree containing the EDM containers is "CollectionTree"
  sh.setMetaString ("nc_tree", "CollectionTree");

  // further sample handler configuration may go here

  // print out the samples we found
  sh.print ();

  // this is the basic description of our job
  EL::Job job;
  job.sampleHandler (sh); // use SampleHandler in this job
  job.options()->setDouble (EL::Job::optMaxEvents, 2); // for testing purposes, limit to run over the first 500 events only!

  // add our algorithm to the job
  xAODPFlowAna *alg = new xAODPFlowAna;

  // later on we'll add some configuration options for our algorithm that go here

  job.algsAdd (alg);

  // make the driver we want to use:
  // this one works by running the algorithm directly:
  EL::DirectDriver driver;
  // we can use other drivers to run things on the Grid, with PROOF, etc.

  // process the job using the driver
  driver.submit (job, submitDir);
}
