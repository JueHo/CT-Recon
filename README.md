# CT-Recon

CT-Recon is a collection of tools for CT reconstruction.
These tools have been developed and extended during the last 11 years.
Backprojection is running on GPU, implemented with NVIDIA CUDA toolkit.
There is no restiction in data size for CT reconstruction. 
Neither for the input data nor the reconstructed voxel volume.
For grating and propagation based phase contrast X-ray imaging 
additional Matlab scripts are provided.

For build instructions see: ***build_info.md***


**Currently the following modules are available:**
| Module | Directory | Description | CLI | GUI | License |
|--------|-----------|-------------|-----|-----|---------|
| Pre-Processor | PreProcessing | Tools for: Re-scaling, ring artifact mitigation, beamhardening correction, and contrast enhancement |  | [x] | LGPL-v3 |
| CoR | CoR & CoR_GUI| Center of rotation and axis tilt determination |[x] |[x]| GPL-v3 |
| Weight/Filtering | WeightAndFilter & BackprojectionFDK_GUI | Weighting and filtering for FDK based reconstruction. Support of RAM and Shepp-Logan filter for absorption X-ray CT. Hilbert filter for differential phase contrast X-ray CT |[x]|[x]|LGPL-v3|
| Backprojection (FDK) | BackprojectionFDK & BackprojectionFDK_GUI | Backprojection using FDK on GPU |[x] |[x]| GPL-v3 |
| Histogram and converting tool | ConversionByHistogramMapping | Histogram evaluation of raw data stacks. Supports data range selection and conversion from 32 Bit to 8 or 16 Bit raw data | | [x] | LGPL-v3 |
| Phase retrieval | PhaseRetrieval_PhaseStepping | Phase retrieval tool for grating based phase contrast X-ray CT |[x] | | GPL-v3 |
| Phase contrast X-ray CT | Matlab_PhaseContrast_X-rayCT | Matlab scripts for grating and propagation based X-ray imaging | [x]| |GPL-v3 |
