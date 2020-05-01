# USMPL

## Runtime ROS animatable SMPL body model for Unreal Engine

## Requirements
- Julia (https://julialang.org/)
- ROSIntegration UE4 plugin (https://github.com/code-iai/ROSIntegration)
- CSMPL (https://github.com/nitin-ppnp/SMPL.jl/tree/CSMPL)

## Setup
Follow these steps to use USMPL plugin in your unreal project

1. **Get ROSIntegration plugin**: USMPL is depends on ROSIntegration for ROS support. Clone the ROSIntegration repository and put it in `%ProjectDirectory%\Plugins` directory. If the `Pluigns` directory doesn't exist, create it.

2. **Get Julia and CSMPL and build CSMPL shared library**: Clone the SMPL.jl repository and switch to branch CSMPL. Julia and CSMPL are not required to be present in the Unreal project directory. These can be anywhere.
```
git clone -b CSMPL https://github.com/nitin-ppnp/SMPL.jl.git
``` 
Follow the instructions to build CSMPL as a shared library. The instructions are available at https://github.com/nitin-ppnp/SMPL.jl/tree/CSMPL. This will generate **smplbuild** directory with multiple dll files in it.

3. **Get USMPL plugin**: Clone the USMPL plugin in `%ProjectDirectory%\Plugins` directory.
```
git clone https://github.com/nitin-ppnp/USMPL.git
```
3. **Set SMPL related environment variables**: Set the following 3 environment variables permanently (not just in a shell) to your system. The values which needs to be set are explained in the CSMPL repository instructions. 

    - SMPLPATH (path to the SMPL .npz file)
    - JULIA_DIR (julia directory path)
    - CSMPL_LIB_PATH (path to the built csmpl.dll file)

4. **Make the header file available in the VS project**: Open the visual studio project and add these to your project vc++ include directories.

    - `$(JULIA_DIR)\include\julia`
    - `$(JULIA_DIR)\include\julia\uv`

5. **Make the DLLs available at runtime**: One way to make this happen is to add the **smplbuild** in the windows **PATH**. A preferred way would be to copy the contents of **smplbuild** to the unreal project build directory. Its path looks like this `%ProjectDirectory%\Binaries\Win64`. If this directory doesn't exist, build your project. It won't compile but create this directory.

6. **Build the unreal project**: The project along with the plugins should build fine at this point. If it fails, check all the above steps. If ROSIntegration fail to build, check its page for issues. It might happen for UE 4.24. Check this issue for solution https://github.com/code-iai/ROSIntegration/issues/114

## Usage
7. **Configure game for ROS**: Follow the "Setting up the plugin" instructions of ROSIntegration plugin. Basically, the `GameInstance` should be changed to `ROSIntegrationGameInstance`.
8. **Spawn the SMPL**: Drag the SMPLActor class in the viewport to create a SMPL Instance.

![](Resources/SMPLClass.png)

9. **Set topic name**: Set the ROS topic name which would cotain the pose message. If you select the SMPLActor instance in the viewport, the PoseTopicName field would appear on the right side (marked in red).

![](Resources/PoseTopicName.png)