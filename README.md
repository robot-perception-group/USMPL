# USMPL

## Runtime ROS animatable SMPL body model for Unreal Engine

## Requirements
- Julia (https://julialang.org/)
- ROSIntegration UE4 plugin (https://github.com/code-iai/ROSIntegration)
- CSMPL (https://github.com/nitin-ppnp/SMPL.jl/tree/CSMPL)

## Setup
Follow these steps to use USMPL plugin in your unreal project

1. **Get ROSIntegration plugin**: USMPL is depends on ROSIntegration for ROS support. Clone the ROSIntegration repository and put it in your `%ProjectDirectory%\Plugins` directory. If the `Pluigns` directory doesn't exist, create it.

2. **Get Julia and CSMPL and build CSMPL shared library**: Clone the SMPL.jl repository and switch to branch CSMPL. Julia and CSMPL are not required to be present in the Unreal project directory. These can be anywhere.
```
git clone -b CSMPL https://github.com/nitin-ppnp/SMPL.jl.git
``` 
Follow the instructions to build CSMPL as a shared library. The instructions are available at https://github.com/nitin-ppnp/SMPL.jl/tree/CSMPL.

3. **Set SMPL related environment variables**: Set the following 3 environment variables permanently to your system. The values which needs to be set are explained in the CSMPL repository instructions. 

    - SMPLPATH
    - JULIA_DIR
    - CSMPL_LIB_PATH

4. 