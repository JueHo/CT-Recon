## News:
* <strong>2025-05-14:<strong> Add prototype of a new Ring Artefact Tool<br>
  At the moment designed as standalone application and proof of concept.
  Will be in future version of the Preprocessing integrated.<br>
  Usage in CT-Recon context:
   - Apply after PreProcessing (without any Ring Artefact Correction).
   - Can be applied as well standalone on raw datasets without using the CT-Recon tool chain for reconstruction.<br>
   - Just correcting Ring Artefact generating features from the projections.
      
  Remarks for this prototype:
   - Complete projection stack must fit into CPU-RAM.
   - GUI may freeze while processsing data.

  This issues will be fixed in future version.
  Adapt the compile options in the VS Studio projectfile according your development environment.
* <strong>2024-07-01:</strong> Added projection expansion for local tomography. <br>
  Added new feature in Pre-Processor. <br>
  Extending projections data by sigmoid function values <br>
  to reduce local tomography artifacts (bright halo ring).<br>
  Length of extension and starting value by specifying averaging range <br>
  of start pixels respectively end pixels of projection line data can be selected.<br>
* <strong>2024-03-08:</strong> Added Solution and Project files for Visual Studio 2022. <br>
  Extract files from VisualStudio2022Files.zip to top folder <br>
  and override Visual Studio 2017 files.<br>
  Visual Studio 2022 is tested with Cuda toolkit <strong>11.6</strong>.<br>
  nvcc compiler option are set for Compute Capability ≥ <strong>3.5</strong>.

