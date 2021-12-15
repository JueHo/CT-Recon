# CT-Recon

CT-Recon is a collection of tools for CT reconstruction.
These tools have been developed and extended during the last 11 years.
Backprojection is running on GPU, implemented with NVIDIA CUDA toolkit.
There is no restiction in data size for CT reconstruction. 
Neither for the input data nor the reconstructed voxel volume.
For grating and propagation based phase contrast X-ray imaging 
additional Matlab scripts are provided.

For build instructions see file: *build_info.txt*


**Currently the following modules are available:**
| Module | Description | CLI | GUI | License |
|--------|-------------|-----|-----|---------|
| Pre-Processor | Tools for: Re-scaling, ring artifact mitigation, beamhardening correction, and contrast enhancement |  | [x] | LGPL-v3 |
| CoR | Center of rotation and axis tilt determination |[x] |[x]| GPL-v3 |
| Weight/Filtering | Weighting and filtering for FDK based reconstruction. Support of RAM and Shepp-Logan filter for absorption X-ray CT. Hilbert filter for differential phase contrast X-ray CT |[x]|[x]|LGPL-v3|
| Backprojection (FDK)| Backprojection using FDK on GPU |[x] |[x]| GPL-v3 |
| Histogram and converting tool | Histogram evaluation of raw data stacks. Supports data range selection and conversion from 32 Bit to 8 or 16 Bit raw data | | [x] | LGPL-v3 |
| Phase retrieval | Phase retrieval tool for grating based phase contrast X-ray CT |[x] |[x]| GPL-v3 |
| Phase contrast X-ray CT | Matlab scripts for grating and propagation based X-ray imaging | [x]| |GPL-v3 |
